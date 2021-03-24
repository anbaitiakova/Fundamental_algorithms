#include "Pars.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "No file!" << std::endl;
        exit(1);
    }
    FromFile(argv[1]);
    return 0;
}