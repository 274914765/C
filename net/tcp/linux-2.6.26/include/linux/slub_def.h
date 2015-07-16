#ifndef _LINUX_SLUB_DEF_H
#define _LINUX_SLUB_DEF_H

/*
 * SLUB : A Slab allocator without object queues.
 *
 * (C) 2007 SGI, Christoph Lameter
 */
#include <linux/types.h>
#include <linux/gfp.h>
#include <linux/workqueue.h>
#include <linux/kobject.h>

enum stat_item {
    ALLOC_FASTPATH,        /* Allocation from cpu slab */
    ALLOC_SLOWPATH,        /* Allocation by getting a new cpu slab */
    FREE_FASTPATH,        /* Free to cpu slub */
    FREE_SLOWPATH,        /* Freeing not to cpu slab */
    FREE_FROZEN,        /* Freeing to frozen slab */
    FREE_ADD_PARTIAL,    /* Freeing moves slab to partial list */
    FREE_REMOVE_PARTIAL,    /* Freeing removes last object */
    ALLOC_FROM_PARTIAL,    /* Cpu slab acquired from partial list */
    ALLOC_SLAB,        /* Cpu slab acquired from page allocator */
    ALLOC_REFILL,        /* Refill cpu slab from slab freelist */
    FREE_SLAB,        /* Slab freed to the page allocator */
    CPUSLAB_FLUSH,        /* Abandoning of the cpu slab */
    DEACTIVATE_FULL,    /* Cpu slab was full when deactivated */
    DEACTIVATE_EMPTY,    /* Cpu slab was empty when deactivated */
    DEACTIVATE_TO_HEAD,    /* Cpu slab was moved to the head of partials */
    DEACTIVATE_TO_TAIL,    /* Cpu slab was moved to the tail of partials */
    DEACTIVATE_REMOTE_FREES,/* Slab contained remotely freed objects */
    ORDER_FALLBACK,        /* Number of times fallback was necessary */
    NR_SLUB_STAT_ITEMS };

struct kmem_cache_cpu {
    void **freelist;    /* Pointer to first free per cpu object */
    struct page *page;    /* The slab from which we are allocating */
    int node;        /* The node of the page (or -1 for debug) */
    unsigned int offset;    /* Freepointer offset (in word units) */
    unsigned int objsize;    /* Size of an object (from kmem_cache) */
#ifdef CONFIG_SLUB_STATS
    unsigned stat[NR_SLUB_STAT_ITEMS];
#endif
};

struct kmem_cache_node {
    spinlock_t list_lock;    /* Protect partial list and nr_partial */
    unsigned long nr_partial;
    struct list_head partial;
#ifdef CONFIG_SLUB_DEBUG
    atomic_long_t nr_slabs;
    atomic_long_t total_objects;
    struct list_head full;
#endif
};

/*
 * Word size structure that can be atomically updated or read and that
 * contains both the order and the number of objects that a slab of the
 * given order would contain.
 */
struct kmem_cache_order_objects {
    unsigned long x;
};

/*
 * Slab cache management.
 */
struct kmem_cache {
    /* Used for retriving partial slabs etc */
    unsigned long flags;
    int size;        /* The size of an object including meta data */
    int objsize;        /* The size of an object without meta data */
    int offset;        /* Free pointer offset. */
    struct kmem_cache_order_objects oo;

    /*
     * Avoid an extra cache line for UP, SMP and for the node local to
     * struct kmem_cache.
     */
    struct kmem_cache_node local_node;

    /* Allocation and freeing of slabs */
    struct kmem_cache_order_objects max;
    struct kmem_cache_order_objects min;
    gfp_t allocflags;    /* gfp flags to use on each alloc */
    int refcount;        /* Refcount for slab cache destroy */
    void (*ctor)(struct kmem_cache *, void *);
    int inuse;        /* Offset to metadata */
    int align;        /* Alignment */
    const char *name;    /* Name (only for display!) */
    struct list_head list;    /* List of slab caches */
#ifdef CONFIG_SLUB_DEBUG
    struct kobject kobj;    /* For sysfs */
#endif

#ifdef CONFIG_NUMA
    /*
     * Defragmentation by allocating from a remote node.
     */
    int remote_node_defrag_ratio;
    struct kmem_cache_node *node[MAX_NUMNODES];
#endif
#ifdef CONFIG_SMP
    struct kmem_cache_cpu *cpu_slab[NR_CPUS];
#else
    struct kmem_cache_cpu cpu_slab;
#endif
};

