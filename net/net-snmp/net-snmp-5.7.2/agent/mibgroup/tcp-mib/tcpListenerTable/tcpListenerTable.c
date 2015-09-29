
/*
 * Note: this file originally auto-generated by mib2c using
 *       version : 1.48 $ of : mfd-top.m2c,v $ 
 *
 * $Id$
 */

/** \page MFD helper for tcpListenerTable
 *
 * \section intro Introduction
 * Introductory text.
 *
 */

/*
 * standard Net-SNMP includes 
 */
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

/*
 * include our parent header 
 */
#include "tcpListenerTable.h"

#include <net-snmp/agent/mib_modules.h>

#include "tcpListenerTable_interface.h"

const oid tcpListenerTable_oid[] = { TCPLISTENERTABLE_OID };

const int tcpListenerTable_oid_size = OID_LENGTH (tcpListenerTable_oid);

tcpListenerTable_registration tcpListenerTable_user_context;

void initialize_table_tcpListenerTable (void);

void shutdown_table_tcpListenerTable (void);


/**
 * Initializes the tcpListenerTable module
 */
void init_tcpListenerTable (void)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:init_tcpListenerTable", "called\n"));

    /*
     * TODO:300:o: Perform tcpListenerTable one-time module initialization.
     */

    /*
     * here we initialize all the tables we're planning on supporting
     */
    if (should_init ("tcpListenerTable"))
        initialize_table_tcpListenerTable ();

}                                /* init_tcpListenerTable */

/**
 * Shut-down the tcpListenerTable module (agent is exiting)
 */
void shutdown_tcpListenerTable (void)
{
    if (should_init ("tcpListenerTable"))
        shutdown_table_tcpListenerTable ();

}

/**
 * Initialize the table tcpListenerTable 
 *    (Define its contents and how it's structured)
 */
void initialize_table_tcpListenerTable (void)
{
    tcpListenerTable_registration *user_context;

    u_long flags;

    DEBUGMSGTL (("verbose:tcpListenerTable:initialize_table_tcpListenerTable", "called\n"));

    /*
     * TODO:301:o: Perform tcpListenerTable one-time table initialization.
     */

    /*
     * TODO:302:o: |->Initialize tcpListenerTable user context
     * if you'd like to pass in a pointer to some data for this
     * table, allocate or set it up here.
     */
    user_context = &tcpListenerTable_user_context;

    /*
     * No support for any flags yet, but in the future you would
     * set any flags here.
     */
    flags = 0;

    /*
     * call interface initialization code
     */
    _tcpListenerTable_initialize_interface (user_context, flags);
}                                /* initialize_table_tcpListenerTable */

/**
 * Shutdown the table tcpListenerTable 
 */
void shutdown_table_tcpListenerTable (void)
{
    /*
     * call interface shutdown code
     */
    _tcpListenerTable_shutdown_interface (&tcpListenerTable_user_context);
}

/**
 * extra context initialization (eg default values)
 *
 * @param rowreq_ctx    : row request context
 * @param user_init_ctx : void pointer for user (parameter to rowreq_ctx_allocate)
 *
 * @retval MFD_SUCCESS  : no errors
 * @retval MFD_ERROR    : error (context allocate will fail)
 */
int tcpListenerTable_rowreq_ctx_init (tcpListenerTable_rowreq_ctx * rowreq_ctx, void *user_init_ctx)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_rowreq_ctx_init", "called\n"));

    netsnmp_assert (NULL != rowreq_ctx);

    /*
     * TODO:210:o: |-> Perform extra tcpListenerTable rowreq initialization. (eg DEFVALS)
     */

    return MFD_SUCCESS;
}                                /* tcpListenerTable_rowreq_ctx_init */

/**
 * extra context cleanup
 *
 */
void tcpListenerTable_rowreq_ctx_cleanup (tcpListenerTable_rowreq_ctx * rowreq_ctx)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_rowreq_ctx_cleanup", "called\n"));

    netsnmp_assert (NULL != rowreq_ctx);

    /*
     * TODO:211:o: |-> Perform extra tcpListenerTable rowreq cleanup.
     */
    netsnmp_access_tcpconn_entry_free (rowreq_ctx->data);
    rowreq_ctx->data = NULL;
}                                /* tcpListenerTable_rowreq_ctx_cleanup */

/**
 * pre-request callback
 *
 *
 * @retval MFD_SUCCESS              : success.
 * @retval MFD_ERROR                : other error
 */
int tcpListenerTable_pre_request (tcpListenerTable_registration * user_context)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_pre_request", "called\n"));

    /*
     * TODO:510:o: Perform tcpListenerTable pre-request actions.
     */

    return MFD_SUCCESS;
}                                /* tcpListenerTable_pre_request */

