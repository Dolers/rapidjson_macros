find_package(RapidJSON REQUIRED)

add_executable(rapidjson_macros_example src/example.cpp)

target_include_directories(rapidjson_macros_example PUBLIC "include")
target_link_libraries(rapidjson_macros_example PUBLIC rapidjson_macros rapidjson)
target_compile_definitions(rapidjson_macros_example PRIVATE RAPIDJSON_HAS_STDSTRING=1)