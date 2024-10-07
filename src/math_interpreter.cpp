
#include "math_interpreter.hpp"

#include <iostream>
#include <stack>
#include <algorithm>

#include "math_interpreter_exceptions.hpp"
#include "math_tokens_helpers.hpp"

using namespace minicalc::exceptions;

constexpr auto DEBUG_TOKENS = false;

namespace minicalc
{
	template<class T>
	void DebugPrintTokens(T tokens)
	{
		for (auto& t : tokens)
		{
			if (t.isOperator)
				std::cout << GetOperator(t.op) << ' ';
			else if (t.isParenthesis)
				std::cout << t.parenthesis << ' ';
			else
				std::cout << t.value << ' ';
		}
		std::cout << '\n';
	}

	double Interpreter::Eval(std::string expression)
	{
		auto tokens = this->m_Tokenize(expression);
		if constexpr (DEBUG_TOKENS)
			DebugPrintTokens(tokens);

		auto postfixTokens = this->m_InfixToPostfix(tokens);
		if constexpr (DEBUG_TOKENS)
			DebugPrintTokens(postfixTokens);

		return this->m_EvaluatePostfix(postfixTokens);
	}

	std::vector<token> Interpreter::m_Tokenize(std::string expression)
	{
		std::vector<token> tokens;
		expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
		std::replace_if(expression.begin(), expression.end(), [](char c) { return c == ','; }, '.');

		auto addValueToken = [&tokens](auto& it, auto& end) {
			auto val = std::string(it, end);
			int dot_count = std::count(val.begin(), val.end(), '.');
			if (dot_count > 1)
				throw InvalidOperandException(val);
			tokens.push_back(std::stod(val));
			it = end - 1;
			};

		for (auto it = expression.begin(); it < expression.end(); ++it)
		{
			if (std::isspace(*it))
				continue;

			if (std::isdigit(*it) || *it == '.')
			{
				auto end = std::find_if_not(it, expression.end(), [](char c) { return (std::isdigit(c) || c == '.'); });
				addValueToken(it, end);
			}
			else if (*it == '-' && (it == expression.begin() || *(it - 1) == '(' || (!std::isdigit(*(it - 1)) && *(it - 1) != ')')))
			{
				auto end = std::find_if_not(it + 1, expression.end(), [](char c) { return (std::isdigit(c) || c == '.'); });
				addValueToken(it, end);
			}
			else
			{
				if (*it == '(' || *it == ')')
				{
					tokens.push_back(token(*it));
				}
				else
				{
					bool found = false;
					for (auto& [key, value] : operatorNameMap)
					{
						if (expression.compare(it - expression.begin(), key.size(), key) == 0)
						{
							tokens.push_back(value);
							it += key.size() - 1;
							found = true;
							break;
						}
					}
					if (!found)
						throw InvalidOperatorException(std::string(1, *it));
				}
			}
		}

		return tokens;
	}

	std::vector<token> Interpreter::m_InfixToPostfix(std::vector<token> tokens)
	{
		std::vector<token> postfix;
		std::stack<token> stack;

		for (auto& t : tokens)
		{
			if (!t.isOperator && !t.isParenthesis)
			{
				postfix.push_back(t);
			}
			else if (t.parenthesis == '(')
			{
				stack.push(t);
			}
			else if (t.parenthesis == ')')
			{
				while (!stack.empty() && stack.top().parenthesis != '(')
				{
					postfix.push_back(stack.top());
					stack.pop();
				}
				if (stack.empty())
					throw MismatchedParenthesesException();
				stack.pop();
			}
			else
			{
				while (!stack.empty() && !stack.top().isParenthesis && GetPrecedence(stack.top().op) >= GetPrecedence(t.op))
				{
					postfix.push_back(stack.top());
					stack.pop();
				}
				stack.push(t);
			}
		}

		while (!stack.empty())
		{
			if (stack.top().isParenthesis)
				throw MismatchedParenthesesException();
			postfix.push_back(stack.top());
			stack.pop();
		}

		return postfix;
	}

	double Interpreter::m_EvaluatePostfix(std::vector<token> tokens)
	{
		std::stack<double> stack;

		for (auto& t : tokens)
		{
			if (!t.isOperator && !t.isParenthesis)
			{
				stack.push(t.value);
			}
			else
			{
				if (t.type & type::unary)
				{
					if (stack.empty())
						throw UnexpectedEndOfExpressionException();

					auto operand = stack.top();
					stack.pop();

					if (t.type & type::integer && operand != static_cast<int>(operand))
						throw InvalidOperandTypeException("integer", "float");

					double result = EvaluateBinaryOperation(t.op, operand, 0);
					stack.push(result);
				}
				else
				{
					if (stack.size() < 2)
						throw UnexpectedEndOfExpressionException();

					auto right = stack.top();
					stack.pop();
					auto left = stack.top();
					stack.pop();

					if (t.type & type::integer && (left != static_cast<int>(left) || right != static_cast<int>(right)))
						throw InvalidOperandTypeException("integer", "float");

					double result = EvaluateBinaryOperation(t.op, left, right);
					stack.push(result);
				}
			}
		}

		if (stack.empty())
			throw UnexpectedEndOfExpressionException();

		return stack.top();
	}
}
