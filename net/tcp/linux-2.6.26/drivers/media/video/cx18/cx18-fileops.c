/*
 *  cx18 file operation functions
 *
 *  Derived from ivtv-fileops.c
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA
 */

#include "cx18-driver.h"
#include "cx18-fileops.h"
#include "cx18-i2c.h"
#include "cx18-queue.h"
#include "cx18-vbi.h"
#include "cx18-audio.h"
#include "cx18-mailbox.h"
#include "cx18-scb.h"
#include "cx18-streams.h"
#include "cx18-controls.h"
#include "cx18-ioctl.h"
#include "cx18-cards.h"

/* This function tries to claim the stream for a specific file descriptor.
   If no one else is using this stream then the stream is claimed and
   associated VBI streams are also automatically claimed.
   Possible error returns: -EBUSY if someone else has claimed
   the stream or 0 on success. */
static int cx18_claim_stream(struct cx18_open_id *id, int type)
{
    struct cx18 *cx = id->cx;
    struct cx18_stream *s = &cx->streams[type];
    struct cx18_stream *s_vbi;
    int vbi_type;

    if (test_and_set_bit(CX18_F_S_CLAIMED, &s->s_flags)) {
        /* someone already claimed this stream */
        if (s->id == id->open_id) {
            /* yes, this file descriptor did. So that's OK. */
            return 0;
        }
        if (s->id == -1 && type == CX18_ENC_STREAM_TYPE_VBI) {
            /* VBI is handled already internally, now also assign
               the file descriptor to this stream for external
               reading of the stream. */
            s->id = id->open_id;
            CX18_DEBUG_INFO("Start Read VBI\n");
            return 0;
        }
        /* someone else is using this stream already */
        CX18_DEBUG_INFO("Stream %d is busy\n", type);
        return -EBUSY;
    }
    s->id = id->open_id;

    /* CX18_DEC_STREAM_TYPE_MPG needs to claim CX18_DEC_STREAM_TYPE_VBI,
       CX18_ENC_STREAM_TYPE_MPG needs to claim CX18_ENC_STREAM_TYPE_VBI
       (provided VBI insertion is on and sliced VBI is selected), for all
       other streams we're done */
    if (type == CX18_ENC_STREAM_TYPE_MPG &&
           cx->vbi.insert_mpeg && cx->vbi.sliced_in->service_set) {
        vbi_type = CX18_ENC_STREAM_TYPE_VBI;
    } else {
        return 0;
    }
    s_vbi = &cx->streams[vbi_type];

    set_bit(CX18_F_S_CLAIMED, &s_vbi->s_flags);

    /* mark that it is used internally */
    set_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags);
    return 0;
}

/* This function releases a previously claimed stream. It will take into
   account associated VBI streams. */
static void cx18_release_stream(struct cx18_stream *s)
{
    struct cx18 *cx = s->cx;
    struct cx18_stream *s_vbi;

    s->id = -1;
    if (s->type == CX18_ENC_STREAM_TYPE_VBI &&
        test_bit(CX18_F_S_INTERNAL_USE, &s->s_flags)) {
        /* this stream is still in use internally */
        return;
    }
    if (!test_and_clear_bit(CX18_F_S_CLAIMED, &s->s_flags)) {
        CX18_DEBUG_WARN("Release stream %s not in use!\n", s->name);
        return;
    }

    cx18_flush_queues(s);

    /* CX18_ENC_STREAM_TYPE_MPG needs to release CX18_ENC_STREAM_TYPE_VBI,
       for all other streams we're done */
    if (s->type == CX18_ENC_STREAM_TYPE_MPG)
        s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
    else
        return;

    /* clear internal use flag */
    if (!test_and_clear_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags)) {
        /* was already cleared */
        return;
    }
    if (s_vbi->id != -1) {
        /* VBI stream still claimed by a file descriptor */
        return;
    }
    clear_bit(CX18_F_S_CLAIMED, &s_vbi->s_flags);
    cx18_flush_queues(s_vbi);
}

