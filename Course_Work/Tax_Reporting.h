#include <iostream>
#include <set>
#include <climits>
#include <random>
#include "Form_Enum.h"
#include <cstdlib>
#include <memory>
#include <map>

class Tax_Form
{
    unsigned long long int INN;
    unsigned int KPP;//Код причины постановки на учет
    unsigned short ReportingYear;//Отчетный год
    std::string TaxAuthority;
    unsigned short CodeTaxAuthority;
    std::string OrganizationName;
    unsigned int CodeOKATO;//Код ОКТМО
    unsigned short CodeEconomicActivity;//Код вида экономической деятельности
    std::set<tax_types> TaxName;//Наименование налога
    tax_period TaxPeriod;
    unsigned int TaxAmount;
    std::string TaxpayerFullName;
    std::string DateOfBirth;
    std::string PhoneNumber;
    std::string Citizenship;
    std::string PlaceOfResidence;
    identification_document PersonalDocument;
    std::set<sources_of_income> IncomeSources;
    transfer_declaration TransferDeclaration;
    category_of_taxpayer CategoryTaxpayer;
    std::string Date;

public:
    unsigned long long int getINN() const { return INN; }
    unsigned int getKPP() const { return KPP; }
    unsigned short getReportingYear() const { return ReportingYear; }
    std::string getTaxAuthority() const {return TaxAuthority; }
    unsigned short getCodeTaxAuthority() const { return CodeTaxAuthority; }
    std::string getOrganizationName() const { return OrganizationName; }
    unsigned int getCodeOKATO() const { return CodeOKATO; }
    unsigned short getCodeEcActivity() const { return CodeEconomicActivity; }
    std::set<tax_types> getTaxName() const { return TaxName; }
    tax_period getTaxPeriod() const { return TaxPeriod; }
    unsigned int getTaxAmount() const { return TaxAmount; }
    std::string getFIO() const { return TaxpayerFullName; }
    std::string getDateBirth() const { return DateOfBirth; }
    std::string getPhoneNumber() const { return PhoneNumber; }
    std::string getCitizenship() const { return Citizenship; }
    std::string getResidence() const {return PlaceOfResidence; }
    identification_document getDocument() const { return PersonalDocument; }
    std::set<sources_of_income> getIncome() const { return IncomeSources; }
    transfer_declaration getTransfer() const { return TransferDeclaration; }
    category_of_taxpayer getCategory() const { return CategoryTaxpayer; }
    std::string getDate() const { return Date; }

private:
    static unsigned long long int Generate_INN()
    {
        unsigned long long int min, max, result;
        min = 1000000000;
        max = 9999999999;
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned long long int> distribution(min, max);
        result = distribution(generator);
        return result;
    }

    static unsigned int Generate_big_number(int n)
    {
        unsigned long long int min, max, result;
        if(n == 9)
        {
            min = 100000000;
            max = 999999999;
        }
        else if(n == 8)
        {
            min = 10000000;
            max = 99999999;
        }
        else
        {
            min = 1000;
            max = 9000000;
        }
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(min, max);
        result = distribution(generator);
        return result;
    }

    static unsigned short Generate_small_number(int n)
    {
        unsigned int min, max, result;
        if(n == 2)
        {
            min = 1;
            max = 99;
        }
        else if (n == 4)
        {
            min = 1980;
            max = 2021;
        }
        else
        {
            min = 1000;
            max = 9999;
        }
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(min, max);
        result = distribution(generator);
        return result;
    }

