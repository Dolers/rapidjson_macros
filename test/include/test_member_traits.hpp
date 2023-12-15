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

class all_member_trait_class
{
public:
    all_member_trait_class() = default;
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

struct n_member_trait_class
{
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
class tpl_all_member_trait_class
{
public:
    tpl_all_member_trait_class() = default;
    T1 my_type1;
    T2 my_type2;
    T3 my_type3;
};

template <typename T1, typename T2, typename T3>
class tpl_n_member_trait_class
{
public:
    tpl_n_member_trait_class() = default;
    T1 my_type1;
    T2 my_type2;
    T3 my_type3;
};