#ifndef LV_DEFAULTS_H
#define LV_DEFAULTS_H

/* clang-format off */

/*===============
 * Feature usage
 *===============*/

/* Enable animations. */
#ifndef LV_USE_ANIMATION
#  define LV_USE_ANIMATION              1
#endif

/* Enable shadow drawing. */
#ifndef LV_USE_SHADOW
#  define LV_USE_SHADOW                 1
#endif

/* Enable object groups. */
#ifndef LV_USE_GROUP
#  define LV_USE_GROUP                  1
#endif

/* Enable GPU interface. */
#ifndef LV_USE_GPU
#  define LV_USE_GPU                    1
#endif

/* Enable file system. */
#ifndef LV_USE_FILESYSTEM
#  define LV_USE_FILESYSTEM             1
#endif

/* Enable user data to drivers and objects. */
#ifndef LV_USE_USER_DATA
#  define LV_USE_USER_DATA              1
#endif

/*==============
 * Log settings
 *==============*/

#ifndef LV_USE_LOG
#  define LV_USE_LOG                    1
#endif

#if LV_USE_LOG
#  ifndef LV_LOG_LEVEL
#    define LV_LOG_LEVEL                LV_LOG_LEVEL_INFO
#  endif
#  ifndef LV_LOG_PRINTF
#    define LV_LOG_PRINTF               1
#  endif
#endif

/*================
 * Debug settings
 *================*/

#ifndef LV_USE_DEBUG
#  define LV_USE_DEBUG                  1
#endif

#ifndef LV_USE_SLOW_DEBUG
#  define LV_USE_SLOW_DEBUG             1
#endif

#if LV_USE_DEBUG
#  ifndef LV_USE_ASSERT_NULL
#    define LV_USE_ASSERT_NULL          1 /* Fast. */
#  endif
#  ifndef LV_USE_ASSERT_MEM
#    define LV_USE_ASSERT_MEM           1 /* Fast. */
#  endif
#  ifndef LV_USE_ASSERT_STYLE
#    define LV_USE_ASSERT_STYLE         1 /* Fast. */
#  endif
#  if LV_USE_SLOW_DEBUG
#    ifndef LV_USE_ASSERT_STR
#      define LV_USE_ASSERT_STR         1 /* Slow. */
#    endif
#    ifndef LV_USE_ASSERT_OBJ
#      define LV_USE_ASSERT_OBJ         1 /* Slow. */
#    endif
#  endif
#endif

/*=================
 * Text settings
 *=================*/

/* Support bidirectional texts. */
#ifndef LV_USE_BIDI
#  define LV_USE_BIDI                   1
#endif

/*================
 * Theme settings
 *================*/

/* Built-in styles. */
#ifndef LV_USE_THEME_DEFAULT
#  define LV_USE_THEME_DEFAULT          0
#endif

/* Dark futuristic theme. */
#ifndef LV_USE_THEME_ALIEN
#  define LV_USE_THEME_ALIEN            0
#endif

/* Dark elegant theme. */
#ifndef LV_USE_THEME_NIGHT
#  define LV_USE_THEME_NIGHT            0
#endif

/* Mono color theme. */
#ifndef LV_USE_THEME_MONO
#  define LV_USE_THEME_MONO             0
#endif

/* Flat theme. */
#ifndef LV_USE_THEME_MATERIAL
#  define LV_USE_THEME_MATERIAL         0
#endif

/* Light theme. */
#ifndef LV_USE_THEME_ZEN
#  define LV_USE_THEME_ZEN              0
#endif

/* Water-like theme. */
#ifndef LV_USE_THEME_NEMO
#  define LV_USE_THEME_NEMO             0
#endif

/*===================
 * Objects settings
 *===================*/

/* Arc (dependencies: -). */
#ifndef LV_USE_ARC
#  define LV_USE_ARC                    1
#endif

/* Bar (dependencies: -). */
#ifndef LV_USE_BAR
#  define LV_USE_BAR                    1
#endif

/* Button (dependencies: lv_cont). */
#ifndef LV_USE_BTN
#  define LV_USE_BTN                    1
#endif

/* Enable button-state animations (dependencies: animation). */
#ifndef LV_BTN_INK_EFFECT
#  define LV_BTN_INK_EFFECT             1
#endif

/* Button matrix (dependencies: -). */
#ifndef LV_USE_BTNM
#  define LV_USE_BTNM                   1
#endif

