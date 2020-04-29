#include "gui.hh"
#include "logger.hh"
#include "lvgl/lvgl.h"

#include <fstream>
#include <iostream>
#include <string>

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

enum ComponentType
{
    OBJECT,
    BUTTON,
    LABEL,
};

NLOHMANN_JSON_SERIALIZE_ENUM(ComponentType,
{
    {OBJECT, "object"},
    {BUTTON, "button"},
    {LABEL, "label"},
})

static void describe(const char * who, const lv_obj_t * obj)
{
    ltrace("%s pos=(%d,%d) size=(%d,%d)", who,
            lv_obj_get_x(obj), lv_obj_get_y(obj),
            lv_obj_get_width(obj), lv_obj_get_height(obj));
}

template <ComponentType T>
static lv_obj_t * draw_object(const json & o,
        lv_obj_t * parent, lv_obj_t * obj = nullptr)
{
}

template <>
lv_obj_t * draw_object<OBJECT>(const json & o,
        lv_obj_t * parent, lv_obj_t * obj)
{
    if (!obj)
        obj = lv_obj_create(parent, nullptr);

    if (o.contains("x"))
    {
        lv_obj_set_x(obj, o["x"].get<int>());
        ltrace("object x set=%d get=%d", o["x"].get<int>(), lv_obj_get_x(obj));
    }

    if (o.contains("y"))
    {
        lv_obj_set_y(obj, o["y"].get<int>());
        ltrace("object y set=%d get=%d", o["y"].get<int>(), lv_obj_get_y(obj));
    }

    if (o.contains("width"))
    {
        lv_obj_set_width(obj, o["width"].get<int>());
        ltrace("object width set=%d get=%d",
                o["width"].get<int>(), lv_obj_get_width(obj));
    }

    if (o.contains("height"))
    {
        lv_obj_set_height(obj, o["height"].get<int>());
        ltrace("object height set=%d get=%d",
                o["height"].get<int>(), lv_obj_get_height(obj));
    }

    describe("object", obj);
    return obj;
}

template <>
lv_obj_t * draw_object<LABEL>(const json & o,
        lv_obj_t * parent, lv_obj_t * obj)
{
    if (!obj)
    {
        obj = lv_cont_create(parent, nullptr);
        obj = draw_object<OBJECT>(o, parent, obj);
        lv_cont_set_fit2(obj, LV_FIT_NONE, LV_FIT_TIGHT);
        lv_cont_set_layout(obj, LV_LAYOUT_CENTER);
        lv_cont_set_style(obj, LV_CONT_STYLE_MAIN, &lv_style_transp);
    }

    if (o.contains("text"))
    {
        const auto & key = o["text"].get_ref<const std::string&>();
        lv_obj_t * lbl = lv_label_create(obj, nullptr);
        lv_label_set_text(lbl, key.c_str());
        lv_label_set_align(lbl, LV_LABEL_ALIGN_CENTER);
    }

    return obj;
}

template <>
lv_obj_t * draw_object<BUTTON>(const json & o,
        lv_obj_t * parent, lv_obj_t * obj)
{
    if (!obj)
        obj = lv_btn_create(parent, nullptr);

    obj = draw_object<OBJECT>(o, parent, obj);

    if (o.contains("text"))
    {
        const auto & key = o["text"].get_ref<const std::string&>();
        lv_obj_t * lbl = lv_label_create(obj, nullptr);
        lv_label_set_text(lbl, key.c_str());
    }

    return obj;
}

static void draw_component(const json & c, lv_obj_t * parent)
{
    const auto & id = c["id"].get_ref<const std::string&>();
    const auto type = c["type"].get<ComponentType>();
    linfo("component id=%s type=%u", id.c_str(), type);

    const auto& properties = c["properties"];
    switch (type)
    {
        case OBJECT:
            draw_object<OBJECT>(properties, parent);
            break;
        case BUTTON:
            draw_object<BUTTON>(properties, parent);
            break;
        case LABEL:
            draw_object<LABEL>(properties, parent);
            break;
        default:
            lwarn("component type not handled id=%s", id.c_str());
            break;
    }

}

static void draw_components(const json & components, lv_obj_t * parent)
{
    linfo("components size=%lu", components.size());
    for (const auto & c : components)
        draw_component(c, parent);
}

static void draw_page(const json & p, lv_obj_t * parent)
{
    const auto & id = p["id"].get_ref<const std::string &>();
    linfo("page id=%s", id.c_str());

    const auto & components = p["components"];
    draw_components(components, parent);
}

static void draw_pages(const json & pages, lv_obj_t * parent)
{
    linfo("pages size=%lu", pages.size());
    for (const auto & p : pages)
        draw_page(p, parent);
}

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

        SdlDisplay display(width, height);
        SdlPointer pointer;

        gui::Screen screen;

        Gui gui(display, pointer, screen);

        lv_obj_t * top = lv_cont_create(screen.get(), nullptr);
        lv_obj_set_height(top, 120);
        lv_cont_set_fit2(top, LV_FIT_FILL, LV_FIT_NONE);
        lv_cont_set_layout(top, LV_LAYOUT_ROW_M);
        lv_cont_set_style(top, LV_CONT_STYLE_MAIN, screen.style());
        (void) top;

        lv_obj_t * pages = lv_cont_create(screen.get(), nullptr);
        lv_cont_set_fit2(pages, LV_FIT_FILL, LV_FIT_FILL);
        lv_cont_set_layout(pages, LV_LAYOUT_GRID);
        lv_cont_set_style(pages, LV_CONT_STYLE_MAIN, screen.style());
        (void) pages;

        /* draw_components(app["components"], top); */
        /* draw_pages(app["pages"], pages); */

        return gui.loop();
    }
    catch (json::exception& e)
    {
        lerror("json exception id=%d message=%s", e.id, e.what());
        return 1;
    }
}
