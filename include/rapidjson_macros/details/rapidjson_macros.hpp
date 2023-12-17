#pragma once

#include <rapidjson_macros/details/primitives.hpp>
#include <rapidjson_macros/details/string.hpp>
#include <rapidjson_macros/details/convenience_macros.hpp>

namespace rapidjson_macros
{
    template <class T, typename Enc = rapidjson::UTF8<>>
    static T as(const rapidjson::GenericValue<Enc>& json, const bool& do_check = true)
    {
        return json_type_traits<T, Enc>::as(json, do_check);
    }

#if RAPIDJSON_HAS_STDSTRING
    template <class T, typename Enc = rapidjson::UTF8<>>
    static T as(const std::basic_string<typename Enc::Ch>& json_str, const bool& do_check = true)
    {
        rapidjson::GenericDocument<Enc> doc;
        doc.Parse(json_str);
        if (doc.HasParseError())
        {
            throw std::runtime_error(std::string("Parse error code: ") + std::to_string(doc.GetParseError()) + " at offset: " + std::to_string(doc.GetErrorOffset()));
        }
        return json_type_traits<T, Enc>::as(doc, do_check);
    }
#endif
    template <class T, typename Enc = rapidjson::UTF8<>>
    static T as(const typename Enc::Ch* json_str, const bool& do_check = true)
    {
        rapidjson::GenericDocument<Enc> doc;
        doc.Parse(json_str);
        if (doc.HasParseError())
        {
            throw std::runtime_error(std::string("Parse error code: ") + std::to_string(doc.GetParseError()) + " at offset: " + std::to_string(doc.GetErrorOffset()));
        }
        return json_type_traits<T, Enc>::as(doc, do_check);
    }

    template <class T, typename Enc = rapidjson::UTF8<>>
    static rapidjson::GenericValue<Enc> to_json(const T& obj, typename rapidjson::GenericDocument<Enc>::AllocatorType& alloc)
    {
        return json_type_traits<T, Enc>::to_json(obj, alloc);
    }

    template <class T, typename SrcEnc = rapidjson::UTF8<>, typename TgtEnc = SrcEnc, typename SAlloc = rapidjson::CrtAllocator, unsigned Flags = rapidjson::kWriteDefaultFlags>
    static void to_stream(std::basic_ostream<typename SrcEnc::Ch>& stream, const T& obj)
    {
        rapidjson::BasicOStreamWrapper<std::basic_ostream<typename SrcEnc::Ch>> osw(stream);
        rapidjson::Writer<rapidjson::BasicOStreamWrapper<std::basic_ostream<typename SrcEnc::Ch>>, SrcEnc, TgtEnc, SAlloc, Flags> w(osw);

        json_type_traits<T, SrcEnc>::to_stream(w, obj);
    }

    template <class T, typename OStr, typename SrcEnc = rapidjson::UTF8<>, typename TgtEnc = SrcEnc, typename SAlloc = rapidjson::CrtAllocator, unsigned Flags = rapidjson::kWriteDefaultFlags>
    static void to_stream(rapidjson::Writer<OStr, SrcEnc, TgtEnc, SAlloc, Flags>& writer, const T& obj)
    {
        json_type_traits<T, SrcEnc>::to_stream(writer, obj);
    }
}