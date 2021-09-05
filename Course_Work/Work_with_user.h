std::shared_ptr<Tax_Form> CreateForm()
{
    Tax_Form* tmp = new Tax_Form;
    std::cin >> *tmp;
    return std::shared_ptr<Tax_Form>(tmp);
}

void Menu()
{
    std::cout << "\nWhat do you want to do next?\n"
                 "1. Add tax form;\n"
                 "2. Delete tax form by INN;\n"
                 "3. Search form by one field;\n"
                 "4. Show statistic;\n"
                 "5. Exit.\n"
                 "-> ";
}

void StatisticMenu()
{
    std::cout << "Select a field on the tax form to display statistics: \n"
                 "1. INN; \n" "2. KPP; \n"
                 "3. Reporting year; \n" "4. Tax authority; \n"
                 "5. Code of tax authority;\n" "6. Organization Name;\n"
                 "7. Code OKATO;\n" "8. Code of the type of economic activity;\n"
                 "9. Tax reporting period;\n" "10. Tax amount:\n"
                 "11. Taxpayer full name;\n" "12. Date of birth;\n"
                 "13. Personal identification document;\n" "14. Citezenship:\n"
                 "15. Place of residence;\n" "16. Phone number;\n"
                 "17. Way of declaration transfer;\n" "18. Taxpayer category;\n"
                 "19. Name of taxes; \n" "20. Sources of income; \n" "21. Date:\n"
                 "-> " ;
}

void Work_Statistic(Decorator<Tax_Form>* container)
{
    size_t choice;
    std::map<unsigned int, int> map_uint;
    std::map<unsigned long long int, int> map_long;
    std::map<unsigned short, int> map_short;
    std::map<std::string, int> map_string;
    std::map<tax_period, int> map_period;
    std::map<identification_document, int> map_document;
    std::map<transfer_declaration, int> map_transfer;
    std::map<category_of_taxpayer, int> map_category;
    std::map<std::set<tax_types>, int> map_set_types;
    std::map<std::set<sources_of_income>, int> map_set_income;
    StatisticMenu();
    std::cin >> choice;
    switch(choice)
    {
        case 1:
            map_long = container->Statistic_long();
            for(auto iter: map_long)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 2:
            map_uint = container->Statistic_uint(1);
            for(auto iter: map_uint)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 3:
            map_short = container->Statistic_short(1);
            for(auto iter: map_short)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 4:
            map_string = container->Statistic_string(1);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 5:
            map_short = container->Statistic_short(2);
            for(auto iter: map_short)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 6:
            map_string = container->Statistic_string(2);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 7:
            map_uint = container->Statistic_uint(2);
            for(auto iter: map_uint)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 8:
            map_short = container->Statistic_short(3);
            for(auto iter: map_short)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 9:
            map_period = container->Statistic_period();
            for(auto iter: map_period)
                std::cout << period(iter.first) << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 10:
            map_uint = container->Statistic_uint(3);
            for(auto iter: map_uint)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 11:
            map_string = container->Statistic_string(3);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 12:
            map_string = container->Statistic_string(4);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 13:
            map_document = container->Statistic_document();
            for(auto iter: map_document)
                std::cout << document(iter.first) << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 14:
            map_string = container->Statistic_string(6);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 15:
            map_string = container->Statistic_string(7);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 16:
            map_string = container->Statistic_string(5);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 17:
            map_transfer = container->Statistic_transfer();
            for(auto iter: map_transfer)
                std::cout << transfer(iter.first) << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 18:
            map_category = container->Statistic_category();
            for(auto iter: map_category)
                std::cout << category(iter.first) << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
        case 19:
            map_set_types = container->Statistic_types();
            for(auto iter: map_set_types)
            {
                for(auto it: iter.first)
                {
                    std::cout << "<" << types(it) << ">";
                }
                std::cout << std::endl <<"ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;

            }
            break;
        case 20:
            map_set_income = container->Statistic_income();
            for(auto iter: map_set_income)
            {
                for(auto it: iter.first)
                {
                    std::cout << "<" << sources(it) << ">";
                }
                std::cout << std::endl <<"ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;

            }
            break;
        case 21:
            map_string = container->Statistic_string(8);
            for(auto iter: map_string)
                std::cout << iter.first << ": ABSOLUTE = " << iter.second << "; RELATIVE = " << (double)iter.second / (double)container->getSize() << std::endl;
            break;
    }
}