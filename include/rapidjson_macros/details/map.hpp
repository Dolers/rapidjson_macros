#pragma once

#include <rapidjson_macros/details/serializer_base.hpp>

#include <string>
#include <map>
#include <unordered_map>

namespace rapidjson_macros
{

#define RAPIDJSON_KEY_MAP_PRIMITIVE(TYPE)                                                                                                                  \
    template <typename K, typename V, typename Enc>                                                                                                        \
    struct json_type_traits<TYPE<K, V>, Enc, typename std::enable_if<!std::is_same<K, std::string>::value && !std::is_same<K, std::wstring>::value>::type> \
    {                                                                                                                                                      \
        using mapped_type = std::pair<K, V>;                                                                                                               \
        using value_type = TYPE<K, V>;                                                                                                                     \
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                                                        \
                                                                                                                                                           \
        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                                                           \
        {                                                                                                                                                  \
            if (json.IsArray())                                                                                                                            \
            {                                                                                                                                              \
                for (auto& elem : json.GetArray())                                                                                                         \
                {                                                                                                                                          \
                    if (!json_type_traits<mapped_type, Enc>::is(elem))                                                                                     \
                        return false;                                                                                                                      \
                }                                                                                                                                          \
                return true;                                                                                                                               \
            }                                                                                                                                              \
            return false;                                                                                                                                  \
        }                                                                                                                                                  \
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                                                        \
        {                                                                                                                                                  \
            if (do_check && !is(json))                                                                                                                     \
                throw std::runtime_error("Not a " #TYPE);                                                                                                  \
                                                                                                                                                           \
            value_type result;                                                                                                                             \
            for (auto& elem : json.GetArray())                                                                                                             \
                result.emplace(json_type_traits<mapped_type, Enc>::as(elem, do_check));                                                                    \
                                                                                                                                                           \
            return result;                                                                                                                                 \
        }                                                                                                                                                  \
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())                                        \
        {                                                                                                                                                  \
            rapidjson::GenericValue<Enc> json(rapidjson::kArrayType);                                                                                      \
                                                                                                                                                           \
            for (auto& e : obj)                                                                                                                            \
                json.PushBack(json_type_traits<mapped_type, Enc>::to_json(e, alloc), alloc);                                                               \
                                                                                                                                                           \
            return json;                                                                                                                                   \
        }                                                                                                                                                  \
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                                                         \
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)                                          \
        {                                                                                                                                                  \
            stream.StartArray();                                                                                                                           \
            for (auto it = obj.begin(); it != obj.end(); ++it)                                                                                             \
                json_type_traits<mapped_type, Enc>::to_stream(stream, *it);                                                                                \
                                                                                                                                                           \
            stream.EndArray();                                                                                                                             \
        }                                                                                                                                                  \
    };

    RAPIDJSON_KEY_MAP_PRIMITIVE(std::map)
    RAPIDJSON_KEY_MAP_PRIMITIVE(std::unordered_map)
#undef RAPIDJSON_KEY_MAP_PRIMITIVE

#define RAPIDJSON_DICTIONARY_PRIMITIVE(TYPE)                                                                                                             \
    template <typename K, typename V, typename Enc>                                                                                                      \
    struct json_type_traits<TYPE<K, V>, Enc, typename std::enable_if<std::is_same<K, std::string>::value || std::is_same<K, std::wstring>::value>::type> \
    {                                                                                                                                                    \
        using value_type = TYPE<K, V>;                                                                                                                   \
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                                                      \
                                                                                                                                                         \
        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                                                         \
        {                                                                                                                                                \
            if (json.IsObject())                                                                                                                         \
            {                                                                                                                                            \
                for (auto it = json.MemberBegin(); it != json.MemberEnd(); it++)                                                                         \
                {                                                                                                                                        \
                    if (!json_type_traits<K, Enc>::is(it->name) || !json_type_traits<V, Enc>::is(it->value))                                             \
                        return false;                                                                                                                    \
                }                                                                                                                                        \
                return true;                                                                                                                             \
            }                                                                                                                                            \
            return false;                                                                                                                                \
        }                                                                                                                                                \
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                                                      \
        {                                                                                                                                                \
            if (do_check && !is(json))                                                                                                                   \
                throw std::runtime_error("Not TYPE");                                                                                                    \
                                                                                                                                                         \
            value_type result;                                                                                                                           \
            for (auto it = json.MemberBegin(); it != json.MemberEnd(); ++it)                                                                             \
                result[json_type_traits<K, Enc>::as(it->name, do_check)] = json_type_traits<V, Enc>::as(it->value, do_check);                            \
                                                                                                                                                         \
            return result;                                                                                                                               \
        }                                                                                                                                                \
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())                                      \
        {                                                                                                                                                \
            rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);                                                                                   \
                                                                                                                                                         \
            for (auto it = obj.begin(); it != obj.end(); ++it)                                                                                           \
                json.AddMember(json_type_traits<K, Enc>::to_json(it->first, alloc), json_type_traits<V, Enc>::to_json(it->second, alloc), alloc);        \
                                                                                                                                                         \
            return json;                                                                                                                                 \
        }                                                                                                                                                \
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                                                       \
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)                                        \
        {                                                                                                                                                \
            stream.StartObject();                                                                                                                        \
            for (auto it = obj.begin(); it != obj.end(); ++it)                                                                                           \
            {                                                                                                                                            \
                json_type_traits<K, Enc>::to_stream(stream, it->first);                                                                                  \
                json_type_traits<V, Enc>::to_stream(stream, it->second);                                                                                 \
            }                                                                                                                                            \
            stream.EndObject();                                                                                                                          \
        }                                                                                                                                                \
    };

    RAPIDJSON_DICTIONARY_PRIMITIVE(std::map)
    RAPIDJSON_DICTIONARY_PRIMITIVE(std::unordered_map)
#undef RAPIDJSON_DICTIONARY_PRIMITIVE
}