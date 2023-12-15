// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <rapidjson_macros/rapidjson_macros>
#include <test_utility.hpp>
#include <test_member_name_traits.hpp>

#include <sstream>

RAPIDJSON_ALL_MEMBER_NAME_TRAITS(all_member_name_trait_class, (my_bool, "b"), (my_int32, "i32"), (my_int64, "i64"), (my_string, "str"), (my_vector, "v"), (my_array, "a"), (my_map, "m"), (my_dict, "d"), (my_set, "set"));
RAPIDJSON_N_MEMBER_NAME_TRAITS(n_member_name_trait_class, 4, (my_bool, "b"), (my_uint32, "u32"), (my_uint64, "u64"), (my_string, "str"), (my_list, "l"), (my_array, "a"), (my_map, "m"), (my_dict, "d"), (my_set, "set"));
RAPIDJSON_TPL_ALL_MEMBER_NAME_TRAITS(3, tpl_all_member_name_trait_class, (my_type1, "t1"), (my_type2, "t2"), (my_type3, "t3"));
RAPIDJSON_TPL_N_MEMBER_NAME_TRAITS(3, tpl_n_member_name_trait_class, 2, (my_type1, "t1"), (my_type2, "t2"), (my_type3, "t3"));

using namespace rapidjson_macros;

