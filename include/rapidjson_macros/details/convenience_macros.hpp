#pragma once

#include <rapidjson_macros/details/string_literal_picker.hpp>
#include <unordered_map>
#include <stdexcept>

// Based upon https://github.com/danielaparker/jsoncons

#define RAPIDJSON_EXPAND(X) X
#define RAPIDJSON_QUOTE(Call, A) RAPIDJSON_EXPAND(Call## #A)

#define RAPIDJSON_CONCAT_RAW(a, b) a##b
#define RAPIDJSON_CONCAT(a, b) RAPIDJSON_CONCAT_RAW(a, b)

#define RAPIDJSON_COMMA ,

#define RAPIDJSON_NARGS(...) RAPIDJSON_NARG_(__VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define RAPIDJSON_NARG_(...) RAPIDJSON_EXPAND(RAPIDJSON_ARG_N(__VA_ARGS__))
#define RAPIDJSON_ARG_N(e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63, e64, e65, e66, e67, e68, e69, e70, N, ...) N

#define RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, Count) Call(P1, P2, P3, P4, Count)

#define RAPIDJSON_VARIADIC_REP_N(Call, P1, P2, P3, ...) RAPIDJSON_VARIADIC_REP_OF_N(Call, P1, P2, P3, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)
#define RAPIDJSON_VARIADIC_REP_OF_N(Call, P1, P2, P3, Count, ...) RAPIDJSON_VARIADIC_REP_OF_N_(Call, P1, P2, P3, Count, __VA_ARGS__)
#define RAPIDJSON_VARIADIC_REP_OF_N_(Call, P1, P2, P3, Count, ...) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_##Count(Call, P1, P2, P3, __VA_ARGS__))

#define RAPIDJSON_VARIADIC_REP_N(Call, P1, P2, P3, ...) RAPIDJSON_VARIADIC_REP_OF_N(Call, P1, P2, P3, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)
#define RAPIDJSON_VARIADIC_REP_OF_N(Call, P1, P2, P3, Count, ...) RAPIDJSON_VARIADIC_REP_OF_N_(Call, P1, P2, P3, Count, __VA_ARGS__)
#define RAPIDJSON_VARIADIC_REP_OF_N_(Call, P1, P2, P3, Count, ...) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_##Count(Call, P1, P2, P3, __VA_ARGS__))

#define RAPIDJSON_VARIADIC_REP_OF_70(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 70) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_69(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_69(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 69) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_68(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_68(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 68) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_67(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_67(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 67) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_66(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_66(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 66) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_65(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_65(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 65) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_64(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_64(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 64) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_63(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_63(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 63) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_62(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_62(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 62) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_61(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_61(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 61) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_60(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_60(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 60) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_59(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_59(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 59) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_58(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_58(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 58) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_57(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_57(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 57) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_56(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_56(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 56) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_55(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_55(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 55) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_54(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_54(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 54) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_53(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_53(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 53) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_52(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_52(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 52) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_51(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_51(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 51) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_50(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_50(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 50) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_49(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_49(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 49) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_48(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_48(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 48) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_47(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_47(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 47) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_46(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_46(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 46) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_45(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_45(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 45) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_44(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_44(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 44) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_43(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_43(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 43) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_42(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_42(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 42) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_41(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_41(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 41) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_40(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_40(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 40) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_39(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_39(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 39) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_38(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_38(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 38) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_37(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_37(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 37) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_36(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_36(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 36) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_35(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_35(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 35) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_34(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_34(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 34) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_33(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_33(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 33) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_32(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_32(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 32) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_31(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_31(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 31) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_30(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_30(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 30) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_29(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_29(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 29) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_28(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_28(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 28) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_27(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_27(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 27) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_26(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_26(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 26) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_25(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_25(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 25) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_24(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_24(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 24) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_23(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_23(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 23) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_22(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_22(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 22) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_21(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_21(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 21) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_20(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_20(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 20) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_19(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_19(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 19) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_18(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_18(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 18) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_17(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_17(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 17) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_16(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_16(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 16) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_15(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_15(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 15) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_14(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_14(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 14) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_13(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_13(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 13) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_12(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_12(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 12) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_11(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_11(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 11) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_10(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_10(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 10) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_9(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_9(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 9) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_8(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_8(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 8) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_7(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_7(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 7) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_6(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_6(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 6) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_5(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_5(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 5) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_4(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_4(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 4) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_3(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_3(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 3) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_2(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_2(Call, P1, P2, P3, P4, ...) RAPIDJSON_EXPAND_CALL5(Call, P1, P2, P3, P4, 2) RAPIDJSON_EXPAND(RAPIDJSON_VARIADIC_REP_OF_1(Call, P1, P2, P3, __VA_ARGS__))
#define RAPIDJSON_VARIADIC_REP_OF_1(Call, P1, P2, P3, P4) RAPIDJSON_EXPAND(Call##_LAST(P1, P2, P3, P4, 1))

#define RAPIDJSON_TRAIT_FRIEND                  \
    template <class T, class Enc, class Enable> \
    friend struct rapidjson_macros::json_type_traits;

#define RAPIDJSON_EXPAND_CALL2(Call, Expr, Id) RAPIDJSON_EXPAND(Call(Expr, Id))

#define RAPIDJSON_REP_OF_N(Call, Expr, Pre, App, Count) RAPIDJSON_REP_OF_##Count(Call, Expr, Pre, App)

#define RAPIDJSON_REP_OF_50(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 50) RAPIDJSON_REP_OF_49(Call, Expr, , App)
#define RAPIDJSON_REP_OF_49(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 49) RAPIDJSON_REP_OF_48(Call, Expr, , App)
#define RAPIDJSON_REP_OF_48(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 48) RAPIDJSON_REP_OF_47(Call, Expr, , App)
#define RAPIDJSON_REP_OF_47(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 47) RAPIDJSON_REP_OF_46(Call, Expr, , App)
#define RAPIDJSON_REP_OF_46(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 46) RAPIDJSON_REP_OF_45(Call, Expr, , App)
#define RAPIDJSON_REP_OF_45(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 45) RAPIDJSON_REP_OF_44(Call, Expr, , App)
#define RAPIDJSON_REP_OF_44(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 44) RAPIDJSON_REP_OF_43(Call, Expr, , App)
#define RAPIDJSON_REP_OF_43(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 43) RAPIDJSON_REP_OF_42(Call, Expr, , App)
#define RAPIDJSON_REP_OF_42(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 42) RAPIDJSON_REP_OF_41(Call, Expr, , App)
#define RAPIDJSON_REP_OF_41(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 41) RAPIDJSON_REP_OF_40(Call, Expr, , App)
#define RAPIDJSON_REP_OF_40(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 40) RAPIDJSON_REP_OF_39(Call, Expr, , App)
#define RAPIDJSON_REP_OF_39(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 39) RAPIDJSON_REP_OF_38(Call, Expr, , App)
#define RAPIDJSON_REP_OF_38(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 38) RAPIDJSON_REP_OF_37(Call, Expr, , App)
#define RAPIDJSON_REP_OF_37(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 37) RAPIDJSON_REP_OF_36(Call, Expr, , App)
#define RAPIDJSON_REP_OF_36(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 36) RAPIDJSON_REP_OF_35(Call, Expr, , App)
#define RAPIDJSON_REP_OF_35(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 35) RAPIDJSON_REP_OF_34(Call, Expr, , App)
#define RAPIDJSON_REP_OF_34(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 34) RAPIDJSON_REP_OF_33(Call, Expr, , App)
#define RAPIDJSON_REP_OF_33(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 33) RAPIDJSON_REP_OF_32(Call, Expr, , App)
#define RAPIDJSON_REP_OF_32(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 32) RAPIDJSON_REP_OF_31(Call, Expr, , App)
#define RAPIDJSON_REP_OF_31(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 31) RAPIDJSON_REP_OF_30(Call, Expr, , App)
#define RAPIDJSON_REP_OF_30(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 30) RAPIDJSON_REP_OF_29(Call, Expr, , App)
#define RAPIDJSON_REP_OF_29(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 29) RAPIDJSON_REP_OF_28(Call, Expr, , App)
#define RAPIDJSON_REP_OF_28(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 28) RAPIDJSON_REP_OF_27(Call, Expr, , App)
#define RAPIDJSON_REP_OF_27(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 27) RAPIDJSON_REP_OF_26(Call, Expr, , App)
#define RAPIDJSON_REP_OF_26(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 26) RAPIDJSON_REP_OF_25(Call, Expr, , App)
#define RAPIDJSON_REP_OF_25(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 25) RAPIDJSON_REP_OF_24(Call, Expr, , App)
#define RAPIDJSON_REP_OF_24(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 24) RAPIDJSON_REP_OF_23(Call, Expr, , App)
#define RAPIDJSON_REP_OF_23(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 23) RAPIDJSON_REP_OF_22(Call, Expr, , App)
#define RAPIDJSON_REP_OF_22(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 22) RAPIDJSON_REP_OF_21(Call, Expr, , App)
#define RAPIDJSON_REP_OF_21(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 21) RAPIDJSON_REP_OF_20(Call, Expr, , App)
#define RAPIDJSON_REP_OF_20(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 20) RAPIDJSON_REP_OF_19(Call, Expr, , App)
#define RAPIDJSON_REP_OF_19(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 19) RAPIDJSON_REP_OF_18(Call, Expr, , App)
#define RAPIDJSON_REP_OF_18(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 18) RAPIDJSON_REP_OF_17(Call, Expr, , App)
#define RAPIDJSON_REP_OF_17(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 17) RAPIDJSON_REP_OF_16(Call, Expr, , App)
#define RAPIDJSON_REP_OF_16(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 16) RAPIDJSON_REP_OF_15(Call, Expr, , App)
#define RAPIDJSON_REP_OF_15(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 15) RAPIDJSON_REP_OF_14(Call, Expr, , App)
#define RAPIDJSON_REP_OF_14(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 14) RAPIDJSON_REP_OF_13(Call, Expr, , App)
#define RAPIDJSON_REP_OF_13(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 13) RAPIDJSON_REP_OF_12(Call, Expr, , App)
#define RAPIDJSON_REP_OF_12(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 12) RAPIDJSON_REP_OF_11(Call, Expr, , App)
#define RAPIDJSON_REP_OF_11(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 11) RAPIDJSON_REP_OF_10(Call, Expr, , App)
#define RAPIDJSON_REP_OF_10(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 10) RAPIDJSON_REP_OF_9(Call, Expr, , App)
#define RAPIDJSON_REP_OF_9(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 9) RAPIDJSON_REP_OF_8(Call, Expr, , App)
#define RAPIDJSON_REP_OF_8(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 8) RAPIDJSON_REP_OF_7(Call, Expr, , App)
#define RAPIDJSON_REP_OF_7(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 7) RAPIDJSON_REP_OF_6(Call, Expr, , App)
#define RAPIDJSON_REP_OF_6(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 6) RAPIDJSON_REP_OF_5(Call, Expr, , App)
#define RAPIDJSON_REP_OF_5(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 5) RAPIDJSON_REP_OF_4(Call, Expr, , App)
#define RAPIDJSON_REP_OF_4(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 4) RAPIDJSON_REP_OF_3(Call, Expr, , App)
#define RAPIDJSON_REP_OF_3(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 3) RAPIDJSON_REP_OF_2(Call, Expr, , App)
#define RAPIDJSON_REP_OF_2(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call, Expr, 2) RAPIDJSON_REP_OF_1(Call, Expr, , App)
#define RAPIDJSON_REP_OF_1(Call, Expr, Pre, App) Pre RAPIDJSON_EXPAND_CALL2(Call##_LAST, Expr, 1) App
#define RAPIDJSON_REP_OF_0(Call, Expr, Pre, App)

