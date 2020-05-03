LVGL_DIR = $(BASE)/lib/lvgl

include $(LVGL_DIR)/lvgl/lvgl.mk

DEFS += -DLV_CONF_INCLUDE_SIMPLE # 'lv_conf.h' is defined per project.

CFLAGS += -I$(LVGL_DIR)

SOURCES += $(CSRCS) $(ASRCS)
