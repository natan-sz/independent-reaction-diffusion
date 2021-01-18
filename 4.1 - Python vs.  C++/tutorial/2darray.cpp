#include <iostream>



int main ()
{
    int numArray[3][3]{
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    //
    //    for (int i=0; i<=2; i++){
    //        for (int j=0; j<=2; j++){
    //            std::cout << numArray[i][j];
    //        }
    //        std::cout  << std::endl;
    //    }

    for (int *p = &numArray[0][0]; p <= &numArray[3][3]; p++){
        printf("%d", *p);
    }

    return 0;

}