    static tax_period Period()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 5);
        auto tmp = static_cast<tax_period>(distribution(generator));
        return tmp;
    }

    static identification_document Document()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 3);
        auto doc = static_cast<identification_document>(distribution(generator));
        return doc;
    }

    static transfer_declaration Transfer()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 3);
        auto dec = static_cast<transfer_declaration>(distribution(generator));
        return dec;
    }

    static category_of_taxpayer Taxpayer()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(0, 2);
        auto category = static_cast<category_of_taxpayer>(distribution(generator));
        return category;
    }

    static std::set<tax_types> Types()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(1, 6);
        int num = distribution(generator);
        std::set<tax_types> set;
        std::uniform_int_distribution<unsigned int> distribution2(0, 7);
        for (int i = 0; i < num; i++)
        {
            set.insert(static_cast<tax_types>(distribution2(generator)));
        }
        return set;
    }

    static std::set<sources_of_income> Income()
    {
        static std::random_device rd;
        std::default_random_engine generator(rd());
        std::uniform_int_distribution<unsigned int> distribution(1, 7);
        int num = distribution(generator);
        std::set<sources_of_income> set;
        std::uniform_int_distribution<unsigned int> distribution2(0, 9);
        for (int i = 0; i < num; i++)
        {
            set.insert(static_cast<sources_of_income>(distribution2(generator)));
        }
        return set;
    }

    static std::string Generate_string(bool flag)
    {
        int num;
        std::string vowels = "aeioyu";
        std::string consonants = "bcdfghjklmnpqrstvwxz";
        std::string result;
        srand(time(0));
        if(flag)
            num = rand() % 11 + 8;
        else
            num = rand() % 11 + 4;
        static std::random_device rd;
        std::default_random_engine generator(rd());
        for(int i = 0; i < num; i++)
        {
            if((i % 2) == 0)
            {
                std::uniform_int_distribution<int> distribution(0, consonants.size() - 1);
                result += consonants[distribution(generator)];
            }
            else
            {
                std::uniform_int_distribution<int> distribution(0, vowels.size() - 1);
                result += vowels[distribution(generator)];
            }
        }
        result[0] = std::toupper(result[0]);
        return result;
    }

    static std::string Generate_time(bool flag, unsigned short year)
    {
        std::string result_time;
        unsigned short tmp_day, tmp_month, tmp_year, birthday;
        static std::random_device rd;
        std::uniform_int_distribution<unsigned short> distribution(1, 30);
        std::default_random_engine generator(rd());
        tmp_day = distribution(generator);
        if(tmp_day < 10)
            result_time = "0" + std::to_string(tmp_day) + '.';
        else result_time = std::to_string(tmp_day) + '.';
        std::uniform_int_distribution<unsigned short> distribution2(1, 12);
        tmp_month = distribution2(generator);
        if(tmp_month < 10)
            result_time += "0" + std::to_string(tmp_month) + '.';
        else result_time += std::to_string(tmp_month) + '.';
        if(flag)
        {
            tmp_year = rand() % 2 + year;
            result_time += std::to_string(tmp_year);
        }
        else
        {
            birthday = year - 16;
            tmp_year = rand() % (birthday - 1940 + 1) + 1940;
            result_time += std::to_string(tmp_year);
        }
        return result_time;
    }

public:
    static std::shared_ptr<Tax_Form> create()
    {
        Tax_Form* tax = new Tax_Form;
        tax->INN = Generate_INN();
        tax->KPP = Generate_big_number(9);
        tax->ReportingYear = Generate_small_number(4);
        tax->TaxAuthority = Generate_string(true) + ' ' + Generate_string(true);
        tax->CodeTaxAuthority = Generate_small_number(0);
        tax->OrganizationName = Generate_string(true);
        tax->CodeOKATO = Generate_big_number(8);
        tax->CodeEconomicActivity = Generate_small_number(2);
        tax->TaxName = Types();
        tax->TaxPeriod = Period();
        tax->TaxAmount = Generate_big_number(0);
        tax->TaxpayerFullName = Generate_string(false) + ' ' + Generate_string(false) + ' ' + Generate_string(false);
        tax->DateOfBirth = Generate_time(false, tax->ReportingYear);
        tax->PhoneNumber = "+79" + std::to_string(Generate_big_number(9));
        tax->Citizenship = Generate_string(false);
        tax->PlaceOfResidence = Generate_string(false) + ' ' + Generate_string(true);//space
        tax->PersonalDocument = Document();
        tax->IncomeSources = Income();
        tax->TransferDeclaration = Transfer();
        tax->CategoryTaxpayer = Taxpayer();
        tax->Date = Generate_time(true, tax->ReportingYear);
        return std::shared_ptr<Tax_Form>(tax);
    }

    void print()
    {
        std::cout << "INN: " << INN << std::endl;
        std::cout << "KPP: " << KPP << "      \t";
        std::cout << "Reporting year: " << ReportingYear << std::endl;
        std::cout << "Tax authority: " << TaxAuthority << "      \t";
        std::cout << "Code: " << CodeTaxAuthority << std::endl;
        std::cout << "Organization Name: " << OrganizationName << "      \t";
        std::cout << "Code OKATO: " << CodeOKATO << std::endl;
        std::cout << "Code of the type of economic activity: " << CodeEconomicActivity << std::endl;
        std::cout << "Name of Taxes: ";
        for(auto iter: TaxName)
        {
            std::cout << "<" << types(iter) << ">  ";
        }
        std::cout << std::endl;
        std::cout << "Tax reporting period: " << period(TaxPeriod) << "\n";
        std::cout << "Tax amount: " << TaxAmount << std::endl;
        std::cout << "Taxpayer full name: " << TaxpayerFullName << "       \t";
        std::cout << "Date of birth: " << DateOfBirth << std::endl;
        std::cout << "Personal identification document: " << document(PersonalDocument) << std::endl;
        std::cout << "Citezenship: " << Citizenship << "      \t";
        std::cout << "Place of residence: " << PlaceOfResidence <<std::endl;
        std::cout << "Phone number: " << PhoneNumber << std::endl;
        std::cout << "Sources of income: ";
        for(auto iter: IncomeSources)
        {
            std::cout << "<" << sources(iter) << ">  ";
        }
        std::cout << std::endl;
        std::cout << "This declaration is submitted: " << transfer(TransferDeclaration) << "       \t";
        std::cout << "Taxpayer category: " << category(CategoryTaxpayer) << std::endl;
        std::cout << "Date: " << Date << std::endl;
        std::cout << std::endl << std::endl;
    }
