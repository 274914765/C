
/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 14170 $ of $
 *
 * $Id:$
 */
#ifndef DOT3STATSTABLE_H
#define DOT3STATSTABLE_H

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup misc misc: Miscellaneous routines
 *
 * @{
 */
#include <net-snmp/library/asn1.h>

    /*
     * OID and column number definitions for dot3StatsTable 
     */
#include "dot3StatsTable_oids.h"

    /*
     * enum definions 
     */
#include "dot3StatsTable_enums.h"

    /*
     *********************************************************************
     * function declarations
     */
    void init_dot3StatsTable (void);
    void shutdown_dot3StatsTable (void);

    /*
     *********************************************************************
     * Table declarations
     */

/**********************************************************************
 **********************************************************************
 ***
 *** Table dot3StatsTable
 ***
 **********************************************************************
 **********************************************************************/
    /*
     * EtherLike-MIB::dot3StatsTable is subid 2 of dot3.
     * Its status is Current.
     * OID: .1.3.6.1.2.1.10.7.2, length: 9
     */
    /*
     *********************************************************************
     * When you register your mib, you get to provide a generic
     * pointer that will be passed back to you for most of the
     * functions calls.
     *
     * TODO:100:r: Review all context structures
     */
    /*
     * TODO:101:o: |-> Review dot3StatsTable registration context.
     */
    typedef netsnmp_data_list dot3StatsTable_registration;

/**********************************************************************/
    /*
     * TODO:110:r: |-> Review dot3StatsTable data context structure.
     * This structure is used to represent the data for dot3StatsTable.
     */
    /*
     * This structure contains storage for all the columns defined in the
     * dot3StatsTable.
     */
    typedef struct dot3StatsTable_data_s
    {

        /*
         * dot3StatsAlignmentErrors(2)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsAlignmentErrors;

        /*
         * dot3StatsFCSErrors(3)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsFCSErrors;

        /*
         * dot3StatsSingleCollisionFrames(4)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsSingleCollisionFrames;

        /*
         * dot3StatsMultipleCollisionFrames(5)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsMultipleCollisionFrames;

        /*
         * dot3StatsSQETestErrors(6)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsSQETestErrors;

        /*
         * dot3StatsDeferredTransmissions(7)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsDeferredTransmissions;

        /*
         * dot3StatsLateCollisions(8)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsLateCollisions;

        /*
         * dot3StatsExcessiveCollisions(9)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsExcessiveCollisions;

        /*
         * dot3StatsInternalMacTransmitErrors(10)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsInternalMacTransmitErrors;

        /*
         * dot3StatsCarrierSenseErrors(11)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsCarrierSenseErrors;

        /*
         * dot3StatsFrameTooLongs(13)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsFrameTooLongs;

        /*
         * dot3StatsInternalMacReceiveErrors(16)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsInternalMacReceiveErrors;

        /*
         * dot3StatsEtherChipSet(17)/OBJECTID/ASN_OBJECT_ID/oid(oid)//L/A/w/e/r/d/h
         */
        oid dot3StatsEtherChipSet[128];
        size_t dot3StatsEtherChipSet_len;    /* # of oid elements, not bytes */

        /*
         * dot3StatsSymbolErrors(18)/COUNTER/ASN_COUNTER/u_long(u_long)//l/A/w/e/r/d/h
         */
        u_long dot3StatsSymbolErrors;

        /*
         * dot3StatsDuplexStatus(19)/INTEGER/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h
         */
        u_long dot3StatsDuplexStatus;

        /*
         * dot3StatsRateControlAbility(20)/TruthValue/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h
         */
        u_long dot3StatsRateControlAbility;

        /*
         * dot3StatsRateControlStatus(21)/INTEGER/ASN_INTEGER/long(u_long)//l/A/w/E/r/d/h
         */
        u_long dot3StatsRateControlStatus;

    } dot3StatsTable_data;


    /*
     * TODO:120:r: |-> Review dot3StatsTable mib index.
     * This structure is used to represent the index for dot3StatsTable.
     */
    typedef struct dot3StatsTable_mib_index_s
    {

        /*
         * dot3StatsIndex(1)/InterfaceIndex/ASN_INTEGER/long(long)//l/A/w/e/R/d/H
         */
        long dot3StatsIndex;


    } dot3StatsTable_mib_index;

    /*
     * TODO:121:r: |   |-> Review dot3StatsTable max index length.
     * If you KNOW that your indexes will never exceed a certain
     * length, update this macro to that length.
     */
#define MAX_dot3StatsTable_IDX_LEN     255


    /*
     *********************************************************************
     * TODO:130:o: |-> Review dot3StatsTable Row request (rowreq) context.
     * When your functions are called, you will be passed a
     * dot3StatsTable_rowreq_ctx pointer.
     */
    typedef struct dot3StatsTable_rowreq_ctx_s
    {

    /** this must be first for container compare to work */
        netsnmp_index oid_idx;
        oid oid_tmp[MAX_dot3StatsTable_IDX_LEN];

        dot3StatsTable_mib_index tbl_idx;

        dot3StatsTable_data data;
        unsigned int column_exists_flags;    /* flags for existence */

        /*
         * flags per row. Currently, the first (lower) 8 bits are reserved
         * for the user. See mfd.h for other flags.
         */
        u_int rowreq_flags;

        /*
         * TODO:131:o: |   |-> Add useful data to dot3StatsTable rowreq context.
         */

        /*
         * storage for future expansion
         */
        netsnmp_data_list *dot3StatsTable_data_list;

    } dot3StatsTable_rowreq_ctx;

    typedef struct dot3StatsTable_ref_rowreq_ctx_s
    {
        dot3StatsTable_rowreq_ctx *rowreq_ctx;
    } dot3StatsTable_ref_rowreq_ctx;

    /*
     *********************************************************************
     * function prototypes
     */
    int dot3StatsTable_pre_request (dot3StatsTable_registration * user_context);
    int dot3StatsTable_post_request (dot3StatsTable_registration * user_context, int rc);

    int dot3StatsTable_rowreq_ctx_init (dot3StatsTable_rowreq_ctx * rowreq_ctx, void *user_init_ctx);
    void dot3StatsTable_rowreq_ctx_cleanup (dot3StatsTable_rowreq_ctx * rowreq_ctx);


      dot3StatsTable_rowreq_ctx * dot3StatsTable_row_find_by_mib_index (dot3StatsTable_mib_index * mib_idx);

    extern oid dot3StatsTable_oid[];
    extern int dot3StatsTable_oid_size;


#include "dot3StatsTable_interface.h"
#include "dot3StatsTable_data_access.h"
#include "dot3StatsTable_data_get.h"
#include "dot3StatsTable_data_set.h"

    /*
     * DUMMY markers, ignore
     *
     * TODO:099:x: *************************************************************
     * TODO:199:x: *************************************************************
     * TODO:299:x: *************************************************************
     * TODO:399:x: *************************************************************
     * TODO:499:x: *************************************************************
     */

#ifdef __cplusplus
}
#endif
#endif                            /* DOT3STATSTABLE_H */

/** @} */
