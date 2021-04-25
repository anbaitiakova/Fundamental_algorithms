#include "Binary_Tree.h"
#include <iostream>
#include <vector>
template<class T>
class AVL_Tree: public binary_tree<T>
{
    // there used inner function, which implements all logic
    // this is entrypoint for public overrided add function, which mocks p param to _root
    void inner_add(Node<T>** p, T&& k)// вставка ключа k в дерево с корнем root
    {
        if (*p == nullptr)
        {
            *p = new Node<T>(k);
            return;
        }
        // not ok, use constructor injected comparer
        int comparisonResult = this->_comparer->compare(k, (*p)->data);
        switch (comparisonResult)
        {
            case -1: // TODO: go to left subtree (if can)
                if ((*p)->leftSubtree == nullptr)
                {
                    (*p)->leftSubtree = new Node<T>(k);
                }
                else
                {
                    inner_add(&((*p)->leftSubtree), static_cast<T&&>(k));
                }
                break;
            case 1: // TODO: go to right subtree (if can)
                if ((*p)->rightSubtree == nullptr)
                {
                    (*p)->rightSubtree = new Node<T>(k);
                }
                else
                {
                    inner_add(&((*p)->rightSubtree), static_cast<T&&>(k));
                }
                break;
            case 0: // TODO: such value already exists
                return;
            default:
                break;
        }
        update_balance_factor_with_rebalance(p);
    }

    enum removing_statuses
    {
        no_grandson,
        one_left_grandson,
        one_right_grandson,
        nothing_to_do
    };

    removing_statuses inner_delete(Node<T>** p, T&& k)
    {
        if (!*p)
        {
            // TODO: throw an exception or do nothing (can't delete element because it's not contained in tree)
            return nothing_to_do;
        }
        int comparisonResult = this->_comparer->compare(k, (*p)->data);
        removing_statuses removeStatus;
        switch (comparisonResult)
        {
            case -1:
                // delete from left subtree
                // if subtree not exist, k not exist in tree (by injected comparer), in next recursive call an exception will be thrown
                removeStatus = inner_delete(&((*p)->leftSubtree), static_cast<T&&>(k));
                if (removeStatus == no_grandson)
                {
                    delete (*p)->leftSubtree;
                    (*p)->leftSubtree = nullptr;
                }
                else if (removeStatus == one_left_grandson)
                {
                    // TODO: reset pointer to grandson, delete it's parent and rebalance
                    Node<T>* childToRemove = (*p)->leftSubtree;
                    (*p)->leftSubtree = (*p)->leftSubtree->leftSubtree;
                    delete childToRemove;
                }
                else if (removeStatus == one_right_grandson)
                {
                    // TODO: reset pointer to grandson, delete it's parent and rebalance
                    Node<T>* childToRemove = (*p)->leftSubtree;
                    (*p)->leftSubtree = (*p)->leftSubtree->rightSubtree;
                    delete childToRemove;
                }
                break;
            case 1:
                // delete from right subtree
                // if subtree not exist, k not exist in tree (by injected comparer), in next recursive call an exception will be thrown
                removeStatus = inner_delete(&((*p)->rightSubtree), static_cast<T&&>(k));
                if (removeStatus == no_grandson)
                {
                    delete (*p)->rightSubtree;
                    (*p)->rightSubtree = nullptr;
                }
                if (removeStatus == one_left_grandson)
                {
                    // TODO: reset pointer to grandson, delete it's parent and rebalance
                    Node<T>* childToRemove = (*p)->rightSubtree;
                    (*p)->rightSubtree = (*p)->rightSubtree->leftSubtree;
                    delete childToRemove;
                }
                else if (removeStatus == one_right_grandson)
                {
                    // TODO: reset pointer to grandson, delete it's parent and rebalance
                    Node<T>* childToRemove = (*p)->rightSubtree;
                    (*p)->rightSubtree = (*p)->rightSubtree->rightSubtree;
                    delete childToRemove;
                }
                break;
            case 0:
                // found (by injected comparer) element to delete, there is main logic:
                Node<T>* leftSubtree = (*p)->leftSubtree;
                Node<T>* rightSubtree = (*p)->rightSubtree;

                if (leftSubtree == nullptr && rightSubtree == nullptr)
                {
                    // TODO: no children for removing element, remove reference to it from parent node
                    return no_grandson;
                }
                else if (leftSubtree == nullptr && rightSubtree != nullptr)
                {
                    // TODO: right child element should be added as child node for parent element
                    return one_right_grandson;
                }
                else if (leftSubtree != nullptr && rightSubtree == nullptr)
                {
                    // TODO: right child element should be added as child node for parent element
                    return one_left_grandson;
                }
                else
                {
                    // TODO: two children detected, find max (min) value in left (right) subtree,
                    // swap data and recursively delete from subtree
                    // after swap, there will be one of the cases below
                    Node<T>* max = find_max(leftSubtree);
                    std::swap(max->data, (*p)->data);
                    // TODO: recursively propagate to max subtree element
                    removeStatus = inner_delete(&((*p)->leftSubtree), static_cast<T&&>(k));
                    if (removeStatus == no_grandson)
                    {
                        delete (*p)->leftSubtree;
                        (*p)->leftSubtree = nullptr;
                    }
                    else if (removeStatus == one_left_grandson)
                    {
                        // TODO: reset pointer to grandson, delete it's parent and rebalance
                        Node<T>* childToRemove = (*p)->leftSubtree;
                        (*p)->leftSubtree = (*p)->leftSubtree->leftSubtree;
                        delete childToRemove;
                    }
                    else if (removeStatus == one_right_grandson)
                    {
                        // TODO: reset pointer to grandson, delete it's parent and rebalance
                        Node<T>* childToRemove = (*p)->leftSubtree;
                        (*p)->leftSubtree = (*p)->leftSubtree->rightSubtree;
                        delete childToRemove;
                    }
                }
        }
        update_balance_factor_with_rebalance(p);
        return nothing_to_do;
    }


