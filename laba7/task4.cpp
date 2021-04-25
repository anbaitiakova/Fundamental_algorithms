#include "Relation.h"
#include <iostream>
#include <forward_list>
#include <cstring>
#include <fstream>
#include <limits>
#include <algorithm>

struct Documents
{
    std::string name_of_person;
    int doc_id;
    tm* duration;
    int price;
};

class NameID_Strategy: public Strategy<Documents>
{
public:
    int compare(const Documents& left, const Documents& right) const override
    {
        int comp = strcmp(left.name_of_person.c_str(), right.name_of_person.c_str());
        if (comp == 0)
        {
            if (left.doc_id == right.doc_id)
                return 0;
            else
                left.doc_id < right.doc_id ? -1 : 1;
        }
        else
            return comp < 0 ? -1 : 1;
    }
};

class Duration_Strategy: public Strategy<Documents>
{
public:
    int compare(const Documents& left, const Documents& right) const override
    {
        time_t time1 = mktime(left.duration);
        time_t time2 = mktime(right.duration);
        double diffInSec = difftime(time1, time2);

        if (diffInSec == 0)
            return 0;
        else
            return diffInSec < 0 ? -1 : 1;
    }
};

class Price_Strategy: public Strategy<Documents>
{
public:
    int compare(const Documents& left, const Documents& right) const override
    {
        if (left.price == right.price)
            return 0;
        else
            return left.price < right.price ? -1 : 1;
    }
};

std::forward_list<Documents> FromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string fullName, tmpstring;
    Documents docs;
    std::forward_list<Documents> flist;
    std::string check, str;
    char tmp;
    int pos, prev;

    while(!file.eof())
    {
        getline(file, fullName);
        file >> check;
        while (check != "}")
        {
            tm begin, end;
            file >> check;
            if (check == "}")
            {
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            docs.duration = new tm;
            docs.name_of_person = fullName;
            file >> tmp;
            file >> check;
            docs.doc_id = stoi(check);
            getline(file, tmpstring);
            prev = tmpstring.find(' ',1);
            pos = tmpstring.find('.', prev);
            begin.tm_mday = stoi(tmpstring.substr(prev + 1, 2));
            begin.tm_mon = stoi(tmpstring.substr(pos + 1, 2));
            begin.tm_year = stoi(tmpstring.substr(pos + 4, 4));
            prev = tmpstring.find("кон.", pos);
            pos = tmpstring.find(' ', prev);
            end.tm_mday = stoi(tmpstring.substr(pos + 1, 2));
            end.tm_mon = stoi(tmpstring.substr(pos + 4, 2));
            end.tm_year = stoi(tmpstring.substr(pos + 7, 4));
            docs.duration->tm_mday = std::abs(end.tm_mday - begin.tm_mday);
            docs.duration->tm_mon = std::abs(end.tm_mon - begin.tm_mon);
            docs.duration->tm_year = end.tm_year - begin.tm_year;
            prev = tmpstring.find(' ', pos + 1);
            pos = tmpstring.find(' ', prev + 1);
            docs.price = stoi(tmpstring.substr(pos + 1, tmpstring.size() - pos));
            flist.push_front(docs);
        }
    }
    return flist;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "No file!" << std::endl;
        exit(1);
    }
    std::vector<int> index_vector;
    relation<Documents>Relation;
    std::forward_list<Documents>tmp = FromFile(argv[1]);
    std::vector<Documents> mess_vector(tmp.begin(), tmp.end());
    std::reverse(mess_vector.begin(), mess_vector.end());
    Relation.New_Flist(tmp);
    index_vector.push_back(Relation.add_Index(AVL, new NameID_Strategy));
    index_vector.push_back(Relation.add_Index(RB, new Duration_Strategy));
    index_vector.push_back(Relation.add_Index(AVL, new Price_Strategy));
    index_vector.push_back(Relation.add_Index(RB, new Price_Strategy));
    Relation.delete_Index(index_vector[1]);
    return 0;
}