#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <functional>

#include "math_tokens.hpp"

namespace minicalc
{
    inline Operators GetOperator(const std::string op)
    {
        auto it = OPERATOR_NAME_MAP.find(op);
        if (it != OPERATOR_NAME_MAP.end())
        {
            return it->second;
        }
        throw std::invalid_argument("Invalid operator");
    }

    inline std::string GetOperator(const Operators op)
    {
        for (auto& [key, value] : OPERATOR_NAME_MAP)
        {
            if (value == op)
            {
                return key;
            }
        }
        throw std::invalid_argument("Invalid operator");
    }

    inline Type GetOperatorType(const Operators op)
    {
        auto it = OPERATOR_TYPE_MAP.find(op);
        if (it != OPERATOR_TYPE_MAP.end())
        {
            return it->second;
        }
        throw std::invalid_argument("Invalid operator");
    }

    inline int GetPrecedence(const Operators op)
    {
        auto it = OPERATOR_PRECEDENCE_MAP.find(op);
        if (it != OPERATOR_PRECEDENCE_MAP.end())
        {
            return it->second;
        }
        return 0;
    }

    inline double EvaluateBinaryOperation(const Operators op, const double l, const double r)
    {
        const auto it = OPERATOR_FUNCTION_MAP.find(op);
        if (it != OPERATOR_FUNCTION_MAP.end())
        {
            return it->second(l, r);
        }
        throw std::invalid_argument("Invalid operator");
    }

    struct Token
    {
        Token() = default;

        explicit Token(const double value) : value(value)
        {
        }

        explicit Token(const char parenthesis) : isParenthesis(true), parenthesis(parenthesis)
        {
        }

        explicit Token(const Operators op) : isOperator(true), op(op)
        {
            type = GetOperatorType(op);
        }

        double value = 0;

        bool isParenthesis = false;
        char parenthesis = 0;

        bool isOperator = false;
        Type type = Type::Binary;
        Operators op = Operators::Plus;
    };

    inline int operator|(Type a, Type b)
    {
        return (static_cast<int>(a) | static_cast<int>(b));
    }

    inline int operator&(Type a, Type b)
    {
        return (static_cast<int>(a) & static_cast<int>(b));
    }
}
