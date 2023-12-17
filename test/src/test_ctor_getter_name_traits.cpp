// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <rapidjson_macros/rapidjson_macros>
#include <test_utility.hpp>
#include <test_ctor_getter_name_traits.hpp>

#include <sstream>
#include <algorithm>

RAPIDJSON_ALL_CTOR_GETTER_NAME_TRAITS(all_ctor_getter_name_trait_class,
                                      (get_bool, "b"),
                                      (get_int32, "i32"),
                                      (get_int64, "i64"),
                                      (get_string, "str"),
                                      (get_vector, "v"),
                                      (get_array, "a"),
                                      (get_map, "m"),
                                      (get_dict, "d"),
                                      (get_set, "set"));
RAPIDJSON_N_CTOR_GETTER_NAME_TRAITS(n_ctor_getter_name_trait_class, 4,
                                    (get_bool, "b"),
                                    (get_uint32, "u32"),
                                    (get_uint64, "u64"),
                                    (get_string, "str"),
                                    (get_list, "l"),
                                    (get_array, "a"),
                                    (get_map, "m"),
                                    (get_dict, "d"),
                                    (get_set, "set"));
RAPIDJSON_TPL_ALL_CTOR_GETTER_NAME_TRAITS(3, tpl_all_ctor_getter_name_trait_class, (get_type1, "t1"), (get_type2, "t2"), (get_type3, "t3"));
RAPIDJSON_TPL_N_CTOR_GETTER_NAME_TRAITS(3, tpl_n_ctor_getter_name_trait_class, 2, (get_type1, "t1"), (get_type2, "t2"), (get_type3, "t3"));

using namespace rapidjson_macros;

