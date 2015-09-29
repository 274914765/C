
/*
 *Copyright(c)2004,Cisco URP imburses and Network Information Center in Beijing University of Posts and Telecommunications researches.
 *
 *All right reserved
 *
 *File Name: expExpressionTable.h
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


#ifndef _MIBGROUP_EXPEXPRESSIONTABLE_H
#define _MIBGROUP_EXPEXPRESSIONTABLE_H

/*
 * we may use header_complex from the header_complex module 
 */


config_require (header_complex)
    /*
     * our storage structure(s) 
     */
     struct expExpressionTable_data
     {

         /*
          * expExpressionTable
          */
         char *expExpressionOwner;
         size_t expExpressionOwnerLen;
         char *expExpressionName;
         size_t expExpressionNameLen;
         char *expExpression;
         size_t expExpressionLen;
         long expExpressionValueType;
         char *expExpressionComment;
         size_t expExpressionCommentLen;
         long expExpressionDeltaInterval;
         oid *expExpressionPrefix;
         size_t expExpressionPrefixLen;
         unsigned long expExpressionErrors;
         long expExpressionEntryStatus;

         /*
          * expError Table 
          */
         unsigned long expErrorTime;
         long expErrorIndex;
         long expErrorCode;
         oid *expErrorInstance;
         size_t expErrorInstanceLen;

         /*
          * internal variables 
          */
         int storageType;

         /*
          * other tables storage
          */
         struct header_complex_index *hc_ObjectTableStorage;
         struct header_complex_index *hc_ValueTableStorage;



         /*
          * pdu auth contents 
          */
         long have_copied_auth_info;
         long pdu_version;
         long pdu_securityModel;
         long pdu_securityLevel;
         void *pdu_transport;
         size_t pdu_transportLen;
         const oid *pdu_tDomain;
         size_t pdu_tDomainLen;
         u_char *pdu_community;
         size_t pdu_community_len;
         char *pdu_contextName;
         size_t pdu_contextNameLen;
         char *pdu_securityName;
         size_t pdu_securityNameLen;
     };



#define EXPEXPRESSION_COUNTER32      1
#define EXPEXPRESSION_UNSIGNED32        2
#define EXPEXPRESSION_TIMETICKS         3
#define EXPEXPRESSION_INTEGER32  4
#define EXPEXPRESSION_IPADDRESS      5
#define EXPEXPRESSION_OCTETSTRING 6
#define EXPEXPRESSION_OBJECTID            7
#define EXPEXPRESSION_COUNTER64           8


#define EXP_FAILURE_INVALIDSYNTAX        1
#define EXP_FAILURE_UNDEFINEOBJECTINDEX        2
#define EXP_FAILURE_UNRECOGNIZEOPERATOR    3
#define EXP_FAILURE_UNRECOGNIZEDFUNCTION            4
#define EXP_FAILURE_INVALIDOPERANDTYPE        5
#define EXP_FAILURE_UNMATCHEDPARENTHESIS        6
#define EXP_FAILURE_TOOMANYWILDCARDVALUES    7
#define EXP_FAILURE_RECURSION            8
#define EXP_FAILURE_DELTATOOSHORT              9
#define EXP_FAILURE_RESOURCEUNAVAILABLE        10
#define EXP_FAILURE_DIVIDEBYZERO        11


/*
 * function prototypes 
 */


     void init_expExpressionTable (void);

     FindVarMethod var_expExpressionTable;

     SNMPCallback store_expExpressionTable;

     void parse_expExpressionTable (const char *, char *);

     WriteMethod write_expExpression;

     WriteMethod write_expExpressionValueType;

     WriteMethod write_expExpressionComment;

     WriteMethod write_expExpressionDeltaInterval;

     WriteMethod write_expExpressionEntryStatus;





#endif                            /*_MIBGROUP_EXPEXPRESSIONTABLE_H */
