
/*
 * Note: this file originally auto-generated by mib2c using
 *  : mib2c.create-dataset.conf,v 5.2 2002/07/17 14:41:53 dts12 Exp $
 */
#ifndef MTEEVENTTABLE_H
#define MTEEVENTTABLE_H

/*
 * function declarations 
 */
void init_mteEventTable (void);

void initialize_table_mteEventTable (void);

void run_mte_events (struct mteTriggerTable_data *item,
                     oid * name_oid, size_t name_oid_len, const char *eventobjowner, const char *eventobjname);


void parse_notificationEvent (const char *token, char *line);

void parse_linkUpDownNotifications (const char *token, char *line);

Netsnmp_Node_Handler mteEventTable_handler;

/*
 * column number definitions for table mteEventTable 
 */
#define COLUMN_MTEEVENTNAME        1
#define COLUMN_MTEEVENTCOMMENT        2
#define COLUMN_MTEEVENTACTIONS        3
#define COLUMN_MTEEVENTENABLED        4
#define COLUMN_MTEEVENTENTRYSTATUS        5
#endif                            /* MTEEVENTTABLE_H */
