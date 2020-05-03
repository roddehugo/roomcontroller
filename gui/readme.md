# Room Controller - GUI

This module hosts the Room Controller Graphical User Interface.

## Structure

    ├── build # build system with make rules, flags and options.
    ├── lib # external dependencies, part of the compilation unit.
    │   ├── json
    │   │   ├── json # nlohmann/json git submodule.
    │   │   ├── json.mk # make module for library.
    │   │   ├── readme.md # module instructions.
    │   │   └── test # test module, for compilation and library playground.
    │   └── lvgl
    │       ├── lv_defaults.h # library wide defaults, mostly enable everything.
    │       ├── lv_drv_defaults.h # same for the drivers.
    │       ├── lv_drivers # littlevgl/lv_drivers git submodule.
    │       ├── lv_ex_defaults.h # same for the examples.
    │       ├── lv_examples # littlevgl/lv_examples git submodule.
    │       ├── lvgl # littlevgl/lvgl git submodule.
    │       ├── lvgl.mk # make module for library.
    │       ├── readme.md # module instructions.
    │       └── test # test module, for compilation and library playground.
    ├── gui # gui module to orchestrate program's busy loop.
    ├── logger # logging module, with ANSI colors, several levels.
    ├── project # project module, where live all applications.
    ├── sdl # SDL display and pointers drivers for LVGL.
    └── readme.md # what your are reading.

## Dependencies

All project dependencies live inside `lib`, they are organised in easy-to-manage
fashion.

A directory per library, in which should live a `.mk` file with the
same name as the directory. Then submodules can be cloned inside this directory,
a test folder should be dedicated to build the library indecently with a few
tests one can run to make sure the library is running fine.

Please refer to the readme inside each dependency for further instructions.

## Projects

All projects, i.e. programs with a `main` entry point, lives in the `project`
directory.

### Application

The main application lives in `project/app`. And the project is built using the
`Makefile` at the same level in working tree.

In short, from this directory, one could run the main app with:

    make -C project/app run

## Requirements

- **Linux** and **macOS** are supported.
- **SDL** a C driver library to use graphics, mouse, keyboard etc.

To get to know better with SDL, please [read the docs][sdl-docs].

## Usage

Open a terminal, amazing things happen there!

> For some commands, you may need to sudo, it is up to you to figure it out.
> Usually it is needed for `apt-get`, `xcode-select` and `port` commands.

### Linux

In case you don't have a compiler already, you may install:

    apt-get update
    apt-get install build-essential

Then, get the SDL2 library with developer files, and other dependencies:

    apt-get update
    apt-get install libsdl2-dev python3
    apt-get install tree # optional

### macOS

In case you don't have a compiler already, you may install:

    xcode-select --install

Then you need Homebrew (or MacPorts) to get SDL2, and other dependencies:

    brew install sdl2 python3
    brew install tree # optional

### Testing SDL2

Now SDL is installed, you should have the following command available:

    sdl2-config --version

It should say something like `2.y.z`, as of May, 1st it is `2.0.8`.

### Compiling the project

Now you have everything, let's get up and running with the project:

    git clone --recursive https://bitbucket.org/sandcrob/sc_room_controller.git roomcontroller

Or if you have setup an SSH key, you won't need to type your login info:

    git clone --recursive git@bitbucket.org:sandcrob/sc_room_controller.git roomcontroller

In case you have the `tree` command installed, you should get the directory
structure mentioned above with

    tree roomcontroller -L 3

Ok, so now, let's move into the git directory:

    cd roomcontroller

You can check everything compiles with the python3 script:

    ./tools/git-make

To get more options regarding this script, simply ask for help:

    ./tools/git-make --help

## Run the application

Now, you should be able to play with tests, and most importantly, the main app:

    make -C gui run

[sdl-docs]:https://wiki.libsdl.org/
