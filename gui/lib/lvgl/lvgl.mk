LVGL_DIR = $(BASE)/lib/lvgl

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

CFLAGS += -I$(LVGL_DIR)
SOURCES += $(CSRCS) $(ASRCS)
