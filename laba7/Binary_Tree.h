enum COLOR {RED, BLACK};
template<class T>
struct Node
{
    T data;
    Node *rightSubtree, *leftSubtree;
    short int height;
    bool color;
    explicit Node(T k)
    {
        data = k;
        leftSubtree = rightSubtree = nullptr;
        height = 1;
        color = RED;
    }
};

template<class T>
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual int compare(const T& left, const T& right) const = 0;
};

class SomeStrategyExample: public Strategy<int>
{
public:
    int compare(const int& left, const int& right) const override
    {
        if (left == right)
        {
            return 0;
        }
        return left < right ? -1 : 1;
    }
};

template<class T>
class binary_tree
{
protected:
    Strategy<T>* _comparer;
    Node<T>* _root;
public:
    virtual void Add_Node(T&& k) = 0;
    virtual void Delete_Node(T&& k) = 0;
    virtual Node<T>* Search_Node(T&&  value) = 0;

    explicit binary_tree(Strategy<T>* comparer = nullptr) : _comparer(comparer)
    {

    }

    virtual ~binary_tree() = default;
    /*{
        delete this->_comparer;
    }*/
};