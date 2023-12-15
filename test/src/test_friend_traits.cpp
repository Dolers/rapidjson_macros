// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <rapidjson_macros/rapidjson_macros>
#include <test_utility.hpp>
#include <test_friend_traits.hpp>

#include <sstream>

// Register with member macros
RAPIDJSON_ALL_MEMBER_TRAITS(friend_all_getter_setter_trait_class, my_bool, my_int32, my_int64, my_string, my_vector, my_array, my_map, my_dict, my_set);
RAPIDJSON_N_MEMBER_TRAITS(friend_n_getter_setter_trait_class, 4, my_bool, my_uint32, my_uint64, my_string, my_list, my_array, my_map, my_dict, my_set);
RAPIDJSON_TPL_ALL_MEMBER_TRAITS(3, friend_tpl_all_getter_setter_trait_class, my_type1, my_type2, my_type3);
RAPIDJSON_TPL_N_MEMBER_TRAITS(3, friend_tpl_n_getter_setter_trait_class, 2, my_type1, my_type2, my_type3);

using namespace rapidjson_macros;

TEMPLATE_TEST_CASE_SIG("FRIEND_ALL_GETTER_SETTER_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<friend_all_getter_setter_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<friend_all_getter_setter_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<friend_all_getter_setter_trait_class, Enc>(
                STR_LITERAL(R"(
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
        auto val = as<friend_all_getter_setter_trait_class, Enc>(
            STR_LITERAL(R"(
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

        friend_all_getter_setter_trait_class val;
        val.set_bool(true);
        val.set_int32(-1234);
        val.set_int64(5678);
        val.set_string("Lupercal");
        val.set_vector({10, 20, 30, 40});
        val.set_array({0, 1});
        val.set_map({{0, 0.5}, {1, 1.5}});
        val.set_dict({{"traitor", "serpent"}, {"battle-brother", "legion"}});
        val.set_set({0, -5, 10});

        auto json = to_json<friend_all_getter_setter_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_bool")));
        CHECK(json[STR_LITERAL("my_bool")].GetBool() == val.get_bool());

        REQUIRE(json.HasMember(STR_LITERAL("my_int32")));
        CHECK(json[STR_LITERAL("my_int32")].GetInt() == val.get_int32());

        REQUIRE(json.HasMember(STR_LITERAL("my_int64")));
        CHECK(json[STR_LITERAL("my_int64")].GetInt64() == val.get_int64());

        REQUIRE(json.HasMember(STR_LITERAL("my_string")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_string")], STR_LITERAL("Lupercal")));

        REQUIRE(json.HasMember(STR_LITERAL("my_vector")));
        CHECK(json[STR_LITERAL("my_vector")].GetArray().Size() == 4);
        int size = json[STR_LITERAL("my_vector")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("my_vector")].GetArray()[i] == val.get_vector().at(i));

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
        std::basic_stringstream<Enc::Ch> ss;

        friend_all_getter_setter_trait_class val;
        val.set_bool(true);
        val.set_int32(-1234);
        val.set_int64(5678);
        val.set_string("Lupercal");
        val.set_vector({10, 20, 30, 40});
        val.set_array({0, 1});
        val.set_map({{0, 0.5}, {1, 1.5}});
        val.set_dict({{"traitor", "serpent"}, {"battle-brother", "legion"}});
        val.set_set({0, -5, 10});

        to_stream<friend_all_getter_setter_trait_class, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
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
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("FRIEND_N_GETTER_SETTER_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<friend_n_getter_setter_trait_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<friend_n_getter_setter_trait_class, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<friend_n_getter_setter_trait_class, Enc>(
                STR_LITERAL(R"(
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
            auto val = as<friend_n_getter_setter_trait_class, Enc>(
                STR_LITERAL(R"(
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
                        "my_set": [0,5,10]
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
            CHECK(val.get_set().count(0) == 1);
            CHECK(val.get_set().count(5) == 1);
            CHECK(val.get_set().count(10) == 1);
        }

        SECTION("with some optional parameters")
        {
            auto val = as<friend_n_getter_setter_trait_class, Enc>(
                STR_LITERAL(R"(
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
            auto val = as<friend_n_getter_setter_trait_class, Enc>(
                STR_LITERAL(R"(
                    {
                        "my_bool": false,
                        "my_uint32": 1234,
                        "my_uint64": 5678,
                        "my_string": "Lupercal"
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

        friend_n_getter_setter_trait_class val;
        val.set_bool(false);
        val.set_uint32(1234);
        val.set_uint64(5678);
        val.set_string("Lupercal");
        val.set_list({10.0, 20.0, 30.0, 40.0});
        val.set_array({0, 1});
        val.set_map({{0, "Human"}, {1, "God"}});
        val.set_dict({{"traitor", "serpent"}, {"battle-brother", "legion"}});
        val.set_set({0, 5, 10});

        auto json = to_json<friend_n_getter_setter_trait_class, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_bool")));
        CHECK(json[STR_LITERAL("my_bool")].GetBool() == val.get_bool());

        REQUIRE(json.HasMember(STR_LITERAL("my_uint32")));
        CHECK(json[STR_LITERAL("my_uint32")].GetInt() == val.get_uint32());

        REQUIRE(json.HasMember(STR_LITERAL("my_uint64")));
        CHECK(json[STR_LITERAL("my_uint64")].GetInt64() == val.get_uint64());

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
        CHECK(json[STR_LITERAL("my_map")].GetArray()[0].GetArray()[0].GetInt() == 0);
        CHECK(test::compare_cstring(json[STR_LITERAL("my_map")].GetArray()[0].GetArray()[1], STR_LITERAL("Human")));
        CHECK(json[STR_LITERAL("my_map")].GetArray()[1].GetArray()[0].GetInt() == 1);
        CHECK(test::compare_cstring(json[STR_LITERAL("my_map")].GetArray()[1].GetArray()[1], STR_LITERAL("God")));

        REQUIRE(json.HasMember(STR_LITERAL("my_dict")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_dict")][STR_LITERAL("battle-brother")], STR_LITERAL("legion")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_dict")][STR_LITERAL("traitor")], STR_LITERAL("serpent")));

        REQUIRE(json.HasMember(STR_LITERAL("my_set")));
        CHECK(json[STR_LITERAL("my_set")].GetArray()[0] == 0);
        CHECK(json[STR_LITERAL("my_set")].GetArray()[1] == 5);
        CHECK(json[STR_LITERAL("my_set")].GetArray()[2] == 10);
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<Enc::Ch> ss;

        friend_n_getter_setter_trait_class val;
        val.set_bool(false);
        val.set_uint32(1234);
        val.set_uint64(5678);
        val.set_string("Lupercal");
        val.set_list({10.0, 20.0, 30.0, 40.0});
        val.set_array({0, 1});
        val.set_map({{0, "Human"}, {1, "God"}});
        val.set_dict({{"battle-brother", "legion"}, {"traitor", "serpent"}});
        val.set_set({0, 5, 10});

        to_stream<friend_n_getter_setter_trait_class, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
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
                    "my_set": [0,5,10]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("FRIEND_TPL_ALL_GETTER_SETTER_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_all_getter_setter_trait_class_isv = friend_tpl_all_getter_setter_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_all_getter_setter_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_all_getter_setter_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_all_getter_setter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                {
                    "my_type1": "",
                    "my_type2": "",
                    "my_type3": ""
                }
            )")));
        }
        auto val = as<tpl_all_getter_setter_trait_class_isv, Enc>(
            STR_LITERAL(R"(
                {
                    "my_type1": 162,
                    "my_type2": "Davin's moon",
                    "my_type3": [45.1,55.5]
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

        tpl_all_getter_setter_trait_class_isv val;
        val.set_type1(162);
        val.set_type2("Davin's moon");
        val.set_type3({45.1f, 55.5f});

        auto json = to_json<tpl_all_getter_setter_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_type1")));
        CHECK(json[STR_LITERAL("my_type1")].GetInt() == val.get_type1());

        REQUIRE(json.HasMember(STR_LITERAL("my_type2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_type2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("my_type3")));
        CHECK(json[STR_LITERAL("my_type3")].GetArray().Size() == 2);
        int size = json[STR_LITERAL("my_vector")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("my_type3")].GetArray()[i] == val.get_type3().at(i));
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<Enc::Ch> ss;

        tpl_all_getter_setter_trait_class_isv val;
        val.set_type1(162);
        val.set_type2("Davin's_moon");
        val.set_type3({45.1f, 55.5f});

        to_stream<tpl_all_getter_setter_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
                {
                    "my_type1": 162,
                    "my_type2": "Davin's_moon",
                    "my_type3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}

TEMPLATE_TEST_CASE_SIG("FRIEND_TPL_N_GETTER_SETTER_TRAITS", "", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    using tpl_n_getter_setter_trait_class_isv = friend_tpl_n_getter_setter_trait_class<int32_t, std::string, std::vector<float>>;

    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<tpl_n_getter_setter_trait_class_isv, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<tpl_n_getter_setter_trait_class_isv, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<tpl_n_getter_setter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                {
                    "my_type1": "",
                    "my_type2": "",
                    "my_type3": ""
                }
            )")));
        }
        SECTION("with all parameter")
        {
            auto val = as<tpl_n_getter_setter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "my_type1": 162,
                        "my_type2": "Davin's moon",
                        "my_type3": [45.1,55.5]
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
            auto val = as<tpl_n_getter_setter_trait_class_isv, Enc>(
                STR_LITERAL(R"(
                    {
                        "my_type1": 162,
                        "my_type2": "Davin's moon"
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

        tpl_n_getter_setter_trait_class_isv val;
        val.set_type1(162);
        val.set_type2("Davin's moon");
        val.set_type3({45.1f, 55.5f});

        auto json = to_json<tpl_n_getter_setter_trait_class_isv, Enc>(val, doc.GetAllocator());
        REQUIRE_FALSE(json.IsNull());
        REQUIRE(json.IsObject());

        REQUIRE(json.HasMember(STR_LITERAL("my_type1")));
        CHECK(json[STR_LITERAL("my_type1")].GetInt() == val.get_type1());

        REQUIRE(json.HasMember(STR_LITERAL("my_type2")));
        CHECK(test::compare_cstring(json[STR_LITERAL("my_type2")], STR_LITERAL("Davin's moon")));

        REQUIRE(json.HasMember(STR_LITERAL("my_type3")));
        CHECK(json[STR_LITERAL("my_type3")].GetArray().Size() == 2);
        int size = json[STR_LITERAL("my_vector")].GetArray().Size();
        for (int i = 0; i < size; i++)
            CHECK(json[STR_LITERAL("my_type3")].GetArray()[i] == val.get_type3().at(i));
    }

    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        std::basic_stringstream<Enc::Ch> ss;

        tpl_n_getter_setter_trait_class_isv val;
        val.set_type1(162);
        val.set_type2("Davin's_moon");
        val.set_type3({45.1f, 55.5f});

        to_stream<tpl_n_getter_setter_trait_class_isv, Enc>(ss, val);
        auto value = ss.str();
        std::basic_string<Enc::Ch> output = STR_LITERAL(R"(
                {
                    "my_type1": 162,
                    "my_type2": "Davin's_moon",
                    "my_type3": [45.099998474121097,55.5]
                }
            )");
        output.erase(std::remove_if(output.begin(), output.end(), std::isspace), output.end());

        CHECK(value == output);
    }
}
