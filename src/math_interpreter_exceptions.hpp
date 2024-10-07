#pragma once

#include <stdexcept>

namespace minicalc::exceptions
{
    class InterpreterException : public std::runtime_error
    {
    public:
        explicit InterpreterException(const std::string& message) : std::runtime_error(message)
        {
        }
    };

    class InvalidOperatorException final : public InterpreterException
    {
    public:
        explicit InvalidOperatorException(const std::string& operatorName) : InterpreterException("Invalid operator: " + operatorName)
        {
        }
    };

    class InvalidOperandException final : public InterpreterException
    {
    public:
        explicit InvalidOperandException(const std::string& operand) : InterpreterException("Invalid operand: " + operand)
        {
        }
    };

    class DivisionByZeroException final : public InterpreterException
    {
    public:
        DivisionByZeroException() : InterpreterException("Division by zero is not allowed.")
        {
        }
    };

    class MismatchedParenthesesException final : public InterpreterException
    {
    public:
        MismatchedParenthesesException() : InterpreterException("Mismatched parentheses in expression.")
        {
        }
    };

    class InvalidOperandTypeException final : public InterpreterException
    {
    public:
        InvalidOperandTypeException(const std::string& expectedType, const std::string& actualType)
            : InterpreterException("Expected operand type: " + expectedType + ", but got: " + actualType)
        {
        }
    };

    class UnexpectedEndOfExpressionException final : public InterpreterException
    {
    public:
        UnexpectedEndOfExpressionException() : InterpreterException("Unexpected end of expression.")
        {
        }
    };
}
