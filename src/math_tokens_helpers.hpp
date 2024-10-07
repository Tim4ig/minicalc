
#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <functional>

#include "math_tokens.hpp"

namespace minicalc
{
	inline operators GetOperator(std::string op)
	{
		auto it = operatorNameMap.find(op);
		if (it != operatorNameMap.end())
		{
			return it->second;
		}
		throw std::invalid_argument("Invalid operator");
	}

	inline std::string GetOperator(operators op)
	{
		for (auto& [key, value] : operatorNameMap)
		{
			if (value == op)
			{
				return key;
			}
		}
		throw std::invalid_argument("Invalid operator");
	}

	inline type GetOperatorType(operators op)
	{
		auto it = operatorTypeMap.find(op);
		if (it != operatorTypeMap.end())
		{
			return it->second;
		}
		throw std::invalid_argument("Invalid operator");
	}

	inline int GetPrecedence(operators op)
	{
		auto it = operatorPrecedenceMap.find(op);
		if (it != operatorPrecedenceMap.end())
		{
			return it->second;
		}
		return 0;
	}

	inline double EvaluateBinaryOperation(operators op, double l, double r)
	{
		auto it = operatorFunctionMap.find(op);
		if (it != operatorFunctionMap.end())
		{
			return it->second(l, r);
		}
		throw std::invalid_argument("Invalid operator");
	}

	struct token
	{
		token() {}
		token(double value) : value(value), isOperator(false) {}
		token(char parenthesis) : parenthesis(parenthesis), isParenthesis(true) {}
		token(operators op) : op(op), isOperator(true)
		{
			type = GetOperatorType(op);
		}

		double value = 0;

		bool isParenthesis = false;
		char parenthesis = 0;

		bool isOperator = false;
		type type = type::binary;
		operators op = operators::plus;
	};

	inline int operator|(type a, type b)
	{
		return (static_cast<int>(a) | static_cast<int>(b));
	}

	inline int operator&(type a, type b)
	{
		return (static_cast<int>(a) & static_cast<int>(b));
	}
}