/*
 * Kmalloc subsystem.
 */
#if defined(ARCH_KMALLOC_MINALIGN) && ARCH_KMALLOC_MINALIGN > 8
#define KMALLOC_MIN_SIZE ARCH_KMALLOC_MINALIGN
#else
#define KMALLOC_MIN_SIZE 8
#endif

#define KMALLOC_SHIFT_LOW ilog2(KMALLOC_MIN_SIZE)

/*
 * We keep the general caches in an array of slab caches that are used for
 * 2^x bytes of allocations.
 */
extern struct kmem_cache kmalloc_caches[PAGE_SHIFT + 1];

/*
 * Sorry that the following has to be that ugly but some versions of GCC
 * have trouble with constant propagation and loops.
 */
static __always_inline int kmalloc_index(size_t size)
{
    if (!size)
        return 0;

    if (size <= KMALLOC_MIN_SIZE)
        return KMALLOC_SHIFT_LOW;

#if KMALLOC_MIN_SIZE <= 64
    if (size > 64 && size <= 96)
        return 1;
    if (size > 128 && size <= 192)
        return 2;
#endif
    if (size <=          8) return 3;
    if (size <=         16) return 4;
    if (size <=         32) return 5;
    if (size <=         64) return 6;
    if (size <=        128) return 7;
    if (size <=        256) return 8;
    if (size <=        512) return 9;
    if (size <=       1024) return 10;
    if (size <=   2 * 1024) return 11;
    if (size <=   4 * 1024) return 12;
/*
 * The following is only needed to support architectures with a larger page
 * size than 4k.
 */
    if (size <=   8 * 1024) return 13;
    if (size <=  16 * 1024) return 14;
    if (size <=  32 * 1024) return 15;
    if (size <=  64 * 1024) return 16;
    if (size <= 128 * 1024) return 17;
    if (size <= 256 * 1024) return 18;
    if (size <= 512 * 1024) return 19;
    if (size <= 1024 * 1024) return 20;
    if (size <=  2 * 1024 * 1024) return 21;
    return -1;

/*
 * What we really wanted to do and cannot do because of compiler issues is:
 *    int i;
 *    for (i = KMALLOC_SHIFT_LOW; i <= KMALLOC_SHIFT_HIGH; i++)
 *        if (size <= (1 << i))
 *            return i;
 */
}

/*
 * Find the slab cache for a given combination of allocation flags and size.
 *
 * This ought to end up with a global pointer to the right cache
 * in kmalloc_caches.
 */
static __always_inline struct kmem_cache *kmalloc_slab(size_t size)
{
    int index = kmalloc_index(size);

    if (index == 0)
        return NULL;

    return &kmalloc_caches[index];
}

#ifdef CONFIG_ZONE_DMA
#define SLUB_DMA __GFP_DMA
#else
/* Disable DMA functionality */
#define SLUB_DMA (__force gfp_t)0
#endif

void *kmem_cache_alloc(struct kmem_cache *, gfp_t);
void *__kmalloc(size_t size, gfp_t flags);

static __always_inline void *kmalloc_large(size_t size, gfp_t flags)
{
    return (void *)__get_free_pages(flags | __GFP_COMP, get_order(size));
}

static __always_inline void *kmalloc(size_t size, gfp_t flags)
{
    if (__builtin_constant_p(size)) {
        if (size > PAGE_SIZE)
            return kmalloc_large(size, flags);

        if (!(flags & SLUB_DMA)) {
            struct kmem_cache *s = kmalloc_slab(size);

            if (!s)
                return ZERO_SIZE_PTR;

            return kmem_cache_alloc(s, flags);
        }
    }
    return __kmalloc(size, flags);
}

#ifdef CONFIG_NUMA
void *__kmalloc_node(size_t size, gfp_t flags, int node);
void *kmem_cache_alloc_node(struct kmem_cache *, gfp_t flags, int node);

static __always_inline void *kmalloc_node(size_t size, gfp_t flags, int node)
{
    if (__builtin_constant_p(size) &&
        size <= PAGE_SIZE && !(flags & SLUB_DMA)) {
            struct kmem_cache *s = kmalloc_slab(size);

        if (!s)
            return ZERO_SIZE_PTR;

        return kmem_cache_alloc_node(s, flags, node);
    }
    return __kmalloc_node(size, flags, node);
}
#endif

#endif /* _LINUX_SLUB_DEF_H */