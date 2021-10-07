#ifndef _ALLOC_H 
#define _ALLOC_H 

#include <tuple>
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <iomanip>

template<typename T,size_t BLOCKS>
struct _allocator {
    public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = _allocator<U,BLOCKS>;
    };

    private:
    T* newMemory = nullptr;
    unsigned takens = 0;
    unsigned limit = 0;
    public:
    T* allocate(std::size_t n)
    {
        
        takens+=n;
		if (takens >= limit)
        {
            limit+=10;
            newMemory = (T*) realloc(newMemory, limit * sizeof(T));
        }
        T* res = newMemory+takens;
        return res;
        
    }

    void deallocate([[maybe_unused]] T* p,[[maybe_unused]] std::size_t n) const {/*std::cout << __PRETTY_FUNCTION__ << std::endl;*/ }

    template<typename U,typename ...Args>
    void construct(U *p,Args&& ...args) const
    {
        //std::cout << __PRETTY_FUNCTION__ << std::endl; 
        new(p) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p) const
    {
        //std::cout << __PRETTY_FUNCTION__ << std::endl; 
        p->~U();
    }


    _allocator()
    {
        //std::cout << __PRETTY_FUNCTION__ << std::endl; 
        newMemory = (T*)std::malloc(BLOCKS * sizeof(T));
        limit = BLOCKS;
    }
    _allocator(const _allocator&) = delete;


    _allocator(_allocator&& ob) noexcept
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl; 
        newMemory = ob.newMemory;
        takens = ob.takens;
        ob.newMemory = nullptr;
        ob.takens = 0;
    }

    ~_allocator()
    {
        //std::cout << __PRETTY_FUNCTION__ << std::endl; 
        if(newMemory)
            std::free(newMemory);
    }

};

#endif