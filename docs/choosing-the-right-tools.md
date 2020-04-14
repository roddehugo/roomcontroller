# Choosing the Right Tools

## Options

- [Qt](#qt)
- [LittlevGL](#littlevgl)
- ~~[TouchGFX](#touchgfx)~~

### Considerations

What are we looking for?

General topics:

- Licensing
- Documentation
- Community Support
- Popularity (Youtube, Google Trend)

Engineering topics:

- Examples project on targeted platforms
- Presence of simulator or integration with Qemu
- Ease of proving on Raspbian or Ubuntu (Debian based OS)
- Ease of portability on Yocto based Linux

## Qt

## LittlevGL

## TouchGFX

TouchGFX has been discarded from the study.  As per their [presentation
slides][tgfx-presentation] and the [help center][tgfx-cortex-a7], it seems no
support for Cortex-A7 devices is targeted, as of August 14, 2018.

Moreover, their licensing is not free for other devices than ST ones. As per
their [presentation slides][tgfx-presentation]:

> TouchGFX is a software framework written in C++ that unlocks the graphical user
interface of STM32 hardware.  The technology lets you create high-end GUIs that
fully live up to today's smartphone standards at a fraction of the cost.

> TouchGFX is integrated with the STM32Cube ecosystem.

> TouchGFX is FREE with STM32!

[qt-homepage]: https://www.qt.io
[lvgl-homepage]: https://littlevgl.com
[tgfx-homepage]:https://www.touchgfx.com
[tgfx-presentation]:https://www.st.com/content/dam/AME/2019/developers-conference-2019/presentations/STDevCon19_1.4_STM32TouchGFX.pdf
[tgfx-cortex-a7]:https://touchgfx.zendesk.com/hc/en-us/community/posts/360019432311-TouchGFX-core-library-for-Cortex-A7
