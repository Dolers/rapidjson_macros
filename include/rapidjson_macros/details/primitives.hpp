#pragma once

#include <rapidjson_macros/details/serializer_base.hpp>
#include <rapidjson_macros/details/rapidjson/stream.hpp>

#include <cstdint>
#include <map>
#include <unordered_map>

namespace rapidjson_macros
{
    template <typename Enc>
    struct json_type_traits<bool, Enc>
    {
        using value_type = bool;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsBool();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not bool");

            return json.GetBool();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.Bool(obj);
        }
    };

    template <typename T, typename Enc>
    struct json_type_traits<T, Enc,
                            typename std::enable_if<
                                std::is_same<T, int8_t>::value ||
                                std::is_same<T, int16_t>::value ||
                                std::is_same<T, int32_t>::value>::type>
    {
        using value_type = T;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsInt();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not int");

            return json.GetInt();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.Int(obj);
        }
    };

    template <typename T, typename Enc>
    struct json_type_traits<T, Enc,
                            typename std::enable_if<
                                std::is_same<T, uint8_t>::value ||
                                std::is_same<T, uint16_t>::value ||
                                std::is_same<T, uint32_t>::value>::type>
    {
        using value_type = T;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsUint();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not int");

            return json.GetUint();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.Uint(obj);
        }
    };

    template <typename Enc>
    struct json_type_traits<int64_t, Enc>
    {
        using value_type = int64_t;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsInt64();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not int64");

            return json.GetInt64();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.Int64(obj);
        }
    };

    template <typename Enc>
    struct json_type_traits<uint64_t, Enc>
    {
        using value_type = uint64_t;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsUint64();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not uint64");

            return json.GetUint64();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.Uint64(obj);
        }
    };

    template <typename Enc>
    struct json_type_traits<double, Enc>
    {
        using value_type = double;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsDouble();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not double");

            return json.GetDouble();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.Double(obj);
        }
    };

    template <typename Enc>
    struct json_type_traits<float, Enc>
    {
        using value_type = float;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsFloat();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not float");

            return json.GetFloat();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.Double(obj);
        }
    };

    template <typename CharType>
    struct null_terminator
    {
        static CharType value() = 0;
    };
    template <>
    struct null_terminator<char>
    {
        static inline char value() { return '\0'; }
    };
    template <>
    struct null_terminator<wchar_t>
    {
        static inline wchar_t value() { return L'\0'; }
    };
    template <>
    struct null_terminator<char16_t>
    {
        static inline char16_t value() { return u'\0'; }
    };
    template <>
    struct null_terminator<char32_t>
    {
        static inline char32_t value() { return U'\0'; }
    };
    template <>
    struct null_terminator<unsigned>
    {
        static inline unsigned value() { return (unsigned)U'\0'; }
    };

    template <typename CharType>
    struct reverse_encoding
    {
    };
    template <>
    struct reverse_encoding<char>
    {
        using Enc = rapidjson::UTF8<char>;
    };
    template <>
    struct reverse_encoding<wchar_t>
    {
        using Enc = rapidjson::UTF16<wchar_t>;
    };
    template <>
    struct reverse_encoding<char16_t>
    {
        using Enc = rapidjson::UTF16<char16_t>;
    };
    template <>
    struct reverse_encoding<char32_t>
    {
        using Enc = rapidjson::UTF32<char32_t>;
    };
    template <>
    struct reverse_encoding<unsigned>
    {
        using Enc = rapidjson::UTF32<unsigned>;
    };

    // Same encoding, no transcoder
    template <typename T, typename Enc>
    struct json_type_traits<const T*,
                            Enc,
                            typename std::enable_if<
                                std::is_same<T, typename Enc::Ch>::value && (std::is_same<T, char>::value ||
                                                                             std::is_same<T, wchar_t>::value ||
                                                                             std::is_same<T, char16_t>::value ||
                                                                             std::is_same<T, char32_t>::value ||
                                                                             std::is_same<T, unsigned>::value)>::type>
    {
        using value_type = const T*;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsString();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not string");

            auto len = json.GetStringLength();
            T* temp = static_cast<T*>(malloc(sizeof(T) * len + 1));
            std::memcpy(temp, json.GetString(), len);
            temp[len] = null_terminator<Enc::Ch>::value();

            return temp;
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type obj, alloc_type& alloc = alloc_type())
        {
            return rapidjson::GenericValue<Enc>(obj, alloc);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.String(obj);
        }
    };

    // Different encoding, use transcoder
    template <typename T, typename Enc>
    struct json_type_traits<const T*,
                            Enc,
                            typename std::enable_if<
                                !std::is_same<T, typename Enc::Ch>::value && (std::is_same<T, char>::value ||
                                                                              std::is_same<T, wchar_t>::value ||
                                                                              std::is_same<T, char16_t>::value ||
                                                                              std::is_same<T, char32_t>::value ||
                                                                              std::is_same<T, unsigned>::value)>::type>
    {
        using value_type = const T*;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsString();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not string");

            auto len = json.GetStringLength();
            T* temp = static_cast<T*>(malloc(sizeof(T) * len + 1));

            rapidjson::GenericStringStream<Enc> source(json.GetString());
            rapidjson::ReadWriteStringStream<reverse_encoding<T>::Enc> target(temp);

            while (source.Peek() != null_terminator<Enc::Ch>::value())
                rapidjson::Transcoder<Enc, reverse_encoding<T>::Enc>::Transcode(source, target);

            temp[len] = null_terminator<T>::value();

            return temp;
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type obj, alloc_type& alloc = alloc_type())
        {
            rapidjson::GenericStringStream<reverse_encoding<T>::Enc> source(obj);
            rapidjson::GenericStringBuffer<Enc> target;

            while (source.Peek() != null_terminator<Enc::Ch>::value())
                rapidjson::Transcoder<reverse_encoding<T>::Enc, Enc>::Transcode(source, target);

            return rapidjson::GenericValue<Enc>(target.GetString(), alloc);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            rapidjson::GenericStringStream<rapidjson::UTF8<>> source(obj);
            rapidjson::GenericStringBuffer<Enc> target;

            while (source.Peek() != null_terminator<Enc::Ch>::value())
                rapidjson::Transcoder<reverse_encoding<T>::Enc, Enc>::Transcode(source, target);

            stream.String(target.GetString());
        }
    };

    template <typename CharType>
    struct CharArrayCompare
    {
        bool operator()(const CharType* s1, const CharType* s2) const
        {
            CharType null_char = null_terminator<CharType>::value();
            while (*s1 != null_char && (*s1 == *s2))
                s1++, s2++;
            return *s1 < *s2;
        }
    };

    template <typename T1, typename T2, typename Enc>
    struct json_type_traits<std::pair<T1, T2>, Enc>
    {
        using value_type = std::pair<T1, T2>;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsArray() && json.Size() == 2;
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not std::pair");

            auto& array = json.GetArray();
            return std::make_pair<T1, T2>(
                json_type_traits<T1, Enc>::as(array[0], do_check),
                json_type_traits<T2, Enc>::as(array[1], do_check));
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
            rapidjson::GenericValue<Enc> json(rapidjson::kArrayType);

            json.PushBack(json_type_traits<T1, Enc>::to_json(obj.first, alloc), alloc);
            json.PushBack(json_type_traits<T2, Enc>::to_json(obj.second, alloc), alloc);

            return json;
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
            stream.StartArray();
            json_type_traits<T1, Enc>::to_stream(stream, obj.first);
            json_type_traits<T2, Enc>::to_stream(stream, obj.second);
            stream.EndArray();
        }
    };
}
