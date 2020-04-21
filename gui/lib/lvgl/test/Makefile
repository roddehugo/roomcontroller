BASE = ../../..

TARGET = host

PROGRAM = hello
SOURCES = hello.cc

# User options, override defaults.
DEFS += -DLV_USE_DEBUG
DEFS += -DLV_USE_LOG=1 -DLV_LOG_LEVEL=LV_LOG_LEVEL_INFO
DEFS += -DUSE_MONITOR=1 -DMONITOR_ZOOM=2
DEFS += -DUSE_MOUSE

include $(BASE)/lib/lvgl/lvgl.mk
include $(BASE)/build/main.mk
