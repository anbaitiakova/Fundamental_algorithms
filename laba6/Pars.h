#include <vector>
#include <fstream>
#include "SqMatrix.h"

const std::string commands[] =
        {
                "det", "trace", "transpose", "inverse", "exp", "+", "-", "*", "==", "!="
        };

std::vector<double> split(const std::string& str, const std::string& delim, unsigned int position)
{
    std::vector<double> vector;
    size_t prev = position, pos, pr, pr1;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        pr1 = prev;
        while (pr1 < pos)
        {
            pr  = str.find(' ', pr1);
            if (pr > pos)
            {
                std::string token = str.substr(pr1, pos - pr1);
                if (!token.empty())
                    vector.push_back(stod(token));
                break;
            }

            std::string token = str.substr(pr1, pr - pr1);
            if (!token.empty())
                vector.push_back(stod(token));


            pr1 = pr + 1;
        }
        prev = pos + delim.length() + 1;
    }
    while (pos < str.length() && prev < str.length());
    return vector;
}


SqMatrix MatFromString(std::string& str)
{
    unsigned int size, pos = 0, ind = 0;
    std::vector<double>vector;

    while (str[pos++] != '[');

    vector = split(str, "]", pos);
    size = sqrt(vector.size());
    SqMatrix Result(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Result.Mat[i][j] = vector[ind];
            ind++;
        }
    }
    return Result;
}


void FromFile(const std::string& name)
{
    std::ifstream file(name);
    std::ofstream out("OutFile.tex");
    std::string str, before, after;
    size_t num;
    size_t pos, prev;
    double multi = 0;
    int index = -1;

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
        for (int i = 0; i < 10; i++)
        {
            if(str.find(commands[i], 0) != -1)
            {
                index = i;
                break;
            }
        }

        switch(index)
        {
            case 0://det
            {
                SqMatrix Res = MatFromString(str);
                out<< "$$det"<<Res.convert()<<" = " <<std::to_string(Determinant(Res)) <<"$$\n" << std::endl;
                break;
            }

            case 1://trace
            {
                SqMatrix Res = MatFromString(str);
                out<< "$$trace"<<Res.convert()<<" = " <<std::to_string(Trace(Res)) <<"$$\n" << std::endl;
                break;
            }

            case 2://transpose
            {
                SqMatrix Res = MatFromString(str);
                out<< "$$transpose"<<Res.convert() <<" = " <<Transpose(Res).convert()<<"$$\n"<< std::endl;
                break;
            }

            case 3://inverse
            {
                SqMatrix Res = MatFromString(str);
                try
                {
                    SqMatrix tmp0 = Res;
                    SqMatrix tmp = Inverse(Res);
                    out<< "$$inverse"<<tmp0.convert() <<" = " <<tmp.convert()<<"$$\n"<< std::endl;
                }
                catch(std::exception& e)
                {
                    std::cout <<e.what() << std::endl;
                }
                break;
            }

            case 4://exp
            {
                SqMatrix Res = MatFromString(str);
                prev = str.find(',', 0) + 1;
                pos = str.find(')', prev);
                std::string tmp = str.substr(prev, pos - prev);
                num = stod(tmp);
                try
                {
                    SqMatrix tmp0 = Res;
                    SqMatrix tmp = MatExp(Res, num);
                    out << "$$exp(" << tmp0.convert() << ", " << num << ") = " << tmp.convert() << "$$\n"
                        << std::endl;
                }
                catch(std::exception& e)
                {
                    std::cout <<e.what() << std::endl;
                }
                break;
            }

            case 5://+
            {
                pos = str.find('+', 0);
                before = str.substr(0, pos - 1);
                after = str.substr(pos + 1, str.length());
                SqMatrix Before = MatFromString(before);
                SqMatrix After = MatFromString(after);
                try
                {
                    SqMatrix tmp0 = Before;
                    SqMatrix tmp = Before + After;
                    out << "$$"<<tmp0.convert()<< " + " << After.convert()
                        <<" = " << tmp.convert()<<"$$\n"<<std::endl;
                }
                catch(std::exception& e)
                {
                    std::cout <<e.what() << std::endl;
                }
                break;
            }

            case 6://-
            {
                pos = str.find('-', 0);
                before = str.substr(0, pos - 1);
                after = str.substr(pos + 1, str.length());
                SqMatrix Before = MatFromString(before);
                SqMatrix After = MatFromString(after);
                try
                {
                    SqMatrix tmp0 = Before;
                    SqMatrix tmp = Before - After;
                    out << "$$"<<tmp0.convert()<< " - " << After.convert()
                        <<" = " << tmp.convert()<<"$$\n"<<std::endl;
                }
                catch(std::exception& e)
                {
                    std::cout <<e.what() << std::endl;
                }
                break;
            }

            case 7://*
            {
                pos = str.find('*', 0);
                before = str.substr(0, pos - 1);
                after = str.substr(pos + 2, str.length());
                SqMatrix Before = MatFromString(before);
                SqMatrix After = MatFromString(after);

                if (Before.getSize() == 0)
                {
                    multi = stod(before);
                    out << "$$"<< std::to_string(multi) << " * " << After.convert()
                        <<" = " << (After *= multi).convert()<<"$$\n"<<std::endl;
                }

                else if (After.getSize() == 0)
                {
                    multi = stod(after);
                    out << "$$"<< Before.convert() << " * " << std::to_string(multi)
                        <<" = " << (Before *= multi).convert()<<"$$\n"<<std::endl;
                }

                else
                {
                    try
                    {
                        SqMatrix tmp0 = Before;
                        SqMatrix tmp = Before * After;
                        out << "$$" << tmp0.convert() << " * " << After.convert() << " = "
                            << tmp.convert() << "$$\n" << std::endl;

                    }
                    catch (std::exception &e) {
                        std::cout << e.what() << std::endl;
                    }
                }
                break;
            }

            case 8://==
            {
                pos = str.find("==", 0);
                before = str.substr(0, pos - 1);
                after = str.substr(pos + 2, str.length());
                SqMatrix Before = MatFromString(before);
                SqMatrix After = MatFromString(after);
                out << "$$"<<Before.convert()<< " == " << After.convert() <<" = "
                    << std::to_string(Before == After)<<"$$\n"<<std::endl;
                break;
            }

            case 9://!=
            {
                pos = str.find("!=", 0);
                before = str.substr(0, pos - 1);
                after = str.substr(pos + 2, str.length());
                SqMatrix Before = MatFromString(before);
                SqMatrix After = MatFromString(after);
                out << "$$"<<Before.convert()<< " != " << After.convert() <<" = "
                    << std::to_string(Before != After)<<"$$\n"<<std::endl;
                break;
            }
        }
    }
    out <<"\\end{document}";
}