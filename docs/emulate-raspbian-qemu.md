# Emulate Raspbian with QEMU

## Getting started

### A word about compatibilities

> As of QEMU 2.6 the raspi2 machine type is part of standard QEMU.

As per [A Virtualised Raspberry Pi inside a Docker image][dockerpi]:

> Note: Pi 2 and Pi 3 support is currently experimental. Networking doesn't work
> and QEMU hangs once the machines are powered down requiring you to docker kill
> the container. See [#4][dockerpi-issue-4] for details.

### The Github repository with adapted Kernels for QEMU

The [Github Readme][qemu-rpi-kernel] is self-explanatory.

Be aware than these are modified kernels!

> Ready-made kernels that can be used to emulate a Raspberry Pi using QEMU.

> They are compiled from the same kernel sources used for official Raspian
> images, with tweaks to make them suitable for use with QEMU, and are supposed
> to be used along with official Raspbian images.

### A good tutorial for Raspberry Pi B+

Follow [Raspberry Pi on QEMU][qemu-rpi-azeria] guide.

### A good tutorial for Raspberry Pi 3

Follow the [Debian for Raspberry Pi 3 on QEMU][qemu-rpi3-tutorial] guide.

> Date: 2018-10-11

> This tutorial explains how to run a 64-bit Linux distribution for the
> Raspberry Pi 3 on QEMU, a generic and open source machine emulator and
> virtualizer.

Watch out!

> QEMU supports many physical hardware platforms, and has recently added support
> for the Raspberry Pi 3 with the raspi3 model. However, this is only for 64-bit
> distributions, and there is currently no emulation of the BCM2835 USB
> controller, so there is no USB support and also, more critically, no
> networking support.

### Resize a filesystem using `qemu-img` and `fdisk`

From this [Githug gist][resize-qemu-img].

> Occasionally we will deploy a virtual instance into our KVM infrastructure and
> realize after the fact that we need more local disk space available. This is
> the process we use to expand the disk image.

On the host machine, run:

    qemu-img resize raspbian-stretch-lite.img +4G

Boot the guest machine, and run:

    df -h
    fdisk /dev/sda

Resize the partition using `fdisk` commands:

    Command (m for help): p
    (...)
    Device    Boot      Start         End      Blocks   Id  System
    /dev/sda1   *        2048     1026047      512000   83  Linux
    /dev/sda2         1026047    16777215     5811200   83  Linux

    Command (m for help): d
    Partition number (1-2): 2
    Partition 2 is deleted

    Command (m for help): n
    Partition type:
        p   primary (2 primary, 0 extended, 2 free)
        e   extended
    Select (default p): p
    Partition number (1-2, default 2): 2
    First sector ({min}-{max}, default {default}): # use Start value from above
    Last sector, +sectors or +size{K,M,G} (...): # use max value, should be > than End value above
    Partition 2 of type Linux and of size {n} GiB is set

Write the partition to disk:

    Command (m for help): w
    The partition table has been altered!

Reboot and expand root file system:

    df -h # nothing changed yet
    resize2fs /dev/sda2
    df -h # youhou!

Reboot again and you're done.

## Issues

### Bad register offset error

In case you face `vpb_sic_write: Bad register offset 0x2c`, add `-serial stdio`
to the qemu command as per [Github issue #75][bad-register-offset].

### Guest has not initialized the display (yet)

In case you face a black screen in QEMU window `pl110_versatile`. Use
`kernel-qemu-4.14.79-stretch` to have a GUI with the buster image.

## Step-by-step guide for macOS

Adapted from this [cheat sheet][qemu-rpi-macos].

1. Install virtualization engine *QEMU*:

       brew install qemu

2. Download Linux Kernel from *qemu-rpi-kernel*:

       https://github.com/dhruvvyas90/qemu-rpi-kernel/blob/master/kernel-qemu-4.14.79-stretch

3. Download ARMv6 Machine *versatile-pb.dtb*:

       wget https://raw.githubusercontent.com/dhruvvyas90/qemu-rpi-kernel/master/versatile-pb.dtb

4. Download OS *Raspbian Stretch*:

       wget http://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2019-04-09/2019-04-08-raspbian-stretch-lite.zip
       unzip 2019-04-08-raspbian-stretch-lite.zip

5. Run emulator:

       qemu-system-arm -cpu arm1176 -m 256 \
           -M versatilepb \
           -kernel kernel-qemu-4.14.79-stretch \
           -dtb versatile-pb.dtb \
           -drive "file=$1,format=raw" \
           -append "dwc_otg.lpm_enable=0 root=/dev/sda2 panic=1 rootwait" \
           -no-reboot \
           -serial stdio \
           -net user,hostfwd=tcp::22222-:22 -net nic

One can add instructions to not display the console frame buffer with boot logs
and disable the blinking cursor to avoid frame buffer refresh. Add the kernel
parameters in `-append` argument.

    fbcon=map:1 consoleblank=0 vt.global_cursor_default=0

6. Wait for login screen... and log in!

7. Enable SSH service on Raspbian:

       systemctl enable --now ssh

8. SSH into emulated Raspbian from host:

       ssh -p 22222 pi@localhost


[qemu-rpi-kernel]:https://github.com/dhruvvyas90/qemu-rpi-kernel
[dockerpi]:https://github.com/lukechilds/dockerpi
[dockerpi-issue-4]:https://github.com/lukechilds/dockerpi/pull/4
[qemu-rpi-azeria]:https://azeria-labs.com/emulate-raspberry-pi-with-qemu/
[qemu-rpi3-tutorial]:https://github.com/wimvanderbauwhede/limited-systems/wiki/Debian-%22buster%22-for-Raspberry-Pi-3-on-QEMU
[bad-register-offset]:https://github.com/dhruvvyas90/qemu-rpi-kernel/issues/75
[guest-has-not-initialized-display]:https://github.com/dhruvvyas90/qemu-rpi-kernel/issues/93
[qemu-rpi-macos]:https://docs.j7k6.org/emulate-raspbian-qemu-macos
[resize-qemu-img]:https://gist.github.com/larsks/3933980
