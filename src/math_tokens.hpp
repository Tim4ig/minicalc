#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <functional>
#include <cmath>

namespace minicalc
{
    enum class Operators : char
    {
        Plus,
        Minus,
        Multiply,
        Divide,
        Exp,
        LogicalAnd,
        LogicalOr,
        LogicalNot,
        Equal,
        NotEqual,
        Greater,
        Less,
        GreaterEqual,
        LessEqual,
        BitwiseAnd,
        BitwiseOr,
        BitwiseXor,
        BitwiseNot,
        LeftShift,
        RightShift,
    };

    enum class Type : char
    {
        Unary = 1,
        Binary = 2,
        Integer = 4,
        BinaryInteger = Binary | Integer,
        UnaryInteger = Unary | Integer,
    };

    const std::unordered_map<Operators, Type> OPERATOR_TYPE_MAP
    {
        {Operators::Plus, Type::Binary},
        {Operators::Minus, Type::Binary},
        {Operators::Multiply, Type::Binary},
        {Operators::Divide, Type::Binary},
        {Operators::Exp, Type::Binary},
        {Operators::LogicalAnd, Type::Binary},
        {Operators::LogicalOr, Type::Binary},
        {Operators::LogicalNot, Type::Unary},
        {Operators::Equal, Type::Binary},
        {Operators::NotEqual, Type::Binary},
        {Operators::Greater, Type::Binary},
        {Operators::Less, Type::Binary},
        {Operators::GreaterEqual, Type::Binary},
        {Operators::LessEqual, Type::Binary},
        {Operators::BitwiseAnd, Type::BinaryInteger},
        {Operators::BitwiseOr, Type::BinaryInteger},
        {Operators::BitwiseXor, Type::BinaryInteger},
        {Operators::LeftShift, Type::BinaryInteger},
        {Operators::RightShift, Type::BinaryInteger},
        {Operators::BitwiseNot, Type::UnaryInteger},
    };

    const std::unordered_map<std::string, Operators> OPERATOR_NAME_MAP
    {
        {"&&", Operators::LogicalAnd},
        {"||", Operators::LogicalOr},
        {"==", Operators::Equal},
        {"!=", Operators::NotEqual},
        {">=", Operators::GreaterEqual},
        {"<=", Operators::LessEqual},
        {"<<", Operators::LeftShift},
        {">>", Operators::RightShift},
        {"+", Operators::Plus},
        {"-", Operators::Minus},
        {"*", Operators::Multiply},
        {"/", Operators::Divide},
        {"^", Operators::Exp},
        {"!", Operators::LogicalNot},
        {">", Operators::Greater},
        {"<", Operators::Less},
        {"&", Operators::BitwiseAnd},
        {"|", Operators::BitwiseOr},
        {"^", Operators::BitwiseXor},
        {"~", Operators::BitwiseNot},
    };

    const std::unordered_map<Operators, int> OPERATOR_PRECEDENCE_MAP
    {
        {Operators::Plus, 1},
        {Operators::Minus, 1},
        {Operators::Multiply, 2},
        {Operators::Divide, 2},
        {Operators::Exp, 3},
        {Operators::LogicalOr, 0},
        {Operators::LogicalAnd, 0},
        {Operators::LogicalNot, 4},
        {Operators::Equal, 0},
        {Operators::NotEqual, 0},
        {Operators::Greater, 0},
        {Operators::Less, 0},
        {Operators::GreaterEqual, 0},
        {Operators::LessEqual, 0},
        {Operators::BitwiseAnd, 2},
        {Operators::BitwiseOr, 1},
        {Operators::BitwiseXor, 1},
        {Operators::BitwiseNot, 4},
        {Operators::LeftShift, 2},
        {Operators::RightShift, 2},
    };

    const std::unordered_map<Operators, std::function<double(double, double)>> OPERATOR_FUNCTION_MAP
    {
        {Operators::Plus, [](const double l, const double r) { return l + r; }},
        {Operators::Minus, [](const double l, const double r) { return l - r; }},
        {Operators::Multiply, [](const double l, const double r) { return l * r; }},
        {Operators::Divide, [](const double l, const double r)
        {
            if (r == 0) throw std::invalid_argument("Division by zero.");
            return l / r;
        }},
        {Operators::Exp, [](const double l, const double r) { return std::pow(l, r); }},
        {Operators::LogicalAnd, [](const double l, const double r) { return (l != 0) && (r != 0) ? 1.0 : 0.0; }},
        {Operators::LogicalOr, [](const double l, const double r) { return (l != 0) || (r != 0) ? 1.0 : 0.0; }},
        {Operators::LogicalNot, [](const double l, const double) { return (l == 0) ? 1.0 : 0.0; }},
        {Operators::Equal, [](const double l, const double r) { return l == r ? 1.0 : 0.0; }},
        {Operators::NotEqual, [](const double l, const double r) { return l != r ? 1.0 : 0.0; }},
        {Operators::Greater, [](const double l, const double r) { return l > r ? 1.0 : 0.0; }},
        {Operators::Less, [](const double l, const double r) { return l < r ? 1.0 : 0.0; }},
        {Operators::GreaterEqual, [](const double l, const double r) { return l >= r ? 1.0 : 0.0; }},
        {Operators::LessEqual, [](const double l, const double r) { return l <= r ? 1.0 : 0.0; }},
        {Operators::BitwiseAnd, [](const double l, const double r) { return static_cast<int>(l) & static_cast<int>(r); }},
        {Operators::BitwiseOr, [](const double l, const double r) { return static_cast<int>(l) | static_cast<int>(r); }},
        {Operators::BitwiseXor, [](const double l, const double r) { return static_cast<int>(l) ^ static_cast<int>(r); }},
        {Operators::LeftShift, [](const double l, const double r) { return static_cast<int>(l) << static_cast<int>(r); }},
        {Operators::RightShift, [](const double l, const double r) { return static_cast<int>(l) >> static_cast<int>(r); }},
        {Operators::BitwiseNot, [](const double l, const double) { return ~static_cast<int>(l); }},
    };
}
