#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include "Memory.h"

struct fileElement
{
    std::string var;
    memoryElement m;
};

std::vector<std::string> Split(const std::string& subject)
{
    std::istringstream ss{subject};
    using StrIt = std::istream_iterator<std::string>;
    std::vector<std::string> container{StrIt{ss}, StrIt{}};
    return container;
}

int main(int argc, char** argv)
{
    std::ifstream file(argv[1]);
    std::string str;
    fileElement element;
    std::vector<std::string> vectorWords;
    std::vector<fileElement> vectorVar;
    size_t N, n, fl = 0;
    if (!file)
        std::cerr << "Something wrong with file" << std::endl;
    getline(file, str);
    N = atoi(str.c_str());
    getline(file, str);
    memory* block;
    if (str == "Border_Descriptor")
    {
        block = new Border_Descriptor(N);
    } else
        if (str == "First_Appropriate")
        {
            block = new First_Appropriate(N);
        }
    while (!file.eof()) {
        getline(file, str);
        vectorWords = Split(str);
        if (vectorWords[0] == "deallocate")
        {
            auto iterend = --(vectorWords[1].end());
            vectorWords[1].erase(vectorWords[1].begin());
            vectorWords[1].erase(--iterend);
            element.var = vectorWords[1];
            for(auto iter = vectorVar.begin(); iter != vectorVar.end(); ++iter)
            {
                if (iter->var == element.var)
                {
                    try
                    {
                        block->deallocate(iter->m);
                    }
                    catch (const char* exception)
                    {
                        std::cerr << "Error: " << exception << '\n';
                    }
                }
            }
            continue;
        }
        else
            element.var = vectorWords[0];
        if (vectorWords[2] == "allocate")
        {
            auto iterend = --(vectorWords[3].end());
            vectorWords[3].erase(vectorWords[3].begin());
            vectorWords[3].erase(--iterend);
            n = std::stoi(vectorWords[3]);
            try
            {
                element.m = block->allocate(n);
            }
            catch (const char* exception)
            {
                std::cerr << "Error: " << exception << '\n';
            }
        }
        else
        {
            std::string var2 = vectorWords[2];
            for (auto iter = vectorVar.begin(); iter != vectorVar.end(); iter++)
            {
                if (iter->var == var2)
                {
                    element.var = vectorWords[0];
                    element.m = iter->m;
                    fl = 1;
                }
            }
            if (fl == 0)
            {
                std::cout << "error";
                return 1;
            }
        }
        vectorVar.push_back(element);

    }
    block->printAllBlocks();
    delete block;
    return 0;
}