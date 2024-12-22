#pragma once


#include <iostream>
#include <cassert>
#include "BoolVector.h"


class BoolMatr {
private:
    BoolVector* m_rows;
    int m_rowsNumber;
    int m_columnsNumber;

public:
    BoolMatr();
    BoolMatr(int rows, int columns, bool value = false);
    BoolMatr(const char** arr, int rows, int cols);
    BoolMatr(const BoolMatr& other);
    ~BoolMatr();

    
    int rowsNumber() const;
    int columnsNumber() const;

    friend std::ostream& operator<<(std::ostream& os, const BoolMatr& matrix);
    friend std::istream& operator>>(std::istream& is, BoolMatr& matrix);

    void swap(BoolMatr& other);
    int weight() const;
    int rowWeight(int j) const;
    void invertComponent(int j, int i);
    void invertComponents(int j, int i, int k);
    void setComponent(int j, int i, bool value);
    void setComponents(int j, int i, int k, bool value);
    BoolVector conjunctionAllRows() const;
    BoolVector disjunctionAllRows() const;

    BoolMatr& operator=(const BoolMatr& other);
    BoolVector& operator[](int index);
    const BoolVector& operator[](int index) const;
    BoolMatr operator&(const BoolMatr& other) const;
    BoolMatr& operator&=(const BoolMatr& other);
    BoolMatr operator|(const BoolMatr& other) const;
    BoolMatr& operator|=(const BoolMatr& other);
    BoolMatr operator^(const BoolMatr& other) const;
    BoolMatr& operator^=(const BoolMatr& other);
    BoolMatr operator~() const;


};