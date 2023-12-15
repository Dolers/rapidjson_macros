#pragma once

#include <rapidjson_macros/details/serializer_base.hpp>

#include <string>

namespace rapidjson_macros
{
    // Same encoding, no transcoder
    template <typename StrEnc, typename Enc>
    struct json_type_traits<std::basic_string<StrEnc>, Enc, typename std::enable_if<std::is_same<typename Enc::Ch, StrEnc>::value>::type>
    {
        using value_type = std::basic_string<StrEnc>;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsString();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not string");

            return json.GetString();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
#if !RAPIDJSON_HAS_STDSTRING
            static_assert(!std::is_same<Enc, Enc>::value, "Tried to serialize std::string with RAPIDJSON_HAS_STDSTRING=0 compile definition. Error.");
#endif
            return rapidjson::GenericValue<Enc>(obj, alloc);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
#if !RAPIDJSON_HAS_STDSTRING
            static_assert(!std::is_same<Enc, Enc>::value, "Tried to deserialize std::string with RAPIDJSON_HAS_STDSTRING=0 compile definition. Error.");
#endif
            stream.String(obj);
        }
    };

    // Different encoding, use transcoder
    template <typename Enc>
    struct json_type_traits<std::basic_string<char>, Enc, typename std::enable_if<!std::is_same<typename Enc::Ch, char>::value>::type>
    {
        using value_type = std::basic_string<char>;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsString();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not string");

            rapidjson::GenericStringStream<Enc> source(json.GetString());
            rapidjson::GenericStringBuffer<rapidjson::UTF8<>> target;

            while (source.Peek() != null_terminator<Enc::Ch>::value())
                rapidjson::Transcoder<Enc, rapidjson::UTF8<>>::Transcode(source, target);

            return target.GetString();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
#if !RAPIDJSON_HAS_STDSTRING
            static_assert(!std::is_same<Enc, Enc>::value, "Tried to serialize std::string with RAPIDJSON_HAS_STDSTRING=0 compile definition. Error.");
#endif
            rapidjson::GenericStringStream<rapidjson::UTF8<>> source(obj.data());
            rapidjson::GenericStringBuffer<Enc> target;

            for (size_t i = 0; i < obj.length(); i++)
                rapidjson::Transcoder<rapidjson::UTF8<>, Enc>::Transcode(source, target);

            return rapidjson::GenericValue<Enc>(target.GetString(), alloc);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
#if !RAPIDJSON_HAS_STDSTRING
            static_assert(!std::is_same<Enc, Enc>::value, "Tried to deserialize std::string with RAPIDJSON_HAS_STDSTRING=0 compile definition. Error.");
#endif
            rapidjson::GenericStringStream<rapidjson::UTF8<>> source(obj.data());
            rapidjson::GenericStringBuffer<Enc> target;

            for (size_t i = 0; i < obj.length(); i++)
                rapidjson::Transcoder<rapidjson::UTF8<>, Enc>::Transcode(source, target);

            stream.String(target.GetString());
        }
    };
    template <typename Enc>
    struct json_type_traits<std::basic_string<wchar_t>, Enc, typename std::enable_if<!std::is_same<typename Enc::Ch, wchar_t>::value>::type>
    {
        using value_type = std::basic_string<wchar_t>;
        using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;

        static inline bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            return json.IsString();
        }
        static inline value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)
        {
            if (do_check && !is(json))
                throw std::runtime_error("Not string");

            rapidjson::GenericStringStream<Enc> source(json.GetString());
            rapidjson::GenericStringBuffer<rapidjson::UTF16<>> target;

            while (source.Peek() != null_terminator<Enc::Ch>::value())
                rapidjson::Transcoder<Enc, rapidjson::UTF16<>>::Transcode(source, target);

            return target.GetString();
        }
        static inline rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())
        {
#if !RAPIDJSON_HAS_STDSTRING
            static_assert(!std::is_same<Enc, Enc>::value, "Tried to serialize std::wstring with RAPIDJSON_HAS_STDSTRING=0 compile definition. Error.");
#endif
            rapidjson::GenericStringBuffer<rapidjson::UTF16<>> source(obj);
            rapidjson::GenericStringBuffer<Enc> target;

            while (source.Peek() != null_terminator<rapidjson::UTF8<>::Ch>::value())
                rapidjson::Transcoder<rapidjson::UTF16<>, Enc>::Transcode(source, target);

            return rapidjson::GenericValue<Enc>(target.GetString(), alloc);
        }
        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)
        {
#if !RAPIDJSON_HAS_STDSTRING
            static_assert(!std::is_same<Enc, Enc>::value, "Tried to deserialize std::string with RAPIDJSON_HAS_STDSTRING=0 compile definition. Error.");
#endif
            rapidjson::GenericStringBuffer<rapidjson::UTF16<>> source(obj);
            rapidjson::GenericStringBuffer<Enc> target;

            while (source.Peek() != null_terminator<rapidjson::UTF8<>::Ch>::value())
                rapidjson::Transcoder<rapidjson::UTF16<>, Enc>::Transcode(source, target);

            stream.String(target.GetString());
        }
    };
}
