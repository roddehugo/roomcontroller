#ifndef LV_DRV_CONF_H
#define LV_DRV_CONF_H
/* clang-format off */

/*=================
 * Driver settings
 *=================*/

#if !USE_MONITOR
#  error "USE_MONITOR is expected to be true"
#endif

/*==================
 * Default settings
 *==================*/

/* Be sure every unset define is defined disabled by default. */
#include "lv_drv_defaults.h"

#endif /* LV_DRV_CONF_H */
