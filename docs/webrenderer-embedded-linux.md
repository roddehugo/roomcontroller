# WebRenderer for Embedded Linux

It would be awesome if we could develop the GUI with Web technologies
(HTML/CSS/JS). It would need most of HTML5 support as well as regular JS API. It
needs to run on embedded linux with limited resources.

Ideally, it would run and display a smooth and reactive user interface on a
single core ARMv7 CPU running at 900MHz and *without* a GPU associated, with
something like 256 MB of SPI Flash ROM and 256 MB of DDR3 SDRAM. Well, something
not too far from an iMX6ULL from NXP.

## Study

### Where does it start?

Everything started with this [StackOverflow][webrenderer-stackoverflow] thread
asked 9 years ago!

> I want to use HTML+CSS+JavaScript to develop a user interface for a
> touchscreen device in a Linux environment and need a suitable rendering
> engine.

> The device in question will have a ARM CPU with 400 to 900 MHz clock, a VGA or
> WVGA display and about 256 MB RAM or more with standard Debian Linux
> (minimalistic install).

> Ideally the rendering engine would directly access /dev/fb0 and mouse events.
> Since the browser is just used as a rendering engine I do not need/want any
> GUI - no windows, no tabs, no dialog boxes, just a single full-screen HTML
> page that heavily uses JavaScript to interact with the user.

> It would be great if Qt / GTK / DirectFB and such could be avoided (to reduce
> memory overhead and startup time) but of course this is not absolutely
> necessary.

> Of course WebKit and Gecko come to my mind but they are both hard to
> understand and hard to compile. Perhaps one of the numerous forks comes close
> to what I need (I searched but had no luck so far)?

Sounds promising right? Exactly what we'd like to achieve. But unfortunately; as
of 2019, the author responded:

> Sorry, I never finished this and ain't working on it anymore

Too bad! Let's move on, there must be something.

### Options to investigate

Taken from a basic [comparison of browser engines][comparison-browser-engines]:

- Chromium Embedded Framework
- WebKit for Embedded Devives
- QtWebKit/QtWebEngine for Embedded Device Creation
- Servo Parallel Browser Engine

There seems to have [OpenEmbedded/Yocto BSP layer for Web
Browsers][yocto-meta-browser], with either Chromium or Firefox. This is a good
sign that it is feasible, but does not say much about the hardware requirements.

### Chromium Embedded Framework

A simple framework for embedding Chromium-based browsers in other applications.
This enables developers to add web browsing functionality to their application,
as well as the ability to use HTML, CSS, and JavaScript to create the
application's user interface.

