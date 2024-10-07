
#pragma once

#include <string>
#include <vector>

#include "math_tokens_helpers.hpp"

namespace minicalc
{
	class Interpreter
	{
	public:
		double Eval(std::string expression);
	private:
		std::vector<token> m_Tokenize(std::string expression);
		std::vector<token> m_InfixToPostfix(std::vector<token> tokens);
		double m_EvaluatePostfix(std::vector<token> tokens);
	};
}
