#include <iostream>
#include "Array_Interface.h"
#include "Vector_Interface.h"
#include "Work_with_user.h"
#include <ctime>
int main()
{
    int count = 100001, choice = 0;
    Decorator<Tax_Form>* collection = new Vector_Decorator<Tax_Form>();
    //Decorator<Tax_Form>* collection = new Array_Decorator<Tax_Form>();
    std::shared_ptr<Tax_Form> generate, tax_form;
    std::vector<std::shared_ptr<Tax_Form>> search;
    for (int i = 0; i < count; ++i)
    {
        generate = Tax_Form::create();
        collection->Add_Form(generate);
    }
    std::cout << "The collection contains " << collection->getSize() << " tax forms!\n";
    while(choice != 5)
    {
        Menu();
        std::cin >> choice;
        switch(choice)
        {
            case 1:
                tax_form = CreateForm();
                collection->Add_Form(std::shared_ptr<Tax_Form>(tax_form));
                std::cout << "New form was added, collection size now: " << collection->getSize()<< std::endl;
                break;
            case 2:
                try
                {
                    collection->Delete_Form();
                    std::cout << "\nCollection size now: " << collection->getSize() << std::endl;
                }
                catch(const char* ex)
                {
                    std::cerr << ex << '\n';
                }
                break;
            case 3:
                search = collection->Search_Form();
                if(!search.empty())
                {
                    for (auto iter: search)
                    {
                        iter->print();
                    }
                    std::cout << search.size() << " tax forms was found!\n";
                }
                else
                    std::cout << "There is no tax for with the specified value!\n";

                break;
            case 4:
                Work_Statistic(collection);
                break;
            case 5:
                std::cout << "See you soon!\n";
                break;
            default:
                std::cout << "No such case!\n";
        }
    }
    delete collection;
    return 0;
}