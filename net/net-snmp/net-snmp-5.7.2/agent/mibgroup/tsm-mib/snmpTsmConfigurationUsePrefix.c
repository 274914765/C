
/*
 * Note: this file originally auto-generated by mib2c
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "snmpTsmConfigurationUsePrefix.h"

/** Initializes the snmpTsmConfigurationUsePrefix module */
void init_snmpTsmConfigurationUsePrefix (void)
{
    const oid snmpTsmConfigurationUsePrefix_oid[] = { 1, 3, 6, 1, 2, 1, 190, 1, 2, 1 };

    DEBUGMSGTL (("snmpTsmConfigurationUsePrefix", "Initializing\n"));

    netsnmp_register_scalar (netsnmp_create_handler_registration
                             ("snmpTsmConfigurationUsePrefix",
                              handle_snmpTsmConfigurationUsePrefix,
                              snmpTsmConfigurationUsePrefix_oid,
                              OID_LENGTH (snmpTsmConfigurationUsePrefix_oid), HANDLER_CAN_RWRITE));
}

int
handle_snmpTsmConfigurationUsePrefix (netsnmp_mib_handler * handler,
                                      netsnmp_handler_registration * reginfo,
                                      netsnmp_agent_request_info * reqinfo, netsnmp_request_info * requests)
{
    int ret;

    /*
     * We are never called for a GETNEXT if it's registered as a
     * "instance", as it's "magically" handled for us.  
     */

    /*
     * a instance handler also only hands us one request at a time, so
     * we don't need to loop over a list of requests; we'll only get one. 
     */

    long current_value = netsnmp_ds_get_boolean (NETSNMP_DS_LIBRARY_ID,
                                                 NETSNMP_DS_LIB_TSM_USE_PREFIX);

    static long original_value = 0;

    switch (reqinfo->mode)
    {

        case MODE_GET:
            if (current_value == 0)
                current_value = TV_FALSE;
            snmp_set_var_typed_value (requests->requestvb, ASN_INTEGER, &current_value, sizeof (current_value));
            break;

            /*
             * SET REQUEST
             *
             * multiple states in the transaction.  See:
             * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
             */
        case MODE_SET_RESERVE1:
            /*
             * or you could use netsnmp_check_vb_type_and_size instead 
             */
            ret = netsnmp_check_vb_type (requests->requestvb, ASN_INTEGER);
            if (ret != SNMP_ERR_NOERROR)
            {
                netsnmp_set_request_error (reqinfo, requests, ret);
            }
            if (*(requests->requestvb->val.integer) != 2 && *(requests->requestvb->val.integer) != 1)
                netsnmp_set_request_error (reqinfo, requests, SNMP_ERR_WRONGVALUE);
            original_value = current_value;
            break;

        case MODE_SET_ACTION:
            if (TV_FALSE == *(requests->requestvb->val.integer))
                netsnmp_ds_set_boolean (NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_TSM_USE_PREFIX, 0);
            else
                netsnmp_ds_set_boolean (NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_TSM_USE_PREFIX, 1);
            break;

        case MODE_SET_UNDO:
            netsnmp_ds_set_boolean (NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_TSM_USE_PREFIX, original_value);
            break;

            /* we don't need these */
        case MODE_SET_COMMIT:
        case MODE_SET_FREE:
        case MODE_SET_RESERVE2:
            break;

        default:
            /*
             * we should never get here, so this is a really bad error 
             */
            snmp_log (LOG_ERR, "unknown mode (%d) in handle_snmpTsmConfigurationUsePrefix\n", reqinfo->mode);
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}