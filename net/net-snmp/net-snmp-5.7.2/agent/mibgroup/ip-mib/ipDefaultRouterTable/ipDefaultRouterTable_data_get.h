
/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 12088 $ of $
 *
 * $Id:$
 *
 * @file ipDefaultRouterTable_data_get.h
 *
 * @addtogroup get
 *
 * Prototypes for get functions
 *
 * @{
 */
#ifndef IPDEFAULTROUTERTABLE_DATA_GET_H
#define IPDEFAULTROUTERTABLE_DATA_GET_H

#ifdef __cplusplus
extern "C"
{
#endif

    /*
     *********************************************************************
     * GET function declarations
     */

    /*
     *********************************************************************
     * GET Table declarations
     */

/**********************************************************************
 **********************************************************************
 ***
 *** Table ipDefaultRouterTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * IP-MIB::ipDefaultRouterTable is subid 37 of ip.
     * Its status is Current.
     * OID: .1.3.6.1.2.1.4.37, length: 8
     */
    /*
     * indexes
     */

    int ipDefaultRouterLifetime_get (ipDefaultRouterTable_rowreq_ctx *
                                     rowreq_ctx, u_long * ipDefaultRouterLifetime_val_ptr);
    int ipDefaultRouterPreference_get (ipDefaultRouterTable_rowreq_ctx *
                                       rowreq_ctx, u_long * ipDefaultRouterPreference_val_ptr);


    int ipDefaultRouterTable_indexes_set_tbl_idx
        (ipDefaultRouterTable_mib_index * tbl_idx,
         u_long ipDefaultRouterAddressType_val,
         char *ipDefaultRouterAddress_val_ptr,
         size_t ipDefaultRouterAddress_val_ptr_len, long ipDefaultRouterIfIndex_val);
    int ipDefaultRouterTable_indexes_set (ipDefaultRouterTable_rowreq_ctx *
                                          rowreq_ctx,
                                          u_long
                                          ipDefaultRouterAddressType_val,
                                          char
                                          *ipDefaultRouterAddress_val_ptr,
                                          size_t ipDefaultRouterAddress_val_ptr_len, long ipDefaultRouterIfIndex_val);




#ifdef __cplusplus
}
#endif
#endif                            /* IPDEFAULTROUTERTABLE_DATA_GET_H */

/** @} */
