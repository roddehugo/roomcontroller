# Ubuntu Core for embedded devices

## Raspberry Pi

The Raspberry Pi B+ with its ARMv6 CPU cannot run a regular Ubuntu. It could run
a smaller [Ubuntu Core][ubuntu-core] though for [IoT][ubuntu-iot].

Canonical has started the support of Raspberry Pi on Ubuntu 'clasic' since the
release of the Raspberry Pi 2 with the ARMv7 CPU. Further details are available
in the [Ubuntu Wiki][ubuntu-pis].

They provide both `armhf` and `arm64` binaries for respectively `armv7l` 32-bit
with `hard float` and `armv8` 64-bit. Further details of ARM architectures can
be found in the [Wikipedia ARM Architectures][wikipedia-arm] cores table.

Though, it can run [Ubuntu Core for Embedded Linux][ubuntu-embedded], which
looks very promising. It requires a Ubuntu SSO account with an SSH key. Ubuntu
Core is a serious candidate for Embedded Linux and is gaining traction from the
community.

## Documentation

A wiki is available for [IoT developers][ubuntu-iot-docs].


[ubuntu-core]:https://ubuntu.com/core
[ubuntu-iot]:https://ubuntu.com/internet-of-things
[ubuntu-pis]:https://wiki.ubuntu.com/ARM/RaspberryPi
[ubuntu-embedded]:https://ubuntu.com/embedded
[ubuntu-iot-docs]:https://docs.ubuntu.com/core/en/index
[wikipedia-arm]:https://en.wikipedia.org/wiki/ARM_architecture#Cores
