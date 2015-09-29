
/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.17 $ of : mfd-data-access.m2c,v $
 *
 * $Id$
 */
#ifndef USMDHUSERKEYTABLE_DATA_ACCESS_H
#define USMDHUSERKEYTABLE_DATA_ACCESS_H

#ifdef __cplusplus
extern "C"
{
#endif


    /*
     *********************************************************************
     * function declarations
     */

    /*
     *********************************************************************
     * Table declarations
     */

/**********************************************************************
 **********************************************************************
 ***
 *** Table usmDHUserKeyTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * SNMP-USM-DH-OBJECTS-MIB::usmDHUserKeyTable is subid 2 of usmDHPublicObjects.
     * Its status is Current.
     * OID: .1.3.6.1.3.101.1.1.2, length: 9
     */


    int usmDHUserKeyTable_init_data (usmDHUserKeyTable_registration * usmDHUserKeyTable_reg);


    /*
     * TODO:180:o: Review usmDHUserKeyTable cache timeout.
     * The number of seconds before the cache times out
     */
#define USMDHUSERKEYTABLE_CACHE_TIMEOUT   60

    void usmDHUserKeyTable_container_init (netsnmp_container ** container_ptr_ptr, netsnmp_cache * cache);
    void usmDHUserKeyTable_container_shutdown (netsnmp_container * container_ptr);

    int usmDHUserKeyTable_container_load (netsnmp_container * container);
    void usmDHUserKeyTable_container_free (netsnmp_container * container);

    int usmDHUserKeyTable_cache_load (netsnmp_container * container);
    void usmDHUserKeyTable_cache_free (netsnmp_container * container);

    int usmDHUserKeyTable_row_prep (usmDHUserKeyTable_rowreq_ctx * rowreq_ctx);



#ifdef __cplusplus
}
#endif
#endif                            /* USMDHUSERKEYTABLE_DATA_ACCESS_H */
