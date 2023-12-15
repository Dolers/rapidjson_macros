find_package(Catch2 REQUIRED)
find_package(RapidJSON REQUIRED)

include(CTest)
enable_testing()

add_executable(test_rapidjson_macros
    src/test_enum_traits.cpp
    src/test_member_traits.cpp
    src/test_member_name_traits.cpp
    src/test_ctor_getter_traits.cpp
    src/test_ctor_getter_name_traits.cpp
    src/test_getter_setter_traits.cpp
    src/test_getter_setter_name_traits.cpp
    src/test_friend_traits.cpp
    src/test_friend_name_traits.cpp)

if (MSVC)
    target_compile_options(test_rapidjson_macros PRIVATE /bigobj)
endif()

target_compile_definitions(test_rapidjson_macros PRIVATE RAPIDJSON_HAS_STDSTRING=1)
target_include_directories(test_rapidjson_macros PRIVATE "include")
target_link_libraries(test_rapidjson_macros rapidjson_macros rapidjson Catch2::Catch2WithMain)
add_test(NAME test_rapidjson_macros COMMAND $<TARGET_FILE:test_rapidjson_macros>)

add_subdirectory(src/bench)