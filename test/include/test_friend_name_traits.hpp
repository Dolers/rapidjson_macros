#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

class friend_all_getter_setter_name_trait_class
{
public:
    const bool& get_bool() const { return my_bool; }
    const int32_t& get_int32() const { return my_int32; }
    const int64_t& get_int64() const { return my_int64; }
    const std::string& get_string() const { return my_string; }
    const std::vector<int>& get_vector() const { return my_vector; }
    const std::array<int8_t, 2>& get_array() const { return my_array; }
    const std::map<int, double>& get_map() const { return my_map; }
    const std::map<std::string, std::string>& get_dict() const { return my_dict; }
    const std::set<int32_t>& get_set() const { return my_set; }
    void set_bool(const bool& value) { my_bool = value; }
    void set_int32(const int32_t& value) { my_int32 = value; }
    void set_int64(const int64_t& value) { my_int64 = value; }
    void set_string(const std::string& value) { my_string = value; }
    void set_vector(const std::vector<int>& value) { my_vector = value; }
    void set_array(const std::array<int8_t, 2>& value) { my_array = value; }
    void set_map(const std::map<int, double>& value) { my_map = value; }
    void set_dict(const std::map<std::string, std::string>& value) { my_dict = value; }
    void set_set(const std::set<int32_t>& value) { my_set = value; }

private:
    RAPIDJSON_TRAIT_FRIEND
    bool my_bool;
    int32_t my_int32;
    int64_t my_int64;
    std::string my_string;
    std::vector<int> my_vector;
    std::array<int8_t, 2> my_array;
    std::map<int, double> my_map;
    std::map<std::string, std::string> my_dict;
    std::set<int32_t> my_set;
};

class friend_n_getter_setter_name_trait_class
{
public:
    const bool& get_bool() const { return my_bool; }
    const uint32_t& get_uint32() const { return my_uint32; }
    const uint64_t& get_uint64() const { return my_uint64; }
    const char* get_string() const { return my_string; }
    const std::list<double>& get_list() const { return my_list; }
    const std::array<uint8_t, 2>& get_array() const { return my_array; }
    const std::unordered_map<int, std::string>& get_map() const { return my_map; }
    const std::unordered_map<std::string, std::string>& get_dict() const { return my_dict; }
    const std::unordered_set<uint32_t>& get_set() const { return my_set; }
    void set_bool(const bool& value) { my_bool = value; }
    void set_uint32(const uint32_t& value) { my_uint32 = value; }
    void set_uint64(const uint64_t& value) { my_uint64 = value; }
    void set_string(const char* value) { my_string = value; }
    void set_list(const std::list<double>& value) { my_list = value; }
    void set_array(const std::array<uint8_t, 2>& value) { my_array = value; }
    void set_map(const std::unordered_map<int, std::string>& value) { my_map = value; }
    void set_dict(const std::unordered_map<std::string, std::string>& value) { my_dict = value; }
    void set_set(const std::unordered_set<uint32_t>& value) { my_set = value; }

private:
    RAPIDJSON_TRAIT_FRIEND
    bool my_bool;
    uint32_t my_uint32;
    uint64_t my_uint64;
    const char* my_string;
    std::list<double> my_list;
    std::array<uint8_t, 2> my_array;
    std::unordered_map<int, std::string> my_map;
    std::unordered_map<std::string, std::string> my_dict;
    std::unordered_set<uint32_t> my_set;
};

template <typename T1, typename T2, typename T3>
class friend_tpl_all_getter_setter_name_trait_class
{
public:
    const T1& get_type1() const { return my_type1; }
    const T2& get_type2() const { return my_type2; }
    const T3& get_type3() const { return my_type3; }
    void set_type1(const T1& value) { my_type1 = value; }
    void set_type2(const T2& value) { my_type2 = value; }
    void set_type3(const T3& value) { my_type3 = value; }

private:
    RAPIDJSON_TRAIT_FRIEND
    T1 my_type1;
    T2 my_type2;
    T3 my_type3;
};

template <typename T1, typename T2, typename T3>
class friend_tpl_n_getter_setter_name_trait_class
{
public:
    const T1& get_type1() const { return my_type1; }
    const T2& get_type2() const { return my_type2; }
    const T3& get_type3() const { return my_type3; }
    void set_type1(const T1& value) { my_type1 = value; }
    void set_type2(const T2& value) { my_type2 = value; }
    void set_type3(const T3& value) { my_type3 = value; }

private:
    RAPIDJSON_TRAIT_FRIEND
    T1 my_type1;
    T2 my_type2;
    T3 my_type3;
};