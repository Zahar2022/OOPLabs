#pragma once
#include <iostream>
#include <assert.h>

template <typename T>

class List
{
public:
    struct Node;

public:
    template <typename ItemType>
    class TemplateIterator;
    using iterator = TemplateIterator<T>;
    using const_iterator = TemplateIterator<const T>;

public:
    List();
    List(const T* array, int const size);
    List(const List<T>& other);
    ~List();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    int size() const;
    void clear();

    void addToHead(const T& value);
    void addToTail(const T& value);
    void addElement(Node* index, const T& value);
    void addElement(const T& key, const T& value);
    void addElement(iterator index, const T& value);

    void deleteFromHead();
    void deleteFromTail();
    void deleteElement(Node* index);
    void deleteElement(const T& key);
    void deleteElement(iterator index);

    void deleteElements(iterator begin, iterator end);

    void print() const;
    void swap(List<T>& other);
    void sort();

    bool isEmpty() const;

    Node* searchElement(const T& value);

    T minElement() const;
    T maxElement() const;

    T& operator[](int const index);
    const T& operator[](int const index) const;
    List<T>& operator=(const List& other);
    List<T> operator+(const List<T>& other);
    List<T>& operator+=(const List<T>& other);

    bool operator==(const List<T>& other) const;
    bool operator!=(const List<T>& other) const;


    friend std::ostream& operator<<(const std::ostream& os, List<T>& other);
    friend std::istream& operator>>(const std::istream& is, List<T>& other);

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
    using value_type = ItemType;
    using reference = ItemType&;
    using pointer = ItemType*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = int;

    TemplateIterator(Node* node);

    Node* getNode() const;

    ItemType& operator*();
    const ItemType& operator*() const;
    TemplateIterator operator++();
    TemplateIterator operator--();
    TemplateIterator operator++(int);
    TemplateIterator operator--(int);
    bool operator==(const TemplateIterator& other) const;
    bool operator!=(const TemplateIterator& other) const;

private:
    Node* m_node = nullptr;
};

