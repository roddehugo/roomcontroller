# Choosing the Right Tools

## Libraries

- [Qt](#qt)
- [LittlevGL](#littlevgl)
- [µGFX](#µgfx)
- ~~[TouchGFX](#touchgfx)~~

## Considerations

What are we looking for?

General topics:

- Licensing
- Documentation
- Community Support
- Popularity (Youtube, Google Trend)

Engineering topics:

- Examples project on targeted platforms
- Presence of simulator or integration with emulating framework
- Ease of proving on Raspbian or Ubuntu (Debian based OS)
- Ease of portability on Yocto based Linux
- Ease of tuning, theming and porting on other MCUs
- Internationalization support
- Drag & Drop support

## Comparison

| Feature       | Qt        | LittlevGL | µGFX      |
| ---           | ---       | ---       | ---       |
| Licensing     | annual    | free      | one-time  |
| Popularity    | very      | growing   | unknown   |
| Community     | big       | growing   | unknown   |
| Documentation | good      | good      | standard  |
| Apprehensibly | hard      | easy      | easy      |
| Extendability | hard      | easy      | unknown   |
| Footprint     | big       | small     | small     |
| PC simulator  | SDL/Vbox  | SDL       | SDL       |
| Yocto ready   | metapkg   | linuxfb   | linuxfb   |
| Language      | C++/QML   | C/python3 | C         |

### [Qt][qt-homepage]

#### Pros

- Go to GUI library for big industries (automotive for instance)
- Stable, proven, widely used library with Qt Creator IDE
- Embedded friendly with Qt for Device Creation and Qt for Embedded Linux
- IDE is cross-platforms, embedded is best supported and documented on Linux
- Ready-to-use Yocto metapackage with configurable modules
- C++ with a lot of common utilities ready (buffer, queues, etc)
- QML for UI creation with QT Creator Designer Tool
- Code modularity with a fairy tiny core, plus extensions and utilities

#### Cons

- Hard to get around and fully apprehend code source
- High learning curve because it is big
- Complicated C++ feature used

### [LittlevGL][lvgl-homepage]

#### Pros

- Rising library for embedded GUI, actively developed
- Open-source under MIT, code available in Github
- Written in C (C++ friendly) and build process uses Make.
- Easy-to-use, easy-to-extend components
- Good visual effects with transitions
- Low memory footprint for single core microprocessors
- Good repository with Open-source standards
- Good documentation examples, tutorials and community
- Project looks apprehendable with a not so big learning curve
- MicroPython bindings for writing Python3 code with better OOP
- Code modularity with a fairy tiny core, plus extensions and utilities
- Desire to keep the number of options in `lv_conf.h` reasonable
- Big companies and project started to use LittlevGL (NXP, ESP32, Zephyr)
- Promising v7 on the starting block (CSS like, anti-aliasing, unit tests, etc.)
- Upcoming new themes made by a graphics designer
- About to create a dedicated company

#### Cons

- Still quite a _young_ library (released on Github in 2016)
- One author, one vision, also he seems to be very listening the community

### [µGFX][ugfx-homepage]

#### Pros

- Alternative mentioned in number of forums and posts.
- Backed by a company head-quarted in Switzerland
- Claims trust from all the big names in the silicon industry like ST
Microelectronics, NXP, Silicon Labs, Nordic Semi, Atmel and also software
companies like Keil, Zephyr, FreeRTOS and so on.
- Written in C (C++ friendly) and build process uses Make.
- Open-source with code available on Github
- One-time licensing for commercial use with unlimited devices, no royalty-fees,
no expiration and updates.
- Offers paid support from their team.
- Low memory footprint for single core microprocessors
- Project looks apprehendable with a not so big learning curve

#### Cons

- No so much examples nor tutorials
- No so much use in community, at least publicly
- No ready-to-use Internationalization

### _Nota Bene_

I did not check for Drag&Drop and did not spend so much time on it as LittlevGL
more or less have the same Pros—except there is no company behind (yet)— and
less Cons.

### [TouchGFX][tgfx-homepage]

TouchGFX has been discarded from the study.  As per their [presentation
slides][tgfx-presentation] and the [help center][tgfx-cortex-a7], it seems no
support for Cortex-A7 devices is targeted, as of August 14, 2018.

Moreover, their licensing is not free for other devices than ST ones. As per
their [presentation slides][tgfx-presentation]:

> TouchGFX is a software framework written in C++ that unlocks the graphical user
> interface of STM32 hardware.  The technology lets you create high-end GUIs that
> fully live up to today's smartphone standards at a fraction of the cost.

> TouchGFX is integrated with the STM32Cube ecosystem.

> TouchGFX is FREE with STM32!


[qt-homepage]: https://www.qt.io
[lvgl-homepage]: https://littlevgl.com
[ugfx-homepage]: https://ugfx.io
[tgfx-homepage]:https://www.touchgfx.com
[tgfx-presentation]:https://www.st.com/content/dam/AME/2019/developers-conference-2019/presentations/STDevCon19_1.4_STM32TouchGFX.pdf
[tgfx-cortex-a7]:https://touchgfx.zendesk.com/hc/en-us/community/posts/360019432311-TouchGFX-core-library-for-Cortex-A7
