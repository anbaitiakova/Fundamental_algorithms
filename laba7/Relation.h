#include "AVL_Tree.h"
#include "RedBlack_Tree.h"
#include <forward_list>
#include <map>
#include <iterator>

enum what_tree
{
    AVL,
    RB
};
template <typename T>
class relation
{
private:
    std::forward_list<T> list_data;
    std::map<int, binary_tree<T>*> map_with_index;

public:
    relation(){};

    relation(const std::forward_list<T>& _dataList)
    {
        list_data = _dataList;
    }

    void New_Flist(const std::forward_list<T>& forwardList)
    {
        if (!list_data.empty())
        {
            list_data.clear();
        }
        for(auto iter: forwardList)
        {
            add_Data(static_cast<T&&>(iter));
        }
    }

    void add_Data(T&& data)
    {
        list_data.push_front(data);
        for (auto iter: map_with_index)
            iter.second->Add_Node(static_cast<T&&>(data));
    }

    void delete_Data(T&& data)
    {
        for(auto item : list_data)
        {
            if (item == data)
            {
                list_data.remove(data);
                for (auto item : map_with_index)
                    item.second->Delete_Node(static_cast<T&&>(data));
                return;
            }
        }
        throw std::invalid_argument("There is no such value!");
    }


    int add_Index(what_tree type, Strategy<T>* comparer)
    {
        int uniq_ind = rand();
        binary_tree<T>* binaryTree;
        for (auto item: map_with_index)
        {
            if (item.first == uniq_ind)
            {
                uniq_ind = rand();
            }
        }
        if (type == AVL)
            binaryTree = new AVL_Tree<T>(comparer);
        else if (type == RB)
            binaryTree = new RB_Tree<T>(comparer);
        else
            throw std::invalid_argument("There is no such kind of tree!");

        map_with_index.insert(std::make_pair(uniq_ind, binaryTree));
        for (auto item : list_data)
            (*binaryTree).Add_Node(static_cast<T&&>(item));
        return uniq_ind;
    }

    bool delete_Index(int index)
    {
        for(auto item: map_with_index)
        {
            if(index == item.first)
            {
                delete(map_with_index[index]);
                map_with_index.erase(index);
                return true;
            }
        }
        return false;
    }

    std::vector<bool> search_Data(T&& data)
    {
        std::vector<bool> vector;
        for (auto iter : map_with_index)
        {
            Node<T>* search;
            search = iter.second->Search_Node(static_cast<T&&>(data));
            if (search != nullptr)
                vector.push_back(true);
            else
                vector.push_back(true);
        }
        return vector;
    }

    ~relation()
    {
        for(std::pair<int, binary_tree<T>*> item: map_with_index)
        {
            delete(item.second);
        }
    };
};