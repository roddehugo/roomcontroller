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

namespace gui
{

lv_obj_t * Object::get() const
{
    return obj_;
}

lv_obj_t * Object::set(lv_obj_t * o)
{
    if (o != nullptr)
        obj_ = o;
    return o;
}

Screen::Screen()
{
    obj_ = lv_scr_act();
}

} // namespace gui
