# Room Controller - App Project

This module hosts the Room Controller Graphical User Interface Application.

## Structure

    ├── Makefile # project makefile, compilation entry point.
    ├── img # images required by the app, stored as C header or binary files.
    ├── app.cc # project main entry point, monolithic structure.
    ├── default.json # JSON markup to describe application.
    ├── lv_conf.h # project scope defaults, overides lv_defaults.h.
    └── readme.md # what your are reading.

## Compiling

    make

## Running

    make run
