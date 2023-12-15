#include <rapidjson/document.h>
#include <rapidjson_macros/details/string_literal_picker.hpp>

namespace rapidjson_macros
{
    // It is safe for tests to specialize unsigned as it
    // * is not used in constexpr fields
    // * won't matter in "performance impact"
    template <>
    constexpr const unsigned* string_literal_picker<unsigned>(const char*, const wchar_t*, const char16_t*, const char32_t* c32)
    {
        return (const unsigned*)c32;
    }

#define __EXPAND(x) x
#define TO_WSTRING(x) __EXPAND(L##x)
#define TO_C8_STRING(x) __EXPAND(u8##x)
#define TO_C16_STRING(x) __EXPAND(u##x)
#define TO_C32_STRING(x) __EXPAND(U##x)
#define TO_USTRING(x) __EXPAND((unsigned*)U##x)
#define STR_LITERAL(STR) rapidjson_macros::string_literal_picker<Enc::Ch>(TO_C8_STRING(STR), TO_WSTRING(STR), TO_C16_STRING(STR), TO_C32_STRING(STR))

    namespace test
    {
        template <typename Enc>
        bool compare_cstring(const rapidjson::GenericValue<Enc>& actual_json, const typename Enc::Ch* expected_cstr)
        {
            return actual_json.IsString() && memcmp(actual_json.GetString(), expected_cstr, sizeof(Enc::Ch) * actual_json.GetStringLength()) == 0;
        }
    }
}