    unsigned char height(Node<T>* p)
    {
        return p ? p->height : 0;
    }

    int balance_factor(Node<T>* p)
    {
        return height(p->rightSubtree) - height(p->leftSubtree);
    }

    void update_balance_factor(Node<T>* subtreeRoot) // update balance factor for current node
    {
        int hl = height(subtreeRoot->leftSubtree);
        int hr = height(subtreeRoot->rightSubtree);
        subtreeRoot->height = (hl > hr ? hl : hr) + 1;
    }

    void clockwise_rotation(Node<T>** parent) // clockwise rotation over parent->leftSubtree rib
    {
        Node<T>* subtree = (*parent)->leftSubtree;
        (*parent)->leftSubtree = subtree->rightSubtree;
        subtree->rightSubtree = *parent;
        update_balance_factor(*parent);
        update_balance_factor(subtree);
        *parent = subtree;
    }

    void counterclockwise_rotation(Node<T>** parent) // counter-clockwise rotation over parent->rightSubtree rib
    {
        Node<T>* subtree = (*parent)->rightSubtree;
        (*parent)->rightSubtree = subtree->leftSubtree;
        subtree->leftSubtree = *parent;
        update_balance_factor(*parent);
        update_balance_factor(subtree);
        *parent = subtree;
    }

    void update_balance_factor_with_rebalance(Node<T>** parent) // балансировка узла root
    {
        update_balance_factor(*parent);
        if (balance_factor(*parent) == 2)
        {
            if (balance_factor((*parent)->rightSubtree) < 0)
            {
                clockwise_rotation(&((*parent)->rightSubtree));
            }
            counterclockwise_rotation(parent);
        }
        else if (balance_factor(*parent) == -2)
        {
            if (balance_factor((*parent)->leftSubtree) > 0)
            {
                counterclockwise_rotation(&((*parent)->leftSubtree));
            }
            clockwise_rotation(parent);
        }
    }

    Node<T>* find_min(Node<T>* p)
    {
        return p->leftSubtree ? find_min(p->leftSubtree) : p;
    }

    Node<T>* find_max(Node<T>* p)
    {
        return p->rightSubtree ? find_max(p->rightSubtree) : p;
    }

    Node<T>* Remove_min(Node<T>* p) // удаление узла с минимальным ключом из дерева root
    {
        if (p->leftSubtree == 0)

            return p->rightSubtree;
        p->leftSubtree = Remove_min(p->leftSubtree);
        return Balance(p);
    }

    Node<T>* Remove_max(Node<T>* p) // удаление узла с максимальным ключом из дерева root
    {
        if(p->rightSubtree == 0)
            return p->leftSubtree;
        p->rightSubtree = Remove_max(p->rightSubtree);
        return Balance(p);
    }

    Node<T>* inner_search(Node<T>* root, T&& value)
    {
        if(root == nullptr)
            return nullptr;
        int comparisonResult;
        while (root)
        {
            comparisonResult = this->_comparer->compare(value, root->data);
            if (comparisonResult == -1)
            {
                root = root->leftSubtree;
                continue;
            }
            else if (comparisonResult == 1)
            {
                root = root->rightSubtree;
                continue;
            }
            else if (comparisonResult == 0)
                return root;
        }
        return nullptr;
    }

    void inner_print_tree(Node<T>* root, int level, std::ostream& stream) const
    {
        stream << std::endl;
        for (int i = 0; i < level; i++)
        {
            stream << '\t';
        }

        if (root == nullptr)
        {
            stream << "<null>";
            return;
        }
        stream << root->data;
        inner_print_tree(root->rightSubtree, level + 1, stream);
        inner_print_tree(root->leftSubtree, level + 1, stream);

    }

public:

    explicit AVL_Tree(Strategy<T>* comparer) : binary_tree<T>(comparer)
    {
        this->_root = nullptr;
    };

    void Add_Node(T&& k) override // вставка ключа k в дерево с корнем root
    {
        inner_add(&this->_root, static_cast<T&&>(k));
    }

    void Delete_Node(T&& k) override // удаление ключа k из дерева root
    {
        removing_statuses rem_st = inner_delete(&this->_root, static_cast<T&&>(k));
        if (rem_st == no_grandson)
        {
            delete(this->_root);
            this->_root = nullptr;
        }
    }

    Node<T>* Search_Node(T&& value) override
    {
        Node<T>* result;
        return (result = inner_search(this->_root, static_cast<T&&>(value)));
    }

    void print_tree(std::ostream& stream) const
    {
        inner_print_tree(this->_root, 0, stream);
    }

    void freeMemory(Node<T>* node)
    {
        if (node != nullptr)
        {
            freeMemory(node->leftSubtree);
            freeMemory(node->rightSubtree);
            delete node;
        }
        this->_root = nullptr;
    }

    ~AVL_Tree()
    {
        freeMemory(this->_root);
        delete(this->_comparer);
    }
};
