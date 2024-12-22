#pragma once


class BoolVector

{
public:
    class Rank;

public:
    using Cell = unsigned char;
    static const int CellSize = 8; // sizeof(Cell) * 8
    BoolVector(int length = CellSize);
    BoolVector(int length, bool value); 
    BoolVector(const BoolVector& other);
    BoolVector(const char* arr);
    ~BoolVector();

    int length() const;
    void swap(BoolVector& other);
    bool bitValue(int index) const;
    void setBitValue(int index, bool value);
    void invert();
    void invert(int index);
    void setBits(int index, int count, bool value);
    void setAllBits(bool value);
    int weight() const;


    BoolVector& operator=(const BoolVector& other);
    BoolVector operator&(const BoolVector& other) const;
    BoolVector& operator&=(const BoolVector& other);
    BoolVector operator|(const BoolVector& other) const;
    BoolVector& operator|=(const BoolVector& other);
    BoolVector operator^(const BoolVector& other) const;
    BoolVector& operator^=(const BoolVector& other);
    BoolVector operator~() const;
    BoolVector operator<<(int shift) const;
    BoolVector& operator<<=(int shift);
    BoolVector operator>>(int shift) const;
    BoolVector& operator>>=(int shift);
    friend std::ostream& operator<<(std::ostream& os, const BoolVector& bv);
    friend std::istream& operator>>(std::istream& is, BoolVector& bv);
    Rank operator[](int index);


private:
    int _excessRankNumber() const;
    static Cell _mask(int index);

private:
    Cell* m_cells = nullptr;
    int m_cellNumber = 0;
    int m_length = 0;
};


class BoolVector::Rank
{
public:
    Rank() = default;
    Rank(Cell* cell, Cell mask);
    Rank& operator=(const Rank& other);
    Rank& operator=(bool value);
    operator bool() const;

private:
    Cell* m_cell = nullptr;
    Cell m_mask = 0;
};