There is a lot of information available in the [Bitbucket
project][cef-bitbucket] page. As per the issue [#1990][cef-issue-1990] CEF
supports ARM platforms since 2016.

Also, a [blog post][cef-rpi3] describes how to port and built CEF on a Raspberry
Pi 3. It does not look like plug&play, more like a journey. As a conclusion, the
author says:

> We now have a build that combines Chromium, CEF, Raspberry Pi patches, and
> mmal decoding. Refining the build process to this point took a lot of
> searching, code review, and learning by failing. The end result is a fairly
> simple path to a great web / GUI platform with hardware accelerated H.264
> decoding on a low cost device.

And finally, a fellow developer asking for support on [CEF3 for iMX6DL
Yocto][cef-imx6dl] on the NXP forum. Unfortunately there is not much to get out
from this threaéd with a single reply. At least, the person tried and the
iMX6DualLite, which is a Dual Cortex-A9 processor running up to 1GHz and a GPU
unit.

### Web Platform for Embedded WebKit

A [WebKit][wpe-webkit] port optimized for embedded devices. [WPE
WebKit][wpe-webkit-org] allows embedders to create simple and performant systems
based on Web platform technologies. It is designed with hardware acceleration in
mind, leveraging common 3D graphics APIs for best performance.


A [presentation][wpe-igalia] of the framework by Igalia, mentioning requirements:

> In addition, WPE WebKit offers great possibilities for deployment on different
> platforms, thanks to its underlying design that allows for integration in a
> variety of hardware configurations. As a minimum, EGL and OpenGL ES 2 support
> and basic GStreamer integration are required.

And [another presentation][wpe-elinux] at the 2017 Embedded Linux Conference
about HTML5 user interfaces for embedded devices, by the same company Igalia:

> About a new WebKit port: WPE – Backends

> - Main goal: efficient cross-process GPU buffer sharing
> - Wayland, libgbm and other native implementations
> - Necessary to glue the backend facilities with the provided EGL platform
> - Renderer backend provides rendering target
> - View backend provides a way to display the rendered buffer on screen

> About a new WebKit port: WPE – Lightweight

> - Reference hardware: Rpi 0-3 (desktop used for development too)
> - A functional Raspberri Pi image can be about 40MB
> - Low memory footprint: possible to define limits to consumption <100MB for a standard configuration
> - Able to play YoutubeTV on a Rpi 0-1
> - Raspberry Pi 0/1 is ~1000 DMIPS

It is worth mentioning two blog posts to further read, one to build a full
screen web application for the Raspberry Pi 3 with
[Buildroot][wpe-rpi-buildroot], and the other one about the same topic but with
[Yocto][wpe-rpi-yocto].

### QtWebKit / QtWebEngine

As per [QtWebEngine][qt-webengine] docs in Qt5.14:

> Qt WebEngine provides functionality for rendering regions of dynamic web content.

As per [QtWebKit][qt-webkit] docs in Qt5.5 (deprecated in later versions):

> Qt WebKit provides the WebView API, which allows QML applications to
render regions of dynamic web content. A WebView component may share the screen
with other QML components or encompass the full screen as specified within the
QML application.

A very interesting blog post about [QtWebKit vs. QtWebEngine for Embedded
Linux][qtwebkit-vs-qtwebengine]. The author mentions a iMX6 Solo device
(Cortex-A9 with GPU) for its comparison:

> Now i’ll go straight on practical comparison between QtWebkit and QtWebengine
> on Linux Embedded.

> - Processor – iMX6 Solo 800MHz (boost upto 1 GB)
> - RAM – 1 GB DDR3
> - Yocto build – Morty 2.2.2
> - Qt – 5.7.1
> - Display Resolution – 800 x 480

### Servo Parallel Browser Engine

[Servo][servo-github] is a prototype web browser engine written in the Rust
language. It is sponsored by Mozilla, but quite early stage.

It looks promising as Rust language can also target small microprocessors like
Cortex-M4 devices.

## Thoughts

Likely to have good performance on Embedded Linux with a GPU and a Cortex-A9. On
a low power single core CPU, I didn't find good resources nor minimal hardware
requirements for running Chromium or Webkit on Embedded devices.

I would not say it is impossible on the current targeted iMX6ULL, but at what
cost? And what performance? Maybe it is the kind of project you spent 3 months
on the hardware and build setup but then you have a fully functional web engine
to build your application on top. I lack knowledge on this topic to be a good
advisor, maybe someone with more Embedded Linux background with HMI, alike in
the automotive industry.

[webrenderer-stackoverflow]:https://stackoverflow.com/questions/5522932/full-featured-html-rendering-engine-like-webkit-gecko-for-embedded-linux
[comparison-browser-engines]:https://en.wikipedia.org/wiki/Comparison_of_browser_engines
[yocto-meta-brower]:https://github.com/OSSystems/meta-browser
[cef-bitbucket]:https://bitbucket.org/chromiumembedded/cef
[cef-issue-1990]:https://bitbucket.org/chromiumembedded/cef/issues/1990/linux-add-arm-build-support
[cef-rpi3]:https://medium.com/@tejohnso/chromium-embedded-framework-on-the-raspberry-pi-b91b01f51c9
[cef-imx6dl]:https://community.nxp.com/thread/375379
[wpe-webkit]:https://webkit.org/wpe/
[wpe-webkit-org]:https://wpewebkit.org
[wpe-github]:https://github.com/WebPlatformForEmbedded/WPEWebKit
[wpe-igalia]:https://www.igalia.com/project/wpe
[wpe-elinux]:https://elinux.org/images/9/9e/WPE_elc_prague_2017.pdf
[wpe-rpi-buildroot]:https://medium.com/@decrocksam/building-web-applications-for-wpe-webkit-using-node-js-3347146013f3
[wpe-rpi-yocto]:https://www.j1nx.nl/ict-matters/compiling-wpe-webkit-for-the-raspberrypi/
[yocto-wpe]:https://github.com/WebPlatformForEmbedded/meta-wpe
[qt-webengine]:https://doc.qt.io/qt-5/qtwebengine-index.html
[qt-webkit]:https://doc.qt.io/archives/qt-5.5/qtwebkit-index.html
[qtwebkit-vs-qtwebengine]:https://shareknowlege29.wordpress.com/2018/08/12/linux-embedded-platform-qtwebkit-or-qtwebengine
[servo-github]:https://github.com/servo/servo
