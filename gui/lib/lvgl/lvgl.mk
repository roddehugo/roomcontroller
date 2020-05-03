LVGL_DIR = $(BASE)/lib/lvgl

include $(LVGL_DIR)/lvgl/lvgl.mk

ifeq ($(LV_DRIVERS),yes)
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
endif

ifeq ($(LV_EXAMPLES),yes)
include $(LVGL_DIR)/lv_examples/lv_examples.mk
endif

DEFS += -DLV_CONF_INCLUDE_SIMPLE # 'lv_conf.h' is defined per project.

CFLAGS += -I$(LVGL_DIR)

SOURCES += $(CSRCS) $(ASRCS)
