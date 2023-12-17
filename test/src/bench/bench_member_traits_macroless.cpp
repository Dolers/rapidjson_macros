// undefine assert
#define RAPIDJSON_ASSERT

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <rapidjson_macros/details/rapidjson_macros.hpp>
#include <test_member_traits.hpp>

#include <sstream>

namespace rapidjson_macros
{
    template <typename Enc>
    struct json_type_traits<all_member_trait_class, Enc>
    {
        static constexpr const char* my_bool_str = "my_bool";
        static constexpr const char* my_int32_str = "my_int32";
        static constexpr const char* my_int64_str = "my_int64";
        static constexpr const char* my_string_str = "my_string";
        static constexpr const char* my_vector_str = "my_vector";
        static constexpr const char* my_map_str = "my_map";
        using value_type = all_member_trait_class;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;
        using char_type = char;
        static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            value_type obj;
            obj.my_bool = json[my_bool_str].GetBool();
            obj.my_int32 = json[my_int32_str].GetInt();
            obj.my_int64 = json[my_int64_str].GetInt64();
            obj.my_string = json[my_string_str].GetString();
            for (auto& e : json[my_vector_str].GetArray())
                obj.my_vector.emplace_back(e.GetInt());

            for (auto& e : json[my_map_str].GetArray())
            {
                auto e_array = e.GetArray();
                obj.my_map.emplace(std::make_pair<int, double>(e_array[0].GetInt(), e_array[1].GetDouble()));
            }

            return obj;
        }
        static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);
            json.AddMember(rapidjson::StringRef(my_bool_str), rapidjson::GenericValue<Enc>(obj.my_bool), alloc);
            json.AddMember(rapidjson::StringRef(my_int32_str), rapidjson::GenericValue<Enc>(obj.my_int32), alloc);
            json.AddMember(rapidjson::StringRef(my_int64_str), rapidjson::GenericValue<Enc>(obj.my_int64), alloc);
            json.AddMember(rapidjson::StringRef(my_string_str), rapidjson::GenericValue<Enc>(rapidjson::StringRef(obj.my_string)), alloc);

            rapidjson::GenericValue<Enc> my_vector(rapidjson::kArrayType);
            for (auto& e : obj.my_vector)
                my_vector.PushBack(rapidjson::GenericValue<Enc>(e), alloc);

            json.AddMember(rapidjson::StringRef(my_vector_str), my_vector, alloc);

            rapidjson::GenericValue<Enc> my_map(rapidjson::kArrayType);
            for (auto& e : obj.my_map)
            {
                rapidjson::GenericValue<Enc> my_map_elem(rapidjson::kArrayType);
                my_map_elem.PushBack(rapidjson::GenericValue<Enc>(e.first), alloc);
                my_map_elem.PushBack(rapidjson::GenericValue<Enc>(e.second), alloc);
                my_map.PushBack(my_map_elem, alloc);
            }
            json.AddMember(rapidjson::StringRef(my_map_str), my_map, alloc);
            return json;
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.StartObject();

            stream.String(my_bool_str);
            stream.Bool(obj.my_bool);
            stream.String(my_int32_str);
            stream.Int(obj.my_int32);
            stream.String(my_int64_str);
            stream.Int64(obj.my_int64);
            stream.String(my_string_str);
            stream.String(obj.my_string);

            stream.String(my_vector_str);
            stream.StartArray();
            for (const auto& elem : obj.my_vector)
                stream.Int(elem);
            stream.EndArray();

            stream.String(my_map_str);
            stream.StartArray();
            for (const auto& elem : obj.my_map)
            {
                stream.StartArray();
                stream.Int(elem.first);
                stream.Double(elem.second);
                stream.EndArray();
            }
            stream.EndArray();

            stream.EndObject();
        }
    };
}

using namespace rapidjson_macros;

TEST_CASE("ALL_MEMBER_TRAITS")
{
    SECTION("Can use as()", "[as]")
    {
        Catch::Benchmark::Benchmark bench(
            "ALL_MEMBER_TRAITS::as",
            [&](int) {
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
            [&](int) {
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
            [&](int) {
                std::stringstream ss;
                to_stream<all_member_trait_class>(ss, val);
                return ss.str();
            });
        bench.run<std::chrono::high_resolution_clock>();
    }
}
