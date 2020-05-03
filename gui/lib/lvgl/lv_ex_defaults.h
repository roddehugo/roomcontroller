#ifndef LV_EX_DEFAULTS_H
#define LV_EX_DEFAULTS_H

/* clang-format off */

/*==================
 * General settings
 *==================*/

#ifndef LV_EX_PRINTF
#  define LV_EX_PRINTF          0
#endif

#ifndef LV_EX_KEYBOARD
#  define LV_EX_KEYBOARD        0
#endif

#ifndef LV_EX_MOUSEWHEEL
#  define LV_EX_MOUSEWHEEL      0
#endif

/*===============
 * Test settings
 *===============*/

#ifndef LV_USE_TESTS
#  define LV_USE_TESTS          0
#endif

/*===================
 * Tutorial settings
 *===================*/

#ifndef LV_USE_TUTORIALS
#  define LV_USE_TUTORIALS      0
#endif

/*======================
 * Application settings
 *======================*/

#ifndef LV_USE_BENCHMARK
#  define LV_USE_BENCHMARK      0
#endif

#ifndef LV_USE_DEMO
#  define LV_USE_DEMO           0
#endif

#if LV_USE_DEMO
#  ifndef LV_DEMO_WALLPAPER
#    define LV_DEMO_WALLPAPER   0
#  endif
#  ifndef LV_DEMO_SLIDE_SHOW
#    define LV_DEMO_SLIDE_SHOW  0
#  endif
#endif

#ifndef LV_USE_SYSMON
#  define LV_USE_SYSMON         0
#endif

#ifndef LV_USE_TERMINAL
#  define LV_USE_TERMINAL       0
#endif

#ifndef LV_USE_TPCAL
#  define LV_USE_TPCAL          0
#endif

#endif /* LV_EX_DEFAULTS_H */
