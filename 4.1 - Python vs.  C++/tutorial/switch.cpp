#include <iostream>

std::string dayOfWeek (int dayNum) 
{
    std::string dayName;

    switch (dayNum){
        case 0:
            dayName = "Monday";
            break;
        case 1:
            dayName = "Tuesday";
            break;
        case 2:
            dayName = "Wednesday";
            break;
        case 3:
            dayName = "Thursday";
            break;
        case 4:
            dayName = "Friday";
            break;
        case 5:
            dayName = "Saturday";
            break;
        case 6:
            dayName = "Sunday";
            break;
        default:
            std::cout << "Wrong input" << std::endl;
    }
    return dayName;
}

int main ()
{
    int inputNum;
    std::string day;

    std::cout << "Enter number of the day of the week" << std::endl;
    std::cin >> inputNum;
    
    std::cout << dayOfWeek(inputNum) << std::endl;

    return 0;
}