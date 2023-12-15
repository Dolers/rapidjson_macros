#pragma once

#include <rapidjson_macros/details/serializer_base.hpp>

#include <vector>

namespace rapidjson_macros
{

    template <typename T, typename Enc>
    struct json_type_traits<std::vector<T>, Enc>
    {
        using value_type = std::vector<T>;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;
        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsArray();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not TYPE");

            value_type vec;
            vec.reserve(json.Size());
            for (auto& elem : json.GetArray())
            {
                vec.emplace_back(json_type_traits<T, Enc>::as(elem, do_check));
            }

            return vec;
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            rapidjson::GenericValue<Enc> json(rapidjson::kArrayType);

            for (auto& e : obj)
                json.PushBack(json_type_traits<T, Enc>::to_json(e, alloc), alloc);

            return json;
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.StartArray();
            for (const auto& elem : obj)
                json_type_traits<T, Enc>::to_stream(stream, elem);

            stream.EndArray();
        }
    };
}