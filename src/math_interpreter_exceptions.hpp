
#pragma once

#include <stdexcept>

namespace minicalc::exceptions
{
	class InterpreterException : public std::runtime_error
	{
	public:
		explicit InterpreterException(const std::string& message) : std::runtime_error(message) {}
	};

	class InvalidOperatorException : public InterpreterException
	{
	public:
		explicit InvalidOperatorException(const std::string& operatorName) : InterpreterException("Invalid operator: " + operatorName) {}
	};

	class InvalidOperandException : public InterpreterException
	{
	public:
		explicit InvalidOperandException(const std::string& operand) : InterpreterException("Invalid operand: " + operand) {}
	};

	class DivisionByZeroException : public InterpreterException
	{
	public:
		DivisionByZeroException() : InterpreterException("Division by zero is not allowed.") {}
	};

	class MismatchedParenthesesException : public InterpreterException
	{
	public:
		MismatchedParenthesesException() : InterpreterException("Mismatched parentheses in expression.") {}
	};

	class InvalidOperandTypeException : public InterpreterException
	{
	public:
		InvalidOperandTypeException(const std::string& expectedType, const std::string& actualType)
			: InterpreterException("Expected operand type: " + expectedType + ", but got: " + actualType) {}
	};

	class UnexpectedEndOfExpressionException : public InterpreterException
	{
	public:
		UnexpectedEndOfExpressionException() : InterpreterException("Unexpected end of expression.") {}
	};
}
