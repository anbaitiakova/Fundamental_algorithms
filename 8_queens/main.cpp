#include <iostream>
#include "Queens_Problem.h"
#include <ctime>




int main()
{
    Solve_Recursive recursive;
    unsigned int start_time =  clock();
    recursive.setQueen(0);
    unsigned int end_time = clock();
    std::cout<<"Recursive: "<<(end_time - start_time)/1000.0 <<std::endl;
    Solve_Iterative iterative;
    start_time = clock();
    iterative.setQueen(0);
    end_time = clock();
    std::cout<<"Iterative: "<<(end_time - start_time)/1000.0 << std::endl;
    return 0;
}
