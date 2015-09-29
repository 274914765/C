#ifndef EXP_ENUM_H
#define EXP_ENUM_H

    /* expExpressionValueType */
#define EXPVALTYPE_COUNTER    1
#define EXPVALTYPE_UNSIGNED    2
#define EXPVALTYPE_TIMETICKS    3
#define EXPVALTYPE_INTEGER    4
#define EXPVALTYPE_IPADDRESS    5
#define EXPVALTYPE_STRING    6
#define EXPVALTYPE_OID        7
#define EXPVALTYPE_COUNTER64    8

    /* expErrorCode */
#define EXPERRCODE_SYNTAX    1
#define EXPERRCODE_INDEX    2
#define EXPERRCODE_OPERATOR    3
#define EXPERRCODE_FUNCTION    4
#define EXPERRCODE_TYPE        5
#define EXPERRCODE_PARENTHESIS    6
#define EXPERRCODE_WILDCARD    7
#define EXPERRCODE_RECURSION    8
#define EXPERRCODE_DELTA    9
#define EXPERRCODE_RESOURCE    10
#define EXPERRCODE_DIVZERO    11

    /* expObjectSampleType */
#define EXPSAMPLETYPE_ABSOLUTE    1
#define EXPSAMPLETYPE_DELTA    2
#define EXPSAMPLETYPE_CHANGED    3

    /* expObjectDiscontinuityIDType */
#define EXPDISCID_TIMETICKS    1
#define EXPDISCID_TIMESTAMP    2
#define EXPDISCID_DATETIME    3

    /* expression operators (in increasing order of priority) */
    /* XXX - Check priority ordering */
#define EXP_OPERATOR_ADD    1
#define EXP_OPERATOR_SUBTRACT    2
#define EXP_OPERATOR_MULTIPLY    3
#define EXP_OPERATOR_DIVIDE    4
#define EXP_OPERATOR_REMAINDER    5
#define EXP_OPERATOR_BITXOR    6
#define EXP_OPERATOR_BITNEGATE    7
#define EXP_OPERATOR_BITOR    8
#define EXP_OPERATOR_BITAND    9
#define EXP_OPERATOR_NOT    10
#define EXP_OPERATOR_OR        11
#define EXP_OPERATOR_AND    12
#define EXP_OPERATOR_EQUAL    13
#define EXP_OPERATOR_NOTEQ    14
#define EXP_OPERATOR_LESS    15
#define EXP_OPERATOR_LESSEQ    16
#define EXP_OPERATOR_GREAT    17
#define EXP_OPERATOR_GREATEQ    18
#define EXP_OPERATOR_LSHIFT    19
#define EXP_OPERATOR_RSHIFT    20
#endif                            /* EXP_ENUM_H */
