#include "gui/gui.hh"
#include "logger/logger.hh"
#include "lvgl/lvgl.h"

#include "lv_examples/lv_tests/lv_test.h"

#include "lv_examples/lv_tutorial/1_hello_world/lv_tutorial_hello_world.h"
#include "lv_examples/lv_tutorial/2_objects/lv_tutorial_objects.h"
#include "lv_examples/lv_tutorial/3_styles/lv_tutorial_styles.h"
#include "lv_examples/lv_tutorial/4_themes/lv_tutorial_themes.h"
#include "lv_examples/lv_tutorial/5_antialiasing/lv_tutorial_antialiasing.h"
#include "lv_examples/lv_tutorial/6_images/lv_tutorial_images.h"
#include "lv_examples/lv_tutorial/7_fonts/lv_tutorial_fonts.h"
#include "lv_examples/lv_tutorial/8_animations/lv_tutorial_animations.h"
#include "lv_examples/lv_tutorial/9_responsive/lv_tutorial_responsive.h"
#include "lv_examples/lv_tutorial/10_keyboard/lv_tutorial_keyboard.h"


#include <iostream>

/* FIXME: use a dedicated source file. */
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

/* FIXME: use a memory monitor wrapper. */
static lv_task_t * sysmon_task;

static void sysmon_handler(lv_task_t * task)
{
    lv_mem_monitor_t mm;
    lv_mem_monitor(&mm);
    unsigned kb = mm.total_size / 1024;
    lwarn("memory kb=%u used=%d%% frag=%d%%", kb, mm.used_pct, mm.frag_pct);
}

static void lvgl_init()
{
    lv_log_register_print_cb(&Logger::log);
    lv_init();
}

static void sysmon_init()
{
    unsigned period_ms = 10000; // 10 seconds.
    lv_task_prio_t prio = LV_TASK_PRIO_LOW;
    sysmon_task = lv_task_create(sysmon_handler, period_ms, prio, nullptr);
    assertm(sysmon_task, "memory monitor task failed");
}

static void sysmon_deinit()
{
    assertm(sysmon_task, "no memory monitor task");
    lv_task_del(sysmon_task);
    sysmon_task = nullptr;
}

int main(int argc, const char ** argv)
{
    // Initialize lvgl core.
    lvgl_init();
    std::atexit(lv_deinit);

    // Initialize system monitor task.
    sysmon_init();
    std::atexit(sysmon_deinit);

    // Initialize display and pointer with sdl backend.
    const int width = LV_HOR_RES_MAX;
    const int height = LV_VER_RES_MAX;
    SdlDisplay display(width, height);
    SdlPointer pointer;

    // Initialize screen holding theme and background style.
    gui::Screen screen;

    // Initialize gui with injected dependencies.
    Gui gui(display, pointer, screen);

    // To get the list of examples, one can run, use the following command:
    //   git grep -h --no-line "^void" lv_examples/**/*.h
    // Uncomment the app, test or tutorial you want to run.

    // Tests.
    /* lv_test_task_1(); */
    /* lv_test_task_2(); */
    /* lv_test_task_3(); */
    /* lv_test_object_1(); */
    /* lv_test_arc_1(); */
    /* lv_test_bar_1(); */
    /* lv_test_btn_1(); */
    /* lv_test_btnm_1(); */
    /* lv_test_canvas_1(); */
    /* lv_test_cb_1(); */
    /* lv_test_chart_1(); */
    /* lv_test_chart_2(chart); */
    /* lv_test_chart_3(chart_type); */
    /* lv_test_cont_1(); */
    /* lv_test_cont_2(); */
    /* lv_test_cpicker_1(); */
    /* lv_test_ddlist_1(); */
    /* lv_test_gauge_1(); */
    /* lv_test_img_1(); */
    /* lv_test_imgbtn_1(); */
    /* lv_test_kb_1(); */
    /* lv_test_kb_2(); */
    /* lv_test_label_1(); */
    /* lv_test_label_2(); */
    /* lv_test_label_3(); */
    /* lv_test_label_4(); */
    /* lv_test_led_1(); */
    /* lv_test_line_1(); */
    /* lv_test_list_1(); */
    /* lv_test_lmeter_1(); */
    /* lv_test_mbox_1(); */
    /* lv_test_page_1(); */
    /* lv_test_page_2(); */
    /* lv_test_preload_1(); */
    /* lv_test_roller_1(); */
    /* lv_test_slider_1(); */
    /* lv_test_sw_1(); */
    /* lv_test_ta_1(); */
    /* lv_test_ta_2(); */
    /* lv_test_table_1(); */
    /* lv_test_table_2(); */
    /* lv_test_tabview_1(); */
    /* lv_test_tabview_2(); */
    /* lv_test_tileview_1(); */
    /* lv_test_win_1(); */
    /* lv_test_stress_1(); */
    /* lv_test_theme_1(theme); */
    /* lv_test_theme_2(); */

    // Tutorials.
    /* lv_tutorial_hello_world(); */
    /* lv_tutorial_objects(); */
    /* lv_tutorial_styles(); */
    /* lv_tutorial_themes(); */
    /* lv_tutorial_antialiasing(); */
    /* lv_tutorial_image(); */
    /* lv_tutorial_fonts(); */
    /* lv_tutorial_animations(); */
    /* lv_tutorial_responsive(); */
    /* lv_tutorial_keyboard(indev); */

    // Loop until application properly exits.
    return gui.loop();
}
