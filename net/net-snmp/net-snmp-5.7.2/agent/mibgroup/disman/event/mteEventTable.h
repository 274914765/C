
/*
 * Note: this file originally auto-generated by mib2c using
 *  : mib2c.table_data.conf,v 1.8 2005/07/19 14:52:03 dts12 Exp $
 */
#ifndef MTEEVENTTABLE_H
#define MTEEVENTTABLE_H

/*
 * function declarations 
 */
void init_mteEventTable (void);

void shutdown_mteEventTable (void);

Netsnmp_Node_Handler mteEventTable_handler;

/*
 * column number definitions for mteEventTable 
 */
#define COLUMN_MTEEVENTNAME        1
#define COLUMN_MTEEVENTCOMMENT        2
#define COLUMN_MTEEVENTACTIONS        3
#define COLUMN_MTEEVENTENABLED        4
#define COLUMN_MTEEVENTENTRYSTATUS    5
#endif                            /* MTEEVENTTABLE_H */