#define RAPIDJSON_GENERATE_TPL_PARAMS(Call, Count) RAPIDJSON_REP_OF_N(Call, , , , Count)
#define RAPIDJSON_GENERATE_TPL_ARGS(Call, Count) RAPIDJSON_REP_OF_N(Call, , <, >, Count)
#define RAPIDJSON_GENERATE_TPL_SPECIALIZE(Call, Count) RAPIDJSON_REP_OF_N(Call, , template <, >, Count)
#define RAPIDJSON_GENERATE_TPL_PARAM(Expr, Id) typename T##Id,
#define RAPIDJSON_GENERATE_TPL_PARAM_LAST(Expr, Id) typename T##Id
#define RAPIDJSON_GENERATE_MORE_TPL_PARAM(Expr, Id) , typename T##Id
#define RAPIDJSON_GENERATE_MORE_TPL_PARAM_LAST(Expr, Id) , typename T##Id
#define RAPIDJSON_GENERATE_TPL_ARG(Expr, Id) T##Id,
#define RAPIDJSON_GENERATE_TPL_ARG_LAST(Ex, Id) T##Id

#define RAPIDJSON_TO_WSTRING(x) RAPIDJSON_EXPAND(L##x)
#define RAPIDJSON_TO_C8_STRING(x) RAPIDJSON_EXPAND(u8##x)
#define RAPIDJSON_TO_C16_STRING(x) RAPIDJSON_EXPAND(u##x)
#define RAPIDJSON_TO_C32_STRING(x) RAPIDJSON_EXPAND(U##x)
#define RAPIDJSON_STR_LITERAL(STR)                  \
    rapidjson_macros::string_literal_picker<CharT>( \
        RAPIDJSON_TO_C8_STRING(STR),                \
        RAPIDJSON_TO_WSTRING(STR),                  \
        RAPIDJSON_TO_C16_STRING(STR),               \
        RAPIDJSON_TO_C32_STRING(STR))

#define RAPIDJSON_GENERATE_NAME_STRUCTS(ValueType, NumTemplateParams, Prefix, Call, ...)                                           \
    template <typename CharT RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_MORE_TPL_PARAM, NumTemplateParams)>                  \
    struct json_traits_macro_names<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), CharT>    \
    {                                                                                                                              \
        RAPIDJSON_VARIADIC_REP_N(Call, CharT, , Prefix, __VA_ARGS__)                                                               \
    };                                                                                                                             \
    template <RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_TPL_PARAM, NumTemplateParams)>                                      \
    struct json_traits_macro_names<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), unsigned> \
    {                                                                                                                              \
        RAPIDJSON_VARIADIC_REP_N(Call, unsigned, , Prefix, __VA_ARGS__)                                                            \
    };                                                                                                                             \
    RAPIDJSON_VARIADIC_REP_N(Call##_UNSIGNED_DECLARE, ValueType, NumTemplateParams, Prefix, __VA_ARGS__)

#define RAPIDJSON_GENERATE_NAME_STR(CharType, P2, Prefix, Member, Count) RAPIDJSON_GENERATE_NAME_STR_LAST(CharType, P2, Prefix, Member, Count)
#define RAPIDJSON_GENERATE_NAME_STR_LAST(CharType, P2, Prefix, Member, Count) RAPIDJSON_GENERATE_NAME_STR_##CharType(Prefix, Member)
#define RAPIDJSON_GENERATE_NAME_STR_CharT(Prefix, Member) \
    static constexpr const CharT* Prefix##Member##_str = RAPIDJSON_STR_LITERAL(#Member);
#define RAPIDJSON_GENERATE_NAME_STR_unsigned(Prefix, Member) \
    static const unsigned* Prefix##Member##_str;

#define RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR(CharType, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_##CharType Seq)
#define RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_LAST(CharType, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_##CharType Seq)
#define RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_CharT(Getter, Name) \
    static constexpr const CharT* Getter##_str = RAPIDJSON_STR_LITERAL(Name);
#define RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_unsigned(Getter, Name) \
    static const unsigned* Getter##_str;

#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR(CharType, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_##CharType Seq)
#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_LAST(CharType, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_##CharType Seq)
#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_CharT(Getter, Setter, Name) \
    static constexpr const CharT* Getter##_str = RAPIDJSON_STR_LITERAL(Name);
#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_unsigned(Getter, Setter, Name) \
    static const unsigned* Getter##_str;

// There is no string literal for unsigned, so we need to cast char32_t to unsigned
// The issue is casting is not allowed for constexpr, so we need a separate struct handling just unsigned
// Alternatively, string_literal_picker could do the cast, but it will lose its constexprness for unsigned
// This variant with a little comp-optimization will result in +1 ASM call than the rest of the types, despite the vast amount of code
#define RAPIDJSON_GENERATE_NAME_STR_UNSIGNED_DECLARE(ValueType, NumTemplateParams, Prefix, Member, Count) RAPIDJSON_GENERATE_NAME_STR_UNSIGNED_DECLARE_LAST(ValueType, NumTemplateParams, Prefix, Member, Count)
#define RAPIDJSON_GENERATE_NAME_STR_UNSIGNED_DECLARE_LAST(ValueType, NumTemplateParams, Prefix, Member, Count) \
    RAPIDJSON_GENERATE_TPL_SPECIALIZE(RAPIDJSON_GENERATE_TPL_PARAM, NumTemplateParams)                         \
    const unsigned* json_traits_macro_names<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), unsigned>::Prefix##Member##_str = (unsigned*)RAPIDJSON_QUOTE(U, Member);

#define RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE(ValueType, NumTemplateParams, P3, Seq, Count) RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_LAST(ValueType, NumTemplateParams, P3, Seq, Count)
#define RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_LAST(ValueType, NumTemplateParams, P3, Seq, Count) \
    RAPIDJSON_GENERATE_TPL_SPECIALIZE(RAPIDJSON_GENERATE_TPL_PARAM, NumTemplateParams)                                     \
    const unsigned* json_traits_macro_names<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), unsigned>::RAPIDJSON_EXPAND(RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_ Seq)
#define RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_(Getter, Name) \
    Getter##_str = (unsigned*)U##Name;

#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE(ValueType, NumTemplateParams, P3, Seq, Count) RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_LAST(ValueType, NumTemplateParams, P3, Seq, Count)
#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_LAST(ValueType, NumTemplateParams, P3, Seq, Count) \
    RAPIDJSON_GENERATE_TPL_SPECIALIZE(RAPIDJSON_GENERATE_TPL_PARAM, NumTemplateParams)                                            \
    const unsigned* json_traits_macro_names<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), unsigned>::RAPIDJSON_EXPAND(RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_ Seq)
#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR_UNSIGNED_DECLARE_(Getter, Setter, Name) \
    Getter##_str = (unsigned*)U##Name;

#ifdef RAPIDJSON_USE_VOLATILE
#define RAPIDJSON_VOLATILE(Member) const_cast<typename std::decay<decltype(value_type::Member)>::type&>(obj.Member)
#else
#define RAPIDJSON_VOLATILE(Member) obj.Member
#endif

//   __  __ _____ __  __ ____  _____ ____    _____ ____      _    ___ _____ ____
//  |  \/  | ____|  \/  | __ )| ____|  _ \  |_   _|  _ \    / \  |_ _|_   _/ ___|
//  | |\/| |  _| | |\/| |  _ \|  _| | |_) |   | | | |_) |  / _ \  | |  | | \___ \ 
//  | |  | | |___| |  | | |_) | |___|  _ <    | | |  _ <  / ___ \ | |  | |  ___) |
//  |_|  |_|_____|_|  |_|____/|_____|_| \_\___|_| |_| \_\/_/   \_\___| |_| |____/
//                                       |_____|

