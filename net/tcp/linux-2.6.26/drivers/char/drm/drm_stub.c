/**
 * \file drm_stub.h
 * Stub support
 *
 * \author Rickard E. (Rik) Faith <faith@valinux.com>
 */

/*
 * Created: Fri Jan 19 10:48:35 2001 by faith@acm.org
 *
 * Copyright 2001 VA Linux Systems, Inc., Sunnyvale, California.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include "drmP.h"
#include "drm_core.h"

unsigned int drm_debug = 0;    /* 1 to enable debug output */
EXPORT_SYMBOL(drm_debug);

MODULE_AUTHOR(CORE_AUTHOR);
MODULE_DESCRIPTION(CORE_DESC);
MODULE_LICENSE("GPL and additional rights");
MODULE_PARM_DESC(debug, "Enable debug output");

module_param_named(debug, drm_debug, int, 0600);

struct idr drm_minors_idr;

struct class *drm_class;
struct proc_dir_entry *drm_proc_root;

static int drm_minor_get_id(struct drm_device *dev, int type)
{
    int new_id;
    int ret;
    int base = 0, limit = 63;

again:
    if (idr_pre_get(&drm_minors_idr, GFP_KERNEL) == 0) {
        DRM_ERROR("Out of memory expanding drawable idr\n");
        return -ENOMEM;
    }
    mutex_lock(&dev->struct_mutex);
    ret = idr_get_new_above(&drm_minors_idr, NULL,
                base, &new_id);
    mutex_unlock(&dev->struct_mutex);
    if (ret == -EAGAIN) {
        goto again;
    } else if (ret) {
        return ret;
    }

    if (new_id >= limit) {
        idr_remove(&drm_minors_idr, new_id);
        return -EINVAL;
    }
    return new_id;
}

static int drm_fill_in_dev(struct drm_device * dev, struct pci_dev *pdev,
               const struct pci_device_id *ent,
               struct drm_driver *driver)
{
    int retcode;

    INIT_LIST_HEAD(&dev->filelist);
    INIT_LIST_HEAD(&dev->ctxlist);
    INIT_LIST_HEAD(&dev->vmalist);
    INIT_LIST_HEAD(&dev->maplist);

    spin_lock_init(&dev->count_lock);
    spin_lock_init(&dev->drw_lock);
    spin_lock_init(&dev->tasklet_lock);
    spin_lock_init(&dev->lock.spinlock);
    init_timer(&dev->timer);
    mutex_init(&dev->struct_mutex);
    mutex_init(&dev->ctxlist_mutex);

    idr_init(&dev->drw_idr);

    dev->pdev = pdev;
    dev->pci_device = pdev->device;
    dev->pci_vendor = pdev->vendor;

#ifdef __alpha__
    dev->hose = pdev->sysdata;
#endif
    dev->irq = pdev->irq;

    if (drm_ht_create(&dev->map_hash, 12)) {
        return -ENOMEM;
    }

    /* the DRM has 6 basic counters */
    dev->counters = 6;
    dev->types[0] = _DRM_STAT_LOCK;
    dev->types[1] = _DRM_STAT_OPENS;
    dev->types[2] = _DRM_STAT_CLOSES;
    dev->types[3] = _DRM_STAT_IOCTLS;
    dev->types[4] = _DRM_STAT_LOCKS;
    dev->types[5] = _DRM_STAT_UNLOCKS;

    dev->driver = driver;

    if (drm_core_has_AGP(dev)) {
        if (drm_device_is_agp(dev))
            dev->agp = drm_agp_init(dev);
        if (drm_core_check_feature(dev, DRIVER_REQUIRE_AGP)
            && (dev->agp == NULL)) {
            DRM_ERROR("Cannot initialize the agpgart module.\n");
            retcode = -EINVAL;
            goto error_out_unreg;
        }
        if (drm_core_has_MTRR(dev)) {
            if (dev->agp)
                dev->agp->agp_mtrr =
                    mtrr_add(dev->agp->agp_info.aper_base,
                         dev->agp->agp_info.aper_size *
                         1024 * 1024, MTRR_TYPE_WRCOMB, 1);
        }
    }

    if (dev->driver->load)
        if ((retcode = dev->driver->load(dev, ent->driver_data)))
            goto error_out_unreg;

    retcode = drm_ctxbitmap_init(dev);
    if (retcode) {
        DRM_ERROR("Cannot allocate memory for context bitmap.\n");
        goto error_out_unreg;
    }

    return 0;

      error_out_unreg:
    drm_lastclose(dev);
    return retcode;
}


/**
 * Get a secondary minor number.
 *
 * \param dev device data structure
 * \param sec-minor structure to hold the assigned minor
 * \return negative number on failure.
 *
 * Search an empty entry and initialize it to the given parameters, and
 * create the proc init entry via proc_init(). This routines assigns
 * minor numbers to secondary heads of multi-headed cards
 */
