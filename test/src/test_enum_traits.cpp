// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <rapidjson_macros/rapidjson_macros>
#include <test_utility.hpp>
#include <test_enum_traits.hpp>

#include <sstream>
#include <algorithm>

RAPIDJSON_ENUM_TRAITS(enum_class, ZERO, ONE, TWO)
RAPIDJSON_ENUM_NAME_TRAITS(enum_class_named, (ZERO_NAME, "zero"), (ONE_NAME, "one"), (TWO_NAME, "two"))

using namespace rapidjson_macros;

TEMPLATE_TEST_CASE_SIG("ENUM_TRAITS", "[ENUM]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<enum_class, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<enum_class, Enc>(STR_LITERAL(R"("unknown")")));
        }
        SECTION("with valid values")
        {
            CHECK(as<enum_class, Enc>(STR_LITERAL(R"("ZERO")")) == enum_class::ZERO);
            CHECK(as<enum_class, Enc>(STR_LITERAL(R"("ONE")")) == enum_class::ONE);
            CHECK(as<enum_class, Enc>(STR_LITERAL(R"("TWO")")) == enum_class::TWO);
        }
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;

        auto zero = to_json<enum_class, Enc>(enum_class::ZERO, doc.GetAllocator());
        REQUIRE_FALSE(zero.IsNull());
        CHECK(test::compare_cstring(zero, STR_LITERAL("ZERO")));

        auto one = to_json<enum_class, Enc>(enum_class::ONE, doc.GetAllocator());
        REQUIRE_FALSE(one.IsNull());
        CHECK(test::compare_cstring(one, STR_LITERAL("ONE")));

        auto two = to_json<enum_class, Enc>(enum_class::TWO, doc.GetAllocator());
        REQUIRE_FALSE(two.IsNull());
        CHECK(test::compare_cstring(two, STR_LITERAL("TWO")));
    }
    SECTION("Can use to_stream()", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        SECTION("with enum_class::ZERO")
        {
            to_stream<enum_class, Enc>(ss, enum_class::ZERO);
            CHECK(ss.str() == STR_LITERAL(R"("ZERO")"));
        }
        SECTION("with enum_class::ONE")
        {
            to_stream<enum_class, Enc>(ss, enum_class::ONE);
            CHECK(ss.str() == STR_LITERAL(R"("ONE")"));
        }
        SECTION("with enum_class::TWO")
        {
            to_stream<enum_class, Enc>(ss, enum_class::TWO);
            CHECK(ss.str() == STR_LITERAL(R"("TWO")"));
        }
    }
}

TEMPLATE_TEST_CASE_SIG("ENUM_NAME_TRAITS", "[ENUM]", (typename Enc), rapidjson::UTF8<>, rapidjson::UTF16<>, rapidjson::UTF16LE<>, rapidjson::UTF16BE<>, rapidjson::UTF32<char32_t>, rapidjson::UTF32<unsigned>)
{
    SECTION("Can use as()", "[as]")
    {
        SECTION("to detect invalids")
        {
            REQUIRE_THROWS(as<enum_class_named, Enc>(STR_LITERAL(R"()")));
            REQUIRE_THROWS(as<enum_class_named, Enc>(STR_LITERAL(R"("unknown")")));
            REQUIRE_THROWS(as<enum_class_named, Enc>(STR_LITERAL(R"("enum":{"zero"})")));
            REQUIRE_THROWS(as<enum_class_named, Enc>(STR_LITERAL(R"([STR_LITERAL("zero")])")));
        }
        SECTION("with valid values")
        {
            CHECK(as<enum_class_named, Enc>(STR_LITERAL(R"("zero")")) == enum_class_named::ZERO_NAME);
            CHECK(as<enum_class_named, Enc>(STR_LITERAL(R"("one")")) == enum_class_named::ONE_NAME);
            CHECK(as<enum_class_named, Enc>(STR_LITERAL(R"("two")")) == enum_class_named::TWO_NAME);
        }
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        rapidjson::Document doc;
        SECTION("with enum_class_named::ZERO_NAME")
        {
            auto value = to_json<enum_class_named, Enc>(enum_class_named::ZERO_NAME, doc.GetAllocator());
            REQUIRE_FALSE(value.IsNull());
            CHECK(test::compare_cstring(value, STR_LITERAL("zero")));
        }
        SECTION("with enum_class_named::ONE_NAME")
        {
            auto value = to_json<enum_class_named, Enc>(enum_class_named::ONE_NAME, doc.GetAllocator());
            REQUIRE_FALSE(value.IsNull());
            CHECK(test::compare_cstring(value, STR_LITERAL("one")));
        }
        SECTION("with enum_class_named::TWO_NAME")
        {
            auto value = to_json<enum_class_named, Enc>(enum_class_named::TWO_NAME, doc.GetAllocator());
            REQUIRE_FALSE(value.IsNull());
            CHECK(test::compare_cstring(value, STR_LITERAL("two")));
        }
    }
    SECTION("Can use to_stream()", "[to_stream]")
    {
        std::basic_stringstream<typename Enc::Ch> ss;

        SECTION("with enum_class_named::ZERO_NAME")
        {
            to_stream<enum_class_named, Enc>(ss, enum_class_named::ZERO_NAME);
            CHECK(ss.str() == STR_LITERAL(R"("zero")"));
        }
        SECTION("with enum_class_named::ONE_NAME")
        {
            to_stream<enum_class_named, Enc>(ss, enum_class_named::ONE_NAME);
            CHECK(ss.str() == STR_LITERAL(R"("one")"));
        }
        SECTION("with enum_class_named::TWO_NAME")
        {
            to_stream<enum_class_named, Enc>(ss, enum_class_named::TWO_NAME);
            CHECK(ss.str() == STR_LITERAL(R"("two")"));
        }
    }
}