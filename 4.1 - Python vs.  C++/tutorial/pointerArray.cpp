#include <iostream>

int main () {

    int** board = new int*[10];;

    for (int i = 0; i < 10; ++i) {
        board[i] = new int[10];
        // each i-th pointer is now pointing to dynamic array (size 10) of actual int values
    }

    for (int i = 0; i < 10; ++i) {   // for each row
        for (int j = 0; j < 10; ++j) { // for each column
            board[i][j] = 1;
        }
    } 

    for (int i = 0; i < 10; ++i) {   // for each row
        for (int j = 0; j < 10; ++j) { // for each column
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    } 

    return 0;
}