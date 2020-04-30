#include "gui.hh"

#include "logger.hh"

Gui::Gui(SdlDisplay & d, SdlPointer & p, gui::Screen & s)
    : display_(d)
    , pointer_(p)
    , screen_(s)
{
    pointer_.attach(this);
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

void Gui::on(const char key, bool pressed)
{
    switch (key)
    {
        case 'b':
        {
            auto * s = screen_.style();
            int width = s->body.border.width;
            if (pressed && !width)
            {
                s->body.border.color = LV_COLOR_RED;
                s->body.border.width = 1;
                lv_obj_report_style_mod(s);
            }
            else if (!pressed && width)
            {
                auto * theme = lv_theme_get_current();
                auto * def = theme->style.bg;
                s->body.border.color = def->body.border.color;
                s->body.border.width = def->body.border.width;
                lv_obj_report_style_mod(s);
            }
            break;
        }
        default:
            /* ltrace("event key='%c' pressed=%d", key, pressed); */
            break;
    }
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
    auto * theme = lv_theme_default_init(0, nullptr);
    lv_theme_set_current(theme);

    lv_style_copy(&style_, theme->style.bg);

    obj_ = lv_cont_create(nullptr, nullptr);
    lv_cont_set_style(obj_, LV_CONT_STYLE_MAIN, &style_);
    lv_cont_set_layout(obj_, LV_LAYOUT_COL_M);
    lv_scr_load(obj_);
}

lv_style_t * Screen::style()
{
    return &style_;
}

} // namespace gui
