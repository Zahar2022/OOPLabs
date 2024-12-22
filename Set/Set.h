#pragma once

#include <iostream>
#include <string>
#include "BoolVector.h"


class Set : public BoolVector {

public:
	Set();
	Set(const Set& other);
	Set(const char* arr, int size);
	~Set();

	friend std::istream& operator >> (std::istream& is, Set& set);
	friend std::ostream& operator << (std::ostream& os, const Set& set);

	bool findElement(const char el);
	const int power() const;
	const char maxElement() const;
	const char minElement() const;

	Set& operator=(const Set& other);
	bool operator==(const Set& other) const;
	bool operator!=(const Set& other) const;
	Set operator|(const Set& other) const;
	Set& operator|=(const Set& other);
	Set operator&(const Set& other) const;
	Set& operator&=(const Set& other);
	Set operator/(const Set& other) const;
	Set& operator/=(const Set& other);
	Set operator~() const;
	Set operator+(const char ch) const;
	Set& operator+=(const char ch);
	Set operator-(const char ch) const;
	Set& operator-=(const char ch);


	static const int stop = 127;
	static const int start = 32;
	static const int charSize = stop - start;



private:
	void appendElement(const char el);
	void deleteElement(const char el);
	
};