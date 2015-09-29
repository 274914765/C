
/*
 * Note: this file originally auto-generated by mib2c using
 *  $
 */
#ifndef SCTPLOOKUPLOCALPORTTABLE_H
#define SCTPLOOKUPLOCALPORTTABLE_H

#include "sctpTables_common.h"

/*
 * function declarations 
 */
void init_sctpLookupLocalPortTable (void);

void shutdown_sctpLookupLocalPortTable (void);

void initialize_table_sctpLookupLocalPortTable (void);

void shutdown_table_sctpLookupLocalPortTable (void);

Netsnmp_Node_Handler sctpLookupLocalPortTable_handler;

/*
 * column number definitions for table sctpLookupLocalPortTable 
 */
#define COLUMN_SCTPLOOKUPLOCALPORTSTARTTIME     1

/** Typical data structure for a row entry */
#define SCTP_LOOKUP_LOCAL_PORT_TABLE_INDEX_SIZE 100
struct sctpLookupLocalPortTable_entry_s
{
    netsnmp_index oid_index;
    oid oid_tmp[SCTP_LOOKUP_LOCAL_PORT_TABLE_INDEX_SIZE];

    /*
     * Index values 
     */
    u_long sctpAssocLocalPort;
    u_long sctpAssocId;

    /*
     * Column values 
     */
    u_long sctpLookupLocalPortStartTime;

    int valid;
};

sctpLookupLocalPortTable_entry *sctpLookupLocalPortTable_entry_create (void);

int sctpLookupLocalPortTable_entry_update_index (sctpLookupLocalPortTable_entry * entry);

void sctpLookupLocalPortTable_entry_copy (sctpLookupLocalPortTable_entry * from, sctpLookupLocalPortTable_entry * to);

void sctpLookupLocalPortTable_entry_free (sctpLookupLocalPortTable_entry * entry);

void sctpLookupLocalPortTable_container_clear (netsnmp_container * container);

#endif                            /* SCTPLOOKUPLOCALPORTTABLE_H */
