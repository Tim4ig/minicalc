#include "math_interpreter.hpp"

#include <iostream>

int main()
{
    while (true)
    {
        std::string expression;
        std::cout << "> ";
        std::getline(std::cin, expression);

        if (expression == "exit")
            break;

        if (expression == "clear")
        {
            system("clear");
            continue;
        }

        try
        {
            std::cout << "= " << minicalc::Interpreter::Eval(expression) << '\n';
        }
        catch (std::exception& e)
        {
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    return 0;
}
