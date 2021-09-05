#include "iostream"
#include "Tax_Reporting.h"
#include <vector>
#include <memory>

template<class T>
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual bool compare(const T& left, const T& right) const = 0;
};


class EconomicActivity_Strategy: public Strategy<std::shared_ptr<Tax_Form>>
{
public:
    bool compare(const std::shared_ptr<Tax_Form>& left, const std::shared_ptr<Tax_Form>& right) const override
    {
        if (left->CodeEconomicActivity == right->CodeEconomicActivity)
        {
            return true;
        }
        return false;
    }
};

class INN_Strategy: public Strategy<std::shared_ptr<Tax_Form>>
{
public:
    bool compare(const std::shared_ptr<Tax_Form>& left, const std::shared_ptr<Tax_Form>& right) const override
    {
        if (left->INN == right->INN)
        {
            return true;
        }
        return false;
    }
};

class OrganizationName_Strategy: public Strategy<std::shared_ptr<Tax_Form>>
{
public:
    bool compare(const std::shared_ptr<Tax_Form>& left, const std::shared_ptr<Tax_Form>& right) const override
    {
        if (left->OrganizationName == right->OrganizationName)
        {
            return true;
        }
        return false;
    }
};

class ReportingYear_Strategy: public Strategy<std::shared_ptr<Tax_Form>>
{
    bool compare(const std::shared_ptr<Tax_Form>& left, const std::shared_ptr<Tax_Form>& right) const override
    {
        if (left->ReportingYear == right->ReportingYear)
        {
            return true;
        }
        return false;
    }
};

class TaxPeriod_Strategy: public Strategy<std::shared_ptr<Tax_Form>>
{
    bool compare(const std::shared_ptr<Tax_Form>& left, const std::shared_ptr<Tax_Form>& right) const override
    {
        if (left->TaxPeriod == right->TaxPeriod)
        {
            return true;
        }
        return false;
    }
};

static std::shared_ptr<Tax_Form> FormDelete()
{
    Tax_Form *tmp = new Tax_Form;
    std::cout << "Fof deleting a specific form, enter INN: ";
    tmp->set_inn();
    return std::shared_ptr<Tax_Form>(tmp);
}

static std::shared_ptr<Tax_Form> FormForWork(Strategy<std::shared_ptr<Tax_Form>>** Strategy)
{
    Tax_Form* tmp = new Tax_Form;
    int n;
    std::cout << "What criteria do you want to search by:\n 1. Code of economic activity;\n 2. INN;\n 3. Organization name;\n "
                 "4. Reporting year;\n 5. Tax reporting period.\n -> ";
    std::cin >> n;
    switch(n)
    {
        case 1:
            std::cout << "Enter code of economic activity (1-99): ";
            tmp->set_economic_activity();
            *Strategy = new EconomicActivity_Strategy();
            break;

        case 2:
            std::cout << "Enter INN (10 digits): ";
            tmp->set_inn();
            *Strategy = new INN_Strategy();
            break;

        case 3:
            std::cout << "Enter organization name: ";
            tmp->set_org_name();
            *Strategy = new OrganizationName_Strategy();
            break;

        case 4:
            std::cout << "Enter the reporting year: ";
            tmp->set_rep_year();
            *Strategy = new ReportingYear_Strategy();
            break;

        case 5:
            std::cout << "Tax reporting period:\n0 - year;\n 1 - month;\n 2 - quarter;\n 3 - half_year;\n 4 - nine_months;\n 5 - other_period:\n-> ";
            tmp->set_tax_period();
            *Strategy = new TaxPeriod_Strategy();
            break;

    }
    return std::shared_ptr<Tax_Form>(tmp);
}

template<class TargetType>
class Decorator
{
public:
    virtual void Add_Form(const std::shared_ptr<TargetType>& Form) = 0;
    virtual void Delete_Form() = 0;
    virtual int getSize() = 0;
    virtual std::vector<std::shared_ptr<TargetType>> Search_Form() = 0;
    virtual std::map<unsigned int, int> Statistic_uint(size_t choice) = 0;
    virtual std::map<unsigned long long int, int> Statistic_long() = 0;
    virtual std::map<unsigned short, int> Statistic_short(size_t choice) = 0;
    virtual std::map<std::string, int> Statistic_string(size_t choice) = 0;
    virtual std::map<tax_period, int> Statistic_period() = 0;
    virtual std::map<identification_document, int> Statistic_document() = 0;
    virtual std::map<transfer_declaration, int> Statistic_transfer() = 0;
    virtual std::map<category_of_taxpayer, int> Statistic_category() = 0;
    virtual std::map<std::set<tax_types>, int> Statistic_types() = 0;
    virtual std::map<std::set<sources_of_income>, int> Statistic_income() = 0;
    virtual ~Decorator() = default;
};