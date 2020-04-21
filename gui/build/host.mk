SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LIBS := $(shell sdl2-config --libs)

LDLIBS += $(SDL2_LIBS)
CFLAGS += $(SDL2_CFLAGS)
