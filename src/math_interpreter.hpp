#pragma once

#include <string>
#include <vector>

#include "math_tokens_helpers.hpp"

namespace minicalc
{
    class Interpreter
    {
    public:
        static double Eval(const std::string& expression);

    private:
        static std::vector<Token> m_Tokenize(std::string expression);
        static std::vector<Token> m_InfixToPostfix(const std::vector<Token>& tokens);
        static double m_EvaluatePostfix(const std::vector<Token>& tokens);
    };
}
