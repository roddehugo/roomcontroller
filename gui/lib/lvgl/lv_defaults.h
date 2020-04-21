#ifndef LV_DEFAULTS_H
#define LV_DEFAULTS_H

/*===============
 * Feature usage
 *===============*/

/* Enable animations. */
#ifndef LV_USE_ANIMATION
#  define LV_USE_ANIMATION              0
#endif

/* Enable shadow drawing. */
#ifndef LV_USE_SHADOW
#  define LV_USE_SHADOW                 0
#endif

/* Enable object groups. */
#ifndef LV_USE_GROUP
#  define LV_USE_GROUP                  0
#endif

/* Enable GPU interface. */
#ifndef LV_USE_GPU
#  define LV_USE_GPU                    0
#endif

/* Enable file system. */
#ifndef LV_USE_FILESYSTEM
#  define LV_USE_FILESYSTEM             0
#endif

/* Enable user data to drivers and objects. */
#ifndef LV_USE_USER_DATA
#  define LV_USE_USER_DATA              0
#endif

/*==============
 * Log settings
 *==============*/

#ifndef LV_USE_LOG
#  define LV_USE_LOG                    0
#endif

#if LV_USE_LOG
#  ifndef LV_LOG_LEVEL
#    define LV_LOG_LEVEL                LV_LOG_LEVEL_WARN
#  endif
#  ifndef LV_LOG_PRINTF
#    define LV_LOG_PRINTF               1
#  endif
#endif

/*================
 * Debug settings
 *================*/

#ifndef LV_USE_DEBUG
#  define LV_USE_DEBUG                  0
#endif

#ifndef LV_USE_SLOW_DEBUG
#  define LV_USE_SLOW_DEBUG             0
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
#  define LV_USE_BIDI                   0
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
#  define LV_USE_ARC                    0
#endif

/* Bar (dependencies: -). */
#ifndef LV_USE_BAR
#  define LV_USE_BAR                    0
#endif

/* Button (dependencies: lv_cont). */
#ifndef LV_USE_BTN
#  define LV_USE_BTN                    0
#endif

/* Button matrix (dependencies: -). */
#ifndef LV_USE_BTNM
#  define LV_USE_BTNM                   0
#endif

/* Calendar (dependencies: -). */
#ifndef LV_USE_CALENDAR
#  define LV_USE_CALENDAR               0
#endif

/* Canvas (dependencies: lv_img). */
#ifndef LV_USE_CANVAS
#  define LV_USE_CANVAS                 0
#endif

/* Check box (dependencies: lv_btn, lv_label). */
#ifndef LV_USE_CB
#  define LV_USE_CB                     0
#endif

/* Chart (dependencies: -). */
#ifndef LV_USE_CHART
#  define LV_USE_CHART                  0
#endif

/* Container (dependencies: -). */
#ifndef LV_USE_CONT
#  define LV_USE_CONT                   0
#endif

/* Color picker (dependencies: -). */
#ifndef LV_USE_CPICKER
#  define LV_USE_CPICKER                0
#endif

/* Drop down list (dependencies: lv_page, lv_label, lv_symbol_def.h). */
#ifndef LV_USE_DDLIST
#  define LV_USE_DDLIST                 0
#endif

/* Gauge (dependencies:lv_bar, lv_lmeter). */
#ifndef LV_USE_GAUGE
#  define LV_USE_GAUGE                  0
#endif

/* Image (dependencies: lv_label). */
#ifndef LV_USE_IMG
#  define LV_USE_IMG                    0
#endif

/* Image Button (dependencies: lv_btn). */
#ifndef LV_USE_IMGBTN
#  define LV_USE_IMGBTN                 0
#endif

/* Keyboard (dependencies: lv_btnm). */
#ifndef LV_USE_KB
#  define LV_USE_KB                     0
#endif

/* Label (dependencies: -). */
#ifndef LV_USE_LABEL
#  define LV_USE_LABEL                  0
#endif

/* LED (dependencies: -). */
#ifndef LV_USE_LED
#  define LV_USE_LED                    0
#endif

/* Line (dependencies: -). */
#ifndef LV_USE_LINE
#  define LV_USE_LINE                   0
#endif

/* List (dependencies: lv_page, lv_btn, lv_label, lv_img). */
#ifndef LV_USE_LIST
#  define LV_USE_LIST                   0
#endif

/* Line meter (dependencies: -). */
#ifndef LV_USE_LMETER
#  define LV_USE_LMETER                 0
#endif

/* Message box (dependencies: lv_rect, lv_btnm, lv_label). */
#ifndef LV_USE_MBOX
#  define LV_USE_MBOX                   0
#endif

