#include "math_interpreter.hpp"

#include <iostream>

#include <Windows.h>

int main()
{
    while (true)
    {
        std::string expression;
        std::cout << "Enter an expression: ";
        std::getline(std::cin, expression);

        if (expression == "exit")
            break;

        if (expression == "clear")
        {
            system("cls");
            continue;
        }

        try
        {
            std::cout << "Result: " << minicalc::Interpreter::Eval(expression) << '\n';
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    return 0;
}