static int drm_get_minor(struct drm_device *dev, struct drm_minor **minor, int type)
{
    struct drm_minor *new_minor;
    int ret;
    int minor_id;

    DRM_DEBUG("\n");

    minor_id = drm_minor_get_id(dev, type);
    if (minor_id < 0)
        return minor_id;

    new_minor = kzalloc(sizeof(struct drm_minor), GFP_KERNEL);
    if (!new_minor) {
        ret = -ENOMEM;
        goto err_idr;
    }

    new_minor->type = type;
    new_minor->device = MKDEV(DRM_MAJOR, minor_id);
    new_minor->dev = dev;
    new_minor->index = minor_id;

    idr_replace(&drm_minors_idr, new_minor, minor_id);

    if (type == DRM_MINOR_LEGACY) {
        ret = drm_proc_init(new_minor, minor_id, drm_proc_root);
        if (ret) {
            DRM_ERROR("DRM: Failed to initialize /proc/dri.\n");
            goto err_mem;
        }
    } else
        new_minor->dev_root = NULL;

    ret = drm_sysfs_device_add(new_minor);
    if (ret) {
        printk(KERN_ERR
               "DRM: Error sysfs_device_add.\n");
        goto err_g2;
    }
    *minor = new_minor;

    DRM_DEBUG("new minor assigned %d\n", minor_id);
    return 0;


err_g2:
    if (new_minor->type == DRM_MINOR_LEGACY)
        drm_proc_cleanup(new_minor, drm_proc_root);
err_mem:
    kfree(new_minor);
err_idr:
    idr_remove(&drm_minors_idr, minor_id);
    *minor = NULL;
    return ret;
}

/**
 * Register.
 *
 * \param pdev - PCI device structure
 * \param ent entry from the PCI ID table with device type flags
 * \return zero on success or a negative number on failure.
 *
 * Attempt to gets inter module "drm" information. If we are first
 * then register the character device and inter module information.
 * Try and register, if we fail to register, backout previous work.
 */
int drm_get_dev(struct pci_dev *pdev, const struct pci_device_id *ent,
        struct drm_driver *driver)
{
    struct drm_device *dev;
    int ret;

    DRM_DEBUG("\n");

    dev = drm_calloc(1, sizeof(*dev), DRM_MEM_STUB);
    if (!dev)
        return -ENOMEM;

    ret = pci_enable_device(pdev);
    if (ret)
        goto err_g1;

    pci_set_master(pdev);
    if ((ret = drm_fill_in_dev(dev, pdev, ent, driver))) {
        printk(KERN_ERR "DRM: Fill_in_dev failed.\n");
        goto err_g2;
    }
    if ((ret = drm_get_minor(dev, &dev->primary, DRM_MINOR_LEGACY)))
        goto err_g2;

    DRM_INFO("Initialized %s %d.%d.%d %s on minor %d\n",
         driver->name, driver->major, driver->minor, driver->patchlevel,
         driver->date, dev->primary->index);

    return 0;

err_g2:
    pci_disable_device(pdev);
err_g1:
    drm_free(dev, sizeof(*dev), DRM_MEM_STUB);
    return ret;
}

/**
 * Put a device minor number.
 *
 * \param dev device data structure
 * \return always zero
 *
 * Cleans up the proc resources. If it is the last minor then release the foreign
 * "drm" data, otherwise unregisters the "drm" data, frees the dev list and
 * unregisters the character device.
 */
int drm_put_dev(struct drm_device * dev)
{
    DRM_DEBUG("release primary %s\n", dev->driver->pci_driver.name);

    if (dev->unique) {
        drm_free(dev->unique, strlen(dev->unique) + 1, DRM_MEM_DRIVER);
        dev->unique = NULL;
        dev->unique_len = 0;
    }
    if (dev->devname) {
        drm_free(dev->devname, strlen(dev->devname) + 1,
             DRM_MEM_DRIVER);
        dev->devname = NULL;
    }
    drm_free(dev, sizeof(*dev), DRM_MEM_STUB);
    return 0;
}

/**
 * Put a secondary minor number.
 *
 * \param sec_minor - structure to be released
 * \return always zero
 *
 * Cleans up the proc resources. Not legal for this to be the
 * last minor released.
 *
 */
int drm_put_minor(struct drm_minor **minor_p)
{
    struct drm_minor *minor = *minor_p;
    DRM_DEBUG("release secondary minor %d\n", minor->index);

    if (minor->type == DRM_MINOR_LEGACY)
        drm_proc_cleanup(minor, drm_proc_root);
    drm_sysfs_device_remove(minor);

    idr_remove(&drm_minors_idr, minor->index);

    kfree(minor);
    *minor_p = NULL;
    return 0;
}