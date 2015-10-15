
/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */
#ifndef SNMPTLSTMCERTTOTSN_TABLE_H
#define SNMPTLSTMCERTTOTSN_TABLE_H

#define SNMP_TLS_TM_CERT_COUNT   SNMP_TLS_TM_BASE, 2, 2, 1, 1
#define SNMP_TLS_TM_CERT_CHANGED SNMP_TLS_TM_BASE, 2, 2, 1, 2
#define SNMP_TLS_TM_CERT_TABLE   SNMP_TLS_TM_BASE, 2, 2, 1, 3

/*
 * function declarations 
 */
void init_snmpTlstmCertToTSNTable (void);

void init_snmpTlstmCertToTSNTable_context (const char *);

/*
 * index definitions for table tlstmCertToTSNTable 
 */

/*
 * column number definitions for table tlstmCertToTSNTable 
 */
#define COL_SNMPTLSTMCERTTOTSN_ID                       1
#define COL_SNMPTLSTMCERTTOTSN_FINGERPRINT              2
#define COL_SNMPTLSTMCERTTOTSN_MAPTYPE                  3
#define COL_SNMPTLSTMCERTTOTSN_DATA                     4
#define COL_SNMPTLSTMCERTTOTSN_STORAGETYPE              5
#define COL_SNMPTLSTMCERTTOTSN_ROWSTATUS                6

#define SNMPTLSTMCERTTOTSN_TABLE_MIN_COL COL_SNMPTLSTMCERTTOTSN_FINGERPRINT
#define SNMPTLSTMCERTTOTSN_TABLE_MAX_COL COL_SNMPTLSTMCERTTOTSN_ROWSTATUS

#define SNMPTLSTMCERTTOTSN_FINGERPRINT_MAX_SIZE          255
#define SNMPTLSTMCERTTOTSN_MAPTYPE_MAX_SIZE              128
#define SNMPTLSTMCERTTOTSN_DATA_MAX_SIZE                 1024

#define TSNM_tlstmCertSpecified                 1
#define TSNM_tlstmCertSANRFC822Name             2
#define TSNM_tlstmCertSANDNSName                3
#define TSNM_tlstmCertSANIpAddress              4
#define TSNM_tlstmCertSANAny                    5
#define TSNM_tlstmCertCommonName                6
#define TSNM_tlstmCert_MAX                      TSNM_tlstmCertCommonName

#endif                            /* SNMPTLSTMCERTTOTSN_TABLE_H */