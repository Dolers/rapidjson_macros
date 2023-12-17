#pragma once

#include <rapidjson/document.h>
#include <rapidjson_macros/details/string_literal_picker.hpp>

namespace rapidjson_macros
{
    // It is safe for tests to specialize unsigned as it
    // * is not used in constexpr fields
    // * won't matter in "performance impact"
    template <>
    inline const unsigned* string_literal_picker<unsigned>(const char*, const wchar_t*, const char16_t*, const char32_t* c32)
    {
        return reinterpret_cast<const unsigned*>(c32);
    }

#define __EXPAND(x) x
#define TO_WSTRING(x) __EXPAND(L##x)
#define TO_C8_STRING(x) __EXPAND(u8##x)
#define TO_C16_STRING(x) __EXPAND(u##x)
#define TO_C32_STRING(x) __EXPAND(U##x)
#define TO_USTRING(x) __EXPAND((unsigned*)U##x)
#define STR_LITERAL(STR) rapidjson_macros::string_literal_picker<typename Enc::Ch>(TO_C8_STRING(STR), TO_WSTRING(STR), TO_C16_STRING(STR), TO_C32_STRING(STR))

    namespace test
    {
        template <typename Enc>
        bool compare_cstring(const rapidjson::GenericValue<Enc>& actual_json, const typename Enc::Ch* expected_cstr)
        {
            return actual_json.IsString() && memcmp(actual_json.GetString(), expected_cstr, sizeof(typename Enc::Ch) * actual_json.GetStringLength()) == 0;
        }

        template <typename Enc, class Pred, bool Const, typename ValueT>
        bool array_contains(rapidjson::GenericArray<Const, ValueT> array, Pred predicate)
        {
            bool contains = false;
            for (typename rapidjson::GenericValue<Enc>::ConstValueIterator itr = array.Begin(); itr != array.End(); ++itr)
            {
                contains |= predicate(itr);
            }
            return contains;
        }

        template <typename CharType>
        struct space
        {
            static bool check(CharType);
        };
        template <>
        struct space<char>
        {
            static inline bool check(char c) { return std::isspace(c, std::locale::classic()); }
        };
        template <>
        struct space<wchar_t>
        {
            static inline bool check(wchar_t c) { return std::isspace(c, std::locale::classic()); }
        };
        template <>
        struct space<char16_t>
        {
            static inline bool check(char16_t c) { return std::isspace(c, std::locale::classic()); }
        };
        template <>
        struct space<char32_t>
        {
            static inline bool check(char32_t c)
            {
                return memcmp(&c, U" ", sizeof(char32_t)) == 0 || memcmp(&c, U"\r", sizeof(char32_t)) == 0 || memcmp(&c, U"\n", sizeof(char32_t)) == 0 || memcmp(&c, U"\t", sizeof(char32_t)) == 0;
            }
        };
        template <>
        struct space<unsigned>
        {
            static inline bool check(unsigned c) { return space<char32_t>::check(c); }
        };

    }
}