static void cx18_dualwatch(struct cx18 *cx)
{
    struct v4l2_tuner vt;
    u16 new_bitmap;
    u16 new_stereo_mode;
    const u16 stereo_mask = 0x0300;
    const u16 dual = 0x0200;

    new_stereo_mode = cx->params.audio_properties & stereo_mask;
    memset(&vt, 0, sizeof(vt));
    cx18_call_i2c_clients(cx, VIDIOC_G_TUNER, &vt);
    if (vt.audmode == V4L2_TUNER_MODE_LANG1_LANG2 &&
            (vt.rxsubchans & V4L2_TUNER_SUB_LANG2))
        new_stereo_mode = dual;

    if (new_stereo_mode == cx->dualwatch_stereo_mode)
        return;

    new_bitmap = new_stereo_mode | (cx->params.audio_properties & ~stereo_mask);

    CX18_DEBUG_INFO("dualwatch: change stereo flag from 0x%x to 0x%x. new audio_bitmask=0x%ux\n",
               cx->dualwatch_stereo_mode, new_stereo_mode, new_bitmap);

    if (cx18_vapi(cx, CX18_CPU_SET_AUDIO_PARAMETERS, 2,
                cx18_find_handle(cx), new_bitmap) == 0) {
        cx->dualwatch_stereo_mode = new_stereo_mode;
        return;
    }
    CX18_DEBUG_INFO("dualwatch: changing stereo flag failed\n");
}


static struct cx18_buffer *cx18_get_buffer(struct cx18_stream *s, int non_block, int *err)
{
    struct cx18 *cx = s->cx;
    struct cx18_stream *s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
    struct cx18_buffer *buf;
    DEFINE_WAIT(wait);

    *err = 0;
    while (1) {
        if (s->type == CX18_ENC_STREAM_TYPE_MPG) {

            if (time_after(jiffies, cx->dualwatch_jiffies + msecs_to_jiffies(1000))) {
                cx->dualwatch_jiffies = jiffies;
                cx18_dualwatch(cx);
            }
            if (test_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
                !test_bit(CX18_F_S_APPL_IO, &s_vbi->s_flags)) {
                while ((buf = cx18_dequeue(s_vbi, &s_vbi->q_full))) {
                    /* byteswap and process VBI data */
/*                    cx18_process_vbi_data(cx, buf, s_vbi->dma_pts, s_vbi->type); */
                    cx18_enqueue(s_vbi, buf, &s_vbi->q_free);
                }
            }
            buf = &cx->vbi.sliced_mpeg_buf;
            if (buf->readpos != buf->bytesused)
                return buf;
        }

        /* do we have leftover data? */
        buf = cx18_dequeue(s, &s->q_io);
        if (buf)
            return buf;

        /* do we have new data? */
        buf = cx18_dequeue(s, &s->q_full);
        if (buf) {
            if (!test_and_clear_bit(CX18_F_B_NEED_BUF_SWAP,
                        &buf->b_flags))
                return buf;
            if (s->type == CX18_ENC_STREAM_TYPE_MPG)
                /* byteswap MPG data */
                cx18_buf_swap(buf);
            else {
                /* byteswap and process VBI data */
                cx18_process_vbi_data(cx, buf,
                        s->dma_pts, s->type);
            }
            return buf;
        }

        /* return if end of stream */
        if (!test_bit(CX18_F_S_STREAMING, &s->s_flags)) {
            CX18_DEBUG_INFO("EOS %s\n", s->name);
            return NULL;
        }

        /* return if file was opened with O_NONBLOCK */
        if (non_block) {
            *err = -EAGAIN;
            return NULL;
        }

        /* wait for more data to arrive */
        prepare_to_wait(&s->waitq, &wait, TASK_INTERRUPTIBLE);
        /* New buffers might have become available before we were added
           to the waitqueue */
        if (!s->q_full.buffers)
            schedule();
        finish_wait(&s->waitq, &wait);
        if (signal_pending(current)) {
            /* return if a signal was received */
            CX18_DEBUG_INFO("User stopped %s\n", s->name);
            *err = -EINTR;
            return NULL;
        }
    }
}

static void cx18_setup_sliced_vbi_buf(struct cx18 *cx)
{
    int idx = cx->vbi.inserted_frame % CX18_VBI_FRAMES;

    cx->vbi.sliced_mpeg_buf.buf = cx->vbi.sliced_mpeg_data[idx];
    cx->vbi.sliced_mpeg_buf.bytesused = cx->vbi.sliced_mpeg_size[idx];
    cx->vbi.sliced_mpeg_buf.readpos = 0;
}

static size_t cx18_copy_buf_to_user(struct cx18_stream *s,
        struct cx18_buffer *buf, char __user *ubuf, size_t ucount)
{
    struct cx18 *cx = s->cx;
    size_t len = buf->bytesused - buf->readpos;

