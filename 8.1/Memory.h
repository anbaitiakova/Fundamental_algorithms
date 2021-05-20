#include "MemoryElement.h"
#include <list>

class memory
{
protected:
    void* ptr;
    size_t size;

    std::list<memoryElement> empty;
    std::list<memoryElement> filled;

public:
    memory()
    {
        size = 0;
        ptr = nullptr;
    }

    memory(size_t N)
    {
        size = N;
        ptr = malloc(N);
        memoryElement freeBlock(ptr, N);
        empty.push_back(freeBlock);
    }

    memoryElement allocate(size_t n)
    {
        try {
            memoryElement tmp = fill_memory(n);
            return tmp;
        }
        catch (const char* exception) {
            try {
                std::cerr << "Error: " << exception << '\n';
                memoryElement tmp = heap(n);
                return tmp;
            }
            catch (const char* exception) {
                throw "allocate error";
            }
        }
    }

    void deallocate(memoryElement block)
    {
        try {
            free(block);
        }
        catch (const char* exception) {
            std::cerr << "Error: " << exception << '\n';
        }
    }

    void printAllBlocks()
    {
        int i = 0;
        std::cout << "Empty blocks: " << std::endl;
        for (auto iter = empty.begin(); iter != empty.end(); iter++) {
            std::cout << "Element " << i << " size: " << (*iter).getSize() << " address: " << (*iter).getAddress() << std::endl;
            i++;
        }
        std::cout << "\n";
        i = 0;
        if (!(filled.empty()))
        {
            std::cout << "Full blocks: " << std::endl;
            for (auto iter = filled.begin(); iter != filled.end(); iter++) {
                std::cout << "Element " << i << ": size: " << (*iter).getSize() << " address: " << (*iter).getAddress() << std::endl;
                i++;
            }
            std::cout << "\n";
        }

    }
    virtual memoryElement fill_memory(size_t n) = 0;
    virtual memoryElement heap(size_t n) = 0;
    virtual void free(memoryElement &block) = 0;

    ~memory()
    {
        size = 0;
        ptr = nullptr;
    }

};

