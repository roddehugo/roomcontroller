#include "gui.hh"
#include "logger.hh"
#include "lvgl/lvgl.h"

#include <fstream>
#include <iostream>

#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

int main(int argc, const char ** argv)
{
    lv_log_register_print_cb(&Logger::log);
    lv_init();

    int width = LV_HOR_RES;
    assertm(width <= LV_HOR_RES_MAX, "width is greater than LV_HOR_RES_MAX");
    int height = LV_VER_RES;
    assertm(height <= LV_VER_RES_MAX, "height is greater than LV_VER_RES_MAX");
    linfo("app width=%3d, height=%3d", width, height);

    SdlDisplay display(width, height);
    SdlPointer pointer;

    gui::Screen screen;

    Gui gui(display, pointer);
    return gui.loop();
}