    if (len > ucount)
        len = ucount;
    if (cx->vbi.insert_mpeg && s->type == CX18_ENC_STREAM_TYPE_MPG &&
        cx->vbi.sliced_in->service_set && buf != &cx->vbi.sliced_mpeg_buf) {
        const char *start = buf->buf + buf->readpos;
        const char *p = start + 1;
        const u8 *q;
        u8 ch = cx->search_pack_header ? 0xba : 0xe0;
        int stuffing, i;

        while (start + len > p) {
            q = memchr(p, 0, start + len - p);
            if (q == NULL)
                break;
            p = q + 1;
            if ((char *)q + 15 >= buf->buf + buf->bytesused ||
                q[1] != 0 || q[2] != 1 || q[3] != ch)
                continue;
            if (!cx->search_pack_header) {
                if ((q[6] & 0xc0) != 0x80)
                    continue;
                if (((q[7] & 0xc0) == 0x80 &&
                     (q[9] & 0xf0) == 0x20) ||
                    ((q[7] & 0xc0) == 0xc0 &&
                     (q[9] & 0xf0) == 0x30)) {
                    ch = 0xba;
                    cx->search_pack_header = 1;
                    p = q + 9;
                }
                continue;
            }
            stuffing = q[13] & 7;
            /* all stuffing bytes must be 0xff */
            for (i = 0; i < stuffing; i++)
                if (q[14 + i] != 0xff)
                    break;
            if (i == stuffing &&
                (q[4] & 0xc4) == 0x44 &&
                (q[12] & 3) == 3 &&
                q[14 + stuffing] == 0 &&
                q[15 + stuffing] == 0 &&
                q[16 + stuffing] == 1) {
                cx->search_pack_header = 0;
                len = (char *)q - start;
                cx18_setup_sliced_vbi_buf(cx);
                break;
            }
        }
    }
    if (copy_to_user(ubuf, (u8 *)buf->buf + buf->readpos, len)) {
        CX18_DEBUG_WARN("copy %zd bytes to user failed for %s\n",
                len, s->name);
        return -EFAULT;
    }
    buf->readpos += len;
    if (s->type == CX18_ENC_STREAM_TYPE_MPG &&
        buf != &cx->vbi.sliced_mpeg_buf)
        cx->mpg_data_received += len;
    return len;
}

static ssize_t cx18_read(struct cx18_stream *s, char __user *ubuf,
        size_t tot_count, int non_block)
{
    struct cx18 *cx = s->cx;
    size_t tot_written = 0;
    int single_frame = 0;

    if (atomic_read(&cx->ana_capturing) == 0 && s->id == -1) {
        /* shouldn't happen */
        CX18_DEBUG_WARN("Stream %s not initialized before read\n",
                s->name);
        return -EIO;
    }

    /* Each VBI buffer is one frame, the v4l2 API says that for VBI the
       frames should arrive one-by-one, so make sure we never output more
       than one VBI frame at a time */
    if (s->type == CX18_ENC_STREAM_TYPE_VBI &&
        cx->vbi.sliced_in->service_set)
        single_frame = 1;

    for (;;) {
        struct cx18_buffer *buf;
        int rc;

        buf = cx18_get_buffer(s, non_block, &rc);
        /* if there is no data available... */
        if (buf == NULL) {
            /* if we got data, then return that regardless */
            if (tot_written)
                break;
            /* EOS condition */
            if (rc == 0) {
                clear_bit(CX18_F_S_STREAMOFF, &s->s_flags);
                clear_bit(CX18_F_S_APPL_IO, &s->s_flags);
                cx18_release_stream(s);
            }
            /* set errno */
            return rc;
        }

        rc = cx18_copy_buf_to_user(s, buf, ubuf + tot_written,
                tot_count - tot_written);

        if (buf != &cx->vbi.sliced_mpeg_buf) {
            if (buf->readpos == buf->bytesused) {
                cx18_buf_sync_for_device(s, buf);
                cx18_enqueue(s, buf, &s->q_free);
                cx18_vapi(cx, CX18_CPU_DE_SET_MDL, 5,
                    s->handle,
                    (void __iomem *)&cx->scb->cpu_mdl[buf->id] -
                      cx->enc_mem,
                    1, buf->id, s->buf_size);
            } else
                cx18_enqueue(s, buf, &s->q_io);
        } else if (buf->readpos == buf->bytesused) {
            int idx = cx->vbi.inserted_frame % CX18_VBI_FRAMES;

            cx->vbi.sliced_mpeg_size[idx] = 0;
            cx->vbi.inserted_frame++;
            cx->vbi_data_inserted += buf->bytesused;
        }
        if (rc < 0)
            return rc;
        tot_written += rc;

        if (tot_written == tot_count || single_frame)
            break;
    }
    return tot_written;
}

