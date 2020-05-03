#include "sdl_display.hh"

#include <cstdlib>
#include <iostream>

SdlDisplay::SdlDisplay(int w, int h, int z)
    : width(w)
    , height(h)
    , zoom(z)
{
    // SDL display buffer.
    pixels_ = new uint32_t[width * height];

    // LittlevGL display buffer.
    buf = new lv_color_t[width * buf_size_];
    lv_disp_buf_init(&disp_buf_, buf, nullptr, width * buf_size_);

    // LittlevGL display driver.
    lv_disp_drv_init(&disp_drv_);
    disp_drv_.flush_cb = &SdlDisplay::display_flush;
    disp_drv_.buffer = &disp_buf_;
    disp_drv_.user_data = this;
    lv_disp_drv_register(&disp_drv_);
}

SdlDisplay::~SdlDisplay()
{
    SDL_DestroyTexture(texture_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void SdlDisplay::sdl_error(const char * error) const
{
    std::cerr << error << ": " << SDL_GetError() << std::endl;
    std::exit(1);
}

int SdlDisplay::quit_filter(void * user_data, SDL_Event * event)
{
    auto & self = *static_cast<SdlDisplay *>(user_data);
    if (event->type == SDL_QUIT
            || (event->type == SDL_WINDOWEVENT
                    && event->window.event == SDL_WINDOWEVENT_CLOSE))
    {
        self.quit_ = true;
    }
    else if (event->type == SDL_KEYUP
            && (event->key.keysym.sym == 'q'
                    || event->key.keysym.sym == SDLK_ESCAPE))
    {
        self.quit_ = true;
    }
    return 1;
}

void SdlDisplay::enable()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        sdl_error("Unable to initialise SDL");
    // Make sure we exit properly.
    std::atexit(SDL_Quit);
    SDL_SetEventFilter(&SdlDisplay::quit_filter, this);

    // Create SDL frame buffer elements.
    window_ = SDL_CreateWindow("GUI Simulator", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, width * zoom, height * zoom, 0);
    if (!window_)
        sdl_error("Unable to create window");

    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (!renderer_)
        sdl_error("Unable to create renderer");

    // Select the boot background color.
    SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer_);
    SDL_RenderPresent(renderer_);

    texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture_)
        sdl_error("Unable to create texture");
    if (SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND) != 0)
        sdl_error("Unable to set blend mode");
}

void SdlDisplay::disable()
{
    SDL_Quit();
}

void SdlDisplay::refresh()
{
    if (refresh_)
    {
        refresh_ = false;
        SDL_UpdateTexture(texture_, nullptr, pixels_, width * sizeof(uint32_t));
        SDL_RenderClear(renderer_);
        SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
        SDL_RenderPresent(renderer_);
    }
}

bool SdlDisplay::running() const
{
    return quit_ ? false : true;
}

void SdlDisplay::display_flush(
        lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color)
{
    auto & self = *static_cast<SdlDisplay *>(drv->user_data);

    int hres = !drv->rotated ? drv->hor_res : drv->ver_res;
    int vres = !drv->rotated ? drv->ver_res : drv->hor_res;

    // Return if the area is out the screen.
    int x1 = area->x1, x2 = area->x2;
    int y1 = area->y1, y2 = area->y2;

    // printf("hres=%3d, vres=%3d\n", hres, vres);
    // printf("x1=%3d, y1=%3d, x2=%3d y2=%3d\n", x1, y1, x2, y2);

    if (x2 >= 0 && y2 >= 0 && x1 < hres && y1 < vres)
    {
        int w = drv->hor_res;
        for (int y = y1; y <= y2 && y < drv->ver_res; y++)
        {
            for (int x = x1; x <= x2; x++)
            {
                self.pixels_[y * w + x] = lv_color_to32(*color);
                color++;
            }
        }
        self.refresh_ = true;
    }

    // Notify LittlevGL the flush is ready.
    lv_disp_flush_ready(drv);
}
