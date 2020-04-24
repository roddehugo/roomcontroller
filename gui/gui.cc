#include "gui.hh"

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
