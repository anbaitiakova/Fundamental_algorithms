#include "Interface.h"
template<class T>
class Array_Decorator: public Decorator<T>
{
    std::shared_ptr<T>* array_forms;
    unsigned int size, capacity, resizeFactor = 2;
public:
    Array_Decorator()
    {
        capacity = 500003;
        size = 0;
        array_forms = new std::shared_ptr<T>[capacity];
    }

    Array_Decorator(Array_Decorator& array)
    {
        capacity = array.capacity;
        resizeFactor = array.resizeFactor;
        size = array.size;
        array_forms = new int[capacity];
        for(int i = 0; i < array.size; i++)
        {
            array_forms[i] = array.array_forms[i];
        }
    }

    int getSize() override
    {
        return size;
    }

    void Add_Form(const std::shared_ptr<T>& Form) override
    {
        array_forms[size] = Form;
        size++;
        if(size == capacity)
        {
            ResizeArray();
        }
    }

    void Delete_Form() override
    {
        std::shared_ptr<Tax_Form> deleted_form;
        bool res;
        unsigned int index;
        deleted_form = FormDelete();
        Strategy<std::shared_ptr<Tax_Form>>* strategy = new INN_Strategy();
        for (int i = 0; i < size; ++i)
        {
            res = strategy->compare(std::shared_ptr<T>(deleted_form), array_forms[i]);
            if (res)
            {
                size--;
                array_forms[i] = nullptr;
                index = size - i;
                if(index > 0)
                {
                    for(int j = 0; j < index; ++j)
                    {
                        array_forms[i + j] = array_forms[i + j + 1];
                    }
                }
                delete strategy;
                std::cout << "Successfully deleted!\n";
                return;
            }
        }
        throw "No such information";
    }

    std::vector<std::shared_ptr<T>> Search_Form()
    {
        std::vector<std::shared_ptr<Tax_Form>> for_search;
        std::shared_ptr<Tax_Form> tmp;
        bool res;
        Strategy<std::shared_ptr<Tax_Form>>* strategy = nullptr;
        tmp = FormForWork(&strategy);
        for(int i = 0; i < size; ++i)
        {
            res = strategy->compare(std::shared_ptr<T>(tmp), array_forms[i]);
            if (res)
            {
                for_search.push_back(array_forms[i]);
            }
        }
        delete strategy;
        return for_search;
    }

    void ResizeArray()
    {
        capacity = capacity * (double)resizeFactor;
        auto* tmp = new std::shared_ptr<T>[capacity];
        for(int i = 0; i < size; i++)
        {
            tmp[i] = array_forms[i];
        }
        delete[] array_forms;
        array_forms = tmp;
    }

    std::shared_ptr<T>& operator[](const int& n)
    {
        if(n >= 0 && n < size) return array_forms[n];
        return array_forms[size];
    }

    std::map<unsigned int, int> Statistic_uint(size_t choice)
    {
        std::map<unsigned int, int> map;
        switch(choice)
        {
            case 1:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getKPP()]++;
                break;
            case 2:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getCodeOKATO()]++;
                break;
            case 3:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getTaxAmount()]++;
                break;
        }
        return map;
    }

    std::map<unsigned long long int, int> Statistic_long()
    {
        std::map<unsigned long long int, int> map;
        for(int i = 0; i < size; ++i)
            map[(array_forms[i])->getINN()]++;
        return map;
    }

    std::map<unsigned short, int> Statistic_short(size_t choice)
    {
        std::map<unsigned short, int> map;
        switch(choice)
        {
            case 1:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getReportingYear()]++;
                break;
            case 2:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getCodeTaxAuthority()]++;
                break;
            case 3:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getCodeEcActivity()]++;
                break;
        }
        return map;
    }

    std::map<std::string, int> Statistic_string(size_t choice)
    {
        std::map<std::string, int> map;
        switch(choice)
        {
            case 1:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getTaxAuthority()]++;
                break;
            case 2:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getOrganizationName()]++;
                break;
            case 3:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getFIO()]++;
                break;
            case 4:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getDateBirth()]++;
                break;
            case 5:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getPhoneNumber()]++;
                break;
            case 6:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getCitizenship()]++;
                break;
            case 7:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getResidence()]++;
                break;
            case 8:
                for(int i = 0; i < size; ++i)
                    map[(array_forms[i])->getDate ()]++;
                break;

        }
        return map;
    }

    std::map<tax_period, int> Statistic_period()
    {
        std::map<tax_period, int> map;
        for(int i = 0; i < size; ++i)
            map[(array_forms[i])->getTaxPeriod()]++;
        return map;
    }

    std::map<identification_document, int> Statistic_document()
    {
        std::map<identification_document, int> map;
        for(int i = 0; i < size; ++i)
            map[(array_forms[i])->getDocument()]++;
        return map;
    }

    std::map<transfer_declaration, int> Statistic_transfer()
    {
        std::map<transfer_declaration, int> map;
        for(int i = 0; i < size; ++i)
            map[(array_forms[i])->getTransfer()]++;
        return map;
    }

    std::map<category_of_taxpayer, int> Statistic_category()
    {
        std::map<category_of_taxpayer, int> map;
        for(int i = 0; i < size; ++i)
            map[(array_forms[i])->getCategory()]++;
        return map;
    }

    std::map<std::set<tax_types>, int> Statistic_types()
    {
        std::map<std::set<tax_types>, int> map;
        for(int i = 0; i < size; ++i)
            map[(array_forms[i])->getTaxName()]++;
        return map;
    }

    std::map<std::set<sources_of_income>, int> Statistic_income()
    {
        std::map<std::set<sources_of_income>, int> map;
        for(int i = 0; i < size; ++i)
            map[(array_forms[i])->getIncome()]++;
        return map;
    }

    ~Array_Decorator()
    {
        if(array_forms != nullptr)
            delete[] array_forms;
    }
};