#define RAPIDJSON_ALL_MEMBER_IS(P0, P2, P3, Member, Count) RAPIDJSON_ALL_MEMBER_IS_LAST(P0, P2, P3, Member, Count)
#define RAPIDJSON_ALL_MEMBER_IS_LAST(P0, P2, P3, Member, Count) \
    if (!json.HasMember(macro_names::Member##_str))             \
        return false;

#define RAPIDJSON_N_MEMBER_IS(P0, P2, P3, Member, Count) RAPIDJSON_N_MEMBER_IS_LAST(P0, P2, P3, Member, Count)
#define RAPIDJSON_N_MEMBER_IS_LAST(P0, P2, P3, Member, Count)                                      \
    if ((num_params - Count) < num_mandatory_params && !json.HasMember(macro_names::Member##_str)) \
        return false;

#define RAPIDJSON_ALL_MEMBER_AS(P0, P2, P3, Member, Count) RAPIDJSON_ALL_MEMBER_AS_LAST(P0, P2, P3, Member, Count)
#define RAPIDJSON_ALL_MEMBER_AS_LAST(P0, P2, P3, Member, Count) \
    obj.Member = json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::as(json[macro_names::Member##_str], do_check);

#define RAPIDJSON_N_MEMBER_AS(P0, P2, P3, Member, Count) RAPIDJSON_N_MEMBER_AS_LAST(P0, P2, P3, Member, Count)
#define RAPIDJSON_N_MEMBER_AS_LAST(P0, P2, P3, Member, Count)                                                                                       \
    if ((num_params - Count) < num_mandatory_params || json.HasMember(macro_names::Member##_str))                                                   \
    {                                                                                                                                               \
        obj.Member = json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::as(json[macro_names::Member##_str], do_check); \
    }

#define RAPIDJSON_MEMBER_TO_JSON(P0, P2, P3, Member, Count) RAPIDJSON_MEMBER_TO_JSON_LAST(P0, P2, P3, Member, Count)
#define RAPIDJSON_MEMBER_TO_JSON_LAST(P0, P2, P3, Member, Count) \
    json.AddMember(                                              \
        rapidjson::StringRef(macro_names::Member##_str),         \
        json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::to_json(obj.Member, alloc), alloc);

#define RAPIDJSON_MEMBER_TO_STREAM(P0, P2, P3, Member, Count) RAPIDJSON_MEMBER_TO_STREAM_LAST(P0, P2, P3, Member, Count)
#define RAPIDJSON_MEMBER_TO_STREAM_LAST(P0, P2, P3, Member, Count) \
    stream.String(macro_names::Member##_str);                      \
    json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::to_stream(stream, obj.Member);

#define RAPIDJSON_MEMBER_TRAITS_BASE(IsT, AsT, NumTemplateParams, ValueType, NumMandatoryParams, ...)                      \
    namespace rapidjson_macros                                                                                             \
    {                                                                                                                      \
        RAPIDJSON_GENERATE_NAME_STRUCTS(ValueType, NumTemplateParams, , RAPIDJSON_GENERATE_NAME_STR, __VA_ARGS__)          \
        template <typename Enc RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_MORE_TPL_PARAM, NumTemplateParams)>        \
        struct json_type_traits<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), Enc> \
        {                                                                                                                  \
            using value_type = ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams);       \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                     \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                    \
            constexpr static size_t num_params = RAPIDJSON_NARGS(__VA_ARGS__);                                             \
            constexpr static size_t num_mandatory_params = NumMandatoryParams;                                             \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                              \
            {                                                                                                              \
                if (!json.IsObject() || json.MemberCount() > num_params || json.MemberCount() < num_mandatory_params)      \
                    return false;                                                                                          \
                RAPIDJSON_VARIADIC_REP_N(IsT, , , , __VA_ARGS__)                                                           \
                return true;                                                                                               \
            }                                                                                                              \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                           \
            {                                                                                                              \
                if (do_check && !is(json))                                                                                 \
                    throw std::runtime_error("Not a " #ValueType);                                                         \
                value_type obj;                                                                                            \
                RAPIDJSON_VARIADIC_REP_N(AsT, , , , __VA_ARGS__)                                                           \
                return obj;                                                                                                \
            }                                                                                                              \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())           \
            {                                                                                                              \
                rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);                                                 \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_MEMBER_TO_JSON, , , , __VA_ARGS__)                                      \
                return json;                                                                                               \
            }                                                                                                              \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                     \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)      \
            {                                                                                                              \
                stream.StartObject();                                                                                      \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_MEMBER_TO_STREAM, , , , __VA_ARGS__)                                    \
                stream.EndObject();                                                                                        \
            }                                                                                                              \
        };                                                                                                                 \
    }

#define RAPIDJSON_ALL_MEMBER_TRAITS(ValueType, ...) \
    RAPIDJSON_MEMBER_TRAITS_BASE(RAPIDJSON_ALL_MEMBER_IS, RAPIDJSON_ALL_MEMBER_AS, 0, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_TPL_ALL_MEMBER_TRAITS(NumTemplateParams, ValueType, ...) \
    RAPIDJSON_MEMBER_TRAITS_BASE(RAPIDJSON_ALL_MEMBER_IS, RAPIDJSON_ALL_MEMBER_AS, NumTemplateParams, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_N_MEMBER_TRAITS(ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_MEMBER_TRAITS_BASE(RAPIDJSON_N_MEMBER_IS, RAPIDJSON_N_MEMBER_AS, 0, ValueType, NumMandatoryParams, __VA_ARGS__)

#define RAPIDJSON_TPL_N_MEMBER_TRAITS(NumTemplateParams, ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_MEMBER_TRAITS_BASE(RAPIDJSON_N_MEMBER_IS, RAPIDJSON_N_MEMBER_AS, NumTemplateParams, ValueType, NumMandatoryParams, __VA_ARGS__)

//   __  __ _____ __  __ ____  _____ ____      _   _    _    __  __ _____   _____ ____      _    ___ _____ ____
//  |  \/  | ____|  \/  | __ )| ____|  _ \    | \ | |  / \  |  \/  | ____| |_   _|  _ \    / \  |_ _|_   _/ ___|
//  | |\/| |  _| | |\/| |  _ \|  _| | |_) |   |  \| | / _ \ | |\/| |  _|     | | | |_) |  / _ \  | |  | | \___ \ 
//  | |  | | |___| |  | | |_) | |___|  _ <    | |\  |/ ___ \| |  | | |___    | | |  _ <  / ___ \ | |  | |  ___) |
//  |_|  |_|_____|_|  |_|____/|_____|_| \_\___|_| \_/_/   \_\_|  |_|_____|___|_| |_| \_\/_/   \_\___| |_| |____/
//                                       |_____|                        |_____|

#define RAPIDJSON_ALL_MEMBER_NAME_IS(P1, P2, P3, Seq, Count) RAPIDJSON_ALL_MEMBER_NAME_IS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_ALL_MEMBER_NAME_IS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_ALL_MEMBER_NAME_IS_ Seq)
#define RAPIDJSON_ALL_MEMBER_NAME_IS_(Member, Name) \
    if (!json.HasMember(macro_names::Member##_str)) \
        return false;

#define RAPIDJSON_N_MEMBER_NAME_IS(P1, P2, P3, Seq, Count) RAPIDJSON_N_MEMBER_NAME_IS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_N_MEMBER_NAME_IS_LAST(P1, P2, P3, Seq, Count) if ((num_params - Count) < num_mandatory_params && RAPIDJSON_N_MEMBER_NAME_IS_ Seq
#define RAPIDJSON_N_MEMBER_NAME_IS_(Member, Name) \
    !json.HasMember(macro_names::Member##_str)) \
        return false;

#define RAPIDJSON_ALL_MEMBER_NAME_AS(P1, P2, P3, Seq, Count) RAPIDJSON_ALL_MEMBER_NAME_AS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_ALL_MEMBER_NAME_AS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_ALL_MEMBER_NAME_AS_ Seq
#define RAPIDJSON_ALL_MEMBER_NAME_AS_(Member, Name) \
    obj.Member = json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::as(json[macro_names::Member##_str], do_check);

#define RAPIDJSON_N_MEMBER_NAME_AS(P1, P2, P3, Seq, Count) RAPIDJSON_N_MEMBER_NAME_AS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_N_MEMBER_NAME_AS_LAST(P1, P2, P3, Seq, Count) if ((num_params - Count) < num_mandatory_params || RAPIDJSON_N_MEMBER_NAME_AS_ Seq
#define RAPIDJSON_N_MEMBER_NAME_AS_(Member, Name)                                                                                                   \
    json.HasMember(macro_names::Member##_str))                                                                                                      \
    {                                                                                                                                               \
        obj.Member = json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::as(json[macro_names::Member##_str], do_check); \
    }
// TODO json.HasMember(RAPIDJSON_STR_LITERAL(Name)))
#define RAPIDJSON_MEMBER_NAME_TO_JSON(P1, P2, P3, Seq, Count) RAPIDJSON_MEMBER_NAME_TO_JSON_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_MEMBER_NAME_TO_JSON_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_MEMBER_NAME_TO_JSON_ Seq
#define RAPIDJSON_MEMBER_NAME_TO_JSON_(Member, Name)     \
    json.AddMember(                                      \
        rapidjson::StringRef(macro_names::Member##_str), \
        json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::to_json(obj.Member, alloc), alloc);

#define RAPIDJSON_MEMBER_NAME_TO_STREAM(P1, P2, P3, Seq, Count) RAPIDJSON_MEMBER_NAME_TO_STREAM_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_MEMBER_NAME_TO_STREAM_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_MEMBER_NAME_TO_STREAM_ Seq
#define RAPIDJSON_MEMBER_NAME_TO_STREAM_(Member, Name) \
    stream.String(macro_names::Member##_str);          \
    json_type_traits<typename std::decay<decltype(value_type::Member)>::type, Enc>::to_stream(stream, obj.Member);

#define RAPIDJSON_MEMBER_NAME_TRAITS_BASE(IsT, AsT, NumTemplateParams, ValueType, NumMandatoryParams, ...)                           \
    namespace rapidjson_macros                                                                                                       \
    {                                                                                                                                \
        RAPIDJSON_GENERATE_NAME_STRUCTS(ValueType, NumTemplateParams, , RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR, __VA_ARGS__) \
        template <typename Enc RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_MORE_TPL_PARAM, NumTemplateParams)>                  \
        struct json_type_traits<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), Enc>           \
        {                                                                                                                            \
            using value_type = ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams);                 \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                               \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                              \
            constexpr static size_t num_params = RAPIDJSON_NARGS(__VA_ARGS__);                                                       \
            constexpr static size_t num_mandatory_params = NumMandatoryParams;                                                       \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                                        \
            {                                                                                                                        \
                if (!json.IsObject() || json.MemberCount() > num_params || json.MemberCount() < num_mandatory_params)                \
                    return false;                                                                                                    \
                RAPIDJSON_VARIADIC_REP_N(IsT, , , , __VA_ARGS__)                                                                     \
                return true;                                                                                                         \
            }                                                                                                                        \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                                     \
            {                                                                                                                        \
                if (do_check && !is(json))                                                                                           \
                    throw std::runtime_error("Not a " #ValueType);                                                                   \
                value_type obj;                                                                                                      \
                RAPIDJSON_VARIADIC_REP_N(AsT, , , , __VA_ARGS__)                                                                     \
                return obj;                                                                                                          \
            }                                                                                                                        \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())                     \
            {                                                                                                                        \
                rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);                                                           \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_MEMBER_NAME_TO_JSON, , , , __VA_ARGS__)                                           \
                return json;                                                                                                         \
            }                                                                                                                        \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                               \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)                \
            {                                                                                                                        \
                stream.StartObject();                                                                                                \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_MEMBER_NAME_TO_STREAM, , , , __VA_ARGS__)                                         \
                stream.EndObject();                                                                                                  \
            }                                                                                                                        \
        };                                                                                                                           \
    }

#define RAPIDJSON_ALL_MEMBER_NAME_TRAITS(ValueType, ...) \
    RAPIDJSON_MEMBER_NAME_TRAITS_BASE(RAPIDJSON_ALL_MEMBER_NAME_IS, RAPIDJSON_ALL_MEMBER_NAME_AS, 0, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_TPL_ALL_MEMBER_NAME_TRAITS(NumTemplateParams, ValueType, ...) \
    RAPIDJSON_MEMBER_NAME_TRAITS_BASE(RAPIDJSON_ALL_MEMBER_NAME_IS, RAPIDJSON_ALL_MEMBER_NAME_AS, NumTemplateParams, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_N_MEMBER_NAME_TRAITS(ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_MEMBER_NAME_TRAITS_BASE(RAPIDJSON_N_MEMBER_NAME_IS, RAPIDJSON_N_MEMBER_NAME_AS, 0, ValueType, NumMandatoryParams, __VA_ARGS__)

#define RAPIDJSON_TPL_N_MEMBER_NAME_TRAITS(NumTemplateParams, ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_MEMBER_NAME_TRAITS_BASE(RAPIDJSON_N_MEMBER_NAME_IS, RAPIDJSON_N_MEMBER_NAME_AS, NumTemplateParams, ValueType, NumMandatoryParams, __VA_ARGS__)

//    ____ _____ ___  ____      ____ _____ _____ _____ _____ ____    _____ ____      _    ___ _____ ____
//   / ___|_   _/ _ \|  _ \    / ___| ____|_   _|_   _| ____|  _ \  |_   _|  _ \    / \  |_ _|_   _/ ___|
//  | |     | || | | | |_) |  | |  _|  _|   | |   | | |  _| | |_) |   | | | |_) |  / _ \  | |  | | \___ \ 
//  | |___  | || |_| |  _ <   | |_| | |___  | |   | | | |___|  _ <    | | |  _ <  / ___ \ | |  | |  ___) |
//   \____| |_| \___/|_| \_\___\____|_____| |_|   |_| |_____|_| \_\___|_| |_| \_\/_/   \_\___| |_| |____/
//                        |_____|                                |_____|

#define RAPIDJSON_ALL_CTOR_GETTER_IS(P0, P2, Prefix, Getter, Count) RAPIDJSON_ALL_CTOR_GETTER_IS_LAST(P0, P2, Prefix, Getter, Count)
#define RAPIDJSON_ALL_CTOR_GETTER_IS_LAST(P0, P2, Prefix, Getter, Count) \
    if (!json.HasMember(macro_names::Prefix##Getter##_str))              \
        return false;

#define RAPIDJSON_N_CTOR_GETTER_IS(P0, P2, Prefix, Getter, Count) RAPIDJSON_N_CTOR_GETTER_IS_LAST(P0, P2, Prefix, Getter, Count)
#define RAPIDJSON_N_CTOR_GETTER_IS_LAST(P0, P2, Prefix, Getter, Count)                                     \
    if ((num_params - Count) < num_mandatory_params && !json.HasMember(macro_names::Prefix##Getter##_str)) \
        return false;

#define RAPIDJSON_ALL_CTOR_GETTER_AS(P0, P2, Prefix, Getter, Count) RAPIDJSON_ALL_CTOR_GETTER_AS_LAST(P0, P2, Prefix, Getter, Count) RAPIDJSON_COMMA
#define RAPIDJSON_ALL_CTOR_GETTER_AS_LAST(P0, P2, Prefix, Getter, Count) \
    json_type_traits<typename std::decay<decltype((std::declval<value_type*>())->Prefix##Getter())>::type, Enc>::as(json[macro_names::Prefix##Getter##_str], do_check)

#define RAPIDJSON_N_CTOR_GETTER_AS(P0, P2, Prefix, Getter, Count) RAPIDJSON_N_CTOR_GETTER_AS_LAST(P0, P2, Prefix, Getter, Count) RAPIDJSON_COMMA
#define RAPIDJSON_N_CTOR_GETTER_AS_LAST(P0, P2, Prefix, Getter, Count)                                           \
    ((num_params - Count) < num_mandatory_params || json.HasMember(macro_names::Prefix##Getter##_str))           \
        ? json_type_traits<typename std::decay<decltype((std::declval<value_type*>())->Prefix##Getter())>::type, \
                           Enc>::as(json[macro_names::Prefix##Getter##_str], do_check)                           \
        : typename std::decay<decltype((std::declval<value_type*>())->Prefix##Getter())>::type()

#define RAPIDJSON_CTOR_GETTER_TO_JSON(P0, P2, Prefix, Getter, Count) RAPIDJSON_CTOR_GETTER_TO_JSON_LAST(P0, P2, Prefix, Getter, Count)
#define RAPIDJSON_CTOR_GETTER_TO_JSON_LAST(P0, P2, Prefix, Getter, Count) \
    json.AddMember(                                                       \
        rapidjson::StringRef(macro_names::Prefix##Getter##_str),          \
        json_type_traits<typename std::decay<decltype((std::declval<value_type*>())->Prefix##Getter())>::type, Enc>::to_json(obj.Prefix##Getter(), alloc), alloc);

#define RAPIDJSON_CTOR_GETTER_TO_STREAM(P0, P2, Prefix, Getter, Count) RAPIDJSON_CTOR_GETTER_TO_STREAM_LAST(P0, P2, Prefix, Getter, Count)
#define RAPIDJSON_CTOR_GETTER_TO_STREAM_LAST(P0, P2, Prefix, Getter, Count) \
    stream.String(macro_names::Prefix##Getter##_str);                       \
    json_type_traits<typename std::decay<decltype((std::declval<value_type*>())->Prefix##Getter())>::type, Enc>::to_stream(stream, obj.Prefix##Getter());

#define RAPIDJSON_CTOR_GETTER_TRAITS_BASE(IsT, AsT, NumTemplateParams, ValueType, Prefix, NumMandatoryParams, ...)         \
    namespace rapidjson_macros                                                                                             \
    {                                                                                                                      \
        RAPIDJSON_GENERATE_NAME_STRUCTS(ValueType, NumTemplateParams, Prefix, RAPIDJSON_GENERATE_NAME_STR, __VA_ARGS__)    \
        template <typename Enc RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_MORE_TPL_PARAM, NumTemplateParams)>        \
        struct json_type_traits<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), Enc> \
        {                                                                                                                  \
            using value_type = ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams);       \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                     \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                    \
            constexpr static size_t num_params = RAPIDJSON_NARGS(__VA_ARGS__);                                             \
            constexpr static size_t num_mandatory_params = NumMandatoryParams;                                             \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                              \
            {                                                                                                              \
                if (!json.IsObject() || json.MemberCount() > num_params || json.MemberCount() < num_mandatory_params)      \
                    return false;                                                                                          \
                RAPIDJSON_VARIADIC_REP_N(IsT, , , Prefix, __VA_ARGS__)                                                     \
                return true;                                                                                               \
            }                                                                                                              \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                           \
            {                                                                                                              \
                if (do_check && !is(json))                                                                                 \
                    throw std::runtime_error("Not a " #ValueType);                                                         \
                return value_type(RAPIDJSON_VARIADIC_REP_N(AsT, , , Prefix, __VA_ARGS__));                                 \
            }                                                                                                              \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())           \
            {                                                                                                              \
                rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);                                                 \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_CTOR_GETTER_TO_JSON, , , Prefix, __VA_ARGS__)                           \
                return json;                                                                                               \
            }                                                                                                              \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                     \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)      \
            {                                                                                                              \
                stream.StartObject();                                                                                      \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_CTOR_GETTER_TO_STREAM, , , Prefix, __VA_ARGS__)                         \
                stream.EndObject();                                                                                        \
            }                                                                                                              \
        };                                                                                                                 \
    }

#define RAPIDJSON_ALL_CTOR_GETTER_TRAITS(ValueType, Prefix, ...) \
    RAPIDJSON_CTOR_GETTER_TRAITS_BASE(RAPIDJSON_ALL_CTOR_GETTER_IS, RAPIDJSON_ALL_CTOR_GETTER_AS, 0, ValueType, Prefix, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_TPL_ALL_CTOR_GETTER_TRAITS(NumTemplateParams, ValueType, Prefix, ...) \
    RAPIDJSON_CTOR_GETTER_TRAITS_BASE(RAPIDJSON_ALL_CTOR_GETTER_IS, RAPIDJSON_ALL_CTOR_GETTER_AS, NumTemplateParams, ValueType, Prefix, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_N_CTOR_GETTER_TRAITS(ValueType, Prefix, NumMandatoryParams, ...) \
    RAPIDJSON_CTOR_GETTER_TRAITS_BASE(RAPIDJSON_N_CTOR_GETTER_IS, RAPIDJSON_N_CTOR_GETTER_AS, 0, ValueType, Prefix, NumMandatoryParams, __VA_ARGS__)

#define RAPIDJSON_TPL_N_CTOR_GETTER_TRAITS(NumTemplateParams, ValueType, Prefix, NumMandatoryParams, ...) \
    RAPIDJSON_CTOR_GETTER_TRAITS_BASE(RAPIDJSON_N_CTOR_GETTER_IS, RAPIDJSON_N_CTOR_GETTER_AS, NumTemplateParams, ValueType, Prefix, NumMandatoryParams, __VA_ARGS__)

//    ____ _____ ___  ____      ____ _____ _____ _____ _____ ____      _   _    _    __  __ _____
//   / ___|_   _/ _ \|  _ \    / ___| ____|_   _|_   _| ____|  _ \    | \ | |  / \  |  \/  | ____|
//  | |     | || | | | |_) |  | |  _|  _|   | |   | | |  _| | |_) |   |  \| | / _ \ | |\/| |  _|
//  | |___  | || |_| |  _ <   | |_| | |___  | |   | | | |___|  _ <    | |\  |/ ___ \| |  | | |___
//   \____| |_| \___/|_| \_\___\____|_____| |_|   |_| |_____|_| \_\___|_| \_/_/   \_\_|  |_|_____|
//                        |_____|                                |_____|

#define RAPIDJSON_ALL_CTOR_GETTER_NAME_IS(P1, P2, P3, Seq, Count) RAPIDJSON_ALL_CTOR_GETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_ALL_CTOR_GETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_ALL_CTOR_GETTER_NAME_IS_ Seq)
#define RAPIDJSON_ALL_CTOR_GETTER_NAME_IS_(Getter, Name) \
    if (!json.HasMember(macro_names::Getter##_str))      \
        return false;

#define RAPIDJSON_N_CTOR_GETTER_NAME_IS(P1, P2, P3, Seq, Count) RAPIDJSON_N_CTOR_GETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_N_CTOR_GETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count) if ((num_params-Count) < num_mandatory_params && RAPIDJSON_EXPAND(RAPIDJSON_N_CTOR_GETTER_NAME_IS_ Seq)
#define RAPIDJSON_N_CTOR_GETTER_NAME_IS_(Getter, Name) !json.HasMember(macro_names::Getter##_str)) return false;

#define RAPIDJSON_ALL_CTOR_GETTER_NAME_AS(P1, P2, P3, Seq, Count) RAPIDJSON_ALL_CTOR_GETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_COMMA
#define RAPIDJSON_ALL_CTOR_GETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_ALL_CTOR_GETTER_NAME_AS_ Seq)
#define RAPIDJSON_ALL_CTOR_GETTER_NAME_AS_(Getter, Name) \
    json_type_traits<typename std::decay<decltype((std::declval<value_type*>())->Getter())>::type, Enc>::as(json[macro_names::Getter##_str], do_check)

#define RAPIDJSON_N_CTOR_GETTER_NAME_AS(P1, P2, P3, Seq, Count) RAPIDJSON_N_CTOR_GETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_COMMA
#define RAPIDJSON_N_CTOR_GETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count) ((num_params-Count) < num_mandatory_params || RAPIDJSON_EXPAND(RAPIDJSON_N_CTOR_GETTER_NAME_AS_ Seq)
#define RAPIDJSON_N_CTOR_GETTER_NAME_AS_(Getter, Name)                                                                                                       \
    json.HasMember(macro_names::Getter##_str))                                                                                                \
        ? json_type_traits<typename std::decay<decltype((std::declval<value_type *>())->Getter())>::type, Enc>::as(json[macro_names::Getter##_str],do_check) \
        : typename std::decay<decltype((std::declval<value_type *>())->Getter())>::type()

#define RAPIDJSON_CTOR_GETTER_NAME_TO_JSON(P1, P2, P3, Seq, Count) RAPIDJSON_CTOR_GETTER_NAME_TO_JSON_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_CTOR_GETTER_NAME_TO_JSON_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_CTOR_GETTER_NAME_TO_JSON_ Seq)
#define RAPIDJSON_CTOR_GETTER_NAME_TO_JSON_(Getter, Name) \
    json.AddMember(                                       \
        rapidjson::StringRef(macro_names::Getter##_str),  \
        json_type_traits<typename std::decay<decltype((std::declval<value_type*>())->Getter())>::type, Enc>::to_json(obj.Getter(), alloc), alloc);

#define RAPIDJSON_CTOR_GETTER_NAME_TO_STREAM(P1, P2, P3, Seq, Count) RAPIDJSON_CTOR_GETTER_NAME_TO_STREAM_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_CTOR_GETTER_NAME_TO_STREAM_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_CTOR_GETTER_NAME_TO_STREAM_ Seq)
#define RAPIDJSON_CTOR_GETTER_NAME_TO_STREAM_(Getter, Name) \
    stream.String(macro_names::Getter##_str);               \
    json_type_traits<typename std::decay<decltype((std::declval<value_type*>())->Getter())>::type, Enc>::to_stream(stream, obj.Getter());

#define RAPIDJSON_CTOR_GETTER_NAME_TRAITS_BASE(IsT, AsT, NumTemplateParams, ValueType, NumMandatoryParams, ...)                      \
    namespace rapidjson_macros                                                                                                       \
    {                                                                                                                                \
        RAPIDJSON_GENERATE_NAME_STRUCTS(ValueType, NumTemplateParams, , RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR, __VA_ARGS__) \
        template <typename Enc RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_MORE_TPL_PARAM, NumTemplateParams)>                  \
        struct json_type_traits<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), Enc>           \
        {                                                                                                                            \
            using value_type = ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams);                 \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                               \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                              \
            constexpr static size_t num_params = RAPIDJSON_NARGS(__VA_ARGS__);                                                       \
            constexpr static size_t num_mandatory_params = NumMandatoryParams;                                                       \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                                        \
            {                                                                                                                        \
                if (!json.IsObject() || json.MemberCount() > num_params || json.MemberCount() < num_mandatory_params)                \
                    return false;                                                                                                    \
                RAPIDJSON_VARIADIC_REP_N(IsT, , , , __VA_ARGS__)                                                                     \
                return true;                                                                                                         \
            }                                                                                                                        \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                                     \
            {                                                                                                                        \
                if (do_check && !is(json))                                                                                           \
                    throw std::runtime_error("Not a " #ValueType);                                                                   \
                return value_type(RAPIDJSON_VARIADIC_REP_N(AsT, , , , __VA_ARGS__));                                                 \
            }                                                                                                                        \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())                     \
            {                                                                                                                        \
                rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);                                                           \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_CTOR_GETTER_NAME_TO_JSON, , , , __VA_ARGS__)                                      \
                return json;                                                                                                         \
            }                                                                                                                        \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                               \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)                \
            {                                                                                                                        \
                stream.StartObject();                                                                                                \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_CTOR_GETTER_NAME_TO_STREAM, , , , __VA_ARGS__)                                    \
                stream.EndObject();                                                                                                  \
            }                                                                                                                        \
        };                                                                                                                           \
    }

#define RAPIDJSON_ALL_CTOR_GETTER_NAME_TRAITS(ValueType, ...) \
    RAPIDJSON_CTOR_GETTER_NAME_TRAITS_BASE(RAPIDJSON_ALL_CTOR_GETTER_NAME_IS, RAPIDJSON_ALL_CTOR_GETTER_NAME_AS, 0, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_TPL_ALL_CTOR_GETTER_NAME_TRAITS(NumTemplateParams, ValueType, ...) \
    RAPIDJSON_CTOR_GETTER_NAME_TRAITS_BASE(RAPIDJSON_ALL_CTOR_GETTER_NAME_IS, RAPIDJSON_ALL_CTOR_GETTER_NAME_AS, NumTemplateParams, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_N_CTOR_GETTER_NAME_TRAITS(ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_CTOR_GETTER_NAME_TRAITS_BASE(RAPIDJSON_N_CTOR_GETTER_NAME_IS, RAPIDJSON_N_CTOR_GETTER_NAME_AS, 0, ValueType, NumMandatoryParams, __VA_ARGS__)

#define RAPIDJSON_TPL_N_CTOR_GETTER_NAME_TRAITS(NumTemplateParams, ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_CTOR_GETTER_NAME_TRAITS_BASE(RAPIDJSON_N_CTOR_GETTER_NAME_IS, RAPIDJSON_N_CTOR_GETTER_NAME_AS, NumTemplateParams, ValueType, NumMandatoryParams, __VA_ARGS__)

//    ____ _____ _____ _____ _____ ____      ____  _____ _____ _____ _____ ____    _____ ____      _    ___ _____ ____
//   / ___| ____|_   _|_   _| ____|  _ \    / ___|| ____|_   _|_   _| ____|  _ \  |_   _|  _ \    / \  |_ _|_   _/ ___|
//  | |  _|  _|   | |   | | |  _| | |_) |   \___ \|  _|   | |   | | |  _| | |_) |   | | | |_) |  / _ \  | |  | | \___ \ 
//  | |_| | |___  | |   | | | |___|  _ <     ___) | |___  | |   | | | |___|  _ <    | | |  _ <  / ___ \ | |  | |  ___) |
//   \____|_____| |_|   |_| |_____|_| \_\___|____/|_____| |_|   |_| |_____|_| \_\___|_| |_| \_\/_/   \_\___| |_| |____/
//                                     |_____|                                 |_____|

#define RAPIDJSON_ALL_GETTER_SETTER_AS(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_ALL_GETTER_SETTER_AS_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_ALL_GETTER_SETTER_AS_LAST(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_ALL_GETTER_SETTER_AS_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_ALL_GETTER_SETTER_AS_(P0, Getter, Setter, Property, Count) \
    obj.Setter(json_type_traits<typename std::decay<decltype(obj.Getter())>::type, Enc>::as(json[macro_names::Property##_str], do_check));

#define RAPIDJSON_N_GETTER_SETTER_AS(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_N_GETTER_SETTER_AS_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_N_GETTER_SETTER_AS_LAST(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_N_GETTER_SETTER_AS_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_N_GETTER_SETTER_AS_(P0, Getter, Setter, Property, Count)                          \
    if ((num_params - Count) < num_mandatory_params || json.HasMember(macro_names::Property##_str)) \
    {                                                                                               \
        RAPIDJSON_ALL_GETTER_SETTER_AS_(P0, Getter, Setter, Property, Count)                        \
    }

#define RAPIDJSON_GETTER_SETTER_TO_JSON(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_GETTER_SETTER_TO_JSON_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_GETTER_SETTER_TO_JSON_LAST(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_GETTER_SETTER_TO_JSON_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_GETTER_SETTER_TO_JSON_(P0, Getter, Setter, Property, Count) \
    json.AddMember(                                                           \
        rapidjson::StringRef(macro_names::Property##_str),                    \
        json_type_traits<typename std::decay<decltype(obj.Getter())>::type, Enc>::to_json(obj.Getter(), alloc), alloc);

#define RAPIDJSON_GETTER_SETTER_TO_STREAM(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_GETTER_SETTER_TO_STREAM_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_GETTER_SETTER_TO_STREAM_LAST(P0, GetPrefix, SetPrefix, Property, Count) RAPIDJSON_GETTER_SETTER_TO_STREAM_(P0, GetPrefix##Property, SetPrefix##Property, Property, Count)
#define RAPIDJSON_GETTER_SETTER_TO_STREAM_(P0, Getter, Setter, Property, Count) \
    stream.String(macro_names::Property##_str);                                 \
    json_type_traits<typename std::decay<decltype(obj.Getter())>::type, Enc>::to_stream(stream, obj.Getter());

#define RAPIDJSON_GETTER_SETTER_TRAITS_BASE(IsT, AsT, NumTemplateParams, ValueType, GetPrefix, SetPrefix, NumMandatoryParams, ...) \
    namespace rapidjson_macros                                                                                                     \
    {                                                                                                                              \
        RAPIDJSON_GENERATE_NAME_STRUCTS(ValueType, NumTemplateParams, , RAPIDJSON_GENERATE_NAME_STR, __VA_ARGS__)                  \
        template <typename Enc RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_MORE_TPL_PARAM, NumTemplateParams)>                \
        struct json_type_traits<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), Enc>         \
        {                                                                                                                          \
            using value_type = ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams);               \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                             \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                            \
            constexpr static size_t num_params = RAPIDJSON_NARGS(__VA_ARGS__);                                                     \
            constexpr static size_t num_mandatory_params = NumMandatoryParams;                                                     \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                                      \
            {                                                                                                                      \
                if (!json.IsObject() || json.MemberCount() > num_params || json.MemberCount() < num_mandatory_params)              \
                    return false;                                                                                                  \
                RAPIDJSON_VARIADIC_REP_N(IsT, Enc, GetPrefix, SetPrefix, __VA_ARGS__)                                              \
                return true;                                                                                                       \
            }                                                                                                                      \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                                   \
            {                                                                                                                      \
                if (do_check && !is(json))                                                                                         \
                    throw std::runtime_error("Not a " #ValueType);                                                                 \
                value_type obj;                                                                                                    \
                RAPIDJSON_VARIADIC_REP_N(AsT, Enc, GetPrefix, SetPrefix, __VA_ARGS__)                                              \
                return obj;                                                                                                        \
            }                                                                                                                      \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())                   \
            {                                                                                                                      \
                rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);                                                         \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_GETTER_SETTER_TO_JSON, Enc, GetPrefix, SetPrefix, __VA_ARGS__)                  \
                return json;                                                                                                       \
            }                                                                                                                      \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                             \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)              \
            {                                                                                                                      \
                stream.StartObject();                                                                                              \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_GETTER_SETTER_TO_STREAM, Enc, GetPrefix, SetPrefix, __VA_ARGS__)                \
                stream.EndObject();                                                                                                \
            }                                                                                                                      \
        };                                                                                                                         \
    }

#define RAPIDJSON_ALL_GETTER_SETTER_TRAITS(ValueType, GetPrefix, SetPrefix, ...) \
    RAPIDJSON_GETTER_SETTER_TRAITS_BASE(RAPIDJSON_ALL_MEMBER_IS, RAPIDJSON_ALL_GETTER_SETTER_AS, 0, ValueType, GetPrefix, SetPrefix, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_TPL_ALL_GETTER_SETTER_TRAITS(NumTemplateParams, ValueType, GetPrefix, SetPrefix, ...) \
    RAPIDJSON_GETTER_SETTER_TRAITS_BASE(RAPIDJSON_ALL_MEMBER_IS, RAPIDJSON_ALL_GETTER_SETTER_AS, NumTemplateParams, ValueType, GetPrefix, SetPrefix, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_N_GETTER_SETTER_TRAITS(ValueType, GetPrefix, SetPrefix, NumMandatoryParams, ...) \
    RAPIDJSON_GETTER_SETTER_TRAITS_BASE(RAPIDJSON_N_MEMBER_IS, RAPIDJSON_N_GETTER_SETTER_AS, 0, ValueType, GetPrefix, SetPrefix, NumMandatoryParams, __VA_ARGS__)

#define RAPIDJSON_TPL_N_GETTER_SETTER_TRAITS(NumTemplateParams, ValueType, GetPrefix, SetPrefix, NumMandatoryParams, ...) \
    RAPIDJSON_GETTER_SETTER_TRAITS_BASE(RAPIDJSON_N_MEMBER_IS, RAPIDJSON_N_GETTER_SETTER_AS, NumTemplateParams, ValueType, GetPrefix, SetPrefix, NumMandatoryParams, __VA_ARGS__)

//    ____ _____ _____ _____ _____ ____      ____  _____ _____ _____ _____ ____      _   _    _    __  __ _____   _____ ____      _    ___ _____ ____
//   / ___| ____|_   _|_   _| ____|  _ \    / ___|| ____|_   _|_   _| ____|  _ \    | \ | |  / \  |  \/  | ____| |_   _|  _ \    / \  |_ _|_   _/ ___|
//  | |  _|  _|   | |   | | |  _| | |_) |   \___ \|  _|   | |   | | |  _| | |_) |   |  \| | / _ \ | |\/| |  _|     | | | |_) |  / _ \  | |  | | \___ \ 
//  | |_| | |___  | |   | | | |___|  _ <     ___) | |___  | |   | | | |___|  _ <    | |\  |/ ___ \| |  | | |___    | | |  _ <  / ___ \ | |  | |  ___) |
//   \____|_____| |_|   |_| |_____|_| \_\___|____/|_____| |_|   |_| |_____|_| \_\___|_| \_/_/   \_\_|  |_|_____|___|_| |_| \_\/_/   \_\___| |_| |____/
//                                     |_____|                                 |_____|                        |_____|

#define RAPIDJSON_ALL_GETTER_SETTER_NAME_IS(P1, P2, P3, Seq, Count) RAPIDJSON_ALL_GETTER_SETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_ALL_GETTER_SETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_ALL_GETTER_SETTER_NAME_IS_ Seq)
#define RAPIDJSON_ALL_GETTER_SETTER_NAME_IS_(Getter, Setter, Name) \
    if (!json.HasMember(macro_names::Getter##_str))                \
        return false;

#define RAPIDJSON_N_GETTER_SETTER_NAME_IS(P1, P2, P3, Seq, Count) RAPIDJSON_N_GETTER_SETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_N_GETTER_SETTER_NAME_IS_LAST(P1, P2, P3, Seq, Count) if ((num_params-Count) < num_mandatory_params && RAPIDJSON_EXPAND(RAPIDJSON_N_GETTER_SETTER_NAME_IS_ Seq)
#define RAPIDJSON_N_GETTER_SETTER_NAME_IS_(Getter, Setter, Name) !json.HasMember(macro_names::Getter##_str)) return false;

#define RAPIDJSON_ALL_GETTER_SETTER_NAME_AS(P1, P2, P3, Seq, Count) RAPIDJSON_ALL_GETTER_SETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_ALL_GETTER_SETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_ALL_GETTER_SETTER_NAME_AS_ Seq)
#define RAPIDJSON_ALL_GETTER_SETTER_NAME_AS_(Getter, Setter, Name) \
    obj.Setter(json_type_traits<typename std::decay<decltype(obj.Getter())>::type, Enc>::as(json[macro_names::Getter##_str], do_check));

#define RAPIDJSON_N_GETTER_SETTER_NAME_AS(P1, P2, P3, Seq, Count) RAPIDJSON_N_GETTER_SETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_N_GETTER_SETTER_NAME_AS_LAST(P1, P2, P3, Seq, Count) if ((num_params-Count) < num_mandatory_params || RAPIDJSON_EXPAND(RAPIDJSON_N_GETTER_SETTER_NAME_AS_ Seq)
#define RAPIDJSON_N_GETTER_SETTER_NAME_AS_(Getter, Setter, Name) json.HasMember(macro_names::Getter##_str)) \
    obj.Setter(json_type_traits<typename std::decay<decltype(obj.Getter())>::type, Enc>::as(json[macro_names::Getter##_str], do_check));

#define RAPIDJSON_GETTER_SETTER_NAME_TO_JSON(P1, P2, P3, Seq, Count) RAPIDJSON_GETTER_SETTER_NAME_TO_JSON_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_GETTER_SETTER_NAME_TO_JSON_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_GETTER_SETTER_NAME_TO_JSON_ Seq)
#define RAPIDJSON_GETTER_SETTER_NAME_TO_JSON_(Getter, Setter, Name) \
    json.AddMember(                                                 \
        rapidjson::StringRef(macro_names::Getter##_str),            \
        json_type_traits<typename std::decay<decltype(obj.Getter())>::type, Enc>::to_json(obj.Getter(), alloc), alloc);

#define RAPIDJSON_GETTER_SETTER_NAME_TO_STREAM(P1, P2, P3, Seq, Count) RAPIDJSON_GETTER_SETTER_NAME_TO_STREAM_LAST(P1, P2, P3, Seq, Count)
#define RAPIDJSON_GETTER_SETTER_NAME_TO_STREAM_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_GETTER_SETTER_NAME_TO_STREAM_ Seq)
#define RAPIDJSON_GETTER_SETTER_NAME_TO_STREAM_(Getter, Setter, Name) \
    stream.String(macro_names::Getter##_str);                         \
    json_type_traits<typename std::decay<decltype(obj.Getter())>::type, Enc>::to_stream(stream, obj.Getter());

#define RAPIDJSON_GETTER_SETTER_NAME_TRAITS_BASE(IsT, AsT, NumTemplateParams, ValueType, NumMandatoryParams, ...)                           \
    namespace rapidjson_macros                                                                                                              \
    {                                                                                                                                       \
        RAPIDJSON_GENERATE_NAME_STRUCTS(ValueType, NumTemplateParams, , RAPIDJSON_GETTER_SETTER_NAME_TRAITS_GENERATE_NAME_STR, __VA_ARGS__) \
        template <typename Enc RAPIDJSON_GENERATE_TPL_PARAMS(RAPIDJSON_GENERATE_MORE_TPL_PARAM, NumTemplateParams)>                         \
        struct json_type_traits<ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams), Enc>                  \
        {                                                                                                                                   \
            using value_type = ValueType RAPIDJSON_GENERATE_TPL_ARGS(RAPIDJSON_GENERATE_TPL_ARG, NumTemplateParams);                        \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                                      \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                                                     \
            constexpr static size_t num_params = RAPIDJSON_NARGS(__VA_ARGS__);                                                              \
            constexpr static size_t num_mandatory_params = NumMandatoryParams;                                                              \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                                               \
            {                                                                                                                               \
                if (!json.IsObject() || json.MemberCount() > num_params || json.MemberCount() < num_mandatory_params)                       \
                    return false;                                                                                                           \
                RAPIDJSON_VARIADIC_REP_N(IsT, , , , __VA_ARGS__)                                                                            \
                return true;                                                                                                                \
            }                                                                                                                               \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                                            \
            {                                                                                                                               \
                if (do_check && !is(json))                                                                                                  \
                    throw std::runtime_error("Not a " #ValueType);                                                                          \
                value_type obj;                                                                                                             \
                RAPIDJSON_VARIADIC_REP_N(AsT, , , , __VA_ARGS__)                                                                            \
                return obj;                                                                                                                 \
            }                                                                                                                               \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())                            \
            {                                                                                                                               \
                rapidjson::GenericValue<Enc> json(rapidjson::kObjectType);                                                                  \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_GETTER_SETTER_NAME_TO_JSON, , , , __VA_ARGS__)                                           \
                return json;                                                                                                                \
            }                                                                                                                               \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                                      \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj)                       \
            {                                                                                                                               \
                stream.StartObject();                                                                                                       \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_GETTER_SETTER_NAME_TO_STREAM, , , , __VA_ARGS__)                                         \
                stream.EndObject();                                                                                                         \
            }                                                                                                                               \
        };                                                                                                                                  \
    }

#define RAPIDJSON_ALL_GETTER_SETTER_NAME_TRAITS(ValueType, ...) \
    RAPIDJSON_GETTER_SETTER_NAME_TRAITS_BASE(RAPIDJSON_ALL_GETTER_SETTER_NAME_IS, RAPIDJSON_ALL_GETTER_SETTER_NAME_AS, 0, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_TPL_ALL_GETTER_SETTER_NAME_TRAITS(NumTemplateParams, ValueType, ...) \
    RAPIDJSON_GETTER_SETTER_NAME_TRAITS_BASE(RAPIDJSON_ALL_GETTER_SETTER_NAME_IS, RAPIDJSON_ALL_GETTER_SETTER_NAME_AS, NumTemplateParams, ValueType, RAPIDJSON_NARGS(__VA_ARGS__), __VA_ARGS__)

#define RAPIDJSON_N_GETTER_SETTER_NAME_TRAITS(ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_GETTER_SETTER_NAME_TRAITS_BASE(RAPIDJSON_N_GETTER_SETTER_NAME_IS, RAPIDJSON_N_GETTER_SETTER_NAME_AS, 0, ValueType, NumMandatoryParams, __VA_ARGS__)

#define RAPIDJSON_TPL_N_GETTER_SETTER_NAME_TRAITS(NumTemplateParams, ValueType, NumMandatoryParams, ...) \
    RAPIDJSON_GETTER_SETTER_NAME_TRAITS_BASE(RAPIDJSON_N_GETTER_SETTER_NAME_IS, RAPIDJSON_N_GETTER_SETTER_NAME_AS, NumTemplateParams, ValueType, NumMandatoryParams, __VA_ARGS__)

//   _____ _   _ _   _ __  __   _____ ____      _    ___ _____ ____
//  | ____| \ | | | | |  \/  | |_   _|  _ \    / \  |_ _|_   _/ ___|
//  |  _| |  \| | | | | |\/| |   | | | |_) |  / _ \  | |  | | \___ \ 
//  | |___| |\  | |_| | |  | |   | | |  _ <  / ___ \ | |  | |  ___) |
//  |_____|_| \_|\___/|_|  |_|___|_| |_| \_\/_/   \_\___| |_| |____/
//                          |_____|

#define RAPIDJSON_ENUM_PAIR(P1, P2, P3, Member, Count) RAPIDJSON_ENUM_PAIR_LAST(P1, P2, P3, Member, Count),
#define RAPIDJSON_ENUM_PAIR_LAST(P1, P2, P0, Member, Count) \
    {                                                       \
        macro_names::Member##_str, value_type::Member       \
    }

#define RAPIDJSON_ENUM_TRAITS(EnumType, ...)                                                                          \
    namespace rapidjson_macros                                                                                        \
    {                                                                                                                 \
        RAPIDJSON_GENERATE_NAME_STRUCTS(EnumType, 0, , RAPIDJSON_GENERATE_NAME_STR, __VA_ARGS__)                      \
        template <typename Enc>                                                                                       \
        struct json_type_traits<EnumType, Enc>                                                                        \
        {                                                                                                             \
            static_assert(std::is_enum<EnumType>::value, #EnumType " must be an enum");                               \
            using value_type = EnumType;                                                                              \
            using mapped_type = std::map<const typename Enc::Ch*, EnumType, CharArrayCompare<typename Enc::Ch>>;      \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                               \
                                                                                                                      \
            static const mapped_type& get_values()                                                                    \
            {                                                                                                         \
                static const mapped_type v = {                                                                        \
                    RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_ENUM_PAIR, , , Enc, __VA_ARGS__)};                             \
                return v;                                                                                             \
            }                                                                                                         \
                                                                                                                      \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                         \
            {                                                                                                         \
                if (!json.IsString())                                                                                 \
                    return false;                                                                                     \
                return get_values().find(json.GetString()) != get_values().end();                                     \
            }                                                                                                         \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                      \
            {                                                                                                         \
                if (do_check && !is(json))                                                                            \
                    throw std::runtime_error("Not a " #EnumType);                                                     \
                return get_values().at(json.GetString());                                                             \
            }                                                                                                         \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())      \
            {                                                                                                         \
                for (auto it = get_values().begin(); it != get_values().end(); ++it)                                  \
                {                                                                                                     \
                    if (it->second == obj)                                                                            \
                        return rapidjson::GenericValue<Enc>(it->first, alloc);                                        \
                }                                                                                                     \
                throw std::runtime_error("Not a " #EnumType);                                                         \
            }                                                                                                         \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj) \
            {                                                                                                         \
                for (auto it = get_values().begin(); it != get_values().end(); ++it)                                  \
                {                                                                                                     \
                    if (it->second == obj)                                                                            \
                    {                                                                                                 \
                        stream.String(it->first);                                                                     \
                        return;                                                                                       \
                    }                                                                                                 \
                }                                                                                                     \
                throw std::runtime_error("Not a " #EnumType);                                                         \
            }                                                                                                         \
        };                                                                                                            \
    }

//   _____ _   _ _   _ __  __     _   _    _    __  __ _____   _____ ____      _    ___ _____ ____
//  | ____| \ | | | | |  \/  |   | \ | |  / \  |  \/  | ____| |_   _|  _ \    / \  |_ _|_   _/ ___|
//  |  _| |  \| | | | | |\/| |   |  \| | / _ \ | |\/| |  _|     | | | |_) |  / _ \  | |  | | \___ \ 
//  | |___| |\  | |_| | |  | |   | |\  |/ ___ \| |  | | |___    | | |  _ <  / ___ \ | |  | |  ___) |
//  |_____|_| \_|\___/|_|  |_|___|_| \_/_/   \_\_|  |_|_____|___|_| |_| \_\/_/   \_\___| |_| |____/
//                          |_____|                        |_____|

#define RAPIDJSON_NAME_ENUM_PAIR(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_NAME_ENUM_PAIR_ Seq),
#define RAPIDJSON_NAME_ENUM_PAIR_LAST(P1, P2, P3, Seq, Count) RAPIDJSON_EXPAND(RAPIDJSON_NAME_ENUM_PAIR_ Seq)
#define RAPIDJSON_NAME_ENUM_PAIR_(Member, Name)       \
    {                                                 \
        macro_names::Member##_str, value_type::Member \
    }

#define RAPIDJSON_ENUM_NAME_TRAITS(EnumType, ...)                                                                     \
    namespace rapidjson_macros                                                                                        \
    {                                                                                                                 \
        RAPIDJSON_GENERATE_NAME_STRUCTS(EnumType, 0, , RAPIDJSON_GETTER_NAME_TRAITS_GENERATE_NAME_STR, __VA_ARGS__)   \
        template <typename Enc>                                                                                       \
        struct json_type_traits<EnumType, Enc>                                                                        \
        {                                                                                                             \
            static_assert(std::is_enum<EnumType>::value, #EnumType " must be an enum");                               \
            using value_type = EnumType;                                                                              \
            using mapped_type = std::map<const typename Enc::Ch*, EnumType, CharArrayCompare<typename Enc::Ch>>;      \
            using macro_names = json_traits_macro_names<value_type, typename Enc::Ch>;                                \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                               \
                                                                                                                      \
            static const mapped_type& get_values()                                                                    \
            {                                                                                                         \
                static const mapped_type v = {                                                                        \
                    RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_NAME_ENUM_PAIR, , , Enc, __VA_ARGS__)};                        \
                return v;                                                                                             \
            }                                                                                                         \
                                                                                                                      \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                         \
            {                                                                                                         \
                if (!json.IsString())                                                                                 \
                    return false;                                                                                     \
                return get_values().find(json.GetString()) != get_values().end();                                     \
            }                                                                                                         \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                      \
            {                                                                                                         \
                if (do_check)                                                                                         \
                {                                                                                                     \
                    if (!is(json))                                                                                    \
                        throw std::runtime_error("Not a " #EnumType);                                                 \
                    return get_values().at(json.GetString());                                                         \
                }                                                                                                     \
                else                                                                                                  \
                {                                                                                                     \
                    auto it = get_values().find(json.GetString());                                                    \
                    if (it == get_values().end())                                                                     \
                        throw std::runtime_error("Not a " #EnumType);                                                 \
                    return it->second;                                                                                \
                }                                                                                                     \
            }                                                                                                         \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())      \
            {                                                                                                         \
                for (auto it = get_values().begin(); it != get_values().end(); ++it)                                  \
                {                                                                                                     \
                    if (it->second == obj)                                                                            \
                        return rapidjson::GenericValue<Enc>(it->first, alloc);                                        \
                }                                                                                                     \
                throw std::runtime_error("Not a " #EnumType);                                                         \
            }                                                                                                         \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& obj) \
            {                                                                                                         \
                for (auto it = get_values().begin(); it != get_values().end(); ++it)                                  \
                {                                                                                                     \
                    if (it->second == obj)                                                                            \
                    {                                                                                                 \
                        stream.String(it->first);                                                                     \
                        return;                                                                                       \
                    }                                                                                                 \
                }                                                                                                     \
                throw std::runtime_error("Not a " #EnumType);                                                         \
            }                                                                                                         \
        };                                                                                                            \
    }

#define RAPIDJSON_POLYMORPHIC_IS(P1, P2, P3, DerivedClass, Count) RAPIDJSON_POLYMORPHIC_IS_LAST(P1, P2, P3, DerivedClass, Count)
#define RAPIDJSON_POLYMORPHIC_IS_LAST(P1, P2, P3, DerivedClass, Count) \
    if (json_type_traits<DerivedClass, Enc>::is(json))                 \
        return true;

#define RAPIDJSON_POLYMORPHIC_AS(P1, P2, P3, DerivedClass, Count) RAPIDJSON_POLYMORPHIC_AS_LAST(P1, P2, P3, DerivedClass, Count)
#define RAPIDJSON_POLYMORPHIC_AS_LAST(P1, P2, P3, DerivedClass, Count) \
    if (json_type_traits<DerivedClass, Enc>::is(json))                 \
        return std::make_shared<DerivedClass>(json_type_traits<DerivedClass, Enc>::as(json, do_check));

#define RAPIDJSON_POLYMORPHIC_AS_UNIQUE_PTR(P1, P2, P3, DerivedClass, Count) RAPIDJSON_POLYMORPHIC_AS_UNIQUE_PTR_LAST(P1, P2, P3, DerivedClass, Count)
#define RAPIDJSON_POLYMORPHIC_AS_UNIQUE_PTR_LAST(P1, P2, P3, DerivedClass, Count) \
    if (json_type_traits<DerivedClass, Enc>::is(json))                            \
        return std::make_unique<DerivedClass>(json_type_traits<DerivedClass, Enc>::as(json, do_check));

#define RAPIDJSON_POLYMORPHIC_AS_SHARED_PTR(P1, P2, P3, DerivedClass, Count) RAPIDJSON_POLYMORPHIC_AS_SHARED_PTR_LAST(P1, P2, P3, DerivedClass, Count)
#define RAPIDJSON_POLYMORPHIC_AS_SHARED_PTR_LAST(P1, P2, P3, DerivedClass, Count) \
    if (json_type_traits<DerivedClass, Enc>::is(json))                            \
        return std::make_shared<DerivedClass>(json_type_traits<DerivedClass, Enc>::as(json, do_check));

#define RAPIDJSON_POLYMORPHIC_TO_JSON(P1, P2, P3, DerivedClass, Count) RAPIDJSON_POLYMORPHIC_TO_JSON_LAST(P1, P2, P3, DerivedClass, Count)
#define RAPIDJSON_POLYMORPHIC_TO_JSON_LAST(P1, P2, P3, DerivedClass, Count) \
    if (DerivedClass* p = dynamic_cast<DerivedClass*>(ptr.get()))           \
        return json_type_traits<DerivedClass, Enc>::to_json(*p, alloc);

#define RAPIDJSON_POLYMORPHIC_TO_STREAM(P1, P2, P3, DerivedClass, Count) RAPIDJSON_POLYMORPHIC_TO_STREAM_LAST(P1, P2, P3, DerivedClass, Count)
#define RAPIDJSON_POLYMORPHIC_TO_STREAM_LAST(P1, P2, P3, DerivedClass, Count) \
    if (DerivedClass* p = dynamic_cast<DerivedClass*>(ptr.get()))             \
        json_type_traits<DerivedClass, Enc>::to_stream(stream, *p);

#define RAPIDJSON_POLYMORPHIC_TRAITS(BaseClass, ...)                                                                  \
    namespace rapidjson_macros                                                                                        \
    {                                                                                                                 \
        template <typename Enc>                                                                                       \
        struct json_type_traits<std::shared_ptr<BaseClass>, Enc>                                                      \
        {                                                                                                             \
            using value_type = std::shared_ptr<BaseClass>;                                                            \
            using alloc_type = typename rapidjson::GenericDocument<Enc>::AllocatorType;                               \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                         \
            {                                                                                                         \
                if (!json.IsObject())                                                                                 \
                    return false;                                                                                     \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_IS, , , , __VA_ARGS__)                                 \
                return false;                                                                                         \
            }                                                                                                         \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                      \
            {                                                                                                         \
                if (!json.IsObject())                                                                                 \
                    return value_type();                                                                              \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_AS_SHARED_PTR, , , , __VA_ARGS__)                      \
                return value_type();                                                                                  \
            }                                                                                                         \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())      \
            {                                                                                                         \
                if (ptr.get() == nullptr)                                                                             \
                    return {};                                                                                        \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_TO_JSON, , , , __VA_ARGS__)                            \
            }                                                                                                         \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& ptr) \
            {                                                                                                         \
                if (ptr.get() == nullptr)                                                                             \
                    stream.Null();                                                                                    \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_TO_STREAM, , , , __VA_ARGS__)                          \
            }                                                                                                         \
        };                                                                                                            \
        template <typename Enc>                                                                                       \
        struct json_type_traits<std::unique_ptr<BaseClass>, Enc>                                                      \
        {                                                                                                             \
            using value_type = std::unique_ptr<BaseClass>;                                                            \
            static bool is(const rapidjson::GenericValue<Enc>& json) noexcept                                         \
            {                                                                                                         \
                if (!json.IsObject())                                                                                 \
                    return false;                                                                                     \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_IS, , , , __VA_ARGS__)                                 \
                return false;                                                                                         \
            }                                                                                                         \
            static value_type as(const rapidjson::GenericValue<Enc>& json, const bool& do_check)                      \
            {                                                                                                         \
                if (!json.IsObject())                                                                                 \
                    return value_type();                                                                              \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_AS_UNIQUE_PTR, , , , __VA_ARGS__)                      \
                return value_type();                                                                                  \
            }                                                                                                         \
            static rapidjson::GenericValue<Enc> to_json(const value_type& obj, alloc_type& alloc = alloc_type())      \
            {                                                                                                         \
                if (ptr.get() == nullptr)                                                                             \
                    return {};                                                                                        \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_TO_JSON, , , , __VA_ARGS__)                            \
            }                                                                                                         \
            template <typename OStr, typename TgtEnc, typename SAlloc, unsigned Flags>                                \
            static void to_stream(rapidjson::Writer<OStr, Enc, TgtEnc, SAlloc, Flags>& stream, const value_type& ptr) \
            {                                                                                                         \
                if (ptr.get() == nullptr)                                                                             \
                    stream.Null();                                                                                    \
                RAPIDJSON_VARIADIC_REP_N(RAPIDJSON_POLYMORPHIC_TO_STREAM, , , , __VA_ARGS__)                          \
            }                                                                                                         \
        };                                                                                                            \
    }
