#include <iostream>

double Square (double num)
{
    return num * num;
}

int main ()
{
    double input;

    std::cout << "Enter Number:" << std::endl;

    std::cin >> input;

    std::cout << Square(input) << std::endl;

    return 0;
}