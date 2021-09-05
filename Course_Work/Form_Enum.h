enum tax_period
{
    year,
    month,
    quarter,//квартал
    half_year,
    nine_months,
    other_period
};

enum tax_types//виды налогов
{
    personal_income,//доход физических лиц
    profit_of_organization,//прибыль организации
    vat,//НДС
    excise_taxes,//акцизы
    organization_property,//на имущество организации
    property_individuals,//на имущество физических лиц
    extraction_of_minerals,//добыча полезных ископаемых
    water_tax//водный налог
};

enum transfer_declaration//способ передачи налоговой формы
{
    personal,
    by_post,
    courier,
    by_trustee//через доверенное лицо
};

enum category_of_taxpayer
{
    largest,
    primary,
    other
};

enum identification_document
{
    passport,
    international_passport,
    birth_certificate,
    military_certificate//удостоверение военнослужащего
};

enum sources_of_income
{
    salary,
    self_employment,//самозанятость
    patent_revenue,//доход от патентов
    rental_of_property,//сдача имущества в аренду
    pension,
    savings_dividends,//сбережения, диведенды
    realisation_of_capital,//реализация капитала
    other_payouts,//другие выплаты
    dependency,//иждивение
    benefits//льготы
};

std::string period(tax_period tmp)
{
    std::string result;
    if(tmp == year)
        result = "Year";
    else if(tmp == month)
        result = "Month";
    else if(tmp == quarter)
        result = "3 months";
    else if(tmp == half_year)
        result = "6 months";
    else if(tmp == nine_months)
        result = "9 months";
    else if(tmp == other_period)
        result = "Other";
    return result;
}

std::istream& operator>>(std::istream& is, tax_period& t)
{
    std::string s;
    is >> s;
    if (s == "0") t = tax_period::year;
    else if (s == "1") t = tax_period::month;
    else if (s == "2") t = tax_period::quarter;
    else if (s == "3") t = tax_period::half_year;
    else if (s == "4") t = tax_period::nine_months;
    else if (s == "5") t = tax_period::other_period;
    return is;
}

std::string types(tax_types tmp)
{
    std::string result;
    if(tmp == personal_income)
        result = "Personal income tax";
    else if(tmp == profit_of_organization)
        result = "Corporate income tax";
    else if(tmp == vat)
        result = "VAT";
    else if(tmp == excise_taxes)
        result = "Excise taxes";
    else if(tmp == organization_property)
        result = "Corporate property tax";
    else if(tmp == property_individuals)
        result = "Personal property tax";
    else if(tmp == extraction_of_minerals)
        result = "Mineral Extraction tax";
    else if(tmp == water_tax)
        result = "Water tax";
    return result;
}

std::set<tax_types>& operator>>(std::istream& is, std::set<tax_types>& t)
{
    int n;
    std::cout << "How many taxes (1-8): ";
    is >> n;
    std::string s;
    for(int i = 0; i < n; ++i)
    {
        is >> s;
        if (s == "0") t.insert(tax_types::personal_income);
        else if (s == "1") t.insert(tax_types::profit_of_organization);
        else if (s == "2") t.insert(tax_types::vat);
        else if (s == "3") t.insert(tax_types::excise_taxes);
        else if (s == "4") t.insert(tax_types::organization_property);
        else if (s == "5") t.insert(tax_types::property_individuals);
        else if (s == "6") t.insert(tax_types::extraction_of_minerals);
        else if (s == "7") t.insert(tax_types::water_tax);
    }
    return t;
}

std::string transfer(transfer_declaration tmp)
{
    std::string result;
    if (tmp == personal)
        result = "Personal";
    else if(tmp == by_post)
        result = "By post";
    else if(tmp == courier)
        result = "By courier";
    else if(tmp == by_trustee)
        result = "By trustee";
    return result;
}

std::istream& operator>>(std::istream& is, transfer_declaration& t)
{
    std::string s;
    is >> s;
    if (s == "0") t = transfer_declaration::personal;
    else if (s == "1") t = transfer_declaration::by_post;
    else if (s == "2") t = transfer_declaration::courier;
    else if (s == "3") t = transfer_declaration::by_trustee;
    return is;
}

std::string category(category_of_taxpayer tmp)
{
    std::string result;
    if(tmp == largest)
        result = "Largest";
    else if(tmp == primary)
        result = "Primary";
    else if(tmp == other)
        result = "Other";
    return result;
}

std::istream& operator>>(std::istream& is, category_of_taxpayer& t)
{
    std::string s;
    is >> s;
    if (s == "0") t = category_of_taxpayer::largest;
    else if (s == "1") t = category_of_taxpayer::primary;
    else if (s == "2") t = category_of_taxpayer::other;
    return is;
}

std::string document(identification_document tmp)
{
    std::string result;
    if (tmp == passport)
        result = "Passport";
    else if(tmp == international_passport)
        result = "International Passport";
    else if(tmp == birth_certificate)
        result = "Birth Certificate";
    else if(tmp == military_certificate)
        result = "Military Certificate";
    return result;
}

std::istream& operator>>(std::istream& is, identification_document& t)
{
    std::string s;
    is >> s;
    if (s == "0") t = identification_document::passport;
    else if (s == "1") t = identification_document::international_passport;
    else if (s == "2") t = identification_document::birth_certificate;
    else if (s == "3") t = identification_document::military_certificate;
    return is;
}

std::string sources(sources_of_income tmp)
{
    std::string result;
    if (tmp == salary)
        result = "Salary";
    else if (tmp == self_employment)
        result = "Self-employment";
    else if (tmp == patent_revenue)
        result = "Patent revenue";
    else if (tmp == rental_of_property)
        result = "Rental of property";
    else if (tmp == pension)
        result = "Pension";
    else if (tmp == savings_dividends)
        result = "Dividends";
    else if (tmp == realisation_of_capital)
        result = "Realisation of capital";
    else if (tmp == other_payouts)
        result = "Other payouts";
    else if (tmp == dependency)
        result = "Dependency";
    else if (tmp == benefits)
        result = "Benefits";
    return result;
}

std::set<sources_of_income>& operator>>(std::istream& is, std::set<sources_of_income>& t)
{
    int n;
    std::cout << "How many sources of income (1-10): ";
    is >> n;
    std::string s;
    for (int i = 0; i < n; ++i)
    {
        is >> s;
        if (s == "0") t.insert(sources_of_income::salary);
        else if (s == "1") t.insert(sources_of_income::self_employment);
        else if (s == "2") t.insert(sources_of_income::patent_revenue);
        else if (s == "3") t.insert(sources_of_income::rental_of_property);
        else if (s == "4") t.insert(sources_of_income::pension);
        else if (s == "5") t.insert(sources_of_income::savings_dividends);
        else if (s == "6") t.insert(sources_of_income::realisation_of_capital);
        else if (s == "7") t.insert(sources_of_income::other_payouts);
        else if (s == "8") t.insert(sources_of_income::dependency);
        else if (s == "9") t.insert(sources_of_income::benefits);
    }
    return t;
}