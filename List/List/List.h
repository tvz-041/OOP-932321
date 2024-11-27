#pragma once

#include <iostream>

template <typename T>
class List
{
    struct Node;
public:
    List();
    ~List();
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
    for (Node* runner = m_head->next; runner != m_tail; runner = runner->next)
    {
        std::cout << runner->value << ' ';
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
