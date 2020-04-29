#include "gui.hh"
#include "lvgl/lvgl.h"

#include <fstream>
#include <iostream>


int main(int argc, const char ** argv)
{
    lv_init();

    SdlDisplay display(LV_HOR_RES, LV_VER_RES);
    SdlPointer pointer;
    Gui gui(display, pointer);
    return gui.loop();
}
