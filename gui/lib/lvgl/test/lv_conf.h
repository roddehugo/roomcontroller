#ifndef LV_CONF_H
#define LV_CONF_H
/* clang-format off */

#include <stdint.h>

/*====================
 * Graphical settings
 *====================*/

/* Maximal horizontal and vertical resolution to support by the library.*/
#define LV_HOR_RES_MAX          (480)
#define LV_VER_RES_MAX          (320)

/* Color depth:
 * - 1:  1 byte per pixel
 * - 8:  RGB233
 * - 16: RGB565
 * - 32: ARGB8888
 */
#define LV_COLOR_DEPTH          32

/*=================
 * User data types
 *=================*/

/* Type of coordinates. */
typedef int16_t lv_coord_t;
/* Type of the user data of animations. */
typedef void * lv_anim_user_data_t;
/* Type of the user data of groups. */
typedef void * lv_group_user_data_t;
/* Type of the user data of file system drivers. */
typedef void * lv_fs_drv_user_data_t;
/* Type of the user data of image decoder. */
typedef void * lv_img_decoder_user_data_t;
/* Type of user data in the display driver. */
typedef void * lv_disp_drv_user_data_t;
/* Type of user data in the input device driver. */
typedef void * lv_indev_drv_user_data_t;
/* Type of the user data of fonts. */
typedef void * lv_font_user_data_t;
/* Type of the user data of object. */
typedef void * lv_obj_user_data_t;

/*==================
 * Default settings
 *==================*/

/* Be sure every define has a default value. */
#include "lvgl/src/lv_conf_checker.h"

#endif /* LV_CONF_H */