TEMPLATE_TEST_CASE_SIG("ALL_MEMBER_NAME_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<all_member_name_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<all_member_name_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<all_member_name_trait_class, Enc>(
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
        auto val = as<all_member_name_trait_class, Enc>(
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
        CHECK(val.my_bool == true);
        CHECK(val.my_int32 == -1234);
        CHECK(val.my_int64 == 5678);
        CHECK(val.my_string == "Lupercal");

        CHECK(val.my_vector.size() == 4);
        for (int i = 0; i < val.my_vector.size(); i++)
            CHECK(val.my_vector[i] == (i * 10) + 10);

        CHECK(val.my_map.size() == 2);
        CHECK(val.my_map[0] == 0.5);
        CHECK(val.my_map[1] == 1.5);

        CHECK(val.my_dict.size() == 2);
        CHECK(val.my_dict["battle-brother"] == "legion");
        CHECK(val.my_dict["traitor"] == "serpent");

        CHECK(val.my_set.size() == 3);
        CHECK(val.my_set.count(0) == 1);
        CHECK(val.my_set.count(-5) == 1);
        CHECK(val.my_set.count(10) == 1);
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        all_member_name_trait_class val;
        val.my_bool = true;
        val.my_int32 = -1234;
        val.my_int64 = 5678;
        val.my_string = "Lupercal";
        val.my_vector = {10, 20, 30, 40};
        val.my_array = {0, 1};
        val.my_map = {{0, 0.5}, {1, 1.5}};
        val.my_dict = {{"traitor", "serpent"}, {"battle-brother", "legion"}};
        val.my_set = {0, -5, 10};

        auto json = to_json<all_member_name_trait_class, Enc>(val, doc.GetAllocator());
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
        std::basic_stringstream<Enc::Ch> ss;

        all_member_name_trait_class val;
        val.my_bool = true;
        val.my_int32 = -1234;
        val.my_int64 = 5678;
        val.my_string = "Lupercal";
        val.my_vector = {10, 20, 30, 40};
        val.my_array = {0, 1};
        val.my_map = {{0, 0.5}, {1, 1.5}};
        val.my_dict = {{"traitor", "serpent"}, {"battle-brother", "legion"}};
        val.my_set = {0, -5, 10};

        to_stream<all_member_name_trait_class, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
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
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("N_MEMBER_NAME_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<n_member_name_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<n_member_name_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<n_member_name_trait_class, Enc>(
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
            auto val = as<n_member_name_trait_class, Enc>(
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
                        "set": [0,5,10]
                    }
                )"));
            CHECK(val.my_bool == false);
            CHECK(val.my_uint32 == 1234);
            CHECK(val.my_uint64 == 5678);
            CHECK(!strcmp(val.my_string, "Lupercal"));

            CHECK(val.my_list.size() == 4);
            int i = 0;
            for (auto& e : val.my_list)
                CHECK(e == (i++ * 10) + 10);

            CHECK(val.my_array[0] == 0);
            CHECK(val.my_array[1] == 1);

            CHECK(val.my_map.size() == 2);
            CHECK(val.my_map[0] == "Human");
            CHECK(val.my_map[1] == "God");

            CHECK(val.my_dict.size() == 2);
            CHECK(val.my_dict["traitor"] == "serpent");
            CHECK(val.my_dict["battle-brother"] == "legion");

            CHECK(val.my_set.size() == 3);
            CHECK(val.my_set.count(0) == 1);
            CHECK(val.my_set.count(5) == 1);
            CHECK(val.my_set.count(10) == 1);
        }

        SECTION("with some optional parameters")
        {
            auto val = as<n_member_name_trait_class, Enc>(
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
            CHECK(val.my_bool == false);
            CHECK(val.my_uint32 == 1234);
            CHECK(val.my_uint64 == 5678);
            CHECK(!strcmp(val.my_string, "Lupercal"));

            CHECK(val.my_list.size() == 4);
            int i = 0;
            for (auto& e : val.my_list)
                CHECK(e == (i++ * 10) + 10);

            CHECK(val.my_array[0] == 0);
            CHECK(val.my_array[1] == 1);

            CHECK(val.my_map.size() == 2);
            CHECK(val.my_map[0] == "Human");
            CHECK(val.my_map[1] == "God");

            CHECK(val.my_dict.size() == 0);
            CHECK(val.my_set.size() == 0);
        }

        SECTION("with only required parameters")
        {
            auto val = as<n_member_name_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "b": false,
                        "u32": 1234,
                        "u64": 5678,
                        "str": "Lupercal"
                    }
                )"));
            CHECK(val.my_bool == false);
            CHECK(val.my_uint32 == 1234);
            CHECK(val.my_uint64 == 5678);
            CHECK(!strcmp(val.my_string, "Lupercal"));

            CHECK(val.my_list.size() == 0);
            CHECK(val.my_map.size() == 0);
            CHECK(val.my_dict.size() == 0);
            CHECK(val.my_set.size() == 0);
        }
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        n_member_name_trait_class val;
        val.my_bool = false;
        val.my_uint32 = 1234;
        val.my_uint64 = 5678;
        val.my_string = "Lupercal";
        val.my_list = {10.0, 20.0, 30.0, 40.0};
        val.my_array = {0, 1};
        val.my_map = {{0, "Human"}, {1, "God"}};
        val.my_dict = {{"traitor", "serpent"}, {"battle-brother", "legion"}};
        val.my_set = {0, 5, 10};

        auto json = to_json<n_member_name_trait_class, Enc>(val, doc.GetAllocator());
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
        CHECK(json[STR_LITERAL("m")].GetArray()[0].GetArray()[0].GetInt() == 0);
        CHECK(test::compare_cstring(json[STR_LITERAL("m")].GetArray()[0].GetArray()[1], STR_LITERAL("Human")));
        CHECK(json[STR_LITERAL("m")].GetArray()[1].GetArray()[0].GetInt() == 1);
        CHECK(test::compare_cstring(json[STR_LITERAL("m")].GetArray()[1].GetArray()[1], STR_LITERAL("God")));

        REQUIRE(json.HasMember(STR_LITERAL("d")));
        CHECK(test::compare_cstring(json[STR_LITERAL("d")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));
        CHECK(test::compare_cstring(json[STR_LITERAL("d")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));

        REQUIRE(json.HasMember(STR_LITERAL("set")));
        CHECK(json[STR_LITERAL("set")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("set")].GetArray()[1] == 5);
        CHECK(json[STR_LITERAL("set")].GetArray()[2] == 10);
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<Enc::Ch> ss;

        n_member_name_trait_class val;
        val.my_bool = false;
        val.my_uint32 = 1234;
        val.my_uint64 = 5678;
        val.my_string = "Lupercal";
        val.my_list = {10.0, 20.0, 30.0, 40.0};
        val.my_array = {0, 1};
        val.my_map = {{0, "Human"}, {1, "God"}};
        val.my_dict = {{"battle-brother", "legion"}, {"traitor", "serpent"}};
        val.my_set = {0, 5, 10};

        to_stream<n_member_name_trait_class, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
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
                    "set": [0,5,10]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("TPL_ALL_MEMBER_NAME_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_all_member_name_trait_class_isv = tpl_all_member_name_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_all_member_name_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_all_member_name_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_all_member_name_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                {
                    "t1": "",
                    "t2": "",
                    "t3": ""
                }
            )")));
        }
        auto val = as<tpl_all_member_name_trait_class_isv, Enc>(
            STR_LITERAL(R"(
                {
                    "t1": 162,
                    "t2": "Davin's moon",
                    "t3": [45.1,55.5]
                }
            )"));
        CHECK(val.my_type1 == 162);
        CHECK(val.my_type2 == "Davin's moon");

        CHECK(val.my_type3.size() == 2);
        CHECK(val.my_type3[0] == 45.1f);
        CHECK(val.my_type3[1] == 55.5f);
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        tpl_all_member_name_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's moon";
        val.my_type3 = {45.1f, 55.5f};

        auto json = to_json<tpl_all_member_name_trait_class_isv, Enc>(val, doc.GetAllocator());
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
        std::basic_stringstream<Enc::Ch> ss;

        tpl_all_member_name_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's_moon";
        val.my_type3 = {45.1f, 55.5f};

        to_stream<tpl_all_member_name_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
                {
                    "t1": 162,
                    "t2": "Davin's_moon",
                    "t3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("TPL_N_MEMBER_NAME_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_n_member_name_trait_class_isv = tpl_n_member_name_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_n_member_name_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_n_member_name_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_n_member_name_trait_class_isv, Enc>(
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
            auto val = as<tpl_n_member_name_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "t1": 162,
                        "t2": "Davin's moon",
                        "t3": [45.1,55.5]
                    }
                )"));
            CHECK(val.my_type1 == 162);
            CHECK(val.my_type2 == "Davin's moon");

            CHECK(val.my_type3.size() == 2);
            CHECK(val.my_type3[0] == 45.1f);
            CHECK(val.my_type3[1] == 55.5f);
        }

        SECTION("with only required parameters")
        {
            auto val = as<tpl_n_member_name_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "t1": 162,
                        "t2": "Davin's moon"
                    }
                )"));
            CHECK(val.my_type1 == 162);
            CHECK(val.my_type2 == "Davin's moon");

            CHECK(val.my_type3.size() == 0);
        }
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        tpl_n_member_name_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's moon";
        val.my_type3 = {45.1f, 55.5f};

        auto json = to_json<tpl_n_member_name_trait_class_isv, Enc>(val, doc.GetAllocator());
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
        std::basic_stringstream<Enc::Ch> ss;

        tpl_n_member_name_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's_moon";
        val.my_type3 = {45.1f, 55.5f};

        to_stream<tpl_n_member_name_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
                {
                    "t1": 162,
                    "t2": "Davin's_moon",
                    "t3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}
