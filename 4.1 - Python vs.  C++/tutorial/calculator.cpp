#include <iostream>

double addition (double num1, double num2)
{
    double total = num1 + num2;
    return total;
}

int main ()
{
    double num1, num2;

    std::cout << "Enter your first number: " << std::endl;

    std::cin >> num1;

    std::cout << "Enter your first number: " << std::endl;

    std::cin >> num2;

    std::cout << addition(num1,num2) << std::endl;

    return 0;
}