#pragma once

#include <SDL2/SDL.h>
#include <lvgl/lvgl.h>

class SdlPointer
{
  public:
    /// Events delegate.
    struct EventDelegate
    {
        virtual ~EventDelegate(){};
        virtual void on(const char key, bool pressed){};
    };

  public:
    /// Constructor.
    SdlPointer(EventDelegate * ed = nullptr, int zoom = 1);
    /// Enable driver.
    void enable();
    /// Disable driver.
    void disable();
    /// Attach an event delegate. Or detach if no pointer.
    void attach(EventDelegate * ed = nullptr);
    /// Handle events.
    void handle(int timeout_ms = 33);
    /// Read last event, return last touch state.
    bool read(int & x, int & y) const;
    /// Callback for LittlevGL.
    static bool mouse_read(lv_indev_drv_t * drv, lv_indev_data_t * data);

  protected:
    /// Event binder.
    EventDelegate * event_delegate_;
    /// Zoom factor.
    int zoom_;
    /// Last coordinates.
    int last_x_ = 0, last_y_ = 0;
    /// Last touch state.
    bool last_touch_ = false;
    /// LittlevGL input driver.
    lv_indev_drv_t indev_drv_;
};
