#ifndef _LIST_H 
#define _LIST_H 
#include "Allocator.h"

template<typename T>
struct Node
{
    public:
    T data;
    Node<T>* m_next;
    Node(T data,Node* m_next = nullptr)
    {
        this->data = data;
        this->m_next = m_next;
    }
};

template<typename T,typename A = std::allocator<T>>
class List{
    public:
    List();

    template <typename ...Args>
    void Emplace(Args ...args);

    ~List();


    //TODO

     List(const List &ob);
     List(List &&ob) noexcept;

    template <typename ObAlloc>
    List(const List<T,ObAlloc> &ob);

    template <typename ObAlloc>
    List(List<T,ObAlloc> &&ob);

    // Iterator<T> begin() {return Iterator<T>(pHead);}
    // Iterator<T> end()   {return Iterator<T>();}

    Node<T>* getHead() const {return m_head;}
    Node<T>* getNext() const {return m_head->m_next;}

    friend std::ostream& operator<<(std::ostream& out, const List<T> &li)
    {
        Node<T>* temp = li.getHead();
        if(!temp)
            return out;
        while(temp)
        {
            out<< temp->data;
            temp = temp->m_next;
            out<<std::endl;
        }
        return out;
    }
    private:
    Node<T>* m_head;
    size_t m_count;
    typename A::template rebind<Node<T>>::other m_Alloc;
};

template <typename T, typename Allocator /*= std::allocator<T>*/>
List<T,Allocator>::List(const List<T,Allocator> &rhs)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl; 

    if(!rhs.getHead())
        return;
    else
    {
        Node<T>* _fromPtr = rhs.getHead();
        m_head = new Node<T>(_fromPtr->data);
        _fromPtr = _fromPtr->m_next;
        Node<T>* _current = m_head;

        while (_fromPtr)
        {
            _current->m_next = new Node<T>(_fromPtr->data);
            _fromPtr = _fromPtr->m_next;
            _current = _current->m_next;
        }
    }
    
}
//move constr
template <typename T, typename Allocator /*= std::allocator<T>*/>
List<T,Allocator>::List(List<T,Allocator> &&rhs) noexcept : m_head(rhs.m_head),m_count(rhs.m_count)
{ 
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    // m_head = rhs.m_head;
    // m_count = rhs.m_count;
    rhs.m_head = nullptr;
    rhs.m_count = 0;
    //also
    // std::swap(m_head, rhs.m_head);
    // std::swap(m_count, rhs.m_count);
 }

template<typename T,typename A>
List<T,A>::List():m_count(0)
{}

template<typename T,typename A>
List<T,A>::~List()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl; 
    while(m_head)
    {
        Node<T>* _temp = m_head;
        m_head = m_head->m_next;
        delete _temp;
    }
}
template<typename T,typename A>
template <typename ...Args>
void List<T,A>::Emplace(Args ...args)
{
    if (!m_head)
        m_head = new Node<T>(std::forward<Args>(args)...);
        else
        {
            Node<T>* _curr = this->m_head;
            while(_curr->m_next)
                _curr=_curr->m_next;
            _curr->m_next = new Node<T>(std::forward<Args>(args)...);
        }
        m_count++;
}


#endif