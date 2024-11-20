
#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <utility>



template<typename T>
class Array
{
public:
    typedef T* iterator;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef int difference_type;

public:
    Array(int size, const T fillvalue = T());
    Array(const Array& other);
    Array(Array&& other);
    ~Array();

    iterator begin();
    iterator end();

    const iterator begin() const;
    const iterator end() const;
    void outputArray() const;
    void inputArray();
    int getSize() const noexcept;
    bool insert(const int index, const T& value);
    int findFirstOccurrence(const T& value) const;
    bool deleteByIndex(const int index);
    bool deleteByValue(const T& value);
    bool deleteAllByValue(const T& value);
    T findMaxNumber() const;
    T findMinNumber() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    void swap(Array& other) noexcept;
    Array& operator=(Array&& other);
    Array& operator+(Array& other);
    Array& operator+=(const Array& other);
    bool operator!=(Array& other);
    bool operator==(Array& other);
    void sortArray();

private:
    T* m_array = nullptr;
    int m_size = 0;
};
