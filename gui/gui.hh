#pragma once

#include "sdl_display.hh"
#include "sdl_pointer.hh"

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