public:
    bool operator==(const Tax_Form& form)
    {
        if(INN == form.INN && KPP == form.KPP && ReportingYear == form.ReportingYear && TaxAuthority == form.TaxAuthority
            && CodeTaxAuthority == form.CodeTaxAuthority && OrganizationName == form.OrganizationName
            && CodeOKATO == form.CodeOKATO && CodeEconomicActivity == form.CodeEconomicActivity && TaxName == form.TaxName
            && TaxPeriod == form.TaxPeriod && TaxAmount == form.TaxAmount && TaxpayerFullName == form.TaxpayerFullName
            && DateOfBirth == form.DateOfBirth && PhoneNumber == form.PhoneNumber && Citizenship == form.Citizenship
            && PlaceOfResidence == form.PlaceOfResidence && IncomeSources == form.IncomeSources && Date == form.Date
            && TransferDeclaration == form.TransferDeclaration && CategoryTaxpayer == form.CategoryTaxpayer)
            return true;
        else
            return false;
    }

    friend std::ostream& operator>>(std::istream &in, Tax_Form& tax)
    {
        int n;
        std::cout << "Enter INN (10 digits): ";
        in >> tax.INN;
        std::cout << "Enter KPP (9 digits): ";
        in >> tax.KPP;
        std::cout << "Enter reporting year: ";
        in >> tax.ReportingYear;
        std::cout << "Enter tax authority: ";
        in.ignore();
        getline(in, tax.TaxAuthority);
        std::cout << "Enter code of tax authority (4 digits): ";
        in >> tax.CodeTaxAuthority;
        std::cout << "Organization Name: ";
        in.ignore();
        getline(in, tax.OrganizationName);
        std::cout << "Code OKATO (8 digits): ";
        in >> tax.CodeOKATO;
        std::cout << "Code of the type of economic activity (1-99): ";
        in >> tax.CodeEconomicActivity;
        std::cout << "Name of Taxes:\n"
                     " 0 - personal_income;\n 1 - profit_of_organization;\n"
                     " 2 - vat;\n 3- excise_taxes;\n 4 - organization_property;\n"
                     " 5 - property_individuals;\n 6 - extraction_of_minerals;\n"
                     " 7 - water_tax\n ";
        in >> tax.TaxName;

        std::cout << "Tax reporting period:\n 0 - year;\n 1 - month;\n 2 - quarter;\n 3 - half_year;\n "
                     "4 - nine_months;\n 5 - other_period\n-> ";
        in >> tax.TaxPeriod;
        std::cout << "Tax amount: ";
        in >> tax.TaxAmount;
        std::cout << "Taxpayer full name: ";
        in.ignore();
        getline(in, tax.TaxpayerFullName);
        std::cout << "Taxpayer date of birth (dd.mm.yyyy): ";
        in >> tax.DateOfBirth;
        std::cout << "Personal identification documen:\n 0 - passport;\n 1 - international_passport;\n "
                     "2 - birth_certificate;\n 3 - military_certificate\n-> ";
        in >> tax.PersonalDocument;
        std::cout << "Citezenship: ";
        in.ignore();
        getline(in, tax.Citizenship);
        std::cout << "Place of residence: ";
        in.ignore();
        getline(in, tax.PlaceOfResidence);
        std::cout << "Phone number (+79*********): ";
        in >> tax.PhoneNumber;
        std::cout << "Sources of income:\n"
                     " 0 - salary;\n 1 - self_employment;\n"
                     " 2 - patent_revenue;\n 3 - rental_of_property;\n"
                     " 4 - pension;\n 5 - savings_dividends;\n"
                     " 6 - realisation_of_capital;\n 7 - other_payouts;\n"
                     " 8 - dependency;\n 9 - benefits\n";
        in >> tax.IncomeSources;
        std::cout << "This declaration is submitted:\n 0 - personal;\n 1 - by_post;\n 2 - courier;\n 3 - by_trustee\n-> ";
        in >> tax.TransferDeclaration;
        std::cout << "Taxpayer category:\n 0 - largest;\n 1 - primary;\n 2 - other\n-> ";
        in >> tax.CategoryTaxpayer;
        std::cout << "Date (dd.mm.yyyy): ";
        in >> tax.Date;
    }

    void set_economic_activity()
    {
        std::cin >> this->CodeEconomicActivity;
    };

    void set_inn()
    {
        std::cin >> this->INN;
    };

    void set_org_name()
    {
        std::cin >> this->OrganizationName;
    };

    void set_rep_year()
    {
        std::cin >> this->ReportingYear;
    };

    void set_tax_period()
    {
        std::cin >> this->TaxPeriod;
    };

    friend class EconomicActivity_Strategy;
    friend class INN_Strategy;
    friend class OrganizationName_Strategy;
    friend class ReportingYear_Strategy;
    friend class TaxPeriod_Strategy;
};