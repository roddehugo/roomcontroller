# Raspberry Pi

## Writing GUI applications on the Raspberry Pi without a desktop environment

Somehow describes what we would like to achieve but with another hardware and a
custom Linux based on the Yocto Project. It is a good starting point to assess a
few hypothesis and test graphical libraries as close to the final product as
possible.

Read [Medium blog post][rpi-gui-no-desktop].

If one is interested in setting up a Raspberry Pi with a 3.5" LCD display, she
can read the precedent [Medium blog post][rpi-lcd-screen-setup].

> Add the following options (all on the same line):
>     fbcon=map:10 fbcon=font:ProFont6x11
> I'm not sure what exactly the first option does, but it's the main change
> required to show the console on the LCD. Perhaps the font-related option
> is not necessary, but again, I don't know.

Well, by reading [the framebuffer console][kernel-framebuffer-console] kernel
documentation, one can figure it out.

It nicely refers to [LCD driver for the Raspberry Pi][git-lcd-show].

## A manifest for Yocto Project style development for Raspberry Pi

A gem, full of well documented sections. In our case, must read:

Get lost in the [Github wiki][rpi-yocto-manifest].

> This wiki describes an alternative way of creating a customized Linux
> distribution for the Raspberry Pi with the Yocto Project. Those Linux
> distributions can be heavily tailored to your project, e.g. you can build a
> small, fast booting image for a headless system or a fully featured mutimedia
> image for a huge info terminal. And, you can create truly embedded software
> without that "it's a tiny PC" feeling.

> The development process described here uses the meta-raspberrypi layer already
> included in Yocto Project.

> Many thanks to Andrei Gherzan, the maintainer of the meta-raspberrypi layer,
> the people from Raspberry Pi Foundation, Yocto Project, Scott Ellis from
> Jumpnow Technologies, LLC, and all other contributors.

- [embedded software](https://github.com/FrankBau/raspi-repo-manifest/wiki/embedded-software)
- [graphical backend](https://github.com/FrankBau/raspi-repo-manifest/wiki/graphical-backend)
- [framebuffer console](https://github.com/FrankBau/raspi-repo-manifest/wiki/fbcon)
- [framebuffer](https://github.com/FrankBau/raspi-repo-manifest/wiki/framebuffer)
- [kernel parameter](https://github.com/FrankBau/raspi-repo-manifest/wiki/kernel-parameter)
- [cmdline.txt](https://github.com/FrankBau/raspi-repo-manifest/wiki/cmdline.txt)
- [config.txt](https://github.com/FrankBau/raspi-repo-manifest/wiki/config.txt)
- [device tree](https://github.com/FrankBau/raspi-repo-manifest/wiki/device-tree)
- [boot partition](https://github.com/FrankBau/raspi-repo-manifest/wiki/boot-partition)
- [boot process](https://github.com/FrankBau/raspi-repo-manifest/wiki/boot-process)
- [prepare microSD card](https://github.com/FrankBau/raspi-repo-manifest/wiki/prepare-microSD-card)


## RPiconfig

To know a little more about most interesting options in `config.txt`.

Read the `Boot` chapter in [eLinux Wiki][elinux-rpiconfig].

## Raspberry Pi TFT Displays and Qt5 on Raspberry Pi with Yocto

A long [blog post][pitft-displays-qt5] by Jumpnow Technologies, LLC about:

> 16 Apr 2017

> Some configuration notes for using the Raspberry Pi TFT displays and Qt5.
> I am primarily testing with RPi3s running a Yocto built system (notes here).

With the [aforementioned notes][rpi-yocto-build] about the Yocto build.

> 03 Apr 2020

> This post is about building 32-bit Linux systems for Raspberry Pi boards using
> software from the Yocto Project.


[pitft-displays-qt5]:https://jumpnowtek.com/rpi/pitft-displays-and-qt5.html
[rpi-yocto-build]:https://jumpnowtek.com/rpi/Raspberry-Pi-Systems-with-Yocto.html
[rpi-gui-no-desktop]:https://medium.com/@avik.das/8f8f840d9867
[rpi-lcd-screen-setup]:https://medium.com/@avik.das/d0b2792783cd
[kernel-framebuffer-console]:https://www.kernel.org/doc/Documentation/fb/fbcon.txt
[git-lcd-show]:https://github.com/goodtft/LCD-show
[rpi-yocto-manifest]:https://github.com/FrankBau/raspi-repo-manifest/wiki
[elinux-rpiconfig]:https://elinux.org/RPiconfig#Boot
