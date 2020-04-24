#include "gui.hh"
#include "lvgl/lvgl.h"

#include <fstream>
#include <iostream>

#ifndef MONITOR_ZOOM
#define MONITOR_ZOOM 1
#endif

int main(int argc, const char ** argv)
{
    lv_init();

    SdlDisplay display(LV_HOR_RES, LV_VER_RES, MONITOR_ZOOM);
    SdlPointer pointer(MONITOR_ZOOM);
    Gui gui(display, pointer);
    return gui.loop();
}
