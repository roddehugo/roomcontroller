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

LV_IMG_DECLARE(logo);

static const json * localized;

static lv_style_t red_style;
static lv_style_t blue_style;

static const auto& data = R"({
    "app": {
        "width": 800,
        "height": 480,
        "language": "en",
        "page": "page_a",
        "components": [
            {
                "id": "logo",
                "type": "image",
                "properties": {
                    "x": 5,
                    "y": 5,
                    "source": "logo"
                }
            },
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
                    "background_color": "blue",
                    "target_background": "blue"
                }
            },
            {
                "id": "red",
                "type": "button",
                "properties": {
                    "x": 400,
                    "y": 5,
                    "text": "RED",
                    "background_color": "red",
                    "target_background": "red"
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
    "translations": {
        "en": {
            "EDIT": "Edit",
            "RED": "Red",
            "BLUE": "Blue",
            "SWITCH_TO_FRENCH": "FR",
            "SWITCH_TO_ENGLISH": "EN",
            "I_AM_PAGE_A": "I am page A",
            "GO_TO_PAGE_A": "Go to page A",
            "I_AM_PAGE_B": "I am page B",
            "GO_TO_PAGE_B": "Go to page B"
        },
        "fr": {
            "EDIT": "Editer",
            "RED": "Rouge",
            "BLUE": "Bleu",
            "SWITCH_TO_FRENCH": "FR",
            "SWITCH_TO_ENGLISH": "EN",
            "I_AM_PAGE_A": "Je suis la page A",
            "GO_TO_PAGE_A": "Aller à la page A",
            "I_AM_PAGE_B": "Je suis la page B",
            "GO_TO_PAGE_B": "Aller à la page B"
        }
    }
})";

enum ComponentType
{
    OBJECT,
    BUTTON,
    LABEL,
    IMAGE,
};

NLOHMANN_JSON_SERIALIZE_ENUM(ComponentType,
{
    {OBJECT, "object"},
    {BUTTON, "button"},
    {LABEL, "label"},
    {IMAGE, "image"},
})

enum Color
{
    DEFAULT,
    RED,
    BLUE,
};

NLOHMANN_JSON_SERIALIZE_ENUM(Color,
{
    {DEFAULT, "default"},
    {RED, "red"},
    {BLUE, "blue"},
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

    if (o.contains("background_color"))
    {
        const auto color = o["background_color"].get<Color>();
        switch (color)
        {
            case RED:
                lv_obj_set_style(obj, &red_style);
                break;
            case BLUE:
                lv_obj_set_style(obj, &blue_style);
                break;
            default:
                lwarn("object background not handled id=%s", "unknown");
                break;
        }
        ltrace("object background color=%u", color);
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
        assertm(localized, "no localized data pointer");
        const auto & key = o["text"].get_ref<const std::string&>();
        const auto & value = localized->at(key).get_ref<const std::string&>();
        lv_obj_t * lbl = lv_label_create(obj, nullptr);
        lv_label_set_text(lbl, value.c_str());
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

    if (o.contains("background_color"))
    {
        const auto color = o["background_color"].get<Color>();
        switch (color)
        {
            case RED:
                lv_btn_set_style(obj, LV_BTN_STYLE_REL, &red_style);
                break;
            case BLUE:
                lv_btn_set_style(obj, LV_BTN_STYLE_REL, &blue_style);
                break;
            default:
                lwarn("object background not handled id=%s", "unknown");
                break;
        }
        ltrace("object background color=%u", color);
    }

    if (o.contains("text"))
    {
        assertm(localized, "no localized data pointer");
        const auto & key = o["text"].get_ref<const std::string&>();
        const auto & value = localized->at(key).get_ref<const std::string&>();
        lv_obj_t * lbl = lv_label_create(obj, nullptr);
        lv_label_set_text(lbl, value.c_str());
    }

    return obj;
}

template <>
lv_obj_t * draw_object<IMAGE>(const json & o,
        lv_obj_t * parent, lv_obj_t * obj)
{
    if (!obj)
        obj = lv_img_create(parent, nullptr);

    obj = draw_object<OBJECT>(o, parent, obj);

    if (o.contains("source"))
    {
        lv_img_set_src(obj, &logo);
        lv_img_set_auto_size(obj, true);
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
        case IMAGE:
            draw_object<IMAGE>(properties, parent);
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
    lv_obj_t * page = lv_tabview_add_tab(parent, id.c_str());
    linfo("page id=%s", id.c_str());

    const auto & components = p["components"];
    draw_components(components, page);
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

        const auto & translations = j["translations"];
        const auto & language = app["language"].get_ref<const std::string&>();
        localized = &translations[language];
        linfo("app language=%s size=%lu", language.c_str(), localized->size());

        SdlDisplay display(width, height);
        SdlPointer pointer;

        gui::Screen screen;

        Gui gui(display, pointer, screen);

        auto * theme = lv_theme_get_current();
        lv_style_copy(&red_style, theme->style.btn.rel);
        red_style.body.main_color = LV_COLOR_RED;
        red_style.body.grad_color = LV_COLOR_RED;
        lv_style_copy(&blue_style, theme->style.btn.rel);
        blue_style.body.main_color = LV_COLOR_BLUE;
        blue_style.body.grad_color = LV_COLOR_BLUE;

        lv_obj_t * top = lv_cont_create(screen.get(), nullptr);
        describe("top after creation", top);

        lv_obj_set_auto_realign(top, true);
        lv_cont_set_fit2(top, LV_FIT_FLOOD, LV_FIT_TIGHT);
        lv_cont_set_layout(top, LV_LAYOUT_ROW_M);
        lv_cont_set_style(top, LV_CONT_STYLE_MAIN, screen.style());
        describe("top after layout", top);

        draw_components(app["components"], top);
        describe("top after components", top);

        lv_obj_t * pages = lv_tabview_create(screen.get(), nullptr);
        describe("pages after creation", pages);

        lv_tabview_set_sliding(pages, false);
        lv_tabview_set_btns_hidden(pages, true);
        lv_tabview_set_style(pages, LV_TABVIEW_STYLE_BG, screen.style());
        int p = screen.style()->body.padding.inner;
        lv_obj_set_auto_realign(pages, true);
        lv_obj_set_height(pages, height - lv_obj_get_height(top) - p * 3);
        describe("pages after components", pages);

        draw_pages(app["pages"], pages);
        describe("pages after components", pages);

        return gui.loop();
    }
    catch (json::exception& e)
    {
        lerror("json exception id=%d message=%s", e.id, e.what());
        return 1;
    }
}
