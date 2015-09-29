
/*
 *Copyright(c)2004,Cisco URP imburses and Network Information Center in Beijing University of Posts and Telecommunications researches.
 *
 *All right reserved
 *
 *File Name:expValueTable.h
 *File Description: head file.
 *
 *Current Version:1.0
 *Author:JianShun Tong
 *Date:2004.8.20
 */

/*
 * This file was generated by mib2c and is intended for use as a mib module
 * for the ucd-snmp snmpd agent. 
 */


/*
 * we may use header_complex from the header_complex module 
 */
config_require (header_complex)
#ifndef _MIBGROUP_EXPVALUETABLE_H
#define _MIBGROUP_EXPVALUETABLE_H
     struct expValueTable_data
     {
         char *expExpressionOwner;
         size_t expExpressionOwnerLen;
         char *expExpressionName;
         size_t expExpressionNameLen;
         oid *expValueInstance;
         size_t expValueInstanceLen;
         unsigned long expValueCounter32Val;
         unsigned long expValueUnsigned32Val;
         unsigned long expValueTimeTicksVal;
         long expValueInteger32Val;
         u_long *expValueIpAddressVal;
         char *expValueOctetStringVal;
         size_t expValueOctetStringValLen;
         oid *expValueOidVal;
         size_t expValueOidValLen;
         long expValueCounter64Val;

         /* internal var */
         struct expExpressionTable_data *expression_data;
         char *valuestr;
     };


    /*
     * function prototypes 
     */
     void init_expValueTable (void);

     unsigned long get_result (char *expr);

     FindVarMethod var_expValueTable;

     int expValueTable_add (struct expExpressionTable_data
                            *expression_data, char *owner,
                            size_t owner_len, char *name, size_t name_len, oid * index, size_t index_len);

#endif                            /* _MIBGROUP_EXPVALUETABLE_H */