class Border_Descriptor : public memory
{
public:
    Border_Descriptor(size_t n) : memory(n) {}
private:
    //alloc
    memoryElement fill_memory(size_t n) override
    {
        size_t newN = n + 2 * sizeof(void*) + sizeof(bool) + sizeof(size_t);
        void* it = ptr;
        for (auto iter = empty.begin(); iter != empty.end(); iter++) {
            if (iter->getSize() < newN) {
                continue;
            }

            memoryElement tmp(iter->getAddress(), newN);
            void **prev = reinterpret_cast<void **>(tmp.getAddress());
            void **next = reinterpret_cast<void **>((reinterpret_cast<char *>(prev)) + sizeof(void *));
            bool *state = reinterpret_cast<bool *>((reinterpret_cast<char *>(next)) + sizeof(void *));
            size_t *currSize = reinterpret_cast<size_t *>((reinterpret_cast<char *>(state)) + sizeof(bool));
            *currSize = newN;

            if (iter->getAddress() == ptr && empty.size() == 1) {
                *prev = nullptr;
                *next = nullptr;
                *state = true;
                iter->setAddress(reinterpret_cast<void*>(reinterpret_cast<char*>(iter->getAddress()) + newN));
                iter->setSize(iter->getSize() - newN);
                return tmp;
            }

            if (iter->getSize() > newN) {
                *state = true;
                while (it != reinterpret_cast<void*>((reinterpret_cast<char*>(it) + newN)))
                {
                    auto t = reinterpret_cast<void**>(reinterpret_cast<char*>(it) + sizeof(void*));
                    if ((*t) == nullptr)
                    {
                        (*t) = tmp.getAddress();
                        *prev = it;
                    }
                    it = (reinterpret_cast<char*>(it) + newN);
                    if (*prev != NULL)
                        break;
                }
                void** nextFilledBlock = reinterpret_cast<void**>((reinterpret_cast<char*>(tmp.getAddress()) + iter->getSize()));
                if (nextFilledBlock == reinterpret_cast<void**>(reinterpret_cast<char*>(ptr) + size))
                    *next = nullptr;
                else
                {
                    *next = nextFilledBlock;
                    *(nextFilledBlock) = tmp.getAddress();
                }
                (*iter).setAddress((void*)(reinterpret_cast<char*>((*iter).getAddress()) + newN));
                (*iter).setSize((*iter).getSize() - newN);


            }
            else if ((*iter).getSize() == newN) {
                *state = true;
                while (it != reinterpret_cast<void*>((reinterpret_cast<char*>(it) + newN)))
                {
                    auto t = reinterpret_cast<void**>(reinterpret_cast<char*>(it) + sizeof(void*));
                    if ((*t) == nullptr)
                    {
                        (*t) = tmp.getAddress();
                        *prev = it;
                    }
                    it = (reinterpret_cast<char*>(it) + newN);
                    if (*prev != NULL)
                        break;

                }
                void** nextFilledBlock = reinterpret_cast<void**>((reinterpret_cast<char*>(tmp.getAddress()) + iter->getSize()));
                if (nextFilledBlock == reinterpret_cast<void**>(reinterpret_cast<char*>(ptr) + size))
                    *next = nullptr;
                else
                {
                    *next = nextFilledBlock;
                    *(nextFilledBlock) = tmp.getAddress();
                }
                empty.erase(iter);
            }
            return tmp;
        }
        throw "allocate error";
    }
    memoryElement heap(size_t n) override
    {
        size_t newN = n + 2 * sizeof(void*) + sizeof(bool) + sizeof(size_t);
        void* it = ptr;
        void **prev = reinterpret_cast<void **>(it);
        void **next = reinterpret_cast<void **>((reinterpret_cast<char *>(prev)) + sizeof(void *));
        bool *state = reinterpret_cast<bool *>((reinterpret_cast<char *>(next)) + sizeof(void *));

        //auto iterFull = filled.begin();

        size_t newSize = 0;
        auto iterEmpty = empty.begin();
        while (it != reinterpret_cast<void*>((reinterpret_cast<char*>(it) + newN)))
        {
            if (it == iterEmpty->getAddress())
            {
                it = reinterpret_cast<char*>(it) + iterEmpty->getSize();
                iterEmpty++;
            }
            else break;
        }
        size_t s = *(reinterpret_cast<char*>(it) + 2 * sizeof(void*) + sizeof(bool));
        memoryElement tmp(ptr, s);
        memoryElement prevTmp = tmp;
        memoryElement nextTmp(*next, *(reinterpret_cast<char*>(*next) + 2 * sizeof(void*) + sizeof(bool)));
        void **i = (reinterpret_cast<void**>(reinterpret_cast<char*>(nextTmp.getAddress()) + sizeof(void*)));
        while ((*i) != nullptr)
        {
            nextTmp.setAddress(prevTmp.getAddress());
            prevTmp.setAddress(*next);
            prevTmp.setSize(*(reinterpret_cast<char*>(*next) + 2 * sizeof(void*) + sizeof(bool)));
        }

        (*iterEmpty).setAddress(reinterpret_cast<size_t*>(prevTmp.getAddress()) + prevTmp.getSize());
        for (iterEmpty; iterEmpty != empty.end(); iterEmpty++) {
            newSize += (*iterEmpty).getSize();
        }
        auto nextit = std::next(empty.begin());
        empty.erase(nextit, empty.end());
        (*empty.begin()).setSize(newSize);

        if (newSize >= n) {
            return (*this).allocate(n);
        }
        else {
            throw "allocate error";
        }
    }

