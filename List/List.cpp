// List.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "List.h"


template <typename T>
List<T>::List()
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
}

template<typename T>
inline List<T>::List(const T* array, int const size)
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
    for (int i = 0; i < size; i++)
        addToTail(array[i]);
}

template<typename T>
List<T>::List(const List<T>& other)
    : m_head(new Node())
    , m_tail(new Node())
{
    m_head->next = m_tail;
    m_tail->prev = m_head;
    Node* runner = other.m_head->next;
    while (runner != other.m_tail)
    {
        addToTail(runner->value);
        runner = runner->next;
    }
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
    if (isEmpty())
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

template<typename T>
void List<T>::addToHead(const T& value)
{
    Node* node = new Node(value, m_head->next, m_head);
    m_head->next->prev = node;
    m_head->next = node;
    ++m_size;
}

template <typename T>
void List<T>::addToTail(const T& value)
{
    Node* node = new Node(value, m_tail, m_tail->prev);
    m_tail->prev->next = node;
    m_tail->prev = node;
    ++m_size;
}

template<typename T>
void List<T>::addElement(Node* index, const T& value)
{
    Node* node = new Node(value, index, index->prev);
    index->prev->next = node;
    index->prev = node;
    ++m_size;
}

template<typename T>
void List<T>::addElement(const T& key, const T& value)
{
    if (searchElement(key) == nullptr)
        return;
    Node* node = searchElement(key);
    addElement(node->next, value);
}

template<typename T>
void List<T>::addElement(iterator index, const T& value)
{
    addElement(index.getNode(), value);
}

template<typename T>
void List<T>::deleteFromHead()
{
    if (isEmpty())
    {
        return;
    }
    Node* node = m_head->next;
    m_head->next = node->next;
    node->next->prev = m_head;
    --m_size;
    delete node;
}

template<typename T>
void List<T>::deleteFromTail()
{
    if (isEmpty())
    {
        return;
    }
    Node* node = m_tail->prev;
    m_tail->prev = node->prev;
    node->prev->next = m_tail;
    --m_size;
    delete node;
}

template<typename T>
void List<T>::deleteElement(Node* index)
{
    if (isEmpty() || index == nullptr)
    {
        return;
    }
    index->prev->next = index->next;
    index->next->prev = index->prev;
    --m_size;
    delete index;
}

template<typename T>
void List<T>::deleteElement(const T& key)
{
    if (searchElement(key) == nullptr)
    {
        return;
    }
    Node* nodeSearch = searchElement(key);
    deleteElement(nodeSearch);
}

template<typename T>
void List<T>::deleteElement(iterator index)
{
    deleteElement(index.getNode());
}

template<typename T>
void List<T>::deleteElements(iterator begin, iterator end)
{
    iterator it = begin;
    iterator it1 = ++end;
    while (it != it1)
    {
        deleteElement(it++);
    }
}

template <typename T>
void List<T>::print() const
{
    for (const T& value : *this)
    {
        std::cout << value << ' ';
    }
    std::cout << "\n";
}

template<typename T>
void List<T>::swap(List<T>& other)
{
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_size, other.m_size);
}

template<typename T>
void List<T>::sort()
{
    List<T> list = *this;
    clear();
    T minElement;
    while (list.isEmpty() == 0)
    {
        minElement = list.minElement();
        addToTail(minElement);
        list.deleteElement(minElement);
    }
}

template<typename T>
bool List<T>::isEmpty() const
{
    if (m_head->next == m_tail)
        return true;
    return false;
}

template<typename T>
typename List<T>::template
Node* List<T>::searchElement(const T& valueSearch)
{
    Node* runner = m_head->next;
    while (runner != m_tail)
    {
        if (runner->value == valueSearch)
            return runner;
        runner = runner->next;
    }
    return nullptr;
}

template<typename T>
T List<T>::minElement() const
{
    T minElement;
    minElement = m_head->next->value;
    Node* runner = m_head->next->next;
    while (runner != m_tail)
    {
        if (minElement > runner->value)
            minElement = runner->value;
        runner = runner->next;
    }
    return minElement;
}

template<typename T>
T List<T>::maxElement() const
{
    T maxElement;
    maxElement = m_head->next->value;
    Node* runner = m_head->next->next;
    while (runner != m_tail)
    {
        if (maxElement < runner->value)
            maxElement = runner->value;
        runner = runner->next;
    }
    return maxElement;
}

template<typename T>
T& List<T>::operator[](int const index)
{
    assert(index >= 0 && index < m_size);
    Node* runner = m_head->next;
    for (int i = 0; i != index; runner = runner->next, i++);
    return(runner->value);
}

template<typename T>
const T& List<T>::operator[](int const index) const
{
    assert(index >= 0 && index < m_size);
    return(operator[](index));
}

template<typename T>
List<T>& List<T>::operator=(const List& other)
{
    List<T> copy(other);
    swap(copy);
    return *this;
}

template<typename T>
List<T>& List<T>::operator+=(const List<T>& other)
{

    Node* runner = other.m_head->next;
    while (runner != other.m_tail)
    {
        addToTail(runner->value);
        runner = runner->next;
    }
    return *this;
}

template<typename T>
List<T> List<T>::operator+(const List<T>& other)
{
    List<T> copy = *this;
    copy += other;
    return copy;
}


template<typename T>
bool List<T>::operator==(const List<T>& other) const
{
    if (m_size != other.m_size)
        return false;
    Node* runner1 = m_head->next;
    Node* runner2 = other.m_head->next;
    while (runner1 != m_tail)
    {
        if (runner1->value != runner2->value)
            return false;
        runner1 = runner1->next;
        runner2 = runner2->next;
    }
    return true;
}

template<typename T>
bool List<T>::operator!=(const List<T>& other) const
{
    return !(*this == other)
}

template <typename T>
std::ostream& operator<<(std::ostream& os, List<T>& other)
{
    for (const T& value : other)
    {
        os << value << ' ';
    }
    os << "\n";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, List<T>& other)
{
    int size = other.size();
    other.clear();
    for (int i = 0; i < size; i++)
    {
        T value;
        is >> value;
        other.addToTail(value);
    }
    return is;
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
typename List<T>::template
Node* List<T>::TemplateIterator<ItemType>::getNode() const
{
    return m_node;
}

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
    TemplateIterator it = *this;
    m_node = m_node->next;
    return it;
}

template <typename T>
template <typename ItemType>
typename List<T>::template
TemplateIterator<ItemType> List<T>::TemplateIterator<ItemType>::operator--(int)
{
    TemplateIterator it = *this;
    m_node = m_node->prev;
    return it;
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

int main()
{


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
