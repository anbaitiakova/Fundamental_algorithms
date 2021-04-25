#include <iostream>
//#include "AVL_Tree.h"
//#include "RedBlack_Tree.h"
#include "Relation.h"
#include <ctime>


int main()
{
    std::forward_list<int> forwardList = {10, 3, 4, 2, 6, 7};
    relation<int> Relation(forwardList);

    int AVLind = Relation.add_Index(AVL, new SomeStrategyExample());
    int RBind = Relation.add_Index(RB, new SomeStrategyExample());

    bool ksad = Relation.search_Data(10);

    Relation.delete_Data(2);
    Relation.delete_Index(RBind);
    Relation.delete_Index(AVLind);

    unsigned int num = 100000;
    unsigned int start_time =  clock();
    AVL_Tree<int> AVLtree(new SomeStrategyExample());
    srand((unsigned)time(NULL));
    for(int it = 0; it < num; it++)
    {
        AVLtree.Add_Node(static_cast<int&&>(rand() % 1000 + 1));
    }
    unsigned int end_time = clock();
    std::cout<<"Insert to AVL: "<<(end_time - start_time)/1000.0;
    start_time =  clock();
    AVLtree.Delete_Node(static_cast<int&&>(rand() % 1000 + 1));
    end_time = clock();
    std::cout<<"\nDelete from AVL: "<<(end_time - start_time)/1000.0;
    start_time =  clock();
    AVLtree.Search_Node(static_cast<int&&>(rand() % 1000 + 1));
    end_time = clock();
    std::cout<<"\nSearch in AVL: "<<(end_time - start_time)/1000.0;

   start_time =  clock();
    RB_Tree<int> RBtree(new SomeStrategyExample());
    srand((unsigned)time(NULL));
    for(int it = 0; it < num; it++)
    {
        RBtree.Add_Node(static_cast<int&&>(rand() % 1000 + 1));
    }
    end_time = clock();
    std::cout<<"\nInsert to RB: "<<(end_time - start_time)/1000.0;
    start_time =  clock();
    RBtree.Delete_Node(static_cast<int&&>(rand() % 1000 + 1));
    end_time = clock();
    std::cout<<"\nDelete from RB: "<<(end_time - start_time)/1000.0;
    start_time =  clock();
    RBtree.Search_Node(static_cast<int&&>(rand() % 1000 + 1));
    end_time = clock();
    std::cout<<"\nSearch in RB: "<<(end_time - start_time)/1000.0;

    return 0;
}


