#ifndef _LIST_H 
#define _LIST_H 
#include "Allocator.h"

    // Структура узла односвязного списка
    template< typename T>
    struct Node {
        Node() : m_next( nullptr ) { }

        Node( const T& t ) : m_t( t ), m_next( nullptr ) { }

        // Значение узла
        T m_t;

        // Указатель на следующий узел
        Node* m_next;
    };


template< typename T, typename A = std::allocator<Node<T>>>
class List {
private:
    // Объявляем структуру узла для использования в классе Iterator
    struct Node;

public:
    // Класс итератора односвязного списка
class Iterator {
public:
    Iterator( Node* node ) : m_node( node ) { }

    // Проверка на равенство
    bool operator==( const Iterator& other ) const {
        if( this == &other ) {
            return true;
        }
        return m_node == other.m_node;
    }

    // Проверка на неравенство
    bool operator!=( const Iterator& other ) const {
        return !operator==( other );
    }

    // Получение значения текущего узла
    T operator*() const {
        if( m_node ) {
            return m_node->m_t;
        } // Иначе достигнут конец списка. Здесь уместно возбудить исключение
        return T();
    }

    // Переход к следующему узлу
    void operator++() {
        if( m_node ) {
            m_node = m_node->m_next;
        } // Иначе достигнут конец списка. Здесь уместно возбудить исключение
    }

private:
    Node* m_node;
};

public:
    List();

    ~List();

    // Добавляем узел в список
    void append( const T& t );

    // Удаляем последний добавленный узел из списка
    void remove();

    // Получаем головной элемент списка
    T head() const;

    // Получаем итератор на начало списка
    Iterator begin() const;
    // Получаем итератор на конец списка
    Iterator end() const;

    // Получаем размер списка
    size_t size() const;

private:

    A allocator_;
    // Голова односвязного списка
    Node* m_head;
};

template< typename T, typename A >
List< T,A >::List() : m_head( nullptr ) {
}

template< typename T, typename A >
void List< T,A >::append( const T &t ) {
   // Создаём новый узел для значения
   // Если произойдёт исключение, контейнер не пострадает
   Node* node = new Node( t );
   // Новый узел привязывается к старому головному элементу
   node->m_next = m_head;
   // Новый узел сам становится головным элементом
   m_head = node;
}

template< typename T, typename A >
void List< T,A >::remove() {
    if( m_head ) { // Если список не пуст:
        // Сохраняем указатель на второй узел, который станет новым головным элементом
        Node* newHead = m_head->m_next;

        // Освобождаем память, выделенную для удаляемого головного элемента
        delete m_head;

        // Назначаем новый головной элемент
        m_head = newHead;
    } // Иначе мы могли бы возбудить исключение
}

template< typename T, typename A >
List< T,A >::~List() {
    while( m_head ) {
        remove();
    }
}


template< typename T, typename A >
typename List< T,A >::Iterator List< T,A >::begin() const {
    // Итератор пойдет от головного элемента...
    return Iterator( m_head );
}

template< typename T, typename A >
typename List< T,A >::Iterator List< T,A >::end() const {
    // ... и до упора, т.е. NULL
    return Iterator( NULL );
}

template< typename T, typename A >
size_t List< T,A >::size() const {
    size_t s = 0;
    for( Iterator it = begin(); it != end(); ++it ) {
        ++s;
    }
    return s;
}

#endif