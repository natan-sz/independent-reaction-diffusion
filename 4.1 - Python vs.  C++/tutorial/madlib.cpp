#include <iostream>

int main ()
{
    std::string colour, adjective, person;

    std::cout << "Enter a colour: " << std::endl;
    getline(std::cin, colour);
    std::cout << "Enter a adjective: " << std::endl;
    getline(std::cin, adjective);
    std::cout << "Enter a person: " << std::endl;
    getline(std::cin, person);
    std::cout << "Roses are " << colour << std::endl;
    std::cout << "Violets are " << adjective << std::endl;
    std::cout << "I love " << person << std::endl;

    return 0;
}