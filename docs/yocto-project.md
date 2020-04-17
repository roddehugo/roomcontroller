# Yocto Project

## Yocto vs Ubuntu for Embedded

A short [Medium blog post][yocto-vs-ubuntu] talking about:

> Yocto Project is a truly great tool to create an embedded Linux distribution of
> your own. Yes, not just embedded Linux image, but distribution.

## Getting Started

If one wants to spend 30mins watching a good introduction, there is [this
video][youtube-getting-started] available on Youtube.

Or maybe, you're more of a reader of official documention, [follow the
guide][official-getting-started].

### Yocto Project Build System

    Poky = BitBake + Metadata

- Poky: build system used by the Yocto Project
- BitBake: a task executor & scheduler
- Metadata: task definitions
    - configuration (`.conf`): global definitions of variables;
    - classes (`.bbclass`): encapsulation & inheritance of build logic,
    packaging, etc;
    - recipes (`.bb`): logical units of software/images to build.


[yocto-vs-ubuntu]:https://medium.com/@zertsekel/e6b13d583e05
[youtube-getting-started]:https://www.youtube.com/watch?v=zNLYanJAQ3s
[official-getting-Started]:https://www.yoctoproject.org/docs/3.0.2/brief-yoctoprojectqs/brief-yoctoprojectqs.html
