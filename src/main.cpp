
#include "math_interpreter.hpp"

#include <iostream>

int main()
{
	minicalc::Interpreter interpreter;
	while (true)
	{
		std::string expression;
		std::cout << "Enter an expression: ";
		std::getline(std::cin, expression);

		if (expression == "exit")
			break;

		else if (expression == "clear") 
		{
			system("cls");
			continue;
		}

		try
		{
			std::cout << "Result: " << interpreter.Eval(expression) << '\n';
		}
		catch (std::exception& e)
		{
			std::cout << "Error: " << e.what() << '\n';
		}
	}

	return 0;
}
