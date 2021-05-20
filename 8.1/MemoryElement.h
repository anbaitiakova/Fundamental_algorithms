#include <iostream>

class memoryElement
{
private:
    void* ElementPtr;
    size_t ElementSize;

public:
    memoryElement()
    {
        ElementPtr = nullptr;
        ElementSize = 0;
    }

    memoryElement(void* ptr, size_t size)
    {
        ElementPtr = ptr;
        ElementSize = size;
    }

    void setSize(size_t size)
    {
        ElementSize = size;
    }

    void setAddress(void* ptr)
    {
        ElementPtr = ptr;
    }

    void* getAddress() const
    {
        return ElementPtr;
    }

    size_t getSize() const
    {
        return ElementSize;
    }
};
