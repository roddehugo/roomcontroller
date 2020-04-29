#include "gui.hh"
#include "logger.hh"
#include "lvgl/lvgl.h"

#include <fstream>
#include <iostream>

#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

#include "nlohmann/json.hpp"
using json = nlohmann::json;

static const auto& data = R"({
    "app": {
        "width": 800,
        "height": 480,
        "language": "en",
        "page": "page_a",
        "components": [
            {
                "id": "edit",
                "type": "button",
                "properties": {
                    "x": 120,
                    "y": 5,
                    "text": "EDIT"
                }
            },
            {
                "id": "blue",
                "type": "button",
                "properties": {
                    "x": 310,
                    "y": 5,
                    "text": "BLUE",
                    "target_background": "blue",
                    "background_color": 255
                }
            },
            {
                "id": "red",
                "type": "button",
                "properties": {
                    "x": 400,
                    "y": 5,
                    "text": "RED",
                    "target_background": "red",
                    "background_color": 16711680
                }
            },
            {
                "id": "french",
                "type": "button",
                "properties": {
                    "x": 560,
                    "y": 5,
                    "text": "SWITCH_TO_FRENCH",
                    "target_language": "fr"
                }
            },
            {
                "id": "english",
                "type": "button",
                "properties": {
                    "x": 640,
                    "y": 5,
                    "text": "SWITCH_TO_ENGLISH",
                    "target_language": "en"
                }
            }
        ],
        "pages": [
            {
                "id": "page_a",
                "components": [
                    {
                        "id": "headline_page_a",
                        "type": "label",
                        "properties": {
                            "x": 300,
                            "y": 140,
                            "width": 200,
                            "text": "I_AM_PAGE_A"
                        }
                    },
                    {
                        "id": "go_to_page_b",
                        "type": "button",
                        "properties": {
                            "x": 300,
                            "y": 200,
                            "width": 200,
                            "text": "GO_TO_PAGE_B",
                            "target_page": "page_b"
                        }
                    }
                ]
            },
            {
                "id": "page_b",
                "components": [
                    {
                        "id": "headline_page_b",
                        "type": "label",
                        "properties": {
                            "x": 300,
                            "y": 140,
                            "width": 200,
                            "text": "I_AM_PAGE_B"
                        }
                    },
                    {
                        "id": "go_to_page_a",
                        "type": "button",
                        "properties": {
                            "x": 300,
                            "y": 200,
                            "width": 200,
                            "text": "GO_TO_PAGE_A",
                            "target_page": "page_a"
                        }
                    }
                ]
            }
        ]
    },
    "translations": {}
})";

int main(int argc, const char ** argv)
{
    lv_log_register_print_cb(&Logger::log);
    lv_init();

    try
    {
        auto j = json::parse(data);
        const auto & app = j["app"];
        const auto width = app["width"].get<int>();
        assert(width <= LV_HOR_RES_MAX);
        const auto height = app["height"].get<int>();
        assert(height <= LV_VER_RES_MAX);
        linfo("app width=%3d height=%3d", width, height);

        const auto& components = app["components"];
        linfo("components size=%lu", components.size());

        SdlDisplay display(width, height);
        SdlPointer pointer;

        gui::Screen screen;

        Gui gui(display, pointer);
        return gui.loop();
    }
    catch (json::exception& e)
    {
        lerror("json exception id=%d message=%s", e.id, e.what());
        return 1;
    }
}
