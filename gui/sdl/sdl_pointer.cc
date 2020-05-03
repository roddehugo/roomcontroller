#include "sdl_pointer.hh"

SdlPointer::SdlPointer(EventDelegate * ed, int zoom)
    : event_delegate_(ed)
    , zoom_(zoom)
{
    lv_indev_drv_init(&indev_drv_);
    indev_drv_.type = LV_INDEV_TYPE_POINTER;
    indev_drv_.read_cb = &SdlPointer::mouse_read;
    indev_drv_.user_data = this;
    lv_indev_drv_register(&indev_drv_);
}

void SdlPointer::enable()
{
}

void SdlPointer::disable()
{
}

void SdlPointer::attach(EventDelegate *ed)
{
    event_delegate_ = ed;
}

bool SdlPointer::mouse_read(lv_indev_drv_t * drv, lv_indev_data_t * data)
{
    auto & self = *static_cast<SdlPointer *>(drv->user_data);
    data->point.x = self.last_x_;
    data->point.y = self.last_y_;
    data->state = self.last_touch_ ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    // Points are not buffered, so no more data to read.
    return false;
}

bool SdlPointer::read(int & x, int & y) const
{
    x = last_x_;
    y = last_y_;
    return last_touch_;
}

void SdlPointer::handle(int timeout_ms)
{
    static uint32_t last_event_ms = 0;
    SDL_Event event;
    while (1)
    {
        int to = last_event_ms - SDL_GetTicks() + timeout_ms;
        if (SDL_WaitEventTimeout(&event, to > 0 ? to : 0))
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                last_event_ms = SDL_GetTicks();
                last_touch_ = true;
                last_x_ = event.button.x / zoom_;
                last_y_ = event.button.y / zoom_;
                break; // Touch down handled.
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                last_touch_ = false;
                // No break, wait for next timeout.
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                last_x_ = event.motion.x / zoom_;
                last_y_ = event.motion.y / zoom_;
                // No break, wait for next timeout.
            }
            else if (event_delegate_
                    && (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                    && ((event.key.keysym.sym >= 'a'
                                && event.key.keysym.sym <= 'z')
                            || (event.key.keysym.sym >= '0'
                                    && event.key.keysym.sym <= '9')))
            {
                event_delegate_->on(event.key.keysym.sym, event.key.state);
                // No break, not concerning touch, directly report to delegate.
            }
        }
        else
        {
            last_event_ms = SDL_GetTicks();
            break; // Timed out, do not block.
        }
    }
}
