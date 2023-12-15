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

class all_ctor_getter_trait_class
{
public:
    all_ctor_getter_trait_class(
        bool b,
        int32_t i32,
        int64_t i64,
        std::string str,
        std::vector<int> v,
        std::array<int8_t, 2> a,
        std::map<int, double> m,
        std::map<std::string, std::string> d,
        std::set<int32_t> set) : my_bool(b), my_int32(i32), my_int64(i64), my_string(str), my_vector(v), my_array(a), my_map(m), my_dict(d), my_set(set)
    {
    }

    const bool& get_bool() const { return my_bool; }
    const int32_t& get_int32() const { return my_int32; }
    const int64_t& get_int64() const { return my_int64; }
    const std::string& get_string() const { return my_string; }
    const std::vector<int>& get_vector() const { return my_vector; }
    const std::array<int8_t, 2>& get_array() const { return my_array; }
    const std::map<int, double>& get_map() const { return my_map; }
    const std::map<std::string, std::string>& get_dict() const { return my_dict; }
    const std::set<int32_t>& get_set() const { return my_set; }

private:
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

class n_ctor_getter_trait_class
{
public:
    n_ctor_getter_trait_class(
        bool b,
        uint32_t u32,
        uint64_t u64,
        const char* str,
        std::list<double> l,
        std::array<uint8_t, 2> a,
        std::unordered_map<int, std::string> m,
        std::unordered_map<std::string, std::string> d,
        std::unordered_set<uint32_t> set) : my_bool(b), my_uint32(u32), my_uint64(u64), my_string(str), my_list(l), my_array(a), my_map(m), my_dict(d), my_set(set)
    {
    }

    const bool& get_bool() const { return my_bool; }
    const uint32_t& get_uint32() const { return my_uint32; }
    const uint64_t& get_uint64() const { return my_uint64; }
    const char* get_string() const { return my_string; }
    const std::list<double>& get_list() const { return my_list; }
    const std::array<uint8_t, 2>& get_array() const { return my_array; }
    const std::unordered_map<int, std::string>& get_map() const { return my_map; }
    const std::unordered_map<std::string, std::string>& get_dict() const { return my_dict; }
    const std::unordered_set<uint32_t>& get_set() const { return my_set; }

private:
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
class tpl_all_ctor_getter_trait_class
{
public:
    tpl_all_ctor_getter_trait_class(T1 type1, T2 type2, T3 type3)
        : my_type1(type1), my_type2(type2), my_type3(type3)
    {
    }
    const T1& get_type1() const { return my_type1; }
    const T2& get_type2() const { return my_type2; }
    const T3& get_type3() const { return my_type3; }

private:
    T1 my_type1;
    T2 my_type2;
    T3 my_type3;
};

template <typename T1, typename T2, typename T3>
class tpl_n_ctor_getter_trait_class
{
public:
    tpl_n_ctor_getter_trait_class(T1 type1, T2 type2, T3 type3)
        : my_type1(type1), my_type2(type2), my_type3(type3)
    {
    }
    const T1& get_type1() const { return my_type1; }
    const T2& get_type2() const { return my_type2; }
    const T3& get_type3() const { return my_type3; }

private:
    T1 my_type1;
    T2 my_type2;
    T3 my_type3;
};