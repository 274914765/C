
/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.check_values.conf $
 */
#ifndef IPCIDRROUTETABLE_CHECKFNS_H
#define IPCIDRROUTETABLE_CHECKFNS_H

/*
 * these functions are designed to check incoming values for 
 * columns in the ipCidrRouteTable table for legality with respect to 
 * datatype and value.
 */

int check_ipCidrRouteIfIndex (int type, long *val, size_t val_len);

int check_ipCidrRouteType (int type, long *val, size_t val_len);

int check_ipCidrRouteInfo (int type, oid * val, size_t val_len);

int check_ipCidrRouteNextHopAS (int type, long *val, size_t val_len);

int check_ipCidrRouteMetric1 (int type, long *val, size_t val_len);

int check_ipCidrRouteMetric2 (int type, long *val, size_t val_len);

int check_ipCidrRouteMetric3 (int type, long *val, size_t val_len);

int check_ipCidrRouteMetric4 (int type, long *val, size_t val_len);

int check_ipCidrRouteMetric5 (int type, long *val, size_t val_len);

int check_ipCidrRouteStatus (int type, long *val, size_t val_len);

#endif                            /* IPCIDRROUTETABLE_CHECKFNS_H */
