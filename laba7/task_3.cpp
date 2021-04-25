#include "Relation.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <forward_list>
#include <vector>

struct Message
{
    tm* datetime;
    std::string username;
    std::string message;
};

class Username_Strategy: public Strategy<Message>
{
public:
    int compare(const Message& left, const Message& right) const override
    {
        int comp = strcmp(left.username.c_str(), right.username.c_str());
        if (comp == 0)
        {
            return 0;
        }
        return comp < 0 ? -1 : 1;
    }
};

class Message_Strategy: public Strategy<Message>
{
public:
    int compare(const Message& left, const Message& right) const override
    {
        std::string strleft = left.message, strright = right.message;
        transform(strleft.begin(), strleft.end(), strleft.begin(), tolower);
        transform(strright.begin(), strright.end(), strright.begin(), tolower);

        int comp = strcmp(left.message.c_str(), right.message.c_str());
        if (comp == 0)
        {
            return 0;
        }
        return comp < 0 ? -1 : 1;
    }
};

class Datetime_Strategy: public Strategy<Message>
{
public:
    int compare(const Message& left, const Message& right) const override
    {
        int minleft = left.datetime->tm_hour * 60 + left.datetime->tm_min;
        int minright = right.datetime->tm_hour * 60 + right.datetime->tm_min;
        if(minleft == minright)
            return 0;
        return minleft < minright ? -1 : 1;
    }
};

class DateUser_Strategy: public Strategy<Message>
{
public:
    int compare(const Message& left, const Message& right) const override
    {
        Datetime_Strategy dt;
        int comp = dt.compare(left, right);
        if (comp == 0)
        {
            Username_Strategy user;
            comp = user.compare(left, right);
        }
        if(comp == 0)
            return 0;
        return comp < 0 ? -1 : 1;
    }
};

std::forward_list<Message> FromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string tmp;
    size_t prev, pos, point;
    Message mess;
    std::forward_list<Message> flist;

    while(!file.eof())
    {
        point = 0;
        getline(file, tmp);
        mess.datetime = new tm;
        pos = tmp.find(' ', 0);
        while(point < pos)
        {
            point = tmp.find(':', point + 1);
            if (point == 2)
            {
                int hour = stoi(tmp.substr(0, point));
                mess.datetime->tm_hour = hour;
            }
            else
                mess.datetime->tm_min = stoi(tmp.substr(3, 2));
        }
        prev = pos;
        pos = tmp.find(' ', pos + 1);
        mess.username = tmp.substr(prev + 1, pos - prev - 1);
        mess.message = tmp.substr(pos + 1, tmp.size() - prev);
        flist.push_front(mess);
    }
    return flist;
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "No file!" << std::endl;
        exit(1);
    }
    std::vector<int> index_vector;

    relation<Message> Relation;
    index_vector.push_back(Relation.add_Index(AVL, new Datetime_Strategy));
    std::forward_list<Message>tmp = FromFile(argv[1]);
    std::vector<Message> mess_vector(tmp.begin(), tmp.end());
    std::reverse(mess_vector.begin(), mess_vector.end());
    Relation.New_Flist(tmp);
    index_vector.push_back(Relation.add_Index(RB, new Username_Strategy));
    index_vector.push_back(Relation.add_Index(AVL, new DateUser_Strategy));
    index_vector.push_back(Relation.add_Index(RB, new Message_Strategy));
    Relation.delete_Index(index_vector[1]);
    std::vector<bool>result = Relation.search_Data(static_cast<Message>(mess_vector[2]));
    for (auto iter: result)
    {
        if (iter == 1)
            std::cout << "The element was found:)\n";
        else
            std::cout << "There is no such element:(";
    }
    return 0;
}