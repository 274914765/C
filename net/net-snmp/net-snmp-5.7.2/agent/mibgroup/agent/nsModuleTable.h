
/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.iterate.conf,v 1.5 2001/12/04 21:36:27 hardaker Exp $
 */
#ifndef NSMODULETABLE_H
#define NSMODULETABLE_H

/*
 * function declarations 
 */
void init_nsModuleTable (void);

void initialize_table_nsModuleTable (void);

Netsnmp_Node_Handler nsModuleTable_handler;

Netsnmp_First_Data_Point nsModuleTable_get_first_data_point;

Netsnmp_Next_Data_Point nsModuleTable_get_next_data_point;

/*
 * column number definitions for table nsModuleTable 
 */
#define COLUMN_NSMCONTEXTNAME        1
#define COLUMN_NSMREGISTRATIONPOINT    2
#define COLUMN_NSMREGISTRATIONPRIORITY    3
#define COLUMN_NSMODULENAME        4
#define COLUMN_NSMODULEMODES        5
#define COLUMN_NSMODULETIMEOUT        6
#endif                            /* NSMODULETABLE_H */
