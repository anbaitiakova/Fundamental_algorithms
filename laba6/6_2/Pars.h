#include "Polinom.h"
#include <fstream>
#include <vector>

const std::string commands[] =
        {
            "+", "-", "*", "/", "==", "!=", "uniformity" ,"harmonicity"
        };


std::vector<std::string>split(const std::string& str)
{
    std::string first, second;
    int pos, prev;
    std::vector<std::string>vector;
    prev = str.find("(", 0);
    pos = str.find(")", 1);
    first = str.substr(prev + 1, pos - prev - 1);
    vector.push_back(first);
    prev = pos + 1;
    pos = str.find(")", prev);
    second = str.substr(prev + 1, pos - prev - 1);
    vector.push_back(second);
    return vector;
}

void FromFile(const std::string& name)
{
    std::ifstream file(name);
    std::ofstream out("OutFile.tex");
    int index = -1, prev, pos;
    const char* tmp;
    std::string str, first, operation, unary;
    std::vector<std::string> vec;
    char priv_der;
    const char* mix_der, *ptr;
    if (!file)
    {
        std::cerr << "Can't open file for reading!" << std::endl;
        exit(1);
    }

    if (!out)
    {
        std::cerr << "Can't open file for writing!" << std::endl;
        exit(1);
    }
    out <<"\\documentclass{article}\n"<<"\\usepackage{amsmath}\n"<<"\\begin{document}\n";

    while(!file.eof())
    {
        getline(file, str);
        if (str.empty())
            continue;
        pos = str.find("(", 0);
        operation = str.substr(0, pos - 1);
        for (int i = 0; i < 8; i++)
        {
            if (operation.find(commands[i], 0) != -1)
            {
                index = i;
                break;
            }
        }
         switch(index)//"+", "-", "*", "/", "==", "!=", "uniformity" ,"harmonicity"
         {
             case 0://+
             {
                 vec = split(str);
                 polynomial first((vec[0]).c_str());
                 polynomial second((vec[1]).c_str());
                 try {
                     polynomial result = first + second;
                     out << "$$"<< first.convert() << " + " << second.convert() << " = " << result.convert()<<"$$"<<std::endl;
                 }
                 catch (const char *ex) {
                     std::cerr << ex << '\n';
                 }
                 break;
             }
             case 1://-
             {
                 vec = split(str);
                 polynomial first((vec[0]).c_str());
                 polynomial second((vec[1]).c_str());
                 try
                 {
                     polynomial result = first - second;
                     out <<"$$"<< first.convert() << " - " << second.convert() << " = " << result.convert()<<"$$"<<std::endl;
                 }
                 catch (const char *ex) {
                     std::cerr << ex << '\n';
                 }
                 break;
             }
             case 2://*
             {
                 vec = split(str);
                 polynomial first((vec[0]).c_str());
                 polynomial second((vec[1]).c_str());
                 try
                 {
                     polynomial result = first * second;
                     out <<"$$"<< first.convert() << " * " << second.convert() <<" = "<< result.convert()<<"$$"<<std::endl;
                 }
                 catch(const char* ex)
                 {
                     std::cerr << ex << '\n';
                 }
                 break;
             }
             case 3:// /
             {
                 prev = pos + 1;
                 pos = str.find(")", prev);
                 unary = str.substr(prev, pos - prev);
                 tmp = unary.c_str();
                 polynomial unar(tmp);
                 prev = pos + 2;
                 pos = str.find(")", prev);
                 unary = str.substr(prev, pos - prev);
                 if(unary.size() == 1)
                 {
                    ptr = unary.c_str();
                    priv_der = ptr[0];
                    out <<"$$"<< unar.convert() << " / (" << unary << ") = " << (unar / priv_der).convert()<<"$$" << std::endl;
                 }
                 else
                 {
                    mix_der = unary.c_str();
                    polynomial res = unar / mix_der;
                    out <<"$$"<< unar.convert() << " / (" << unary << ") = " << res.convert()<<"$$" << std::endl;
                 }

                 break;
             }
             case 4://==
             {
                 vec = split(str);
                 polynomial first((vec[0]).c_str());
                 polynomial second((vec[1]).c_str());
                     out <<"$$"<< first.convert() << " == " << second.convert() <<" = "<< std::to_string(first == second)<<"$$"<<std::endl;
                 break;
             }
             case 5://!=
             {
                 vec = split(str);
                 polynomial first((vec[0]).c_str());
                 polynomial second((vec[1]).c_str());
                 out<<"$$" << first.convert() << " != " << second.convert() <<" = "<< std::to_string(first != second)<<"$$"<<std::endl;
                 break;
             }
             case 6://uniformity
             {
                unary = str.substr(pos + 1, str.size() - pos - 2);
                tmp = unary.c_str();
                polynomial unar(tmp);
                out <<"$$"<< "uniformity" << unar.convert() << " = " << std::to_string(uniformity(unar)) <<"$$"<<std::endl;
                break;
             }
             case 7://harmonicity
             {
                 unary = str.substr(pos + 1, str.size() - pos - 2);
                 tmp = unary.c_str();
                 polynomial unar(tmp);
                 out<<"$$" << "harmonicity" << unar.convert() << " = " << std::to_string(harmonicity(unar)) <<"$$"<<std::endl;
                 break;
             }
         }
    }
    out <<"\\end{document}";
}