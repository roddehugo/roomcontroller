#pragma once

#include "sdl/sdl_display.hh"
#include "sdl/sdl_pointer.hh"

namespace gui
{
class Object;
class Screen;
} // namespace gui

class Gui: SdlPointer::EventDelegate
{
  public:
    /// Constructor.
    Gui(SdlDisplay & d, SdlPointer & p, gui::Screen & s);
    /// Loop until a quit is requested.
    int loop();
    /// Act upon events notified by the pointer.
    void on(const char key, bool pressed) override;

  private:
    SdlDisplay & display_;
    SdlPointer & pointer_;
    gui::Screen & screen_;
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
    lv_style_t * style();

  protected:
    lv_style_t style_;
};

} // namespace gui
