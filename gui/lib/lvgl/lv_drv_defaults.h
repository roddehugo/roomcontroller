#ifndef LV_DRV_DEFAULTS_H
#define LV_DRV_DEFAULTS_H

/* clang-format off */

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

#endif /* LV_DRV_DEFAULTS_H */
