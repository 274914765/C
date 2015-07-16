/*
 * linux/include/linux/sunrpc/svc_xprt.h
 *
 * RPC server transport I/O
 */

#ifndef SUNRPC_SVC_XPRT_H
#define SUNRPC_SVC_XPRT_H

#include <linux/sunrpc/svc.h>
#include <linux/module.h>

struct svc_xprt_ops {
    struct svc_xprt    *(*xpo_create)(struct svc_serv *,
                       struct sockaddr *, int,
                       int);
    struct svc_xprt    *(*xpo_accept)(struct svc_xprt *);
    int        (*xpo_has_wspace)(struct svc_xprt *);
    int        (*xpo_recvfrom)(struct svc_rqst *);
    void        (*xpo_prep_reply_hdr)(struct svc_rqst *);
    int        (*xpo_sendto)(struct svc_rqst *);
    void        (*xpo_release_rqst)(struct svc_rqst *);
    void        (*xpo_detach)(struct svc_xprt *);
    void        (*xpo_free)(struct svc_xprt *);
};

struct svc_xprt_class {
    const char        *xcl_name;
    struct module        *xcl_owner;
    struct svc_xprt_ops    *xcl_ops;
    struct list_head    xcl_list;
    u32            xcl_max_payload;
};

struct svc_xprt {
    struct svc_xprt_class    *xpt_class;
    struct svc_xprt_ops    *xpt_ops;
    struct kref        xpt_ref;
    struct list_head    xpt_list;
    struct list_head    xpt_ready;
    unsigned long        xpt_flags;
#define    XPT_BUSY    0        /* enqueued/receiving */
#define    XPT_CONN    1        /* conn pending */
#define    XPT_CLOSE    2        /* dead or dying */
#define    XPT_DATA    3        /* data pending */
#define    XPT_TEMP    4        /* connected transport */
#define    XPT_DEAD    6        /* transport closed */
#define    XPT_CHNGBUF    7        /* need to change snd/rcv buf sizes */
#define    XPT_DEFERRED    8        /* deferred request pending */
#define    XPT_OLD        9        /* used for xprt aging mark+sweep */
#define    XPT_DETACHED    10        /* detached from tempsocks list */
#define XPT_LISTENER    11        /* listening endpoint */
#define XPT_CACHE_AUTH    12        /* cache auth info */

    struct svc_pool        *xpt_pool;    /* current pool iff queued */
    struct svc_serv        *xpt_server;    /* service for transport */
    atomic_t                xpt_reserved;    /* space on outq that is rsvd */
    struct mutex        xpt_mutex;    /* to serialize sending data */
    spinlock_t        xpt_lock;    /* protects sk_deferred
                         * and xpt_auth_cache */
    void            *xpt_auth_cache;/* auth cache */
    struct list_head    xpt_deferred;    /* deferred requests that need
                         * to be revisted */
    struct sockaddr_storage    xpt_local;    /* local address */
    size_t            xpt_locallen;    /* length of address */
    struct sockaddr_storage    xpt_remote;    /* remote peer's address */
    size_t            xpt_remotelen;    /* length of address */
};

int    svc_reg_xprt_class(struct svc_xprt_class *);
void    svc_unreg_xprt_class(struct svc_xprt_class *);
void    svc_xprt_init(struct svc_xprt_class *, struct svc_xprt *,
              struct svc_serv *);
int    svc_create_xprt(struct svc_serv *, char *, unsigned short, int);
void    svc_xprt_enqueue(struct svc_xprt *xprt);
void    svc_xprt_received(struct svc_xprt *);
void    svc_xprt_put(struct svc_xprt *xprt);
void    svc_xprt_copy_addrs(struct svc_rqst *rqstp, struct svc_xprt *xprt);
void    svc_close_xprt(struct svc_xprt *xprt);
void    svc_delete_xprt(struct svc_xprt *xprt);
int    svc_port_is_privileged(struct sockaddr *sin);
int    svc_print_xprts(char *buf, int maxlen);
struct    svc_xprt *svc_find_xprt(struct svc_serv *, char *, int, int);
int    svc_xprt_names(struct svc_serv *serv, char *buf, int buflen);

static inline void svc_xprt_get(struct svc_xprt *xprt)
{
    kref_get(&xprt->xpt_ref);
}
static inline void svc_xprt_set_local(struct svc_xprt *xprt,
                      struct sockaddr *sa, int salen)
{
    memcpy(&xprt->xpt_local, sa, salen);
    xprt->xpt_locallen = salen;
}
static inline void svc_xprt_set_remote(struct svc_xprt *xprt,
                       struct sockaddr *sa, int salen)
{
    memcpy(&xprt->xpt_remote, sa, salen);
    xprt->xpt_remotelen = salen;
}
static inline unsigned short svc_addr_port(struct sockaddr *sa)
{
    unsigned short ret = 0;
    switch (sa->sa_family) {
    case AF_INET:
        ret = ntohs(((struct sockaddr_in *)sa)->sin_port);
        break;
    case AF_INET6:
        ret = ntohs(((struct sockaddr_in6 *)sa)->sin6_port);
        break;
    }
    return ret;
}

static inline size_t svc_addr_len(struct sockaddr *sa)
{
    switch (sa->sa_family) {
    case AF_INET:
        return sizeof(struct sockaddr_in);
    case AF_INET6:
        return sizeof(struct sockaddr_in6);
    }
    return -EAFNOSUPPORT;
}

static inline unsigned short svc_xprt_local_port(struct svc_xprt *xprt)
{
    return svc_addr_port((struct sockaddr *)&xprt->xpt_local);
}

static inline unsigned short svc_xprt_remote_port(struct svc_xprt *xprt)
{
    return svc_addr_port((struct sockaddr *)&xprt->xpt_remote);
}

static inline char *__svc_print_addr(struct sockaddr *addr,
                     char *buf, size_t len)
{
    switch (addr->sa_family) {
    case AF_INET:
        snprintf(buf, len, "%u.%u.%u.%u, port=%u",
            NIPQUAD(((struct sockaddr_in *) addr)->sin_addr),
            ntohs(((struct sockaddr_in *) addr)->sin_port));
        break;

    case AF_INET6:
        snprintf(buf, len, "%x:%x:%x:%x:%x:%x:%x:%x, port=%u",
            NIP6(((struct sockaddr_in6 *) addr)->sin6_addr),
            ntohs(((struct sockaddr_in6 *) addr)->sin6_port));
        break;

    default:
        snprintf(buf, len, "unknown address type: %d", addr->sa_family);
        break;
    }
    return buf;
}
#endif /* SUNRPC_SVC_XPRT_H */