/**
 * post-request callback
 *
 * Note:
 *   New rows have been inserted into the container, and
 *   deleted rows have been removed from the container and
 *   released.
 * @param user_context
 * @param rc : MFD_SUCCESS if all requests succeeded
 *
 * @retval MFD_SUCCESS : success.
 * @retval MFD_ERROR   : other error (ignored)
 */
int tcpListenerTable_post_request (tcpListenerTable_registration * user_context, int rc)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_post_request", "called\n"));

    /*
     * TODO:511:o: Perform tcpListenerTable post-request actions.
     */

    return MFD_SUCCESS;
}                                /* tcpListenerTable_post_request */


/**********************************************************************
 **********************************************************************
 ***
 *** Table tcpListenerTable
 ***
 **********************************************************************
 **********************************************************************/

/*
 * TCP-MIB::tcpListenerTable is subid 20 of tcp.
 * Its status is Current.
 * OID: .1.3.6.1.2.1.6.20, length: 8
 */

/*
 * ---------------------------------------------------------------------
 * * TODO:200:r: Implement tcpListenerTable data context functions.
 */

/*
 * tcpListenerTable_allocate_data
 *
 * Purpose: create new tcpListenerTable_data.
 */
tcpListenerTable_data *tcpListenerTable_allocate_data (void)
{
    /*
     * TODO:201:r: |-> allocate memory for the tcpListenerTable data context.
     */
    tcpListenerTable_data *rtn = SNMP_MALLOC_TYPEDEF (tcpListenerTable_data);

    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_allocate_data", "called\n"));

    if (NULL == rtn)
    {
        snmp_log (LOG_ERR, "unable to malloc memory for new " "tcpListenerTable_data.\n");
    }

    return rtn;
}                                /* tcpListenerTable_allocate_data */

/*
 * tcpListenerTable_release_data
 *
 * Purpose: release tcpListenerTable data.
 */
void tcpListenerTable_release_data (tcpListenerTable_data * data)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_release_data", "called\n"));

    /*
     * TODO:202:r: |-> release memory for the tcpListenerTable data context.
     */
    free (data);
}                                /* tcpListenerTable_release_data */



/**
 * set mib index(es)
 *
 * @param tbl_idx mib index structure
 * @param tcpListenerLocalAddressType_val
 * @param tcpListenerLocalAddress_val_ptr
 * @param tcpListenerLocalAddress_val_ptr_len
 * @param tcpListenerLocalPort_val
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 *
 * @remark
 *  This convenience function is useful for setting all the MIB index
 *  components with a single function call. It is assume that the C values
 *  have already been mapped from their native/rawformat to the MIB format.
 */
int
tcpListenerTable_indexes_set_tbl_idx (tcpListenerTable_mib_index * tbl_idx,
                                      u_long
                                      tcpListenerLocalAddressType_val,
                                      char *tcpListenerLocalAddress_val_ptr,
                                      size_t tcpListenerLocalAddress_val_ptr_len, u_long tcpListenerLocalPort_val)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_indexes_set_tbl_idx", "called\n"));

    /*
     * tcpListenerLocalAddressType(1)/InetAddressType/ASN_INTEGER/long(u_long)//l/a/w/E/r/d/h 
     */

    /** WARNING: this code might not work for netsnmp_tcpconn_entry */
    if (4 == tcpListenerLocalAddressType_val)
        tbl_idx->tcpListenerLocalAddressType = INETADDRESSTYPE_IPV4;
    else if (16 == tcpListenerLocalAddressType_val)
        tbl_idx->tcpListenerLocalAddressType = INETADDRESSTYPE_IPV6;
    else
        tbl_idx->tcpListenerLocalAddressType = INETADDRESSTYPE_UNKNOWN;

    /*
     * tcpListenerLocalAddress(2)/InetAddress/ASN_OCTET_STR/char(char)//L/a/w/e/R/d/h 
     */
    tbl_idx->tcpListenerLocalAddress_len = sizeof (tbl_idx->tcpListenerLocalAddress) / sizeof (tbl_idx->tcpListenerLocalAddress[0]);    /* max length */

    /** WARNING: this code might not work for netsnmp_tcpconn_entry */
    /*
     * make sure there is enough space for tcpListenerLocalAddress data
     */
    if ((NULL == tbl_idx->tcpListenerLocalAddress) ||
        (tbl_idx->tcpListenerLocalAddress_len < (tcpListenerLocalAddress_val_ptr_len)))
    {
        snmp_log (LOG_ERR, "not enough space for value\n");
        return MFD_ERROR;
    }
    tbl_idx->tcpListenerLocalAddress_len = tcpListenerLocalAddress_val_ptr_len;
    memcpy (tbl_idx->tcpListenerLocalAddress,
            tcpListenerLocalAddress_val_ptr,
            tcpListenerLocalAddress_val_ptr_len * sizeof (tcpListenerLocalAddress_val_ptr[0]));

    /*
     * tcpListenerLocalPort(3)/InetPortNumber/ASN_UNSIGNED/u_long(u_long)//l/a/w/e/R/d/H 
     */

    /** WARNING: this code might not work for netsnmp_tcpconn_entry */
    tbl_idx->tcpListenerLocalPort = tcpListenerLocalPort_val;


    return MFD_SUCCESS;
}                                /* tcpListenerTable_indexes_set_tbl_idx */