/* Page (dependencies: lv_cont). */
#ifndef LV_USE_PAGE
#  define LV_USE_PAGE                   0
#endif

/* Preload (dependencies: lv_arc, lv_anim). */
#ifndef LV_USE_PRELOAD
#  define LV_USE_PRELOAD                0
#endif

/* Roller (dependencies: lv_ddlist). */
#ifndef LV_USE_ROLLER
#  define LV_USE_ROLLER                 0
#endif

/* Slider (dependencies: lv_bar). */
#ifndef LV_USE_SLIDER
#  define LV_USE_SLIDER                 0
#endif

/* Spinbox (dependencies: lv_ta). */
#ifndef LV_USE_SPINBOX
#  define LV_USE_SPINBOX                0
#endif

/* Switch (dependencies: lv_slider). */
#ifndef LV_USE_SW
#  define LV_USE_SW                     0
#endif

/* Text area (dependencies: lv_label, lv_page). */
#ifndef LV_USE_TA
#  define LV_USE_TA                     0
#endif

/* Table (dependencies: lv_label). */
#ifndef LV_USE_TABLE
#  define LV_USE_TABLE                  0
#endif

/* Tab (dependencies: lv_page, lv_btnm). */
#ifndef LV_USE_TABVIEW
#  define LV_USE_TABVIEW                0
#endif

/* Tileview (dependencies: lv_page). */
#ifndef LV_USE_TILEVIEW
#  define LV_USE_TILEVIEW               0
#endif

/* Window (dependencies: lv_cont, lv_btn, lv_label, lv_img, lv_page). */
#ifndef LV_USE_WIN
#  define LV_USE_WIN                    0
#endif

/*=================
 * Drivers
 *=================*/

/* Enable monitor of PC using SDL. */
#ifndef USE_MONITOR
#  define USE_MONITOR                   0
#endif

#if USE_MONITOR
#  ifndef MONITOR_ZOOM
#    define MONITOR_ZOOM                1
#  endif
#  ifndef MONITOR_DOUBLE_BUFFERED
#    define MONITOR_DOUBLE_BUFFERED     0
#  endif
#  ifndef MONITOR_VIRTUAL_MACHINE
#    define MONITOR_VIRTUAL_MACHINE     0
#  endif
#  ifndef MONITOR_DUAL
#    define MONITOR_DUAL                0
#  endif
#endif

/* Mouse or touchpad on PC using SDL. */
#ifndef USE_MOUSE
#  define USE_MOUSE                     0
#endif

/* Mousewheel as encoder on PC using SDL. */
#ifndef USE_MOUSEWHEEL
#  define USE_MOUSEWHEEL                0
#endif

/* Keyboard of a PC using SDL. */
#ifndef USE_KEYBOARD
#  define USE_KEYBOARD                  0
#endif

/* Enable native Windows with mouse. */
#ifndef USE_WINDOWS
#  define USE_WINDOWS                   0
#endif

/* Enable SSD1963. */
#ifndef USE_SSD1963
#  define USE_SSD1963                   0
#endif

/* Enable R61581. */
#ifndef USE_R61581
#  define USE_R61581                    0
#endif

/* Enable ST7565. */
#ifndef USE_ST7565
#  define USE_ST7565                    0
#endif

/* Enable UC1610. */
#ifndef USE_UC1610
#  define USE_UC1610                    0
#endif

/* SHARP memory in pixel monochrome display series. */
#ifndef USE_SHARP_MIP
#  define USE_SHARP_MIP                 0
#endif

/* Linux frame buffer device. */
#ifndef USE_FBDEV
#  define USE_FBDEV                     0
#endif

/* FreeBSD frame buffer device. */
#ifndef USE_BSD_FBDEV
#  define USE_BSD_FBDEV                 0
#endif

/* Enable XPT2046. */
#ifndef USE_XPT2046
#  define USE_XPT2046                   0
#endif

/* Enable FT5406EE8. */
#ifndef USE_FT5406EE8
#  define USE_FT5406EE8                 0
#endif

/* Enable AD TOUCH. */
#ifndef USE_AD_TOUCH
#  define USE_AD_TOUCH                  0
#endif

/* Touchscreen as libinput interface for Linux. */
#ifndef USE_LIBINPUT
#  define USE_LIBINPUT                  0
#endif

/* Mouse or touchpad as evdev interface for Linux. */
#ifndef USE_EVDEV
#  define USE_EVDEV                     0
#endif

#endif /* LV_DEFAULTS_H */
