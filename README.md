# rapidjson_macros

rapidjson_macros is a C++, header-only library macro based extension for [rapidjson](https://rapidjson.org/) based on [jsoncons](https://github.com/danielaparker/jsoncons)' [json_type_traits](https://github.com/danielaparker/jsoncons/blob/master/doc/ref/corelib/json_type_traits.md).

It provides a number of macros that can be used to generate the code to specialize rapidjson based json_type_traits for a user-defined class.

Macro names follow naming conventions.

Component | Description
----------|--------------------
TPL       | Template class with a specified number of template parameters
ALL       | All data members are mandatory
N         | A specified number of data members are mandatory
MEMBER    | Accesses and modifies class data members
CTOR      | Requires constructor that takes all data members in the order they appear in the list
GETTER    | Accesses data members through getter functions
SETTER    | Modifies data members through setter functions
NAME      | Serialize with provided names (instead of C++ member names)

For more in depth guide, follow [jsoncons' macro guide](https://github.com/danielaparker/jsoncons/blob/master/doc/ref/corelib/json_type_traits/convenience-macros.md).
Macros follow the same naming and logic (expect the prefix is `RAPIDJSON_` instead of `JSONCONS_`)

## API
```
# Appropriate macro have been called, like
# RAPIDJSON_ALL_MEMBER_TRAITS(MyClass, ...);

namespace rapidjson_macros
{
    MyClass as<MyClass>(const std::string&);
    rapidjson::GenericValue to_json<MyClass>(const MyClass&, rapidjson::MemoryPoolAllocator<>);
    void to_stream<MyClass>(std::basic_ostream&, const MyClass&);
}
```

## Example

### Enums

``` c++
enum class Week { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

-------------------------------------------------------------------------------

#include <rapidjson_macros/rapidjson_macros>

RAPIDJSON_ENUM_NAME_TRAITS(Week,
                           (MONDAY, "monday"),
                           (TUESDAY, "tuesday"),
                           (WEDNESDAY, "wednesday"),
                           (THURSDAY, "thursday"),
                           (FRIDAY, "friday"),
                           (SATURDAY, "saturday"),
                           (SUNDAY, "sunday"));
```
### Structs

``` c++

struct MyStruct
{
    bool my_bool;
    uint64_t my_uint64;
    std::string my_string;
    std::list<double> my_list;
    std::unordered_map<std::string, std::string> my_dict;
};

-------------------------------------------------------------------------------

#include <rapidjson_macros/rapidjson_macros>

RAPIDJSON_N_MEMBER_TRAITS(MyStruct, 4, my_bool, my_uint64, my_string, my_list, my_dict);
```

### Classes

``` c++

class MyClass
{
public:
    const int32_t& get_int32() const { return my_int32; }
    const std::string& get_string() const { return my_string; }
    const std::vector<int>& get_vector() const { return my_vector; }
    const std::array<int8_t, 2>& get_array() const { return my_array; }
    const std::set<int32_t>& get_set() const { return my_set; }
    void set_int64(const int64_t& value) { my_int64 = value; }
    void set_string(const std::string& value) { my_string = value; }
    void set_vector(const std::vector<int>& value) { my_vector = value; }
    void set_array(const std::array<int8_t, 2>& value) { my_array = value; }
    void set_set(const std::set<int32_t>& value) { my_set = value; }

private:
    int32_t my_int32;
    std::string my_string;
    std::vector<int> my_vector;
    std::array<int8_t, 2> my_array;
    std::set<int32_t> my_set;
};

-------------------------------------------------------------------------------

#include <rapidjson_macros/rapidjson_macros>

RAPIDJSON_ALL_GETTER_SETTER_NAME_TRAITS(MyClass,
                                        (get_int32, set_int32, "i32"),
                                        (get_string, set_string, "str"),
                                        (get_vector, set_vector, "vector"),
                                        (get_array, set_array, "array"),
                                        (get_set, set_set, "set"));
```

## Building

Get the dependent packages
``` bash
conan install -of build/<release|debug> .
```

> Note: Conan2 seems to have a nasty habit of marking dependent modules properties (eg INTERFACE_INCLUDE_FOLDER is behind `$<CONFIG:RELEASE>`) with the configured build config.
> This means you are forbidden to consume and build different build configs.

### Build through IDE

Follow the steps of building a project of your favourite IDE. Don't forget to select both configuration and build preset before building.

### Manual build

CMake configure
```
cmake -DCMAKE_BUILD_TYPE=<Release|Debug> -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -S<root folder path> -B<build folder path> -G "Ninja"
```

CMake build
```
cmake --build <build folder path> -- config <Release|Debug>
```