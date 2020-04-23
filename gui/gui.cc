#include "gui.hh"

#ifndef MONITOR_ZOOM
#    define MONITOR_ZOOM 1
#endif

Gui::Gui(SdlDisplay & d, SdlPointer & p)
    : display_(d)
    , pointer_(p)
{
}

int Gui::loop()
{
    display_.enable();
    pointer_.enable();
    while (display_.running())
    {
        // Redraw display.
        display_.refresh();
        // Handle events, with timeout.
        pointer_.handle();
        // Handle LittlevGL task.
        lv_task_handler();
    }
    return 0;
}

int main(int argc, const char ** argv)
{
    lv_init();

    SdlDisplay display(LV_HOR_RES, LV_VER_RES, MONITOR_ZOOM);
    SdlPointer pointer(MONITOR_ZOOM);

    Gui gui(display, pointer);

    return gui.loop();
}
