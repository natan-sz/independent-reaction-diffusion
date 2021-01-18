#include <iostream>

int main ()
{
    int age = 22;
    double grade = 77.2;
    std::string name = "Natan";

    int *pAge = &age;
    double *pGrade = &grade;
    std::string *pName = &name;

    //Pointers are a memory address datatype
    std::cout << "age: " << pAge << std::endl;
    std::cout << "grade: " << pGrade << std::endl;
    std::cout << "name: " << pName << std::endl;


    return 0;
}