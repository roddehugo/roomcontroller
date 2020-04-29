#include "gui.hh"
#include "logger.hh"
#include "lvgl/lvgl.h"

#include <fstream>
#include <iostream>
#include <string>

/* FIXME: use a dedicated source file. */
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

#include "nlohmann/json.hpp"
using json = nlohmann::json;

/* FIXME: need a File System to retrieve binary data from image files. */
LV_IMG_DECLARE(logo);

/* FIXME: cheap global for easier access, replace with better OOP. */
static const json * translations;
static const json::string_t * language;

/* FIXME: only use screen as background color style with transparent containers
 * on top to avoid such a global. */
static lv_style_t * screen_style;

/* FIXME: need to find a proper way to handle on the fly styles. */
static lv_style_t red_style;
static lv_style_t blue_style;

/* FIXME: use more appropriate wrapper around objects.
 * Use lv_obj_allocate_ext_attr with user defined extended data. This brings
 * some of the OO paradigms to C structs, see well documented article in blog:
 * https://blog.littlevgl.com/2018-12-13/extend-lvgl-objects
 *
 * // Example extended data of an ancestor.
 * typedef struct {
 *   int value1;
 *   int value2;
 * } ancestor_t;
 *
 * // Example extended data of a derived object.
 * typedef struct {
 *   ancestor_t ancestor;      // Include the ancestors extend data first.
 *   char * text;              // Add new data afterwards.
 * } derived_t;
 *
 * // Then, re-allocate extended data.
 * lv_obj_allocate_ext_attr(obj, sizeof(derived_t));
 * // And use it somewhere else, in callbacks for instance.
 * derived_t * ext = lv_obj_get_ext_attr(obj);
 *
 * TODO: one can use the extended data type to store application data. The big
 * advantage is that memory management is left to the library and the linked
 * list of objects. There is no *risk* of us mis-manipulating wrappers.
 * TODO: evaluate the pros/cons of doing C++ wrapping around lvgl objects (how
 * to deal with the memory management if C++ objects are higher-level
 * representations of lvgl objects (e.g. a GuiLabel would combine lv_cont with a
 * lv_lavel inside for better positioning).
 * Here are the options:
 * - create our own LinkedList of children and parents with C++; this should be
 *   feasible with signal callbacks to properly manage memory. But this will
 *   require a lot of verbosity to just wrap functions and bind application data
 *   with lvgl objects, events and signals. By storing a pointer to the C++
 *   object in the lv_obj_t struct as user_data, callbacks would be static but
 *   object instances can be de-referenced back (e.g. Sdl{Pointer,Display}).
 * - store application user data in object's extended data with custom types and
 *   write everything in plain C, or Orthodox C++, a minimal C++ subset of good
 *   and easy to apprehend features, no STL at all, only libc.
 * */
static void edit_event_cb(lv_obj_t * obj, lv_event_t event);
static void page_event_cb(lv_obj_t * obj, lv_event_t event);
static void language_event_cb(lv_obj_t * obj, lv_event_t event);
static void background_event_cb(lv_obj_t * obj, lv_event_t event);

