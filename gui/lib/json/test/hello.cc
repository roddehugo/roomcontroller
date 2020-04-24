#include "nlohmann/json.hpp"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using json = nlohmann::json;

static void test_dump()
{
    // Create a JSON object.
    /* clang-format off. */
    json j =
    {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };
    /* clang-format on */

    // Add new values.
    j["new"]["key"]["value"] = {"another", "list"};

    // Count elements.
    auto s = j.size();
    j["size"] = s;

    // Pretty print with indent of 4 spaces.
    std::cout << std::setw(2) << j << std::endl;
}

static void test_sstream()
{
    // Create stream with serialized JSON.
    std::stringstream ss;
    ss << R"({
        "number": 23,
        "string": "Hello, world!",
        "array": [1, 2, 3, 4, 5],
        "boolean": false,
        "null": null
    })";

    // Create JSON value and read the serialization from the stream.
    json j;
    ss >> j;

    // Perform basic checks.
    assert(!j.empty());
    assert(j.is_array());

    // Serialize JSON.
    std::cout << "json contains " << j.size() << " items" << std::endl;
    std::cout << std::setw(2) << j << std::endl;
}

static void test_ifstream()
{
    // Create filestream with serialized JSON.
    std::ifstream ifs("hello.json");
    json j;
    ifs >> j;

    // Perform basic checks.
    assert(!j.empty());
    assert(j.is_array());

    // Print all ids.
    std::cout << "json contains " << j.size() << " items" << std::endl;
    for (auto & i : j)
        std::cout << "id: " << i.at("id") << '\n';
}

namespace ns
{

struct inner;
void to_json(json & j, const inner & i);
void from_json(const json & j, inner & i);

struct object;
void to_json(json & j, const object & o);
void from_json(const json & j, object & o);

struct inner
{
    int id;
    std::string hash;
};

void to_json(json & j, const inner & i)
{
    j = json{
        {"id", i.id},
        {"hash", i.hash},
    };
}

void from_json(const json & j, inner & i)
{
    j.at("id").get_to(i.id);
    j.at("hash").get_to(i.hash);
}

struct object
{
    int number;
    bool boolean;
    std::string string;
    std::nullptr_t null;
    std::vector<inner> inners;
};

void to_json(json & j, const object & o)
{
    j = json{
        {"number", o.number},
        {"boolean", o.boolean},
        {"string", o.string},
        {"null", o.null},
        {"inners", o.inners},
    };
}

void from_json(const json & j, object & o)
{
    j.at("number").get_to(o.number);
    j.at("boolean").get_to(o.boolean);
    j.at("string").get_to(o.string);
    j.at("null").get_to(o.null);
    j.at("inners").get_to(o.inners);
}

} // namespace ns

static void test_struct()
{
    const auto & data = R"({
        "number": 23,
        "boolean": true,
        "string": "Hello, world!",
        "null": null,
        "inners": [
            {"id": 1, "hash": "5ea2e54d"},
            {"id": 2, "hash": "7261da5e"}
        ]
    })";
    auto j = json::parse(data);

    // Perform basic checks.
    assert(!j.empty());
    assert(j.is_array());

    // Report parsed data.
    auto obj = j.get<ns::object>();
    std::cout << "json contains " << j.size() << " items" << std::endl;
    std::cout << "object: " << (obj.null == nullptr ? "null " : "not null ")
              << obj.number << " " << obj.string << " " << obj.boolean
              << " with inners:" << std::endl;

    for (const auto & i : obj.inners)
        std::cout << "inner: " << i.id << " " << i.hash << std::endl;
}

int main()
{
    test_dump();
    test_sstream();
    test_ifstream();
    test_struct();
    return 0;
}
