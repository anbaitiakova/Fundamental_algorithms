template<class T>
class Vector_Decorator: public Decorator<T>
{
    std::vector<std::shared_ptr<T>> vector_forms;
public:
    Vector_Decorator() = default;

    int getSize() override
    {
        return vector_forms.size();
    }

    void Add_Form(const std::shared_ptr<T>& Form) override
    {
        vector_forms.push_back(Form);
    }

    void Delete_Form() override
    {
        std::shared_ptr<Tax_Form> deleted_form;
        bool res;
        deleted_form = FormDelete();
        Strategy<std::shared_ptr<Tax_Form>>* strategy = new INN_Strategy();
        for (auto iter = vector_forms.begin(); iter != vector_forms.end(); ++iter)
        {
            res = strategy->compare(std::shared_ptr<T>(deleted_form), *iter);
            if (res)
            {
                vector_forms.erase(iter);
                std::cout << "Successfully deleted!";
                delete strategy;
                return;
            }
        }
        throw "No such information";
    }

    std::vector<std::shared_ptr<T>> Search_Form() override
    {
        std::vector<std::shared_ptr<Tax_Form>> for_search;
        std::shared_ptr<Tax_Form> tmp;
        bool res;
        Strategy<std::shared_ptr<Tax_Form>>* strategy = nullptr;
        tmp = FormForWork(&strategy);
        for (auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
        {
            res = strategy->compare(std::shared_ptr<T>(tmp), *iter);
            if (res)
            {
                for_search.push_back(*iter);
            }
        }
        delete strategy;
        return for_search;
    }

    std::map<unsigned int, int> Statistic_uint(size_t choice) override
    {
        std::map<unsigned int, int> map;
        switch(choice)
        {
            case 1:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getKPP()]++;
                break;
            case 2:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getCodeOKATO()]++;
                break;
            case 3:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getTaxAmount()]++;
                break;
        }
        return map;
    }

    std::map<unsigned long long int, int> Statistic_long() override
    {
        std::map<unsigned long long int, int> map;
        for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
            map[(*iter)->getINN()]++;
        return map;
    }

    std::map<unsigned short, int> Statistic_short(size_t choice) override
    {
        std::map<unsigned short, int> map;
        switch(choice)
        {
            case 1:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getReportingYear()]++;
                break;
            case 2:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getCodeTaxAuthority()]++;
                break;
            case 3:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getCodeEcActivity()]++;
                break;
        }
        return map;
    }

    std::map<std::string, int> Statistic_string(size_t choice)  override
    {
        std::map<std::string, int> map;
        switch(choice)
        {
            case 1:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getTaxAuthority()]++;
                break;
            case 2:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getOrganizationName()]++;
                break;
            case 3:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getFIO()]++;
                break;
            case 4:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getDateBirth()]++;
                break;
            case 5:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getPhoneNumber()]++;
                break;
            case 6:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getCitizenship()]++;
                break;
            case 7:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getResidence()]++;
                break;
            case 8:
                for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
                    map[(*iter)->getDate ()]++;
                break;
        }
        return map;
    }

    std::map<tax_period, int> Statistic_period() override
    {
        std::map<tax_period, int> map;
        for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
            map[(*iter)->getTaxPeriod()]++;
        return map;
    }

    std::map<identification_document, int> Statistic_document() override
    {
        std::map<identification_document, int> map;
        for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
            map[(*iter)->getDocument()]++;
        return map;
    }

    std::map<transfer_declaration, int> Statistic_transfer() override
    {
        std::map<transfer_declaration, int> map;
        for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
            map[(*iter)->getTransfer()]++;
        return map;
    }

    std::map<category_of_taxpayer, int> Statistic_category() override
    {
        std::map<category_of_taxpayer, int> map;
        for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
            map[(*iter)->getCategory()]++;
        return map;
    }

    std::map<std::set<tax_types>, int> Statistic_types() override
    {
        std::map<std::set<tax_types>, int> map;
        for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
            map[(*iter)->getTaxName()]++;
        return map;
    }

    std::map<std::set<sources_of_income>, int> Statistic_income() override
    {
        std::map<std::set<sources_of_income>, int> map;
        for(auto iter = vector_forms.begin(); iter < vector_forms.end(); ++iter)
            map[(*iter)->getIncome()]++;
        return map;
    }
    ~Vector_Decorator() = default;
};