/* FIXME: store this in plain json file once mostly done with prototyping. */
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
                    "text": "EDIT",
                    "toggle": true,
                    "target_edit": true
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
            "GO_TO_PAGE_A": "Aller a la page A",
            "I_AM_PAGE_B": "Je suis la page B",
            "GO_TO_PAGE_B": "Aller a la page B"
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
        const auto & c = o["background_color"];
        const auto & dsc = c.get_ref<const std::string &>();
        ltrace("object background color=%s", dsc.c_str());
        switch (c.get<Color>())
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
        assertm(language, "no language pointer");
        assertm(translations, "no translations data pointer");
        const auto & localized = translations->at(*language);
        const auto & key = o["text"].get_ref<const std::string &>();
        const auto & value = localized[key].get_ref<const std::string &>();
        lv_obj_t * lbl = lv_label_create(obj, nullptr);
        lv_label_set_static_text(lbl, value.c_str());
        lv_label_set_align(lbl, LV_LABEL_ALIGN_CENTER);

        /* FIXME: user_data is void, a better user data would be a C++ object.
         * Or actually use extended data attribute in lv_obj_t! */
        lbl->user_data = (void *) (key.c_str());
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
    /* FIXME: without tight fitting, everything goes wild in top container. */
    lv_btn_set_fit2(obj, LV_FIT_TIGHT, LV_FIT_TIGHT);

    /* FIXME: DRY, need a proper way of handling btn styles. */
    if (o.contains("background_color"))
    {
        const auto & c = o["background_color"];
        const auto & dsc = c.get_ref<const std::string &>();
        ltrace("object background color=%s", dsc.c_str());
        switch (c.get<Color>())
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
    }

    if (o.contains("toggle"))
    {
        bool toggle = o["toggle"].get<bool>();
        lv_btn_set_toggle(obj, toggle);
    }

    if (o.contains("text"))
    {
        assertm(language, "no language pointer");
        assertm(translations, "no translations data pointer");
        const auto & localized = translations->at(*language);
        const auto & key = o["text"].get_ref<const std::string &>();
        const auto & value = localized[key].get_ref<const std::string &>();
        lv_obj_t * lbl = lv_label_create(obj, nullptr);
        lv_label_set_static_text(lbl, value.c_str());

        /* FIXME: user_data is void, a better user data would be a C++ object.
         * Or actually use extended data attribute in lv_obj_t! */
        lbl->user_data = (void *) (key.c_str());
    }

    /* FIXME: user_data is void, a better user data would be a C++ object.
     * Or actually use extended data attribute in lv_obj_t! */
    obj->user_data = (void *) (&o);

    if (o.contains("target_edit"))
        lv_obj_set_event_cb(obj, edit_event_cb);
    if (o.contains("target_page"))
        lv_obj_set_event_cb(obj, page_event_cb);
    if (o.contains("target_language"))
        lv_obj_set_event_cb(obj, language_event_cb);
    if (o.contains("target_background"))
        lv_obj_set_event_cb(obj, background_event_cb);

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
    const auto & id = c["id"].get_ref<const std::string &>();
    const auto & type = c["type"];
    const auto & dsc = type.get_ref<const std::string &>();
    linfo("component id=%s type=%s", id.c_str(), dsc.c_str());

    const auto& properties = c["properties"];
    /* FIXME: template deduction cannot happen at runtime.
     * Use inheritance with some kind of factory method design pattern. */
    switch (type.get<ComponentType>())
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

static bool lv_obj_has_type(lv_obj_t * obj, const char * type)
{
    lv_obj_type_t types;
    lv_obj_get_type(obj, &types);
    for (int i = 0; i < LV_MAX_ANCESTOR_NUM; i++)
    {
        if(!types.type[i])
            break;
        else if(std::strcmp(types.type[i], type) == 0)
            return true;
    }
    return false;
}

static lv_obj_t * lv_obj_get_parent_by_type(lv_obj_t * obj, const char * type)
{
    lv_obj_t * parent = obj;
    while ((parent = lv_obj_get_parent(parent)))
    {
        if(lv_obj_has_type(parent, type))
            return parent;
    }
    return nullptr;
}

static void edit_event_cb(lv_obj_t * obj, lv_event_t event)
{
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        /* FIXME: lv_event_get_data() with temporary data stored in static void
         * pointer in lv_obj.c, see lv_event_send_func. Looks a little crappy to
         * me. Not sure why this is done like this, but I am not a fan at all.
         * In C++, with strong types, such static casting is then needed. And it
         * does not really looks good! Watch this API design and investigate why
         * it has been done like this. Ok it brings generic event handling with
         * a single lv_event_cb_t.
         * Ok, according to [documentation](overview/event.html#custom-data),
         * this is expected. */
        assertm(lv_obj_has_type(obj, "lv_btn"), "object is not a button");
        const bool state = *static_cast<const uint32_t*>(lv_event_get_data());
        linfo("edit event=value-changed state=%s", state ? "true" : "false");
    }
}

static void page_event_cb(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED)
    {
        /* FIXME: a better approach? Will assert if parent is not pages. */
        lv_obj_t * tabview = lv_obj_get_parent_by_type(obj, "lv_tabview");
        assertm(tabview, "tabview parent not found");

        lv_tabview_ext_t * ext =
            static_cast<lv_tabview_ext_t *> (lv_obj_get_ext_attr(tabview));
        unsigned count = ext->tab_cnt;
        const char ** names = ext->tab_name_ptr;

        const auto & o = *static_cast<const json *>(obj->user_data);
        const auto & p = o["target_page"].get_ref<const std::string &>();

        for(unsigned i = 0; i < count; i++)
        {
            if (std::strncmp(names[i], p.c_str(), p.size()) != 0)
            {
                linfo("event target=page value=%s", names[i]);
                lv_tabview_set_tab_act(tabview, i - 1, LV_ANIM_OFF);
            }
        }
    }
}

