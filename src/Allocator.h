#ifndef _ALLOC_H 
#define _ALLOC_H 

#include <tuple>
#include <iostream>
#include <vector>
#include <cstring>

//класс который резервирует память
//сейчас утечка памяти
class memory_pool
{
    public:
    memory_pool(std::size_t type_size,std::size_t reserve_count)
    { 
        mem_pool_ = std::malloc(type_size * reserve_count); //резервируем согласно шаблону и количеству элементов

        if(mem_pool_ != nullptr)
            {
                reserved_count_ = reserve_count;
                element_size_ = type_size;
            }
    }

    void* get_next_allocated_mem()
    {
        if(elements_count_ < reserved_count_)
        {
            return mem_pool_ + (elements_count_++ * element_size_);
        }
        else
        {
            void *ptr = std::malloc(element_size_ * reserved_count_ * 2); //если выделяемых количество элементов превышает резерв,выделяем память*2
            if(ptr != nullptr)
            {
            std::memmove(ptr, mem_pool_, element_size_ * reserved_count_); //перемещаем в новое место
            reserved_count_ *= 2;
            mem_pool_ = ptr;
            return mem_pool_ + (elements_count_++ * element_size_);
            }
        }
    }

  private:
    void* mem_pool_ = nullptr;
    std::size_t element_size_ = 0;
    std::size_t elements_count_ = 0;
    std::size_t reserved_count_ = 0;
};

template<typename T>
struct logging_allocator {
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = logging_allocator<U>;
    };

    logging_allocator(): _mem(sizeof(T), 10){ }

    T *allocate(std::size_t n)  {
        auto p = _mem.get_next_allocated_mem(); //здесь происходит выделение памяти
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n)  {
       // std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)  {

        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p)  {

        p->~T();
    }
    private:
    memory_pool _mem; //та самая область
};

#endif