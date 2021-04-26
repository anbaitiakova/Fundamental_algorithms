#include <iostream>
#include <vector>
template<class T>
class RB_Tree: public binary_tree<T>
{
private:
    enum insert_statuses
    {
        inserted_as_left_child,
        inserted_as_right_child,
        uncle_black_now,
        nothing_to_do,
        already_exist
    };

    insert_statuses inner_add(Node<T>** subtreeRoot, T&& data)
    {
        insert_statuses insertStatus;

        if (*subtreeRoot == nullptr)
        {
            *subtreeRoot = new Node<T>(data);
            (*subtreeRoot)->color = BLACK;
            return nothing_to_do;
        }

        int comparisonResult = this->_comparer->compare(data, (*subtreeRoot)->data);

        switch (comparisonResult)
        {
            case 0:
                return already_exist;
            case -1:
                if ((*subtreeRoot)->leftSubtree == nullptr)
                {
                    (*subtreeRoot)->leftSubtree = new Node<T>(data);
                    return inserted_as_left_child;
                }
                else
                {
                    insertStatus = inner_add(&((*subtreeRoot)->leftSubtree), static_cast<T&&>(data));
                    if (insertStatus == inserted_as_left_child) {
                        // 1. if parent is black, all is ok.
                        if ((*subtreeRoot)->leftSubtree->color == BLACK) {
                            return nothing_to_do;
                        }
                        // 2. parent is red, then grandparent is black and exists
                        // 2.1. uncle not exist: uncle is sentinel and then it's black
                        if ((*subtreeRoot)->rightSubtree == nullptr ||
                            (*subtreeRoot)->rightSubtree->color == BLACK)
                        {
                            rotateRight(subtreeRoot);
                            (*subtreeRoot)->rightSubtree->color = RED;
                            (*subtreeRoot)->color = BLACK;
                            return nothing_to_do;
                        }
                        // 2.2. uncle is red: repaint parent, uncle and grandfather and all is ok
                        else if ((*subtreeRoot)->rightSubtree->color == RED)
                        {
                            (*subtreeRoot)->leftSubtree->color = BLACK;
                            (*subtreeRoot)->rightSubtree->color = BLACK;
                            (*subtreeRoot)->color = RED;
                            return uncle_black_now;
                        }
                    }
                    else if (insertStatus == inserted_as_right_child)
                    {
                        // 1. if parent is black, all is ok.
                        if ((*subtreeRoot)->leftSubtree->color == BLACK) {
                            return nothing_to_do;
                        }
                        // 2. parent is red, then grandparent is black and exists
                        // 2.1. uncle not exist: uncle is sentinel and then it's black
                        if ((*subtreeRoot)->rightSubtree == nullptr ||
                            (*subtreeRoot)->rightSubtree->color == BLACK)
                        {
                            rotateLeft(&(*subtreeRoot)->leftSubtree);
                            rotateRight(subtreeRoot);
                            (*subtreeRoot)->rightSubtree->color = RED;
                            (*subtreeRoot)->color = BLACK;
                            return nothing_to_do;
                        }
                            // 2.2. uncle is red: repaint parent, uncle and grandfather and all is ok
                        else if ((*subtreeRoot)->rightSubtree->color == RED)
                        {
                            (*subtreeRoot)->leftSubtree->color = BLACK;
                            (*subtreeRoot)->rightSubtree->color = BLACK;
                            (*subtreeRoot)->color = RED;
                            return uncle_black_now;
                        }
                    }
                    else if (insertStatus == uncle_black_now)
                    {
                        if ((*subtreeRoot)->color == BLACK)
                        {
                            return nothing_to_do;
                        }
                        return inserted_as_left_child;
                    }
                    else
                    {
                        return insertStatus;
                    }
                }
                break;
            case 1:
                if ((*subtreeRoot)->rightSubtree == nullptr)
                {
                    (*subtreeRoot)->rightSubtree = new Node<T>(data);
                    return inserted_as_right_child;
                }
                else
                {
                    insertStatus = inner_add(&((*subtreeRoot)->rightSubtree), static_cast<T&&>(data));
                    if (insertStatus == inserted_as_right_child) {
                        // 1. if parent is black, all is ok.
                        if ((*subtreeRoot)->rightSubtree->color == BLACK) {
                            return nothing_to_do;
                        }
                        // 2. parent is red, then grandparent is black and exists
                        // 2.1. uncle not exist: uncle is sentinel and then it's black
                        if ((*subtreeRoot)->leftSubtree == nullptr ||
                            (*subtreeRoot)->leftSubtree->color == BLACK)
                        {
                            rotateLeft(subtreeRoot);
                            (*subtreeRoot)->leftSubtree->color = RED;
                            (*subtreeRoot)->color = BLACK;
                            return nothing_to_do;
                        }
                            // 2.2. uncle is red: repaint parent, uncle and grandfather and all is ok
                        else if ((*subtreeRoot)->leftSubtree->color == RED)
                        {
                            (*subtreeRoot)->rightSubtree->color = BLACK;
                            (*subtreeRoot)->leftSubtree->color = BLACK;
                            (*subtreeRoot)->color = RED;
                            return uncle_black_now;
                        }
                    }
                    else if (insertStatus == inserted_as_left_child)
                    {
                        // 1. if parent is black, all is ok.
                        if ((*subtreeRoot)->rightSubtree->color == BLACK) {
                            return nothing_to_do;
                        }
                        // 2. parent is red, then grandparent is black and exists
                        // 2.1. uncle not exist: uncle is sentinel and then it's black
                        if ((*subtreeRoot)->leftSubtree == nullptr ||
                            (*subtreeRoot)->leftSubtree->color == BLACK)
                        {
                            rotateRight(&(*subtreeRoot)->rightSubtree);
                            rotateLeft(subtreeRoot);
                            (*subtreeRoot)->leftSubtree->color = RED;
                            (*subtreeRoot)->color = BLACK;
                            return nothing_to_do;
                        }
                            // 2.2. uncle is red: repaint parent, uncle and grandfather and all is ok
                        else if ((*subtreeRoot)->leftSubtree->color == RED)
                        {
                            (*subtreeRoot)->rightSubtree->color = BLACK;
                            (*subtreeRoot)->leftSubtree->color = BLACK;
                            (*subtreeRoot)->color = RED;
                            return uncle_black_now;
                        }
                    }
                    else if (insertStatus == uncle_black_now)
                    {
                        if ((*subtreeRoot)->color == BLACK)
                        {
                            return nothing_to_do;
                        }
                        return inserted_as_right_child;
                    }
                    else
                    {
                        return insertStatus;
                    }
                }
                break;
        }
    }

