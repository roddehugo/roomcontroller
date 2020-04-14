# Yocto Project

## Getting Started

[Getting Started with the Yocto Project • Youtube](https://www.youtube.com/watch?v=zNLYanJAQ3s)

### Yocto Project Build System

    Poky = BitBake + Metadata

- Poky: build system used by the Yocto Project
- BitBake: a task executor & scheduler
- Metadata: task definitions
    - configuration (`.conf`): global definitions of variables;
    - classes (`.bbclass`): encapsulation & inheritance of build logic,
    packaging, etc;
    - recipes (`.bb`): logical units of software/images to build.
