# User can redefine path to prefix of compiler.
PREFIX ?=

# Compiler programs.
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
LD = $(PREFIX)g++ # Not a typo, pass flags with '-Wl,<flag>'
GDB = $(PREFIX)gdb
SIZE = $(PREFIX)size