    void rotateLeft(Node<T>** subtreeRoot)
    {
        Node<T>* newRoot;
        if (*subtreeRoot == nullptr)
        {
            return; // TODO: maybe throw an exception
        }
        if ((newRoot = (*subtreeRoot)->rightSubtree) == nullptr)
        {
            return; // TODO: maybe throw an exception
        }
        (*subtreeRoot)->rightSubtree = newRoot->leftSubtree;
        newRoot->leftSubtree = *subtreeRoot;
        *subtreeRoot = newRoot;
    }

    void rotateRight(Node<T>** subtreeRoot)
    {
        Node<T>* newRoot;
        if (*subtreeRoot == nullptr)
        {
            return; // TODO: maybe throw an exception
        }
        if ((newRoot = (*subtreeRoot)->leftSubtree) == nullptr)
        {
            return; // TODO: maybe throw an exception
        }
        (*subtreeRoot)->leftSubtree = newRoot->rightSubtree;
        newRoot->rightSubtree = *subtreeRoot;
        *subtreeRoot = newRoot;
    }

    enum remove_statuses
    {
        to_do_nothing,
        one_left_subtree,
        one_right_subtree,
        no_subtrees_red,
        no_subtrees_black,
        go_to_grandfather
    };

    remove_statuses inner_delete(Node<T>** subtreeRoot, T&& data)
    {
        if (!*subtreeRoot)
        {
            return to_do_nothing;
        }
        int comparisonResult = this->_comparer->compare(data, (*subtreeRoot)->data);
        remove_statuses removeStatus;
        switch (comparisonResult)
        {
            case -1:
                removeStatus = inner_delete(&((*subtreeRoot)->leftSubtree), static_cast<T&&>(data));

                if(removeStatus == to_do_nothing)
                    return to_do_nothing;

                if (removeStatus == one_left_subtree)
                {
                    (*subtreeRoot)->leftSubtree->data = (*subtreeRoot)->leftSubtree->leftSubtree->data;
                    delete((*subtreeRoot)->leftSubtree->leftSubtree);
                    (*subtreeRoot)->leftSubtree->leftSubtree = nullptr;
                }

                if (removeStatus == one_right_subtree)
                {
                    (*subtreeRoot)->leftSubtree->data = (*subtreeRoot)->leftSubtree->rightSubtree->data;
                    delete((*subtreeRoot)->leftSubtree->rightSubtree);
                    (*subtreeRoot)->leftSubtree->rightSubtree = nullptr;
                }

                if(removeStatus == no_subtrees_red)
                {
                    delete ((*subtreeRoot)->leftSubtree);
                    (*subtreeRoot)->leftSubtree = nullptr;
                }

                if(removeStatus == no_subtrees_black || removeStatus == go_to_grandfather)
                {
                    if(removeStatus == no_subtrees_black)
                    {
                        delete ((*subtreeRoot)->leftSubtree);
                        (*subtreeRoot)->leftSubtree = nullptr;
                    }

                    //Left grandchild is red, parent red or black
                    if(((*subtreeRoot)->rightSubtree->rightSubtree != nullptr) && ((*subtreeRoot)->rightSubtree->rightSubtree->color == RED))
                    {
                        if((*subtreeRoot)->color == RED)
                        {
                            (*subtreeRoot)->color = BLACK;
                            (*subtreeRoot)->rightSubtree->color = RED;
                        }
                        rotateLeft(subtreeRoot);
                        (*subtreeRoot)->rightSubtree->color = BLACK;
                    }

                        //Right grandchild is red, parent red or black
                    else if(((*subtreeRoot)->rightSubtree->leftSubtree != nullptr) && ((*subtreeRoot)->rightSubtree->leftSubtree->color == RED))
                    {
                        rotateRight(&((*subtreeRoot)->rightSubtree));
                        if((*subtreeRoot)->color == BLACK)
                            (*subtreeRoot)->rightSubtree->color = BLACK;
                        rotateLeft(subtreeRoot);
                        if((*subtreeRoot)->leftSubtree->color == RED)
                            (*subtreeRoot)->leftSubtree->color = BLACK;
                    }
///////
                    else if ((*subtreeRoot)->color == RED)
                    {
                        (*subtreeRoot)->color = BLACK;
                        (*subtreeRoot)->rightSubtree->color = RED;
                    }

                        //Parent of deleted element is black
                    else if ((*subtreeRoot)->color == BLACK)
                    {
                        if ((*subtreeRoot)->rightSubtree->color == RED)
                        {
                            rotateLeft(subtreeRoot);
                            (*subtreeRoot)->color = BLACK;
                            (*subtreeRoot)->leftSubtree->rightSubtree->color = RED;

                            if(((*subtreeRoot)->leftSubtree->rightSubtree->rightSubtree == nullptr) &&
                               ((*subtreeRoot)->leftSubtree->rightSubtree->leftSubtree == nullptr))
                            {
                                return to_do_nothing;
                            }

                            if(((*subtreeRoot)->leftSubtree->rightSubtree->rightSubtree == nullptr) &&
                               ((*subtreeRoot)->leftSubtree->rightSubtree->leftSubtree != nullptr))
                            {
                                rotateRight(&((*subtreeRoot)->leftSubtree->rightSubtree));
                                rotateLeft(&((*subtreeRoot)->leftSubtree));
                                (*subtreeRoot)->leftSubtree->color = RED;
                                (*subtreeRoot)->leftSubtree->rightSubtree->color = BLACK;
                                return to_do_nothing;
                            }
                            else
                            {
                                rotateLeft(&((*subtreeRoot)->leftSubtree));
                                (*subtreeRoot)->leftSubtree->color = RED;
                                (*subtreeRoot)->leftSubtree->rightSubtree->color = BLACK;
                                return to_do_nothing;
                            }

                        }
                        else
                        {
                            (*subtreeRoot)->rightSubtree->color = RED;
                            return go_to_grandfather;
                        }
                    }
                }

                break;

            case 1:
                removeStatus = inner_delete(&((*subtreeRoot)->rightSubtree), static_cast<T&&>(data));

                if(removeStatus == to_do_nothing)
                    return to_do_nothing;

                if (removeStatus == one_left_subtree)
                {
                    (*subtreeRoot)->rightSubtree->data = (*subtreeRoot)->rightSubtree->leftSubtree->data;
                    delete((*subtreeRoot)->rightSubtree->leftSubtree);
                    (*subtreeRoot)->rightSubtree->leftSubtree = nullptr;
                }

                if (removeStatus == one_right_subtree)
                {
                    (*subtreeRoot)->rightSubtree->data = (*subtreeRoot)->leftSubtree->rightSubtree->data;
                    delete((*subtreeRoot)->rightSubtree->rightSubtree);
                    (*subtreeRoot)->rightSubtree->rightSubtree = nullptr;
                }

                if(removeStatus == no_subtrees_red)
                {
                    delete ((*subtreeRoot)->rightSubtree);
                    (*subtreeRoot)->rightSubtree = nullptr;
                }

                if(removeStatus == no_subtrees_black || removeStatus == go_to_grandfather)
                {
                    if(removeStatus == no_subtrees_black)
                    {
                        delete ((*subtreeRoot)->rightSubtree);
                        (*subtreeRoot)->rightSubtree = nullptr;
                    }
                    //Left grandchild is red, parent red or black
                   if(((*subtreeRoot)->leftSubtree->leftSubtree != nullptr) && ((*subtreeRoot)->leftSubtree->leftSubtree->color == RED))
                    {
                       if((*subtreeRoot)->color == RED)
                       {
                           (*subtreeRoot)->color = BLACK;
                           (*subtreeRoot)->leftSubtree->color = RED;
                       }
                        rotateRight(subtreeRoot);
                        (*subtreeRoot)->leftSubtree->color = BLACK;
                    }

                    //Right grandchild is red, parent red or black
                    else if(((*subtreeRoot)->leftSubtree->rightSubtree != nullptr) && ((*subtreeRoot)->leftSubtree->rightSubtree->color == RED))
                    {
                        rotateLeft(&((*subtreeRoot)->leftSubtree));
                        if((*subtreeRoot)->color == BLACK)
                            (*subtreeRoot)->leftSubtree->color = BLACK;
                        rotateRight(subtreeRoot);
                        if((*subtreeRoot)->rightSubtree->color == RED)
                            (*subtreeRoot)->rightSubtree->color = BLACK;
                    }

                    //Parent of deleted element is red
                    //Both grandchild are black
                    else if ((*subtreeRoot)->color == RED)
                    {
                        (*subtreeRoot)->color = BLACK;
                        (*subtreeRoot)->leftSubtree->color = RED;
                    }

                    //Parent of deleted element is black
                    else if ((*subtreeRoot)->color == BLACK)
                    {
                        if ((*subtreeRoot)->leftSubtree->color == RED)
                        {
                            rotateRight(subtreeRoot);
                            (*subtreeRoot)->color = BLACK;
                            (*subtreeRoot)->rightSubtree->leftSubtree->color = RED;

                            if(((*subtreeRoot)->rightSubtree->leftSubtree->leftSubtree == nullptr) &&
                               ((*subtreeRoot)->rightSubtree->leftSubtree->rightSubtree == nullptr))
                            {
                                return to_do_nothing;
                            }

                           if(((*subtreeRoot)->rightSubtree->leftSubtree->leftSubtree == nullptr) &&
                                   ((*subtreeRoot)->rightSubtree->leftSubtree->rightSubtree != nullptr))
                           {
                               rotateLeft(&((*subtreeRoot)->rightSubtree->leftSubtree));
                               rotateRight(&((*subtreeRoot)->rightSubtree));
                                (*subtreeRoot)->rightSubtree->color = RED;
                                (*subtreeRoot)->rightSubtree->leftSubtree->color = BLACK;
                                return to_do_nothing;
                           }
                           else
                            {
                               rotateRight(&((*subtreeRoot)->rightSubtree));
                                (*subtreeRoot)->rightSubtree->color = RED;
                                (*subtreeRoot)->rightSubtree->leftSubtree->color = BLACK;
                                return to_do_nothing;
                            }

                        }
                        else
                        {
                            (*subtreeRoot)->leftSubtree->color = RED;
                            return go_to_grandfather;
                        }

                    }
                }
                break;

            case 0:
                //No subtrees
                //TODO: for red only delete
                //TODO: for black 6 cases:(
                if(((*subtreeRoot)->leftSubtree == nullptr) && ((*subtreeRoot)->rightSubtree == nullptr))
                {
                    if((*subtreeRoot)->color == RED)
                        return no_subtrees_red;
                    else return no_subtrees_black;
                }

                //If only rightsubtree (case only for black parent)
                if (((*subtreeRoot)->leftSubtree == nullptr) && ((*subtreeRoot)->rightSubtree != nullptr))
                {
                    return one_right_subtree;
                }
                //If only leftsubtree (case only for black parent)
                if (((*subtreeRoot)->leftSubtree != nullptr) && ((*subtreeRoot)->rightSubtree == nullptr))
                {
                    return one_left_subtree;
                }

                else if((*subtreeRoot)->leftSubtree != nullptr && (*subtreeRoot)->rightSubtree != nullptr)
                {
                    Node<T>* max = find_max((*subtreeRoot)->leftSubtree);
                    std::swap(max->data, (*subtreeRoot)->data);
                    removeStatus = inner_delete(&((*subtreeRoot)->leftSubtree), static_cast<T&&>(data));

                    if(removeStatus == to_do_nothing)
                        return to_do_nothing;

                    if (removeStatus == one_left_subtree)
                    {
                        (*subtreeRoot)->leftSubtree->data = (*subtreeRoot)->leftSubtree->leftSubtree->data;
                        delete((*subtreeRoot)->leftSubtree->leftSubtree);
                        (*subtreeRoot)->leftSubtree->leftSubtree = nullptr;
                    }

                    if (removeStatus == one_right_subtree)
                    {
                        (*subtreeRoot)->leftSubtree->data = (*subtreeRoot)->leftSubtree->rightSubtree->data;
                        delete((*subtreeRoot)->leftSubtree->rightSubtree);
                        (*subtreeRoot)->leftSubtree->rightSubtree = nullptr;
                    }

                    if (removeStatus == no_subtrees_red)
                    {
                        delete ((*subtreeRoot)->leftSubtree);
                        (*subtreeRoot)->leftSubtree = nullptr;
                        return to_do_nothing;
                    }

                    if (removeStatus == no_subtrees_black)
                    {

                        //return no_subtrees_red;
                    }

                    if(removeStatus == no_subtrees_black || removeStatus == go_to_grandfather)
                    {
                        if(removeStatus == no_subtrees_black)
                        {
                            delete ((*subtreeRoot)->leftSubtree);
                            (*subtreeRoot)->leftSubtree = nullptr;
                        }


                        //Left grandchild is red, parent red or black
                        if(((*subtreeRoot)->rightSubtree->rightSubtree != nullptr) && ((*subtreeRoot)->rightSubtree->rightSubtree->color == RED))
                        {
                            if((*subtreeRoot)->color == RED)
                            {
                                (*subtreeRoot)->color = BLACK;
                                (*subtreeRoot)->rightSubtree->color = RED;
                            }
                            rotateLeft(subtreeRoot);
                            (*subtreeRoot)->rightSubtree->color = BLACK;
                        }

                            //Right grandchild is red, parent red or black
                        else if(((*subtreeRoot)->rightSubtree->leftSubtree != nullptr) && ((*subtreeRoot)->rightSubtree->leftSubtree->color == RED))
                        {
                            rotateRight(&((*subtreeRoot)->rightSubtree));
                            if((*subtreeRoot)->color == BLACK)
                                (*subtreeRoot)->rightSubtree->color = BLACK;
                            rotateLeft(subtreeRoot);
                            if((*subtreeRoot)->leftSubtree->color == RED)
                                (*subtreeRoot)->leftSubtree->color = BLACK;
                        }
///////
                        else if ((*subtreeRoot)->color == RED)
                        {
                            (*subtreeRoot)->color = BLACK;
                            (*subtreeRoot)->rightSubtree->color = RED;
                        }

                            //Parent of deleted element is black
                        else if ((*subtreeRoot)->color == BLACK)
                        {
                            if ((*subtreeRoot)->rightSubtree->color == RED)
                            {
                                rotateLeft(subtreeRoot);
                                (*subtreeRoot)->color = BLACK;
                                (*subtreeRoot)->leftSubtree->rightSubtree->color = RED;

                                if(((*subtreeRoot)->leftSubtree->rightSubtree->rightSubtree == nullptr) &&
                                   ((*subtreeRoot)->leftSubtree->rightSubtree->leftSubtree == nullptr))
                                {
                                    return to_do_nothing;
                                }

                                if(((*subtreeRoot)->leftSubtree->rightSubtree->rightSubtree == nullptr) &&
                                   ((*subtreeRoot)->leftSubtree->rightSubtree->leftSubtree != nullptr))
                                {
                                    rotateRight(&((*subtreeRoot)->leftSubtree->rightSubtree));
                                    rotateLeft(&((*subtreeRoot)->leftSubtree));
                                    (*subtreeRoot)->leftSubtree->color = RED;
                                    (*subtreeRoot)->leftSubtree->rightSubtree->color = BLACK;
                                    return to_do_nothing;
                                }
                                else
                                {
                                    rotateLeft(&((*subtreeRoot)->leftSubtree));
                                    (*subtreeRoot)->leftSubtree->color = RED;
                                    (*subtreeRoot)->leftSubtree->rightSubtree->color = BLACK;
                                    return to_do_nothing;
                                }
                            }
                            else
                            {
                                (*subtreeRoot)->rightSubtree->color = RED;
                                return go_to_grandfather;
                            }
                        }
                    }
                }
                break;
        }
    }