static ssize_t cx18_read_pos(struct cx18_stream *s, char __user *ubuf,
        size_t count, loff_t *pos, int non_block)
{
    ssize_t rc = count ? cx18_read(s, ubuf, count, non_block) : 0;
    struct cx18 *cx = s->cx;

    CX18_DEBUG_HI_FILE("read %zd from %s, got %zd\n", count, s->name, rc);
    if (rc > 0)
        pos += rc;
    return rc;
}

int cx18_start_capture(struct cx18_open_id *id)
{
    struct cx18 *cx = id->cx;
    struct cx18_stream *s = &cx->streams[id->type];
    struct cx18_stream *s_vbi;

    if (s->type == CX18_ENC_STREAM_TYPE_RAD) {
        /* you cannot read from these stream types. */
        return -EPERM;
    }

    /* Try to claim this stream. */
    if (cx18_claim_stream(id, s->type))
        return -EBUSY;

    /* If capture is already in progress, then we also have to
       do nothing extra. */
    if (test_bit(CX18_F_S_STREAMOFF, &s->s_flags) ||
        test_and_set_bit(CX18_F_S_STREAMING, &s->s_flags)) {
        set_bit(CX18_F_S_APPL_IO, &s->s_flags);
        return 0;
    }

    /* Start VBI capture if required */
    s_vbi = &cx->streams[CX18_ENC_STREAM_TYPE_VBI];
    if (s->type == CX18_ENC_STREAM_TYPE_MPG &&
        test_bit(CX18_F_S_INTERNAL_USE, &s_vbi->s_flags) &&
        !test_and_set_bit(CX18_F_S_STREAMING, &s_vbi->s_flags)) {
        /* Note: the CX18_ENC_STREAM_TYPE_VBI is claimed
           automatically when the MPG stream is claimed.
           We only need to start the VBI capturing. */
        if (cx18_start_v4l2_encode_stream(s_vbi)) {
            CX18_DEBUG_WARN("VBI capture start failed\n");

            /* Failure, clean up and return an error */
            clear_bit(CX18_F_S_STREAMING, &s_vbi->s_flags);
            clear_bit(CX18_F_S_STREAMING, &s->s_flags);
            /* also releases the associated VBI stream */
            cx18_release_stream(s);
            return -EIO;
        }
        CX18_DEBUG_INFO("VBI insertion started\n");
    }

    /* Tell the card to start capturing */
    if (!cx18_start_v4l2_encode_stream(s)) {
        /* We're done */
        set_bit(CX18_F_S_APPL_IO, &s->s_flags);
        /* Resume a possibly paused encoder */
        if (test_and_clear_bit(CX18_F_I_ENC_PAUSED, &cx->i_flags))
            cx18_vapi(cx, CX18_CPU_CAPTURE_PAUSE, 1, s->handle);
        return 0;
    }

    /* failure, clean up */
    CX18_DEBUG_WARN("Failed to start capturing for stream %s\n", s->name);

    /* Note: the CX18_ENC_STREAM_TYPE_VBI is released
       automatically when the MPG stream is released.
       We only need to stop the VBI capturing. */
    if (s->type == CX18_ENC_STREAM_TYPE_MPG &&
        test_bit(CX18_F_S_STREAMING, &s_vbi->s_flags)) {
        cx18_stop_v4l2_encode_stream(s_vbi, 0);
        clear_bit(CX18_F_S_STREAMING, &s_vbi->s_flags);
    }
    clear_bit(CX18_F_S_STREAMING, &s->s_flags);
    cx18_release_stream(s);
    return -EIO;
}

