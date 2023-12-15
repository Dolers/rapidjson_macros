#pragma once

#include <type_traits>
#include <ostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

namespace rapidjson_macros
{
    // Base class of rapidjson_macros json type trait handling
    // @note If you have a compile error here, it means that you are missing a macro for a class.
    // Error should state which class
    template <typename T, typename Enc, class Enable = void>
    struct json_type_traits
    {
        static bool is(const rapidjson::GenericValue<Enc>& json) noexcept
        {
            static_assert(!std::is_same<T, T>::value, "json_type_traits::is is not implemented. Might be missing macro for type T");
        }

        static T as(const rapidjson::GenericValue<Enc>&, const bool& do_check)
        {
            static_assert(!std::is_same<T, T>::value, "json_type_traits::as<Enc> is not implemented. Might be missing macro for type T");
        }

        static rapidjson::GenericValue<Enc> to_json(const T&, typename rapidjson::GenericDocument<Enc>::AllocatorType&)
        {
            static_assert(!std::is_same<T, T>::value, "json_type_traits::to_json<Enc> is not implemented. Might be missing macro for type T");
        }

        template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>
        static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const T&)
        {
            static_assert(!std::is_same<T, T>::value, "json_type_traits::to_stream is not implemented. Might be missing macro for type T");
        }
    };
    template <typename T, typename Enc>
    struct json_traits_macro_names
    {
    };
}