#pragma once

#include "sdl_display.hh"
#include "sdl_pointer.hh"

namespace gui
{
class Object;
class Screen;
} // namespace gui

class Gui
{
  public:
    /// Constructor.
    Gui(SdlDisplay & d, SdlPointer & p);
    /// Loop until a quit is requested.
    int loop();

  private:
    SdlDisplay & display_;
    SdlPointer & pointer_;
};

namespace gui
{

class Object
{
  public:
    virtual ~Object() = default;
    lv_obj_t * get() const;
    lv_obj_t * set(lv_obj_t * o);

  protected:
    lv_obj_t * obj_;
};

class Screen: public Object
{
  public:
    Screen();

  protected:
    lv_theme_t * th_;
};

} // namespace gui