ssize_t cx18_v4l2_read(struct file *filp, char __user *buf, size_t count,
        loff_t *pos)
{
    struct cx18_open_id *id = filp->private_data;
    struct cx18 *cx = id->cx;
    struct cx18_stream *s = &cx->streams[id->type];
    int rc;

    CX18_DEBUG_HI_FILE("read %zd bytes from %s\n", count, s->name);

    mutex_lock(&cx->serialize_lock);
    rc = cx18_start_capture(id);
    mutex_unlock(&cx->serialize_lock);
    if (rc)
        return rc;
    return cx18_read_pos(s, buf, count, pos, filp->f_flags & O_NONBLOCK);
}

unsigned int cx18_v4l2_enc_poll(struct file *filp, poll_table *wait)
{
    struct cx18_open_id *id = filp->private_data;
    struct cx18 *cx = id->cx;
    struct cx18_stream *s = &cx->streams[id->type];
    int eof = test_bit(CX18_F_S_STREAMOFF, &s->s_flags);

    /* Start a capture if there is none */
    if (!eof && !test_bit(CX18_F_S_STREAMING, &s->s_flags)) {
        int rc;

        mutex_lock(&cx->serialize_lock);
        rc = cx18_start_capture(id);
        mutex_unlock(&cx->serialize_lock);
        if (rc) {
            CX18_DEBUG_INFO("Could not start capture for %s (%d)\n",
                    s->name, rc);
            return POLLERR;
        }
        CX18_DEBUG_FILE("Encoder poll started capture\n");
    }

    /* add stream's waitq to the poll list */
    CX18_DEBUG_HI_FILE("Encoder poll\n");
    poll_wait(filp, &s->waitq, wait);

    if (s->q_full.length || s->q_io.length)
        return POLLIN | POLLRDNORM;
    if (eof)
        return POLLHUP;
    return 0;
}

void cx18_stop_capture(struct cx18_open_id *id, int gop_end)
{
    struct cx18 *cx = id->cx;
    struct cx18_stream *s = &cx->streams[id->type];

    CX18_DEBUG_IOCTL("close() of %s\n", s->name);

    /* 'Unclaim' this stream */

    /* Stop capturing */
    if (test_bit(CX18_F_S_STREAMING, &s->s_flags)) {
        struct cx18_stream *s_vbi =
            &cx->streams[CX18_ENC_STREAM_TYPE_VBI];

        CX18_DEBUG_INFO("close stopping capture\n");
        /* Special case: a running VBI capture for VBI insertion
           in the mpeg stream. Need to stop that too. */
        if (id->type == CX18_ENC_STREAM_TYPE_MPG &&
            test_bit(CX18_F_S_STREAMING, &s_vbi->s_flags) &&
            !test_bit(CX18_F_S_APPL_IO, &s_vbi->s_flags)) {
            CX18_DEBUG_INFO("close stopping embedded VBI capture\n");
            cx18_stop_v4l2_encode_stream(s_vbi, 0);
        }
        if (id->type == CX18_ENC_STREAM_TYPE_VBI &&
            test_bit(CX18_F_S_INTERNAL_USE, &s->s_flags))
            /* Also used internally, don't stop capturing */
            s->id = -1;
        else
            cx18_stop_v4l2_encode_stream(s, gop_end);
    }
    if (!gop_end) {
        clear_bit(CX18_F_S_APPL_IO, &s->s_flags);
        clear_bit(CX18_F_S_STREAMOFF, &s->s_flags);
        cx18_release_stream(s);
    }
}

int cx18_v4l2_close(struct inode *inode, struct file *filp)
{
    struct cx18_open_id *id = filp->private_data;
    struct cx18 *cx = id->cx;
    struct cx18_stream *s = &cx->streams[id->type];

    CX18_DEBUG_IOCTL("close() of %s\n", s->name);

    v4l2_prio_close(&cx->prio, &id->prio);

    /* Easy case first: this stream was never claimed by us */
    if (s->id != id->open_id) {
        kfree(id);
        return 0;
    }

    /* 'Unclaim' this stream */

    /* Stop radio */
    mutex_lock(&cx->serialize_lock);
    if (id->type == CX18_ENC_STREAM_TYPE_RAD) {
        /* Closing radio device, return to TV mode */
        cx18_mute(cx);
        /* Mark that the radio is no longer in use */
        clear_bit(CX18_F_I_RADIO_USER, &cx->i_flags);
        /* Switch tuner to TV */
        cx18_call_i2c_clients(cx, VIDIOC_S_STD, &cx->std);
        /* Select correct audio input (i.e. TV tuner or Line in) */
        cx18_audio_set_io(cx);
        if (atomic_read(&cx->ana_capturing) > 0) {
            /* Undo video mute */
            cx18_vapi(cx, CX18_CPU_SET_VIDEO_MUTE, 2, s->handle,
                cx->params.video_mute |
                    (cx->params.video_mute_yuv << 8));
        }
        /* Done! Unmute and continue. */
        cx18_unmute(cx);
        cx18_release_stream(s);
    } else {
        cx18_stop_capture(id, 0);
    }
    kfree(id);
    mutex_unlock(&cx->serialize_lock);
    return 0;
}