    Node<T>* find_max(Node<T>* p)
    {
        return p->rightSubtree ? find_max(p->rightSubtree) : p;
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
        stream << root->data << "(" << root->color << ")";
        inner_print_tree(root->leftSubtree, level + 1, stream);
        inner_print_tree(root->rightSubtree, level + 1, stream);
    }


public:
    explicit RB_Tree(Strategy<T>* comparer) : binary_tree<T>(comparer)
    {
        this->_root = nullptr;
    };

    void Add_Node(T&& k) override // вставка ключа k в дерево с корнем root
    {
        insert_statuses insertStatus = inner_add(&this->_root, static_cast<T&&>(k));
        if (insertStatus == uncle_black_now)
        {
            this->_root->color = BLACK;
        }
        else if (insertStatus == already_exist)
        {
            // TODO: throw an exception
            //throw "\n The element is already exist!";
            return;
        }
    }

    void Delete_Node(T&& k) override // удаление ключа k из дерева root
    {
        remove_statuses rem_st = inner_delete(&this->_root, static_cast<T&&>(k));
        if (rem_st == no_subtrees_black)
        {
            delete(this->_root);
            this->_root = nullptr;
        }

    }

    Node<T>* Search_Node(T&& value) override
    {
        Node<T>* result;
        return(result = inner_search(this->_root, static_cast<T&&>(value)));
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
    ~RB_Tree()
    {
        freeMemory(this->_root);
        delete(this->_comparer);
    }
};