// BoolMatr.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <assert.h>
#include "BoolVector.h"
#include "BoolMatr.h"



BoolMatr::BoolMatr() : m_rows(nullptr), m_rowsNumber(0), m_columnsNumber(0) {}


BoolMatr::BoolMatr(int rows, int cols, bool value)
    : m_rowsNumber(rows), m_columnsNumber(cols) {
    m_rows = new BoolVector[m_rowsNumber];
    for (int i = 0; i < m_rowsNumber; ++i) {
        m_rows[i] = BoolVector(m_columnsNumber, value);
    }
}


BoolMatr::BoolMatr(const char** arr, int rows, int columns)
    : m_rowsNumber(rows), m_columnsNumber(columns) {
    assert(arr != nullptr);
    assert(rows > 0 && columns > 0);

    m_rows = new BoolVector[m_rowsNumber];
    for (int i = 0; i < m_rowsNumber; ++i) {
        m_rows[i] = BoolVector(columns);
        for (int j = 0; j < m_columnsNumber; ++j) {
            if (arr[i][j] == '1') {
                m_rows[i].setBitValue(j, true);
            }
            else if (arr[i][j] == '0') {
                m_rows[i].setBitValue(j, false);
            }
            else {
                assert(false && "Input should be '0' or '1'");
            }
        }
    }
}


BoolMatr::BoolMatr(const BoolMatr& other)
    : m_rowsNumber(other.m_rowsNumber), m_columnsNumber(other.m_columnsNumber) {
    m_rows = new BoolVector[m_rowsNumber];
    for (int i = 0; i < m_rowsNumber; ++i) {
        m_rows[i] = other.m_rows[i];
    }
}


BoolMatr::~BoolMatr() {
    delete[] m_rows;
}


int BoolMatr::rowsNumber() const {
    return m_rowsNumber;
}


int BoolMatr::columnsNumber() const {
    return m_columnsNumber;
}


void BoolMatr::swap(BoolMatr& other) {
    std::swap(m_rows, other.m_rows);
    std::swap(m_rowsNumber, other.m_rowsNumber);
    std::swap(m_columnsNumber, other.m_columnsNumber);
}


int BoolMatr::weight() const {
    int totalWeight = 0;
    for (int i = 0; i < m_rowsNumber; ++i) {
        totalWeight += m_rows[i].weight();
    }
    return totalWeight;
}


int BoolMatr::rowWeight(int j) const {
    assert(j >= 0 && j < m_rowsNumber);
    return m_rows[j].weight();
}


void BoolMatr::invertComponent(int j, int i) {
    assert(j >= 0 && j < m_rowsNumber);
    m_rows[j].invert(i);
}

void BoolMatr::invertComponents(int j, int i, int k) {
    assert(j >= 0 && j < m_rowsNumber);
    assert(i >= 0 && i + k <= m_columnsNumber);
    BoolVector& row = m_rows[j];
    for (int index = i; index < i + k; ++index) {
        row[index] = ~row[index];
    }
}

void BoolMatr::setComponent(int j, int i, bool value) {
    assert(j >= 0 && j < m_rowsNumber);
    m_rows[j].setBitValue(i, value);
}


void BoolMatr::setComponents(int j, int i, int k, bool value) {
    assert(j >= 0 && j < m_rowsNumber);
    m_rows[j].setBits(i, k, value);
}


BoolVector BoolMatr::conjunctionAllRows() const {
    assert(m_rowsNumber > 0);
    BoolVector result = m_rows[0];
    for (int i = 1; i < m_rowsNumber; ++i) {
        result &= m_rows[i];
    }
    return result;
}


BoolVector BoolMatr::disjunctionAllRows() const {
    assert(m_rowsNumber > 0);
    BoolVector result = m_rows[0];
    for (int i = 1; i < m_rowsNumber; ++i) {
        result |= m_rows[i];
    }
    return result;
}

BoolMatr& BoolMatr::operator=(const BoolMatr& other) {
    if (this != &other) {
        delete[] m_rows;
        m_rowsNumber = other.m_rowsNumber;
        m_columnsNumber = other.m_columnsNumber;
        m_rows = new BoolVector[m_rowsNumber];
        for (int i = 0; i < m_rowsNumber; ++i) {
            m_rows[i] = other.m_rows[i];
        }
    }
    return *this;
}

BoolVector& BoolMatr::operator[](int index) {
    assert(index >= 0 && index < m_rowsNumber);
    return m_rows[index];
}

const BoolVector& BoolMatr::operator[](int index) const {
    assert(index >= 0 && index < m_rowsNumber);
    return m_rows[index];
}

BoolMatr BoolMatr::operator|(const BoolMatr& other) const {
    BoolMatr result = *this;
    result |= other;
    return result;
}

BoolMatr& BoolMatr::operator|=(const BoolMatr& other) {
    assert(m_rowsNumber == other.m_rowsNumber && m_columnsNumber == other.m_columnsNumber);
    for (int i = 0; i < m_rowsNumber; ++i) {
        m_rows[i] |= other.m_rows[i];
    }
    return *this;
}

BoolMatr BoolMatr::operator^(const BoolMatr& other) const {
    BoolMatr result = *this;
    result ^= other;
    return result;
}

BoolMatr& BoolMatr::operator^=(const BoolMatr& other) {
    assert(m_rowsNumber == other.m_rowsNumber && m_columnsNumber == other.m_columnsNumber);
    for (int i = 0; i < m_rowsNumber; ++i) {
        m_rows[i] ^= other.m_rows[i];
    }
    return *this;
}

BoolMatr BoolMatr::operator~() const {
    BoolMatr result = *this;
    for (int i = 0; i < m_rowsNumber; ++i) {
        result.m_rows[i].invert();
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const BoolMatr& matrix) {
    for (int i = 0; i < matrix.m_rowsNumber; ++i) {
        os << matrix.m_rows[i] << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, BoolMatr& matrix) {
    int rows, cols;
    is >> rows >> cols;
    delete[] matrix.m_rows;
    matrix.m_rowsNumber = rows;
    matrix.m_columnsNumber = cols;
    matrix.m_rows = new BoolVector[rows];
    for (int i = 0; i < rows; ++i) {
        is >> matrix.m_rows[i];
    }
    return is;
}




int main()
{
    const char* inputMatrix[] = {
       "1010",
       "0101",
       "1111",
       "0000"
    };

    int rows = 4;
    int cols = 4;

    BoolMatr matrix(inputMatrix, rows, cols);
    std::cout << matrix;

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