    void free(memoryElement &block) override
    {
        int fl = 0;
        void **prev = reinterpret_cast<void **>(block.getAddress());
        void **next = reinterpret_cast<void **>((reinterpret_cast<char *>(prev)) + sizeof(void *));
        bool *state = reinterpret_cast<bool *>((reinterpret_cast<char *>(next)) + sizeof(void *));
        for (auto iter = empty.begin(); iter != empty.end(); iter++)
        {
            if ((reinterpret_cast<char*>(iter->getAddress()) + iter->getSize()) == block.getAddress())
            {
                iter->setSize(iter->getSize() + block.getSize());
                block.setSize(iter->getSize());
                if (std::prev(iter)->getAddress() == block.getAddress())
                    empty.erase(std::prev(iter));

                if (*next == nullptr && *prev != nullptr)
                    (*(reinterpret_cast<char*>(*prev) + sizeof(void *))) = NULL;
                else if (*next != nullptr)
                {
                    *(reinterpret_cast<char*>(*prev) + sizeof(void *)) = *reinterpret_cast<char*>(next);
                    *(reinterpret_cast<char*>(*next)) = *reinterpret_cast<char*>(prev);
                }
                *prev = nullptr;
                *next = nullptr;
                *state = false;
                fl = 1;
            }
            if ((reinterpret_cast<char*>(block.getAddress()) + block.getSize()) == iter->getAddress())
            {
                iter->setSize(iter->getSize() + block.getSize());
                iter->setAddress(block.getAddress());
                block.setSize(iter->getSize());
                if (*next == nullptr && *prev != nullptr)
                    (*(reinterpret_cast<char*>(*prev) + sizeof(void *))) = NULL;
                else if (*next != nullptr)
                {
                    *(reinterpret_cast<char*>(*prev) + sizeof(void *)) = *reinterpret_cast<char*>(next);
                    *(reinterpret_cast<char*>(*next)) = *reinterpret_cast<char*>(prev);
                }
                *next = nullptr;
                *prev = nullptr;
                *state = false;
                fl = 1;
            }

        }
        if (fl == 0)
        {
            empty.push_back(block);
            if (*prev != nullptr)
            {
                *(reinterpret_cast<void**>(reinterpret_cast<char*>(*prev) + sizeof(void *))) = *next;
                *(reinterpret_cast<void**>(reinterpret_cast<char*>(*prev))) = *next;
            }
            *state = false;
        }
    }
};

class First_Appropriate : public memory
{
public:
    First_Appropriate(size_t n) : memory(n) {}

private:
    memoryElement fill_memory(size_t n) override
    {
        for (auto iter = empty.begin(); iter != empty.end(); iter++)
        {
            if (iter->getSize() < n)
            {
                continue;
            }

            memoryElement tmp((*iter).getAddress(), n);
            if ((*iter).getSize() == n)
            {
                filled.push_back(tmp);
                (*iter).setSize(0);
                (*iter).setAddress(nullptr);
                return tmp;
            } else
            if ((*iter).getSize() > n)
            {
                (*iter).setAddress(reinterpret_cast<size_t *>((*iter).getAddress()) + n);
                (*iter).setSize((*iter).getSize() - n);
                filled.push_back(tmp);
                return tmp;
            }
        }
        throw "allocate error";
    }

    memoryElement heap(size_t n) override
    {
        auto iterFull = filled.begin();

        size_t newSize = 0;
        (*iterFull).setAddress(ptr);
        auto prev = iterFull;

        iterFull++;
        for (iterFull; iterFull != filled.end(); iterFull++)
        {
            (*iterFull).setAddress(reinterpret_cast<size_t*>((*prev).getAddress()) + (*prev).getSize());
            prev++;
        }
        auto iterEmpty = empty.begin();
        (*iterEmpty).setAddress(reinterpret_cast<size_t*>((*prev).getAddress()) + (*prev).getSize());
        for (iterEmpty; iterEmpty != empty.end(); iterEmpty++)
        {
            newSize += (*iterEmpty).getSize();
        }
        auto next = std::next(empty.begin());
        empty.erase(next, empty.end());
        (*empty.begin()).setSize(newSize);

        if (newSize >= n)
        {
            return (*this).allocate(n);
        }
        else
        {
            throw "allocate error";
        }
    }

    void free(memoryElement &block) override
    {
        auto prev = empty.begin();
        auto next = prev;
        auto iter = filled.begin();
        while  (iter != filled.end())
        {
            if ((*iter).getAddress() == block.getAddress())
            {
                break;
            }
            iter++;
        }
        if (iter == filled.end() && iter->getAddress() != block.getAddress())
            throw "Deallocate error";
        while (next->getAddress() < block.getAddress() && next != empty.end())
        {
            prev = next;
            next++;
        }
        empty.splice(next, filled, iter);//(куда, откуда, что)

        if (prev != empty.begin())
            prev--;

        if (reinterpret_cast<size_t*>(prev->getAddress()) + prev->getSize() == iter->getAddress())
        {
            prev->setSize(prev->getSize() + iter->getSize());
            empty.erase(iter);
        }

        if (reinterpret_cast<size_t*>(prev->getAddress()) + prev->getSize() == next->getAddress())
        {
            prev->setSize(prev->getSize() + next->getSize());
            empty.erase(next);
        }
    }
};