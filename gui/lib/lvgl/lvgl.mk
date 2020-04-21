LVGL_DIR = $(BASE)/lib/lvgl

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

DEFS += -DLV_CONF_INCLUDE_SIMPLE # 'lv_conf.h' is defined per project.

CFLAGS += -I$(LVGL_DIR)
CPPFLAGS += -imacros $(LVGL_DIR)/lv_defaults.h

SOURCES += $(CSRCS) $(ASRCS)
