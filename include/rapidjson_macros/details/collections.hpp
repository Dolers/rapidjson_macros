#pragma once

#include <rapidjson_macros/details/serializer_base.hpp>

#include <array>
#include <set>
#include <list>
#include <unordered_set>

namespace rapidjson_macros
{

#define RAPIDJSON_ARRAY_PRIMITIVE(TYPE, INSERTER)                                                                   \
    template <typename T, typename Enc>                                                                             \
    struct json_type_traits<TYPE<T>, Enc>                                                                           \
    {                                                                                                               \
        using value_type = TYPE<T>;                                                                                 \
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                 \
        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                    \
        {                                                                                                           \
            return json.IsArray();                                                                                  \
        }                                                                                                           \
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                 \
        {                                                                                                           \
            if (do_check && !is(json))                                                                              \
                throw std::runtime_error("Not TYPE");                                                               \
                                                                                                                    \
            value_type vec;                                                                                         \
            for (auto& elem : json.GetArray())                                                                      \
            {                                                                                                       \
                vec.INSERTER(json_type_traits<T, Enc>::as(elem, do_check));                                         \
            }                                                                                                       \
                                                                                                                    \
            return vec;                                                                                             \
        }                                                                                                           \
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type()) \
        {                                                                                                           \
            rapidjson::GenericValue<Enc> json(rapidjson::kArrayType);                                               \
                                                                                                                    \
            for (auto& e : obj)                                                                                     \
                json.PushBack(json_type_traits<T, Enc>::to_json(e, alloc), alloc);                                  \
                                                                                                                    \
            return json;                                                                                            \
        }                                                                                                           \
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                  \
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)   \
        {                                                                                                           \
            stream.StartArray();                                                                                    \
            for (const auto& elem : obj)                                                                            \
                json_type_traits<T, Enc>::to_stream(stream, elem);                                                  \
                                                                                                                    \
            stream.EndArray();                                                                                      \
        }                                                                                                           \
    };

    RAPIDJSON_ARRAY_PRIMITIVE(std::list, emplace_back)
    RAPIDJSON_ARRAY_PRIMITIVE(std::set, emplace)
    RAPIDJSON_ARRAY_PRIMITIVE(std::unordered_set, emplace)
#undef RAPIDJSON_ARRAY_PRIMITIVE

    template <class E, std::size_t N, typename Enc>
    struct json_type_traits<std::array<E, N>, Enc>
    {
        using value_type = std::array<E, N>;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            if (json.IsArray() && json.Size() == N)
            {
                for (auto& elem : json.GetArray())
                {
                    if (!json_type_traits<E, Enc>::is((elem)))
                        return false;
                }
                return true;
            }
            return false;
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not std::array");

            value_type buff;

            size_t i = 0;
            for (auto& e : json.GetArray())
                buff[i++] = json_type_traits<E, Enc>::as(e, do_check);

            return buff;
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            rapidjson::GenericValue<Enc> json(rapidjson::kArrayType);

            for (auto& e : obj)
                json.PushBack(json_type_traits<E, Enc>::to_json(e, alloc), alloc);

            return json;
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.StartArray();
            for (auto it = obj.begin(); it != obj.end(); ++it)
                json_type_traits<E, Enc>::to_stream(stream, *it);

            stream.EndArray();
        }
    };
} // namespace rapidjson_macros