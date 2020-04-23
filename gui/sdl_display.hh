#pragma once

#include <SDL.h>
#include <lvgl/lvgl.h>

class SdlDisplay
{
  public:
    /// Constructor.
    SdlDisplay(int w, int h, int z = 1);
    /// Destructor.
    ~SdlDisplay();
    /// Enable driver.
    void enable();
    /// Disable driver.
    void disable();
    /// Refresh screen.
    void refresh();
    /// Is the display running?
    bool running() const;
    /// Callback for LittlevGL.
    static void display_flush(
            lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color);

  private:
    void sdl_error(const char * error) const;
    static int quit_filter(void * user_data, SDL_Event * event);

  public:
    /// SDL window size.
    const int width, height;
    /// SDL window zoom.
    const int zoom;

  private:
    /// Should quit?
    bool quit_ = false;
    /// Should refresh?
    bool refresh_ = true;
    /// SDL frame buffer.
    SDL_Window * window_;
    SDL_Renderer * renderer_;
    SDL_Texture * texture_;
    uint32_t * pixels_;
    /// LittlevGL display driver.
    lv_disp_buf_t disp_buf_;
    lv_disp_drv_t disp_drv_;
    lv_color_t * buf;
    /// LittlevGL work buffer size.
    static const int buf_size_ = 10;
};
