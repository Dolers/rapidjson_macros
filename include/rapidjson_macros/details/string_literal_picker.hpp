#pragma once

namespace rapidjson_macros
{
    template <typename CharT>
    constexpr const CharT* string_literal_picker(const char*, const wchar_t*, const char16_t*, const char32_t*);
    template <>
    constexpr const char* string_literal_picker<char>(const char* c, const wchar_t*, const char16_t*, const char32_t*)
    {
        return c;
    }
    template <>
    constexpr const wchar_t* string_literal_picker<wchar_t>(const char*, const wchar_t* w, const char16_t*, const char32_t*)
    {
        return w;
    }
    template <>
    constexpr const char16_t* string_literal_picker<char16_t>(const char*, const wchar_t*, const char16_t* c16, const char32_t*)
    {
        return c16;
    }
    template <>
    constexpr const char32_t* string_literal_picker<char32_t>(const char*, const wchar_t*, const char16_t*, const char32_t* c32)
    {
        return c32;
    }
}