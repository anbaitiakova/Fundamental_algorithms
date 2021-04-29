#include <iostream>
#include "Pars.h"
int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "No file!" << std::endl;
        exit(1);
    }
    FromFile(argv[1]);
    /*polynomial poly("- 2x^2y^2z");
    polynomial monom("2x^2y^2z");
    char* x = "x y z";
    polynomial tmp = poly + monom;
    std::cout << tmp;*/
    //std::cout << harmonicity(poly);
    return 0;
}
