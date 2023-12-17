// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <rapidjson_macros/rapidjson_macros>
#include <test_utility.hpp>
#include <test_ctor_getter_traits.hpp>

#include <sstream>
#include <algorithm>
RAPIDJSON_ALL_CTOR_GETTER_TRAITS(all_ctor_getter_trait_class, get_, bool, int32, int64, string, vector, array, map, dict, set);
RAPIDJSON_N_CTOR_GETTER_TRAITS(n_ctor_getter_trait_class, get_, 4, bool, uint32, uint64, string, list, array, map, dict, set);
RAPIDJSON_TPL_ALL_CTOR_GETTER_TRAITS(3, tpl_all_ctor_getter_trait_class, get_, type1, type2, type3);
RAPIDJSON_TPL_N_CTOR_GETTER_TRAITS(3, tpl_n_ctor_getter_trait_class, get_, 2, type1, type2, type3);

using namespace rapidjson_macros;

TEMPLATE_TEST_CASE_SIG("ALL_CTOR_GETTER_TRAITS", "[ALL][CTOR_GETTER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<all_ctor_getter_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<all_ctor_getter_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<all_ctor_getter_trait_class, Enc>(
                STR_LITERAL(R"(
                {
                    "bool": true,
                    "int32": 1234,
                    "int64": "Lupercal",
                    "string": 546,
                    "vector": [10,20,30,40],
                    "array": [0,1],
                    "map": {
                        "battle-brother": "legion",
                        "traitor": "serpent"  
                    },
                    "dict": [[0,0.5],[1,1.5]],
                    "set": [-5,0,10]
                }
            )")));
        }
        auto val = as<all_ctor_getter_trait_class, Enc>(
            STR_LITERAL(R"(
                {
                    "bool": true,
                    "int32": -1234,
                    "int64": 5678,
                    "string": "Lupercal",
                    "vector": [10,20,30,40],
                    "array": [0,1],
                    "map": [[0,0.5],[1,1.5]],
                    "dict": {
                        "battle-brother": "legion",
                        "traitor": "serpent"  
                    },
                    "set": [-5,0,10]
                }
            )"));
        CHECK(val.get_bool() == true);
        CHECK(val.get_int32() == -1234);
        CHECK(val.get_int64() == 5678);
        CHECK(val.get_string() == "Lupercal");

        CHECK(val.get_vector().size() == 4);
        for (int i = 0; i < val.get_vector().size(); i++)
            CHECK(val.get_vector()[i] == (i * 10) + 10);

        CHECK(val.get_array()[0] == 0);
        CHECK(val.get_array()[1] == 1);

        CHECK(val.get_map().size() == 2);
        CHECK(val.get_map().at(0) == 0.5);
        CHECK(val.get_map().at(1) == 1.5);

        CHECK(val.get_map().size() == 2);
        CHECK(val.get_map().at(0) == 0.5);
        CHECK(val.get_map().at(1) == 1.5);

        CHECK(val.get_dict().size() == 2);
        CHECK(val.get_dict().at("battle-brother") == "legion");
        CHECK(val.get_dict().at("traitor") == "serpent");

        CHECK(val.get_set().size() == 3);
        CHECK(val.get_set().count(0) == 1);
        CHECK(val.get_set().count(-5) == 1);
        CHECK(val.get_set().count(10) == 1);
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        all_ctor_getter_trait_class val(true, -1234, 5678, "Lupercal", {10, 20, 30, 40}, {0, 1}, {{0, 0.5}, {1, 1.5}}, {{"traitor", "serpent"}, {"battle-brother", "legion"}}, {0, -5, 10});

        auto json = to_json<all_ctor_getter_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("bool")));
        CHECK(json[STR_LITERAL("bool")].GetBool() == true);

        REQUIRE(json.HasMember(STR_LITERAL("int32")));
        CHECK(json[STR_LITERAL("int32")].GetInt() == -1234);

        REQUIRE(json.HasMember(STR_LITERAL("int64")));
        CHECK(json[STR_LITERAL("int64")].GetInt64() == 5678);

        REQUIRE(json.HasMember(STR_LITERAL("string")));
        CHECK(test::compare_cstring(json[STR_LITERAL("string")], STR_LITERAL("Lupercal")));

        REQUIRE(json.HasMember(STR_LITERAL("vector")));
        CHECK(json[STR_LITERAL("vector")].GetArray().Size() == 4);
        int size = json[STR_LITERAL("vector")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("vector")].GetArray()[i] == (i * 10) + 10);

        REQUIRE(json.HasMember(STR_LITERAL("array")));
        CHECK(json[STR_LITERAL("array")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("array")].GetArray()[1] == 1);

        REQUIRE(json.HasMember(STR_LITERAL("map")));
        CHECK(json[STR_LITERAL("map")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("map")].GetArray()[0].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("map")].GetArray()[0].GetArray()[1] == 0.5);
        CHECK(json[STR_LITERAL("map")].GetArray()[1].GetArray()[0] == 1);
        CHECK(json[STR_LITERAL("map")].GetArray()[1].GetArray()[1] == 1.5);

        REQUIRE(json.HasMember(STR_LITERAL("dict")));
        CHECK(json[STR_LITERAL("dict")].GetArray().Size() == 2);
        CHECK(test::compare_cstring(json[STR_LITERAL("dict")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));
        CHECK(test::compare_cstring(json[STR_LITERAL("dict")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));

        REQUIRE(json.HasMember(STR_LITERAL("set")));
        CHECK(json[STR_LITERAL("set")].GetArray().Size() == 3);
        CHECK(json[STR_LITERAL("set")].GetArray()[0].GetInt() == -5);
        CHECK(json[STR_LITERAL("set")].GetArray()[1].GetInt() == 0);
        CHECK(json[STR_LITERAL("set")].GetArray()[2].GetInt() == 10);
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        all_ctor_getter_trait_class val(true, -1234, 5678, "Lupercal", {10, 20, 30, 40}, {0, 1}, {{0, 0.5}, {1, 1.5}}, {{"traitor", "serpent"}, {"battle-brother", "legion"}}, {0, -5, 10});

        to_stream<all_ctor_getter_trait_class, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "bool": true,
                    "int32": -1234,
                    "int64": 5678,
                    "string": "Lupercal",
                    "vector": [10,20,30,40],
                    "array": [0,1],
                    "map": [[0,0.5],[1,1.5]],
                    "dict": {
                        "battle-brother": "legion",
                        "traitor": "serpent"
                    },
                    "set": [-5,0,10]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("N_CTOR_GETTER_TRAITS", "[N][CTOR_GETTER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<n_ctor_getter_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<n_ctor_getter_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<n_ctor_getter_trait_class, Enc>(
                STR_LITERAL(R"(
                {
                    "bool": {
                            "battle-brother": "legion",
                            "traitor": "serpent"
                        },
                    "uint32": 1234,
                    "uint64": [10.0,20.0,30.0,40.0],
                    "string": 546,
                    "list": "Lupercal",
                    "array": [0,1],
                    "map": [[0,"Human"],[1,"God"]],
                    "dict": false,
                    "set": [0,-5,10]
                }
            )")));
        }
        SECTION("with all parameter")
        {
            auto val = as<n_ctor_getter_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "bool": false,
                        "uint32": 1234,
                        "uint64": 5678,
                        "string": "Lupercal",
                        "list": [10.0,20.0,30.0,40.0],
                        "array": [0,1],
                        "map": [[0,"Human"],[1,"God"]],
                        "dict": {
                            "battle-brother": "legion",
                            "traitor": "serpent"                            
                        },
                        "set": [2,5,10]
                    }
                )"));
            CHECK(val.get_bool() == false);
            CHECK(val.get_uint32() == 1234);
            CHECK(val.get_uint64() == 5678);
            CHECK(!strcmp(val.get_string(), "Lupercal"));

            CHECK(val.get_list().size() == 4);
            int i = 0;
            for (auto& e : val.get_list())
                CHECK(e == (i++ * 10) + 10);

            CHECK(val.get_array()[0] == 0);
            CHECK(val.get_array()[1] == 1);

            CHECK(val.get_map().size() == 2);
            CHECK(val.get_map().at(0) == "Human");
            CHECK(val.get_map().at(1) == "God");

            CHECK(val.get_dict().size() == 2);
            CHECK(val.get_dict().at("traitor") == "serpent");
            CHECK(val.get_dict().at("battle-brother") == "legion");

            CHECK(val.get_set().size() == 3);
            CHECK(val.get_set().count(2) == 1);
            CHECK(val.get_set().count(5) == 1);
            CHECK(val.get_set().count(10) == 1);
        }

        SECTION("with some optional parameters")
        {
            auto val = as<n_ctor_getter_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "bool": false,
                        "uint32": 1234,
                        "uint64": 5678,
                        "string": "Lupercal",
                        "list": [10.0,20.0,30.0,40.0],
                        "array": [0,1],
                        "map": [[0,"Human"],[1,"God"]]
                    }
                )"));
            CHECK(val.get_bool() == false);
            CHECK(val.get_uint32() == 1234);
            CHECK(val.get_uint64() == 5678);
            CHECK(!strcmp(val.get_string(), "Lupercal"));

            CHECK(val.get_list().size() == 4);
            int i = 0;
            for (auto& e : val.get_list())
                CHECK(e == (i++ * 10) + 10);

            CHECK(val.get_array()[0] == 0);
            CHECK(val.get_array()[1] == 1);

            CHECK(val.get_map().size() == 2);
            CHECK(val.get_map().at(0) == "Human");
            CHECK(val.get_map().at(1) == "God");

            CHECK(val.get_dict().size() == 0);
            CHECK(val.get_set().size() == 0);
        }

        SECTION("with only required parameters")
        {
            auto val = as<n_ctor_getter_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "bool": false,
                        "uint32": 1234,
                        "uint64": 5678,
                        "string": "Lupercal"
                    }
                )"));
            CHECK(val.get_bool() == false);
            CHECK(val.get_uint32() == 1234);
            CHECK(val.get_uint64() == 5678);
            CHECK(!strcmp(val.get_string(), "Lupercal"));

            CHECK(val.get_list().size() == 0);
            CHECK(val.get_map().size() == 0);
            CHECK(val.get_dict().size() == 0);
            CHECK(val.get_set().size() == 0);
        }
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        n_ctor_getter_trait_class val(
            false, 1234, 5678, "Lupercal",
            {10.0, 20.0, 30.0, 40.0},
            {0, 1},
            {{0, "Human"}, {1, "God"}},
            {{"traitor", "serpent"}, {"battle-brother", "legion"}},
            {2, 5, 10});

        auto json = to_json<n_ctor_getter_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("bool")));
        CHECK(json[STR_LITERAL("bool")].GetBool() == false);

        REQUIRE(json.HasMember(STR_LITERAL("uint32")));
        CHECK(json[STR_LITERAL("uint32")].GetInt() == 1234);

        REQUIRE(json.HasMember(STR_LITERAL("uint64")));
        CHECK(json[STR_LITERAL("uint64")].GetInt64() == 5678);

        REQUIRE(json.HasMember(STR_LITERAL("string")));
        CHECK(test::compare_cstring(json[STR_LITERAL("string")], STR_LITERAL("Lupercal")));

        REQUIRE(json.HasMember(STR_LITERAL("list")));
        CHECK(json[STR_LITERAL("list")].GetArray().Size() == 4);
        int size = json[STR_LITERAL("list")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("list")].GetArray()[i] == (i * 10) + 10);

        REQUIRE(json.HasMember(STR_LITERAL("array")));
        CHECK(json[STR_LITERAL("array")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("array")].GetArray()[1] == 1);

        REQUIRE(json.HasMember(STR_LITERAL("map")));
        auto map = json[STR_LITERAL("map")].GetArray();

        CHECK(map.Size() == 2);
        CHECK(test::array_contains<Enc>(map, [](auto it) {
            return it->GetArray()[0].GetInt() == 0 &&
                   test::compare_cstring(it->GetArray()[1], STR_LITERAL("Human"));
        }));
        CHECK(test::array_contains<Enc>(map, [](auto it) {
            return it->GetArray()[0].GetInt() == 1 &&
                   test::compare_cstring(it->GetArray()[1], STR_LITERAL("God"));
        }));

        REQUIRE(json.HasMember(STR_LITERAL("dict")));
        CHECK(test::compare_cstring(json[STR_LITERAL("dict")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));
        CHECK(test::compare_cstring(json[STR_LITERAL("dict")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));

        REQUIRE(json.HasMember(STR_LITERAL("set")));
        auto set = json[STR_LITERAL("set")].GetArray();

        CHECK(set.Size() == 3);
        CHECK(test::array_contains<Enc>(set, [](auto it) { return *it == 2; }));
        CHECK(test::array_contains<Enc>(set, [](auto it) { return *it == 5; }));
        CHECK(test::array_contains<Enc>(set, [](auto it) { return *it == 10; }));
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        n_ctor_getter_trait_class val(
            false, 1234, 5678, "Lupercal",
            {10.0, 20.0, 30.0, 40.0},
            {0, 1},
            {{0, "Human"}, {1, "God"}},
            {{"traitor", "serpent"}, {"battle-brother", "legion"}},
            {2, 5, 10});

        to_stream<n_ctor_getter_trait_class, Enc>(ss, val);
        auto value = ss.str();

        using AnyString = std::basic_string<typename Enc::Ch>;
        AnyString output = STR_LITERAL(R"(
                {
                    "bool": false,
                    "uint32": 1234,
                    "uint64": 5678,
                    "string": "Lupercal",
                    "list": [10.0,20.0,30.0,40.0],
                    "array": [0,1],
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        // unordered type does not guaranteed to have the same order
        // regex is not implemented for char32_t

        auto currPos = value.find(output);
        CHECK(currPos != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("map":)"), currPos);
        CHECK(currPos != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"([0,"Human"])"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"([1,"God"])"), currPos) != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("dict":)"), currPos);
        CHECK(currPos != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"("traitor":"serpent")"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"("battle-brother":"legion")"), currPos) != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("set":)"), currPos);
        CHECK(value.find(STR_LITERAL("2"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL("5"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL("10"), currPos) != AnyString::npos);

        CHECK(value.find(STR_LITERAL("}"), currPos) != AnyString::npos);
    }
}

TEMPLATE_TEST_CASE_SIG("TPL_ALL_CTOR_GETTER_TRAITS", "[TPL][ALL][CTOR_GETTER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_all_ctor_getter_trait_class_isv = tpl_all_ctor_getter_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_all_ctor_getter_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_all_ctor_getter_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_all_ctor_getter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                {
                    "type1": "",
                    "type2": "",
                    "type3": ""
                }
            )")));
        }
        auto val = as<tpl_all_ctor_getter_trait_class_isv, Enc>(
            STR_LITERAL(R"(
                {
                    "type1": 162,
                    "type2": "Davin's moon",
                    "type3": [45.1,55.5]
                }
            )"));
        CHECK(val.get_type1() == 162);
        CHECK(val.get_type2() == "Davin's moon");

        CHECK(val.get_type3().size() == 2);
        CHECK(val.get_type3()[0] == 45.1f);
        CHECK(val.get_type3()[1] == 55.5f);
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        tpl_all_ctor_getter_trait_class_isv val(162, "Davin's moon", {45.1f, 55.5f});

        auto json = to_json<tpl_all_ctor_getter_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("type1")));
        CHECK(json[STR_LITERAL("type1")].GetInt() == 162);

        REQUIRE(json.HasMember(STR_LITERAL("type2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("type2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("type3")));
        CHECK(json[STR_LITERAL("type3")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("type3")].GetArray()[0] == 45.1f);
        CHECK(json[STR_LITERAL("type3")].GetArray()[1] == 55.5f);
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        tpl_all_ctor_getter_trait_class_isv val(162, "Davin's_moon", {45.1f, 55.5f});

        to_stream<tpl_all_ctor_getter_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "type1": 162,
                    "type2": "Davin's_moon",
                    "type3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("TPL_N_CTOR_GETTER_TRAITS", "[TPL][N][CTOR_GETTER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_n_ctor_getter_trait_class_isv = tpl_n_ctor_getter_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_n_ctor_getter_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_n_ctor_getter_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_n_ctor_getter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                {
                    "type1": "",
                    "type2": "",
                    "type3": ""
                }
            )")));
        }
        SECTION("with all parameter")
        {
            auto val = as<tpl_n_ctor_getter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "type1": 162,
                        "type2": "Davin's moon",
                        "type3": [45.1,55.5]
                    }
                )"));
            CHECK(val.get_type1() == 162);
            CHECK(val.get_type2() == "Davin's moon");

            CHECK(val.get_type3().size() == 2);
            CHECK(val.get_type3()[0] == 45.1f);
            CHECK(val.get_type3()[1] == 55.5f);
        }

        SECTION("with only required parameters")
        {
            auto val = as<tpl_n_ctor_getter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "type1": 162,
                        "type2": "Davin's moon"
                    }
                )"));
            CHECK(val.get_type1() == 162);
            CHECK(val.get_type2() == "Davin's moon");

            CHECK(val.get_type3().size() == 0);
        }
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        tpl_n_ctor_getter_trait_class_isv val(162, "Davin's moon", {45.1f, 55.5f});

        auto json = to_json<tpl_n_ctor_getter_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("type1")));
        CHECK(json[STR_LITERAL("type1")].GetInt() == 162);

        REQUIRE(json.HasMember(STR_LITERAL("type2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("type2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("type3")));
        CHECK(json[STR_LITERAL("type3")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("type3")].GetArray()[0] == 45.1f);
        CHECK(json[STR_LITERAL("type3")].GetArray()[1] == 55.5f);
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        tpl_n_ctor_getter_trait_class_isv val(162, "Davin's_moon", {45.1f, 55.5f});

        to_stream<tpl_n_ctor_getter_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "type1": 162,
                    "type2": "Davin's_moon",
                    "type3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}