/* Calendar (dependencies: -). */
#ifndef LV_USE_CALENDAR
#  define LV_USE_CALENDAR               1
#endif

/* Canvas (dependencies: lv_img). */
#ifndef LV_USE_CANVAS
#  define LV_USE_CANVAS                 1
#endif

/* Check box (dependencies: lv_btn, lv_label). */
#ifndef LV_USE_CB
#  define LV_USE_CB                     1
#endif

/* Chart (dependencies: -). */
#ifndef LV_USE_CHART
#  define LV_USE_CHART                  1
#endif

/* Define tick axis label max len to saner value:
 * 256 leads to [-Wtautological-constant-out-of-range-compare] warning. */
#ifndef LV_CHART_AXIS_TICK_LABEL_MAX_LEN
#  define LV_CHART_AXIS_TICK_LABEL_MAX_LEN    32
#endif

/* Container (dependencies: -). */
#ifndef LV_USE_CONT
#  define LV_USE_CONT                   1
#endif

/* Color picker (dependencies: -). */
#ifndef LV_USE_CPICKER
#  define LV_USE_CPICKER                1
#endif

/* Drop down list (dependencies: lv_page, lv_label, lv_symbol_def.h). */
#ifndef LV_USE_DDLIST
#  define LV_USE_DDLIST                 1
#endif

/* Gauge (dependencies:lv_bar, lv_lmeter). */
#ifndef LV_USE_GAUGE
#  define LV_USE_GAUGE                  1
#endif

/* Image (dependencies: lv_label). */
#ifndef LV_USE_IMG
#  define LV_USE_IMG                    1
#endif

/* Image Button (dependencies: lv_btn). */
#ifndef LV_USE_IMGBTN
#  define LV_USE_IMGBTN                 1
#endif

/* Keyboard (dependencies: lv_btnm). */
#ifndef LV_USE_KB
#  define LV_USE_KB                     1
#endif

/* Label (dependencies: -). */
#ifndef LV_USE_LABEL
#  define LV_USE_LABEL                  1
#endif

/* LED (dependencies: -). */
#ifndef LV_USE_LED
#  define LV_USE_LED                    1
#endif

/* Line (dependencies: -). */
#ifndef LV_USE_LINE
#  define LV_USE_LINE                   1
#endif

/* List (dependencies: lv_page, lv_btn, lv_label, lv_img). */
#ifndef LV_USE_LIST
#  define LV_USE_LIST                   1
#endif

/* Line meter (dependencies: -). */
#ifndef LV_USE_LMETER
#  define LV_USE_LMETER                 1
#endif

/* Message box (dependencies: lv_rect, lv_btnm, lv_label). */
#ifndef LV_USE_MBOX
#  define LV_USE_MBOX                   1
#endif

/* Page (dependencies: lv_cont). */
#ifndef LV_USE_PAGE
#  define LV_USE_PAGE                   1
#endif

/* Preload (dependencies: lv_arc, lv_anim). */
#ifndef LV_USE_PRELOAD
#  define LV_USE_PRELOAD                1
#endif

/* Roller (dependencies: lv_ddlist). */
#ifndef LV_USE_ROLLER
#  define LV_USE_ROLLER                 1
#endif

/* Slider (dependencies: lv_bar). */
#ifndef LV_USE_SLIDER
#  define LV_USE_SLIDER                 1
#endif

/* Spinbox (dependencies: lv_ta). */
#ifndef LV_USE_SPINBOX
#  define LV_USE_SPINBOX                1
#endif

/* Switch (dependencies: lv_slider). */
#ifndef LV_USE_SW
#  define LV_USE_SW                     1
#endif

/* Text area (dependencies: lv_label, lv_page). */
#ifndef LV_USE_TA
#  define LV_USE_TA                     1
#endif

/* Table (dependencies: lv_label). */
#ifndef LV_USE_TABLE
#  define LV_USE_TABLE                  1
#endif

/* Tab (dependencies: lv_page, lv_btnm). */
#ifndef LV_USE_TABVIEW
#  define LV_USE_TABVIEW                1
#endif

/* Tileview (dependencies: lv_page). */
#ifndef LV_USE_TILEVIEW
#  define LV_USE_TILEVIEW               1
#endif

/* Window (dependencies: lv_cont, lv_btn, lv_label, lv_img, lv_page). */
#ifndef LV_USE_WIN
#  define LV_USE_WIN                    1
#endif

#endif /* LV_DEFAULTS_H */
