// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <rapidjson_macros/rapidjson_macros>
#include <test_member_traits.hpp>

#include <sstream>

RAPIDJSON_ALL_MEMBER_TRAITS(all_member_trait_class, my_bool, my_int32, my_int64, my_string, my_vector, my_map);

using namespace rapidjson_macros;

TEST_CASE("ALL_MEMBER_TRAITS")
{
    SECTION("Can use as()", "[as]")
    {
        Catch::Benchmark::Benchmark bench(
            "ALL_MEMBER_TRAITS::as",
            [&](int)
            {
                return as<all_member_trait_class>(
                    R"(
                        {
                            "my_bool": true,
                            "my_int32": 1234,
                            "my_int64": 5678,
                            "my_string": "Lupercal",
                            "my_vector": [10,20,30,40],
                            "my_map": [[0,0.5],[1,1.5]]
                        }
                    )",
                    false);
            });
        bench.run<std::chrono::high_resolution_clock>();
    }

    SECTION("Can use to_json()", "[to_json]")
    {
        all_member_trait_class val;
        val.my_bool = true;
        val.my_int32 = 1234;
        val.my_int64 = 5678;
        val.my_string = "Lupercal";
        val.my_vector = {10, 20, 30, 40};
        val.my_map = {{0, 0.5}, {1, 1.5}};

        Catch::Benchmark::Benchmark bench(
            "ALL_MEMBER_TRAITS::as",
            [&](int)
            {
                rapidjson::Document doc;
                return to_json<all_member_trait_class>(val, doc.GetAllocator());
            });
        bench.run<std::chrono::high_resolution_clock>();
    }
    SECTION("Can use to_stream(std::ostream)", "[to_stream]")
    {
        all_member_trait_class val;
        val.my_bool = true;
        val.my_int32 = 1234;
        val.my_int64 = 5678;
        val.my_string = "Lupercal";
        val.my_vector = {10, 20, 30, 40};
        val.my_map = {{0, 0.5}, {1, 1.5}};

        Catch::Benchmark::Benchmark bench(
            "ALL_MEMBER_TRAITS::to_stream",
            [&](int)
            {
                std::stringstream ss;
                to_stream<all_member_trait_class>(ss, val);
                return ss.str();
            });
        bench.run<std::chrono::high_resolution_clock>();
    }
}
