#pragma once

#include <iostream>

template <typename T>
class List
{
    struct Node;

public:
    template <typename ItemType>
    class TemplateIterator;
    using iterator = TemplateIterator<T>;
    using const_iterator = TemplateIterator<const T>;

public:
    List();
    ~List();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    int size() const;
    void clear();
    void append(const T& value);
    void print() const;

private:
    int m_size = 0;
    Node* m_head = nullptr;
    Node* m_tail = nullptr;
};

template <typename T>
struct List<T>::Node
{
    Node(Node* next = nullptr, Node* prev = nullptr);
    Node(const T& value, Node* next = nullptr, Node* prev = nullptr);

    T value;
    Node* next = nullptr;
    Node* prev = nullptr;
};


template <typename T>
template <typename ItemType>
class List<T>::TemplateIterator
{
public:
    TemplateIterator(Node* node);

    ItemType& operator*();
    const ItemType& operator*() const;
    TemplateIterator operator++();
    TemplateIterator operator--();
    TemplateIterator operator++(int);
    TemplateIterator operator--(int);
    bool operator==(const TemplateIterator& other) const;
    bool operator!=(const TemplateIterator& other) const;

protected:
    Node* m_node = nullptr;
};



template <typename T>
List<T>::List()
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
}

template <typename T>
List<T>::~List()
{
    clear();
    delete m_head;
    delete m_tail;
}

template <typename T> typename
List<T>::iterator List<T>::begin()
{
    return iterator(m_head->next);
}

template <typename T> typename
List<T>::iterator List<T>::end()
{
    return iterator(m_tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(m_head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(m_tail);
}

template <typename T>
int List<T>::size() const
{
    return m_size;
}

template <typename T>
void List<T>::clear()
{
    if (!size())
    {
        return;
    }

    Node* runner = m_head->next;
    while (runner != m_tail)
    {
        Node* node = runner;
        runner = runner->next;
        delete node;
    }
    m_head->next = m_tail;
    m_tail->prev = m_head;
    m_size = 0;
}

template <typename T>
void List<T>::append(const T& value)
{
    Node* node = new Node(value, m_tail, m_tail->prev);
    m_tail->prev->next = node;
    m_tail->prev = node;
    ++m_size;
}

template <typename T>
void List<T>::print() const
{
    /*
        // C-style print
        for (Node* it = m_head->next; it != m_tail; it = it->next)
        {
            std::cout << it->value << ' ';
        }
        std::cout << "\n";

        // Print with iterator
        for (const_iterator it = begin(); it != end(); ++it)
        {
            std::cout << *it << ' ';
        }
        std::cout << "\n";
    */
    // Print with range-based for
    for (const T& value : *this)
    {
        std::cout << value << ' ';
    }
    std::cout << "\n";
}

template <typename T>
List<T>::Node::Node(Node* next, Node* prev)
    : next(next)
    , prev(prev)
{}

template <typename T>
List<T>::Node::Node(const T& value, Node* next, Node* prev)
    : value(value)
    , next(next)
    , prev(prev)
{}

template <typename T>
template <typename ItemType>
List<T>::TemplateIterator<ItemType>::TemplateIterator(Node* node)
    : m_node(node)
{}

template <typename T>
template <typename ItemType>
ItemType& List<T>::TemplateIterator<ItemType>::operator*()
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
const ItemType& List<T>::TemplateIterator<ItemType>::operator*() const
{
    return m_node->value;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++()
{
    m_node = m_node->next;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--()
{
    m_node = m_node->prev;
    return *this;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator++(int)
{
    TemplateIterator old = *this;
    m_node = m_node->next;
    return old;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--(int)
{
    TemplateIterator old = *this;
    m_node = m_node->prev;
    return old;
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator==(const TemplateIterator& other) const
{
    return (m_node == other.m_node);
}

template <typename T>
template <typename ItemType>
bool List<T>::TemplateIterator<ItemType>::operator!=(const TemplateIterator& other) const
{
    return (m_node != other.m_node);
}
