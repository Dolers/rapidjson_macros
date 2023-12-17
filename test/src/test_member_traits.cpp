// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <rapidjson_macros/rapidjson_macros>
#include <test_utility.hpp>
#include <test_member_traits.hpp>

#include <sstream>
#include <algorithm>

RAPIDJSON_ALL_MEMBER_TRAITS(all_member_trait_class, my_bool, my_int32, my_int64, my_string, my_vector, my_array, my_map, my_dict, my_set);
RAPIDJSON_N_MEMBER_TRAITS(n_member_trait_class, 4, my_bool, my_uint32, my_uint64, my_string, my_list, my_array, my_map, my_dict, my_set);
RAPIDJSON_TPL_ALL_MEMBER_TRAITS(3, tpl_all_member_trait_class, my_type1, my_type2, my_type3);
RAPIDJSON_TPL_N_MEMBER_TRAITS(3, tpl_n_member_trait_class, 2, my_type1, my_type2, my_type3);

using namespace rapidjson_macros;
TEMPLATE_TEST_CASE_SIG("ALL_MEMBER_TRAITS", "[ALL][MEMBER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<all_member_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<all_member_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<all_member_trait_class, Enc>(STR_LITERAL(R"(
                    {
                        "my_bool": true,
                        "my_int32": 1234,
                        "my_int64": "Lupercal",
                        "my_string": 546,
                        "my_vector": [10,20,30,40],
                        "my_array": [0,1],
                        "my_map": {
                            "battle-brother": "legion",
                            "traitor": "serpent"  
                        },
                        "my_dict": [[0,0.5],[1,1.5]],
                        "my_set": [-5,0,10]
                    }
                )")));
        }
        SECTION("with valid values")
        {
            auto val = as<all_member_trait_class, Enc>(STR_LITERAL(R"(
                    {
                        "my_bool": true,
                        "my_int32": -1234,
                        "my_int64": 5678,
                        "my_string": "Lupercal",
                        "my_vector": [10,20,30,40],
                        "my_array": [0,1],
                        "my_map": [[0,0.5],[1,1.5]],
                        "my_dict": {
                            "battle-brother": "legion",
                            "traitor": "serpent"  
                        },
                        "my_set": [-5,0,10]
                    }
                )"));
            CHECK(val.my_bool == true);
            CHECK(val.my_int32 == -1234);
            CHECK(val.my_int64 == 5678);
            CHECK(val.my_string == "Lupercal");

            CHECK(val.my_vector.size() == 4);
            for (int i = 0; i < val.my_vector.size(); i++)
                CHECK(val.my_vector[i] == (i * 10) + 10);

            CHECK(val.my_array[0] == 0);
            CHECK(val.my_array[1] == 1);

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
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        all_member_trait_class val;
        val.my_bool = true;
        val.my_int32 = -1234;
        val.my_int64 = 5678;
        val.my_string = "Lupercal";
        val.my_vector = {10, 20, 30, 40};
        val.my_array = {0, 1};
        val.my_map = {{0, 0.5}, {1, 1.5}};
        val.my_dict = {{"traitor", "serpent"}, {"battle-brother", "legion"}};
        val.my_set = {0, -5, 10};

        auto json = to_json<all_member_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_bool")));
        CHECK(json[STR_LITERAL("my_bool")].GetBool() == val.my_bool);

        REQUIRE(json.HasMember(STR_LITERAL("my_int32")));
        CHECK(json[STR_LITERAL("my_int32")].GetInt() == val.my_int32);

        REQUIRE(json.HasMember(STR_LITERAL("my_int64")));
        CHECK(json[STR_LITERAL("my_int64")].GetInt64() == val.my_int64);

        REQUIRE(json.HasMember(STR_LITERAL("my_string")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_string")], STR_LITERAL("Lupercal")));

        REQUIRE(json.HasMember(STR_LITERAL("my_vector")));
        CHECK(json[STR_LITERAL("my_vector")].GetArray().Size() == 4);
        int size = json[STR_LITERAL("my_vector")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("my_vector")].GetArray()[i] == (i * 10) + 10);

        REQUIRE(json.HasMember(STR_LITERAL("my_array")));
        CHECK(json[STR_LITERAL("my_array")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("my_array")].GetArray()[1] == 1);

        REQUIRE(json.HasMember(STR_LITERAL("my_map")));
        CHECK(json[STR_LITERAL("my_map")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("my_map")].GetArray()[0].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("my_map")].GetArray()[0].GetArray()[1] == 0.5);
        CHECK(json[STR_LITERAL("my_map")].GetArray()[1].GetArray()[0] == 1);
        CHECK(json[STR_LITERAL("my_map")].GetArray()[1].GetArray()[1] == 1.5);

        REQUIRE(json.HasMember(STR_LITERAL("my_dict")));
        CHECK(json[STR_LITERAL("my_dict")].GetArray().Size() == 2);
        CHECK(test::compare_cstring(json[STR_LITERAL("my_dict")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_dict")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));

        REQUIRE(json.HasMember(STR_LITERAL("my_set")));
        CHECK(json[STR_LITERAL("my_set")].GetArray().Size() == 3);
        CHECK(json[STR_LITERAL("my_set")].GetArray()[0].GetInt() == -5);
        CHECK(json[STR_LITERAL("my_set")].GetArray()[1].GetInt() == 0);
        CHECK(json[STR_LITERAL("my_set")].GetArray()[2].GetInt() == 10);
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        all_member_trait_class val;
        val.my_bool = true;
        val.my_int32 = -1234;
        val.my_int64 = 5678;
        val.my_string = "Lupercal";
        val.my_vector = {10, 20, 30, 40};
        val.my_array = {0, 1};
        val.my_map = {{0, 0.5}, {1, 1.5}};
        val.my_dict = {{"traitor", "serpent"}, {"battle-brother", "legion"}};
        val.my_set = {0, -5, 10};

        std::basic_stringstream<typename Enc::Ch> ss;

        to_stream<all_member_trait_class, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                    {
                        "my_bool": true,
                        "my_int32": -1234,
                        "my_int64": 5678,
                        "my_string": "Lupercal",
                        "my_vector": [10,20,30,40],
                        "my_array": [0,1],
                        "my_map": [[0,0.5],[1,1.5]],
                        "my_dict": {
                            "battle-brother": "legion",
                            "traitor": "serpent"  
                        },
                        "my_set": [-5,0,10]
                    }
                )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("N_MEMBER_TRAITS", "[N][MEMBER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<n_member_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<n_member_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<n_member_trait_class, Enc>(STR_LITERAL(R"(
                {
                    "my_bool": {
                            "battle-brother": "legion",
                            "traitor": "serpent"
                        },
                    "my_uint32": 1234,
                    "my_uint64": [10.0,20.0,30.0,40.0],
                    "my_string": 546,
                    "my_list": "Lupercal",
                    "my_array": [0,1],
                    "my_map": [[0,"Human"],[1,"God"]],
                    "my_dict": false,
                    "my_set": [0,-5,10]
                }
            )")));
        }
        SECTION("with all parameter")
        {
            auto val = as<n_member_trait_class, Enc>(STR_LITERAL(R"(
                    {
                        "my_bool": false,
                        "my_uint32": 1234,
                        "my_uint64": 5678,
                        "my_string": "Lupercal",
                        "my_list": [10.0,20.0,30.0,40.0],
                        "my_array": [0,1],
                        "my_map": [[0,"Human"],[1,"God"]],
                        "my_dict": {
                            "battle-brother": "legion",
                            "traitor": "serpent"
                        },
                        "my_set": [2,5,10]
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
            CHECK(val.my_set.count(2) == 1);
            CHECK(val.my_set.count(5) == 1);
            CHECK(val.my_set.count(10) == 1);
        }

        SECTION("with some optional parameters")
        {
            auto val = as<n_member_trait_class, Enc>(STR_LITERAL(R"(
                    {
                        "my_bool": false,
                        "my_uint32": 1234,
                        "my_uint64": 5678,
                        "my_string": "Lupercal",
                        "my_list": [10.0,20.0,30.0,40.0],
                        "my_array": [0,1],
                        "my_map": [[0,"Human"],[1,"God"]]
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
            auto val = as<n_member_trait_class, Enc>(STR_LITERAL(R"(
                    {
                        "my_bool": false,
                        "my_uint32": 1234,
                        "my_uint64": 5678,
                        "my_string": "Lupercal"
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

        n_member_trait_class val;
        val.my_bool = false;
        val.my_uint32 = 1234;
        val.my_uint64 = 5678;
        val.my_string = "Lupercal";
        val.my_list = {10.0, 20.0, 30.0, 40.0};
        val.my_array = {0, 1};
        val.my_map = {{0, "Human"}, {1, "God"}};
        val.my_dict = {{"traitor", "serpent"}, {"battle-brother", "legion"}};
        val.my_set = {2, 5, 10};

        auto json = to_json<n_member_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_bool")));
        CHECK(json[STR_LITERAL("my_bool")].GetBool() == false);

        REQUIRE(json.HasMember(STR_LITERAL("my_uint32")));
        CHECK(json[STR_LITERAL("my_uint32")].GetInt() == 1234);

        REQUIRE(json.HasMember(STR_LITERAL("my_uint64")));
        CHECK(json[STR_LITERAL("my_uint64")].GetInt64() == 5678);

        REQUIRE(json.HasMember(STR_LITERAL("my_string")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_string")], STR_LITERAL("Lupercal")));

        REQUIRE(json.HasMember(STR_LITERAL("my_list")));
        CHECK(json[STR_LITERAL("my_list")].GetArray().Size() == 4);
        int size = json[STR_LITERAL("my_list")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("my_list")].GetArray()[i] == (i * 10) + 10);

        REQUIRE(json.HasMember(STR_LITERAL("my_array")));
        CHECK(json[STR_LITERAL("my_array")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("my_array")].GetArray()[1] == 1);

        REQUIRE(json.HasMember(STR_LITERAL("my_map")));
        auto map = json[STR_LITERAL("my_map")].GetArray();

        CHECK(map.Size() == 2);
        CHECK(test::array_contains<Enc>(map, [](auto it) {
            return it->GetArray()[0].GetInt() == 0 &&
                   test::compare_cstring(it->GetArray()[1], STR_LITERAL("Human"));
        }));
        CHECK(test::array_contains<Enc>(map, [](auto it) {
            return it->GetArray()[0].GetInt() == 1 &&
                   test::compare_cstring(it->GetArray()[1], STR_LITERAL("God"));
        }));

        REQUIRE(json.HasMember(STR_LITERAL("my_dict")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_dict")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_dict")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));

        REQUIRE(json.HasMember(STR_LITERAL("my_set")));
        auto set = json[STR_LITERAL("my_set")].GetArray();

        CHECK(set.Size() == 3);
        CHECK(test::array_contains<Enc>(set, [](auto it) { return *it == 2; }));
        CHECK(test::array_contains<Enc>(set, [](auto it) { return *it == 5; }));
        CHECK(test::array_contains<Enc>(set, [](auto it) { return *it == 10; }));
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        n_member_trait_class val;
        val.my_bool = false;
        val.my_uint32 = 1234;
        val.my_uint64 = 5678;
        val.my_string = "Lupercal";
        val.my_list = {10.0, 20.0, 30.0, 40.0};
        val.my_array = {0, 1};
        val.my_map = {{0, "Human"}, {1, "God"}};
        val.my_dict = {{"battle-brother", "legion"}, {"traitor", "serpent"}};
        val.my_set = {2, 5, 10};

        to_stream<n_member_trait_class, Enc>(ss, val);
        auto value = ss.str();

        using AnyString = std::basic_string<typename Enc::Ch>;
        AnyString output = STR_LITERAL(R"(
                {
                    "my_bool": false,
                    "my_uint32": 1234,
                    "my_uint64": 5678,
                    "my_string": "Lupercal",
                    "my_list": [10.0,20.0,30.0,40.0],
                    "my_array": [0,1],
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        // unordered type does not guaranteed to have the same order
        // regex is not implemented for char32_t

        auto currPos = value.find(output);
        CHECK(currPos != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("my_map":)"), currPos);
        CHECK(currPos != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"([0,"Human"])"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"([1,"God"])"), currPos) != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("my_dict":)"), currPos);
        CHECK(currPos != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"("traitor":"serpent")"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL(R"("battle-brother":"legion")"), currPos) != AnyString::npos);

        currPos = value.find(STR_LITERAL(R"("my_set":)"), currPos);
        CHECK(value.find(STR_LITERAL("2"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL("5"), currPos) != AnyString::npos);
        CHECK(value.find(STR_LITERAL("10"), currPos) != AnyString::npos);

        CHECK(value.find(STR_LITERAL("}"), currPos) != AnyString::npos);
    }
}

TEMPLATE_TEST_CASE_SIG("TPL_ALL_MEMBER_TRAITS", "[TPL][ALL][MEMBER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_all_member_trait_class_isv = tpl_all_member_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_all_member_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_all_member_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_all_member_trait_class_isv, Enc>(STR_LITERAL(R"(
                {
                    "my_type1": "",
                    "my_type2": "",
                    "my_type3": ""
                }
            )")));
        }
        auto val = as<tpl_all_member_trait_class_isv, Enc>(STR_LITERAL(R"(
                {
                    "my_type1": 162,
                    "my_type2": "Davin's moon",
                    "my_type3": [45.1,55.5]
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

        tpl_all_member_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's moon";
        val.my_type3 = {45.1f, 55.5f};

        auto json = to_json<tpl_all_member_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_type1")));
        CHECK(json[STR_LITERAL("my_type1")].GetInt() == 162);

        REQUIRE(json.HasMember(STR_LITERAL("my_type2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_type2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("my_type3")));
        CHECK(json[STR_LITERAL("my_type3")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("my_type3")].GetArray()[0] == 45.1f);
        CHECK(json[STR_LITERAL("my_type3")].GetArray()[1] == 55.5f);
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        tpl_all_member_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's_moon";
        val.my_type3 = {45.1f, 55.5f};

        to_stream<tpl_all_member_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "my_type1": 162,
                    "my_type2": "Davin's_moon",
                    "my_type3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("TPL_N_MEMBER_TRAITS", "[TPL][N][MEMBER]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_n_member_trait_class_isv = tpl_n_member_trait_class<int32_t, std::string, std::list<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_n_member_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_n_member_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_n_member_trait_class_isv, Enc>(STR_LITERAL(R"(
                {
                    "my_type1": "",
                    "my_type2": "",
                    "my_type3": ""
                }
            )")));
        }
        SECTION("with all parameter")
        {
            auto val = as<tpl_n_member_trait_class_isv, Enc>(STR_LITERAL(R"(
                    {
                        "my_type1": 162,
                        "my_type2": "Davin's moon",
                        "my_type3": [45.1,55.5]
                    }
            )"));
            CHECK(val.my_type1 == 162);
            CHECK(val.my_type2 == "Davin's moon");

            CHECK(val.my_type3.size() == 2);
            auto it = val.my_type3.begin();
            CHECK(*(it++) == 45.1f);
            CHECK(*(it++) == 55.5f);
        }

        SECTION("with only required parameters")
        {
            auto val = as<tpl_n_member_trait_class_isv, Enc>(STR_LITERAL(R"(
                    {
                        "my_type1": 162,
                        "my_type2": "Davin's moon"
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

        tpl_n_member_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's moon";
        val.my_type3 = {45.1f, 55.5f};

        auto json = to_json<tpl_n_member_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_type1")));
        CHECK(json[STR_LITERAL("my_type1")].GetInt() == 162);

        REQUIRE(json.HasMember(STR_LITERAL("my_type2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_type2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("my_type3")));
        CHECK(json[STR_LITERAL("my_type3")].GetArray().Size() == 2);
        CHECK(json[STR_LITERAL("my_type3")].GetArray()[0] == 45.1f);
        CHECK(json[STR_LITERAL("my_type3")].GetArray()[1] == 55.5f);
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        tpl_n_member_trait_class_isv val;
        val.my_type1 = 162;
        val.my_type2 = "Davin's_moon";
        val.my_type3 = {45.1f, 55.5f};

        to_stream<tpl_n_member_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<typename Enc::Ch> output = STR_LITERAL(R"(
                {
                    "my_type1": 162,
                    "my_type2": "Davin's_moon",
                    "my_type3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), test::space<typename Enc::Ch>::check), output.end());

        CHECK(value == output);
    }
}