/**
 * @internal
 * set row context indexes
 *
 * @param reqreq_ctx the row context that needs updated indexes
 *
 * @retval MFD_SUCCESS     : success.
 * @retval MFD_ERROR       : other error.
 *
 * @remark
 *  This function sets the mib indexs, then updates the oid indexs
 *  from the mib index.
 */
int
tcpListenerTable_indexes_set (tcpListenerTable_rowreq_ctx * rowreq_ctx,
                              u_long tcpListenerLocalAddressType_val,
                              char *tcpListenerLocalAddress_val_ptr,
                              size_t tcpListenerLocalAddress_val_ptr_len, u_long tcpListenerLocalPort_val)
{
    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerTable_indexes_set", "called\n"));

    if (MFD_SUCCESS !=
        tcpListenerTable_indexes_set_tbl_idx (&rowreq_ctx->tbl_idx,
                                              tcpListenerLocalAddressType_val,
                                              tcpListenerLocalAddress_val_ptr,
                                              tcpListenerLocalAddress_val_ptr_len, tcpListenerLocalPort_val))
        return MFD_ERROR;

    /*
     * convert mib index to oid index
     */
    rowreq_ctx->oid_idx.len = sizeof (rowreq_ctx->oid_tmp) / sizeof (oid);
    if (0 != tcpListenerTable_index_to_oid (&rowreq_ctx->oid_idx, &rowreq_ctx->tbl_idx))
    {
        return MFD_ERROR;
    }

    return MFD_SUCCESS;
}                                /* tcpListenerTable_indexes_set */


/*---------------------------------------------------------------------
 * TCP-MIB::tcpListenerEntry.tcpListenerProcess
 * tcpListenerProcess is subid 4 of tcpListenerEntry.
 * Its status is Current, and its access level is ReadOnly.
 * OID: .1.3.6.1.2.1.6.20.1.4
 * Description:
The system's process ID for the process associated with 
            this listener, or zero if there is no such process.  This 
            value is expected to be the same as HOST-RESOURCES-MIB::
            hrSWRunIndex or SYSAPPL-MIB::sysApplElmtRunIndex for some
            row in the appropriate tables.
 *
 * Attributes:
 *   accessible 1     isscalar 0     enums  0      hasdefval 0
 *   readable   1     iscolumn 1     ranges 0      hashint   0
 *   settable   0
 *
 *
 * Its syntax is UNSIGNED32 (based on perltype UNSIGNED32)
 * The net-snmp type is ASN_UNSIGNED. The C type decl is u_long (u_long)
 */

/**
 * Extract the current value of the tcpListenerProcess data.
 *
 * Set a value using the data context for the row.
 *
 * @param rowreq_ctx
 *        Pointer to the row request context.
 * @param tcpListenerProcess_val_ptr
 *        Pointer to storage for a u_long variable
 *
 * @retval MFD_SUCCESS         : success
 * @retval MFD_SKIP            : skip this node (no value for now)
 * @retval MFD_ERROR           : Any other error
 */
int tcpListenerProcess_get (tcpListenerTable_rowreq_ctx * rowreq_ctx, u_long * tcpListenerProcess_val_ptr)
{

   /** we should have a non-NULL pointer */
    netsnmp_assert (NULL != tcpListenerProcess_val_ptr);


    DEBUGMSGTL (("verbose:tcpListenerTable:tcpListenerProcess_get", "called\n"));

    netsnmp_assert (NULL != rowreq_ctx);

    /*
     * TODO:231:o: |-> Extract the current value of the tcpListenerProcess data.
     * copy (* tcpListenerProcess_val_ptr ) from rowreq_ctx->data
     */
    (*tcpListenerProcess_val_ptr) = rowreq_ctx->data->pid;

    return MFD_SUCCESS;
}                                /* tcpListenerProcess_get */



/** @} */

/** @} */

/** @{ */
