// Set.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Set.h"
#include "BoolVector.h"

Set::Set() :BoolVector(charSize) {}


Set::~Set() {}


Set::Set(const char* array, int const size)
    : BoolVector(charSize)
{
    for (int i = 0; i < size; i++)
        appendElement(array[i]);
}


Set::Set(const Set& other)
    :BoolVector(other)
{}


const char Set::maxElement() const
{
    for (int i = charSize - 1; i >= 0; i--)
        if (bitValue(i))
            return i;
    return 0;
}


const char Set::minElement() const
{
    for (int i = 0; i < charSize; i++)
        if (bitValue(i))
            return i;
    return 0;
}


bool Set::findElement(const char ch)
{
    return bitValue(ch);
}


const int Set::power() const
{
    return weight();
}


Set& Set::operator=(const Set& other) {
    BoolVector::operator=(other);
    return *this;
}


bool Set::operator==(const Set& other) const {
    return *this == other;
}


bool Set::operator!=(const Set& other) const
{
    return !(*this == other);
}


Set Set::operator|(const Set& other) const {
    Set result = *this;
    result |= other;
    return result;
}


Set& Set::operator|=(const Set& other) {
    BoolVector::operator|=(other);
    return *this;
}


Set Set::operator&(const Set& other) const {
    Set result = *this;
    result &= other;
    return result;
}


Set& Set::operator&=(const Set& other) {
    BoolVector::operator&=(other);
    return *this;
}


Set Set::operator/(const Set& other) const {
    Set result = *this; 
    for (int i = 0; i < charSize; ++i) {
        if (other.bitValue(i)) {
            result.deleteElement(i); 
        }
    }
    return result;
}


Set& Set::operator/=(const Set& other) {
    Set result = *this;
    result /= other;
    return result;
}


Set Set::operator~() const {
    Set result = *this;
    result.invert();
    return result;
}


Set Set::operator+(const char ch) const {
    Set result = *this;
    result.appendElement(ch);
    return result;
}


Set& Set::operator+=(const char ch) {
    appendElement(ch);
    return *this;
}


Set Set::operator-(const char ch) const {
    Set result = *this;
    result.deleteElement(ch);
    return result;
}


Set& Set::operator-=(const char ch) {
    deleteElement(ch);
    return *this;
}


std::ostream& operator<<(std::ostream& os, const Set& set) {
    os << "{";
    bool first = true;
    for (int i = 0; i < set.charSize; ++i) {
        if (set.bitValue(i)) {
            if (!first) {
                os << ", ";
            }
            os << static_cast<char>(i + set.start);
            first = false;
        }
    }
    os << "}";
    return os;
}


std::istream& operator>>(std::istream& is, Set& set) {
    std::string input;
    is >> input;

    set.setAllBits(false);
    for (char c : input) {
        if (c != '{' && c != '}' && c != ',' && c != ' ') {
            set.appendElement(c);
        }
    }
    return is;
}


void Set::appendElement(const char ch)
{
    setBitValue(ch, true);
}


void Set::deleteElement(const char ch)
{
    setBitValue(ch, false);
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