static void update_label_text_recursive(lv_ll_t * ll)
{
    lv_obj_t * obj = static_cast<lv_obj_t *>(lv_ll_get_head(ll));
    while (obj)
    {
        update_label_text_recursive(&obj->child_ll);

        if (lv_obj_has_type(obj, "lv_label"))
        {
            assertm(language, "no language pointer");
            assertm(translations, "no translations data pointer");
            const auto & localized = translations->at(*language);
            const char * key = (const char *) (obj->user_data);
            const auto & value = localized[key].get_ref<const std::string &>();
            lv_label_set_static_text(obj, value.c_str());
        }

        obj = static_cast<lv_obj_t *>(lv_ll_get_next(ll, obj));
    }
}

static void language_event_cb(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED)
    {
        const auto & o = *static_cast<const json *>(obj->user_data);
        const auto & l = o["target_language"].get_ref<const std::string &>();
        assertm(language, "no language pointer");
        if (language->compare(l) != 0)
        {
            language = &l;
            assertm(translations, "no translations data pointer");
            const auto & localized = translations->at(*language);
            linfo("event target=language value=%s size=%lu",
                    language->c_str(), localized.size());
            /* std::cout << std::setw(2) << localized << std::endl; */

            /* For each display. */
            lv_disp_t * d = nullptr;
            while((d = lv_disp_get_next(d)))
            {
                /* FIXME: might cost a lot if GUI has deep child nesting. */
                /* For each screen, and children recursively, depth first. */
                update_label_text_recursive(&d->scr_ll);
            }
        }
    }
}

static void background_event_cb(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED)
    {
        const auto & o = *static_cast<const json *>(obj->user_data);
        const auto & c = o["target_background"];
        const auto & dsc = c.get_ref<const std::string &>();
        linfo("event target=background value=%s", dsc.c_str());

        /* FIXME: DRY, need a proper way of handling color styles. */
        switch (c.get<Color>())
        {
            case RED:
                screen_style->body.main_color = LV_COLOR_RED;
                screen_style->body.grad_color = LV_COLOR_RED;
                break;
            case BLUE:
                screen_style->body.main_color = LV_COLOR_BLUE;
                screen_style->body.grad_color = LV_COLOR_BLUE;
                break;
            default:
                lwarn("object background not handled id=%s", "unknown");
                break;
        }
        lv_obj_report_style_mod(screen_style);
    }
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

        language = app["language"].get_ptr<const json::string_t *>();
        assertm(language, "no language pointer");
        translations = &j["translations"];
        assertm(translations, "no translations data pointer");
        const auto & localized = translations->at(*language);
        linfo("app language=%s size=%lu", language->c_str(), localized.size());

        SdlDisplay display(width, height);
        SdlPointer pointer;

        gui::Screen screen;
        screen_style = screen.style();

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

        /* TODO: understand when this is needed, and why? */
        /* lv_obj_set_auto_realign(top, true); */
        lv_cont_set_fit2(top, LV_FIT_FLOOD, LV_FIT_TIGHT);
        /* FIXME: with layout, pos properties are not taken into account. */
        /* lv_cont_set_layout(top, LV_LAYOUT_ROW_M); */
        lv_cont_set_style(top, LV_CONT_STYLE_MAIN, screen_style);
        describe("top after layout", top);

        draw_components(app["components"], top);
        describe("top after components", top);

        lv_obj_t * pages = lv_tabview_create(screen.get(), nullptr);
        describe("pages after creation", pages);

        lv_tabview_set_sliding(pages, false);
        lv_tabview_set_btns_hidden(pages, true);
        lv_tabview_set_style(pages, LV_TABVIEW_STYLE_BG, screen_style);
        /* TODO: understand when this is needed, and why? */
        /* lv_obj_set_auto_realign(pages, true); */
        /* FIXME: why do I have to compute it by myself? I'd expect the layout
         * system to handle it for me. It seems like sibling children does not
         * know each other and does not behave accordingly and in harmony in a
         * layout. Why? I am missing something? */
        int p = screen.style()->body.padding.inner;
        lv_obj_set_height(pages, height - lv_obj_get_height(top) - p * 3);
        describe("pages after components", pages);

        draw_pages(app["pages"], pages);
        describe("pages after components", pages);

        return gui.loop();
    }
    catch (json::exception& e)
    {
        /* FIXME: without exception handling, program aborts abruptly. */
        lerror("json exception id=%d message=%s", e.id, e.what());
        return 1;
    }
}
