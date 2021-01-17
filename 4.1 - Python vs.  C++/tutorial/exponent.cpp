#include <iostream>

int power(int num, int power){

    int result = 1;

    for (int i = 0; i < power; i++){
        result = result * num;
    }

    return result;
}

int main ()
{
    int baseNum,powerNum;

    std::cout << "Enter base number: " << std::endl;
    std::cin >> baseNum;
    std::cout << "Enter power: " << std::endl;
    std::cin >> powerNum;
    std::cout << power(baseNum,powerNum) << std::endl;
}