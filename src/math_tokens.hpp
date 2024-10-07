
#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <functional>
#include <cmath> 

namespace minicalc
{
    enum class operators
    {
        plus,
        minus,
        multiply,
        divide,
        exp,
        logical_and,
        logical_or,
        logical_not,
        equal,
        not_equal,
        greater,
        less,
        greater_equal,
        less_equal,
        bitwise_and,  
        bitwise_or,   
        bitwise_xor,  
        left_shift,   
        right_shift,  
    };

    enum class type : int
    {
        unary = 1,
        binary = 2,
        integer = 4,
		binary_integer = binary | integer,
    };

    const std::unordered_map<operators, type> operatorTypeMap
    {
        {operators::plus,          type::binary},
        {operators::minus,         type::binary},
        {operators::multiply,      type::binary},
        {operators::divide,        type::binary},
        {operators::exp,           type::binary},
        {operators::logical_and,   type::binary},
        {operators::logical_or,    type::binary},
        {operators::logical_not,   type::unary },
        {operators::equal,         type::binary},
        {operators::not_equal,     type::binary},
        {operators::greater,       type::binary},
        {operators::less,          type::binary},
        {operators::greater_equal, type::binary},
        {operators::less_equal,    type::binary},
        {operators::bitwise_and,   type::binary_integer},
        {operators::bitwise_or,    type::binary_integer},
        {operators::bitwise_xor,   type::binary_integer},
        {operators::left_shift,    type::binary_integer},
        {operators::right_shift,   type::binary_integer},
    };

    const std::unordered_map<std::string, operators> operatorNameMap
    {
        {"&&",	operators::logical_and},
        {"||",	operators::logical_or},
        {"==",	operators::equal},
        {"!=",	operators::not_equal},
        {">=",	operators::greater_equal},
        {"<=",	operators::less_equal},
        {"<<",	operators::left_shift},   
        {">>",	operators::right_shift},  
        {"+",	operators::plus},
        {"-",	operators::minus},
        {"*",	operators::multiply},
        {"/",	operators::divide},
        {"^",	operators::exp},
        {"!",	operators::logical_not},
        {">",	operators::greater},
        {"<",	operators::less},
        {"&",	operators::bitwise_and},  
        {"|",	operators::bitwise_or},   
        {"^",	operators::bitwise_xor},  
    };

    const std::unordered_map<operators, int> operatorPrecedenceMap
    {
        {operators::plus,          1},
        {operators::minus,         1},
        {operators::multiply,      2},
        {operators::divide,        2},
        {operators::exp,           3},
        {operators::logical_or,    0},
        {operators::logical_and,   0},
        {operators::logical_not,   4},
        {operators::equal,         0},
        {operators::not_equal,     0},
        {operators::greater,       0},
        {operators::less,          0},
        {operators::greater_equal, 0},
        {operators::less_equal,    0},
        {operators::bitwise_and,   2},
        {operators::bitwise_or,    1},
        {operators::bitwise_xor,   1},
        {operators::left_shift,    2},
        {operators::right_shift,   2},
    };

    const std::unordered_map<operators, std::function<double(double, double)>> operatorFunctionMap
    {
        {operators::plus,			[](double l, double r) { return l + r; }},
        {operators::minus,			[](double l, double r) { return l - r; }},
        {operators::multiply,		[](double l, double r) { return l * r; }},
        {operators::divide,			[](double l, double r) {
            if (r == 0) throw std::invalid_argument("Division by zero.");
            return l / r;
        }},
        {operators::exp,			[](double l, double r) { return std::pow(l, r); }},
        {operators::logical_and,    [](double l, double r) { return (l != 0) && (r != 0) ? 1.0 : 0.0; }},
        {operators::logical_or,     [](double l, double r) { return (l != 0) || (r != 0) ? 1.0 : 0.0; }},
        {operators::logical_not,    [](double l, double) { return (l == 0) ? 1.0 : 0.0; }},
        {operators::equal,          [](double l, double r) { return l == r ? 1.0 : 0.0; }},
        {operators::not_equal,      [](double l, double r) { return l != r ? 1.0 : 0.0; }},
        {operators::greater,        [](double l, double r) { return l > r ? 1.0 : 0.0; }},
        {operators::less,           [](double l, double r) { return l < r ? 1.0 : 0.0; }},
        {operators::greater_equal,  [](double l, double r) { return l >= r ? 1.0 : 0.0; }},
        {operators::less_equal,     [](double l, double r) { return l <= r ? 1.0 : 0.0; }},
        {operators::bitwise_and,    [](double l, double r) { return static_cast<int>(l) & static_cast<int>(r); }},
        {operators::bitwise_or,     [](double l, double r) { return static_cast<int>(l) | static_cast<int>(r); }},
        {operators::bitwise_xor,    [](double l, double r) { return static_cast<int>(l) ^ static_cast<int>(r); }},
        {operators::left_shift,     [](double l, double r) { return static_cast<int>(l) << static_cast<int>(r); }},
        {operators::right_shift,    [](double l, double r) { return static_cast<int>(l) >> static_cast<int>(r); }},
    };
}