static int cx18_serialized_open(struct cx18_stream *s, struct file *filp)
{
    struct cx18 *cx = s->cx;
    struct cx18_open_id *item;

    CX18_DEBUG_FILE("open %s\n", s->name);

    /* Allocate memory */
    item = kmalloc(sizeof(struct cx18_open_id), GFP_KERNEL);
    if (NULL == item) {
        CX18_DEBUG_WARN("nomem on v4l2 open\n");
        return -ENOMEM;
    }
    item->cx = cx;
    item->type = s->type;
    v4l2_prio_open(&cx->prio, &item->prio);

    item->open_id = cx->open_id++;
    filp->private_data = item;

    if (item->type == CX18_ENC_STREAM_TYPE_RAD) {
        /* Try to claim this stream */
        if (cx18_claim_stream(item, item->type)) {
            /* No, it's already in use */
            kfree(item);
            return -EBUSY;
        }

        if (!test_bit(CX18_F_I_RADIO_USER, &cx->i_flags)) {
            if (atomic_read(&cx->ana_capturing) > 0) {
                /* switching to radio while capture is
                   in progress is not polite */
                cx18_release_stream(s);
                kfree(item);
                return -EBUSY;
            }
        }

        /* Mark that the radio is being used. */
        set_bit(CX18_F_I_RADIO_USER, &cx->i_flags);
        /* We have the radio */
        cx18_mute(cx);
        /* Switch tuner to radio */
        cx18_call_i2c_clients(cx, AUDC_SET_RADIO, NULL);
        /* Select the correct audio input (i.e. radio tuner) */
        cx18_audio_set_io(cx);
        /* Done! Unmute and continue. */
        cx18_unmute(cx);
    }
    return 0;
}

int cx18_v4l2_open(struct inode *inode, struct file *filp)
{
    int res, x, y = 0;
    struct cx18 *cx = NULL;
    struct cx18_stream *s = NULL;
    int minor = iminor(inode);

    /* Find which card this open was on */
    spin_lock(&cx18_cards_lock);
    for (x = 0; cx == NULL && x < cx18_cards_active; x++) {
        /* find out which stream this open was on */
        for (y = 0; y < CX18_MAX_STREAMS; y++) {
            if (cx18_cards[x] == NULL)
                continue;
            s = &cx18_cards[x]->streams[y];
            if (s->v4l2dev && s->v4l2dev->minor == minor) {
                cx = cx18_cards[x];
                break;
            }
        }
    }
    spin_unlock(&cx18_cards_lock);

    if (cx == NULL) {
        /* Couldn't find a device registered
           on that minor, shouldn't happen! */
        printk(KERN_WARNING "No cx18 device found on minor %d\n",
                minor);
        return -ENXIO;
    }

    mutex_lock(&cx->serialize_lock);
    if (cx18_init_on_first_open(cx)) {
        CX18_ERR("Failed to initialize on minor %d\n", minor);
        mutex_unlock(&cx->serialize_lock);
        return -ENXIO;
    }
    res = cx18_serialized_open(s, filp);
    mutex_unlock(&cx->serialize_lock);
    return res;
}

void cx18_mute(struct cx18 *cx)
{
    if (atomic_read(&cx->ana_capturing))
        cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2,
                cx18_find_handle(cx), 1);
    CX18_DEBUG_INFO("Mute\n");
}

void cx18_unmute(struct cx18 *cx)
{
    if (atomic_read(&cx->ana_capturing)) {
        cx18_msleep_timeout(100, 0);
        cx18_vapi(cx, CX18_CPU_SET_MISC_PARAMETERS, 2,
                cx18_find_handle(cx), 12);
        cx18_vapi(cx, CX18_CPU_SET_AUDIO_MUTE, 2,
                cx18_find_handle(cx), 0);
    }
    CX18_DEBUG_INFO("Unmute\n");
}
