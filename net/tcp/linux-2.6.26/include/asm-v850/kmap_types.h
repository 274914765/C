#ifndef __V850_KMAP_TYPES_H__
#define __V850_KMAP_TYPES_H__

enum km_type {
    KM_BOUNCE_READ,
    KM_SKB_SUNRPC_DATA,
    KM_SKB_DATA_SOFTIRQ,
    KM_USER0,
    KM_USER1,
    KM_BIO_SRC_IRQ,
    KM_BIO_DST_IRQ,
    KM_PTE0,
    KM_PTE1,
    KM_IRQ0,
    KM_IRQ1,
    KM_TYPE_NR
};

#endif /* __V850_KMAP_TYPES_H__ */