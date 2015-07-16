#ifndef WM8785_H_INCLUDED
#define WM8785_H_INCLUDED

#define WM8785_R0    0
#define WM8785_R1    1
#define WM8785_R2    2
#define WM8785_R7    7

/* R0 */
#define WM8785_MCR_MASK        0x007
#define WM8785_MCR_SLAVE    0x000
#define WM8785_MCR_MASTER_128    0x001
#define WM8785_MCR_MASTER_192    0x002
#define WM8785_MCR_MASTER_256    0x003
#define WM8785_MCR_MASTER_384    0x004
#define WM8785_MCR_MASTER_512    0x005
#define WM8785_MCR_MASTER_768    0x006
#define WM8785_OSR_MASK        0x018
#define WM8785_OSR_SINGLE    0x000
#define WM8785_OSR_DOUBLE    0x008
#define WM8785_OSR_QUAD        0x010
#define WM8785_FORMAT_MASK    0x060
#define WM8785_FORMAT_RJUST    0x000
#define WM8785_FORMAT_LJUST    0x020
#define WM8785_FORMAT_I2S    0x040
#define WM8785_FORMAT_DSP    0x060
/* R1 */
#define WM8785_WL_MASK        0x003
#define WM8785_WL_16        0x000
#define WM8785_WL_20        0x001
#define WM8785_WL_24        0x002
#define WM8785_WL_32        0x003
#define WM8785_LRP        0x004
#define WM8785_BCLKINV        0x008
#define WM8785_LRSWAP        0x010
#define WM8785_DEVNO_MASK    0x0e0
/* R2 */
#define WM8785_HPFR        0x001
#define WM8785_HPFL        0x002
#define WM8785_SDODIS        0x004
#define WM8785_PWRDNR        0x008
#define WM8785_PWRDNL        0x010
#define WM8785_TDM_MASK        0x1c0

#endif