TEMPLATE_TEST_CASE_SIG("ALL_CTOR_GETTER_NAME_TRAITS", "[ALL][CTOR_GETTER_NAME]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<all_ctor_getter_name_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<all_ctor_getter_name_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<all_ctor_getter_name_trait_class, Enc>(
                STR_LITERAL(R"(
                {
                    "b": true,
                    "i32": 1234,
                    "i64": "Lupercal",
                    "str": 546,
                    "v": [10,20,30,40],
                    "a": [0,1],
                    "m": {
                        "battle-brother": "legion",
                        "traitor": "serpent"  
                    },
                    "d": [[0,0.5],[1,1.5]],
                    "set": [-5,0,10]
                }
            )")));
        }
        auto val = as<all_ctor_getter_name_trait_class, Enc>(
            STR_LITERAL(R"(
                {
                    "b": true,
                    "i32": -1234,
                    "i64": 5678,
                    "str": "Lupercal",
                    "v": [10,20,30,40],
                    "a": [0,1],
                    "m": [[0,0.5],[1,1.5]],
                    "d": {
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

        all_ctor_getter_name_trait_class val(true, -1234, 5678, "Lupercal", {10, 20, 30, 40}, {0, 1}, {{0, 0.5}, {1, 1.5}}, {{"traitor", "serpent"}, {"battle-brother", "legion"}}, {0, -5, 10});

        auto json = to_json<all_ctor_getter_name_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("b")));
        CHECK(json[STR_LITERAL("b")].GetBool() == true);

        REQUIRE(json.HasMember(STR_LITERAL("i32")));
        CHECK(json[STR_LITERAL("i32")].GetInt() == -1234);

        REQUIRE(json.HasMember(STR_LITERAL("i64")));
        CHECK(json[STR_LITERAL("i64")].GetInt64() == 5678);

        REQUIRE(json.HasMember(STR_LITERAL("str")));
        CHECK(test::compare_cstring(json[STR_LITERAL("str")], STR_LITERAL("Lupercal")));

        REQUIRE(json.HasMember(STR_LITERAL("v")));
        CHECK(json[STR_LITERAL("v")].GetArray().Size() == 4);
        int size = json[STR_LITERAL("v")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("v")].GetArray()[i] == (i * 10) + 10);

        REQUIRE(json.HasMember(STR_LITERAL("a")));
        CHECK(json[STR_LITERAL("a")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("a")].GetArray()[1] == 1);

        REQUIRE(json.HasMember(STR_LITERAL("m")));
        CHECK(json[STR_LITERAL("m")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("m")].GetArray()[0].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("m")].GetArray()[0].GetArray()[1] == 0.5);
        CHECK(json[STR_LITERAL("m")].GetArray()[1].GetArray()[0] == 1);
        CHECK(json[STR_LITERAL("m")].GetArray()[1].GetArray()[1] == 1.5);

        REQUIRE(json.HasMember(STR_LITERAL("d")));
        CHECK(json[STR_LITERAL("d")].GetArray().Size() == 2);
        CHECK(test::compare_cstring(json[STR_LITERAL("d")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));
        CHECK(test::compare_cstring(json[STR_LITERAL("d")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));

        REQUIRE(json.HasMember(STR_LITERAL("set")));
        CHECK(json[STR_LITERAL("set")].GetArray().Size() == 3);
        CHECK(json[STR_LITERAL("set")].GetArray()[0].GetInt() == -5);
        CHECK(json[STR_LITERAL("set")].GetArray()[1].GetInt() == 0);
        CHECK(json[STR_LITERAL("set")].GetArray()[2].GetInt() == 10);
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        all_ctor_getter_name_trait_class val(true, -1234, 5678, "Lupercal", {10, 20, 30, 40}, {0, 1}, {{0, 0.5}, {1, 1.5}}, {{"traitor", "serpent"}, {"battle-brother", "legion"}}, {0, -5, 10});

        to_stream<all_ctor_getter_name_trait_class, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "b": true,
                    "i32": -1234,
                    "i64": 5678,
                    "str": "Lupercal",
                    "v": [10,20,30,40],
                    "a": [0,1],
                    "m": [[0,0.5],[1,1.5]],
                    "d": {
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

TEMPLATE_TEST_CASE_SIG("N_CTOR_GETTER_NAME_TRAITS", "[N][CTOR_GETTER_NAME]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<n_ctor_getter_name_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<n_ctor_getter_name_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<n_ctor_getter_name_trait_class, Enc>(
                STR_LITERAL(R"(
                {
                    "b": {
                            "battle-brother": "legion",
                            "traitor": "serpent"
                        },
                    "u32": 1234,
                    "u64": [10.0,20.0,30.0,40.0],
                    "str": 546,
                    "l": "Lupercal",
                    "a": [0,1],
                    "m": [[0,"Human"],[1,"God"]],
                    "d": false,
                    "set": [0,-5,10]
                }
            )")));
        }
        SECTION("with all parameter")
        {
            auto val = as<n_ctor_getter_name_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "b": false,
                        "u32": 1234,
                        "u64": 5678,
                        "str": "Lupercal",
                        "l": [10.0,20.0,30.0,40.0],
                        "a": [0,1],
                        "m": [[0,"Human"],[1,"God"]],
                        "d": {
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

        SECTION("with some optional parameter")
        {
            auto val = as<n_ctor_getter_name_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "b": false,
                        "u32": 1234,
                        "u64": 5678,
                        "str": "Lupercal",
                        "l": [10.0,20.0,30.0,40.0],
                        "a": [0,1],
                        "m": [[0,"Human"],[1,"God"]]
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
            auto val = as<n_ctor_getter_name_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "b": false,
                        "u32": 1234,
                        "u64": 5678,
                        "str": "Lupercal"
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

        n_ctor_getter_name_trait_class val(
            false, 1234, 5678, "Lupercal",
            {10.0, 20.0, 30.0, 40.0},
            {0, 1},
            {{0, "Human"}, {1, "God"}},
            {{"traitor", "serpent"}, {"battle-brother", "legion"}},
            {2, 5, 10});

        auto json = to_json<n_ctor_getter_name_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("b")));
        CHECK(json[STR_LITERAL("b")].GetBool() == false);

        REQUIRE(json.HasMember(STR_LITERAL("u32")));
        CHECK(json[STR_LITERAL("u32")].GetInt() == 1234);

        REQUIRE(json.HasMember(STR_LITERAL("u64")));
        CHECK(json[STR_LITERAL("u64")].GetInt64() == 5678);

        REQUIRE(json.HasMember(STR_LITERAL("str")));
        CHECK(test::compare_cstring(json[STR_LITERAL("str")], STR_LITERAL("Lupercal")));

        REQUIRE(json.HasMember(STR_LITERAL("l")));
        CHECK(json[STR_LITERAL("l")].GetArray().Size() == 4);
        int size = json[STR_LITERAL("l")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("l")].GetArray()[i] == (i * 10) + 10);

        REQUIRE(json.HasMember(STR_LITERAL("a")));
        CHECK(json[STR_LITERAL("a")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("a")].GetArray()[1] == 1);

        REQUIRE(json.HasMember(STR_LITERAL("m")));
        auto map = json[STR_LITERAL("m")].GetArray();

        CHECK(map.Size() == 2);
        CHECK(test::array_contains<Enc>(map, [](auto it) {
            return it->GetArray()[0].GetInt() == 0 &&
                   test::compare_cstring(it->GetArray()[1], STR_LITERAL("Human"));
        }));
        CHECK(test::array_contains<Enc>(map, [](auto it) {
            return it->GetArray()[0].GetInt() == 1 &&
                   test::compare_cstring(it->GetArray()[1], STR_LITERAL("God"));
        }));

        REQUIRE(json.HasMember(STR_LITERAL("d")));
        CHECK(test::compare_cstring(json[STR_LITERAL("d")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));
        CHECK(test::compare_cstring(json[STR_LITERAL("d")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));

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

        n_ctor_getter_name_trait_class val(
            false, 1234, 5678, "Lupercal",
            {10.0, 20.0, 30.0, 40.0},
            {0, 1},
            {{0, "Human"}, {1, "God"}},
            {{"traitor", "serpent"}, {"battle-brother", "legion"}},
            {2, 5, 10});

        to_stream<n_ctor_getter_name_trait_class, Enc>(ss, val);
        auto value = ss.str();

        using AnyString = std::basic_string<typename Enc::Ch>;
        AnyString output = STR_LITERAL(R"(
                {
                    "b": false,
                    "u32": 1234,
                    "u64": 5678,
                    "str": "Lupercal",
                    "l": [10.0,20.0,30.0,40.0],
                    "a": [0,1],
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        // unordered type does not guaranteed to have the same order
        // regex is not implemented for char32_t

        auto currPos = value.find(output);
        CHECK(currPos != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("m":)"), currPos);
        CHECK(currPos != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"([0,"Human"])"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"([1,"God"])"), currPos) != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("d":)"), currPos);
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

TEMPLATE_TEST_CASE_SIG("TPL_ALL_CTOR_GETTER_NAME_TRAITS", "[TPL][ALL][CTOR_GETTER_NAME]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_all_ctor_getter_name_trait_class_isv = tpl_all_ctor_getter_name_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_all_ctor_getter_name_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_all_ctor_getter_name_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_all_ctor_getter_name_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                {
                    "t1": "",
                    "t2": "",
                    "t3": ""
                }
            )")));
        }
        auto val = as<tpl_all_ctor_getter_name_trait_class_isv, Enc>(
            STR_LITERAL(R"(
                {
                    "t1": 162,
                    "t2": "Davin's moon",
                    "t3": [45.1,55.5]
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

        tpl_all_ctor_getter_name_trait_class_isv val(162, "Davin's moon", {45.1f, 55.5f});

        auto json = to_json<tpl_all_ctor_getter_name_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("t1")));
        CHECK(json[STR_LITERAL("t1")].GetInt() == 162);

        REQUIRE(json.HasMember(STR_LITERAL("t2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("t2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("t3")));
        CHECK(json[STR_LITERAL("t3")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("t3")].GetArray()[0] == 45.1f);
        CHECK(json[STR_LITERAL("t3")].GetArray()[1] == 55.5f);
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        tpl_all_ctor_getter_name_trait_class_isv val(162, "Davin's_moon", {45.1f, 55.5f});

        to_stream<tpl_all_ctor_getter_name_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "t1": 162,
                    "t2": "Davin's_moon",
                    "t3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("TPL_N_CTOR_GETTER_NAME_TRAITS", "[TPL][N][CTOR_GETTER_NAME]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_n_ctor_getter_name_trait_class_isv = tpl_n_ctor_getter_name_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_n_ctor_getter_name_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_n_ctor_getter_name_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_n_ctor_getter_name_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                {
                    "t1": "",
                    "t2": "",
                    "t3": ""
                }
            )")));
        }
        SECTION("with all parameter")
        {
            auto val = as<tpl_n_ctor_getter_name_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "t1": 162,
                        "t2": "Davin's moon",
                        "t3": [45.1,55.5]
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
            auto val = as<tpl_n_ctor_getter_name_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "t1": 162,
                        "t2": "Davin's moon"
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

        tpl_n_ctor_getter_name_trait_class_isv val(162, "Davin's moon", {45.1f, 55.5f});

        auto json = to_json<tpl_n_ctor_getter_name_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("t1")));
        CHECK(json[STR_LITERAL("t1")].GetInt() == 162);

        REQUIRE(json.HasMember(STR_LITERAL("t2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("t2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("t3")));
        CHECK(json[STR_LITERAL("t3")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("t3")].GetArray()[0] == 45.1f);
        CHECK(json[STR_LITERAL("t3")].GetArray()[1] == 55.5f);
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        tpl_n_ctor_getter_name_trait_class_isv val(162, "Davin's_moon", {45.1f, 55.5f});

        to_stream<tpl_n_ctor_getter_name_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "t1": 162,
                    "t2": "Davin's_moon",
                    "t3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}
