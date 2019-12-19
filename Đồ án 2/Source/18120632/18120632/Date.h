#pragma once
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Date
{
private:
	int _day, _month, _year;

public:

	static const int noDay[];
	Date();
	Date(int day, int month, int year);
	Date(const Date& rhs);

	Date& operator=(const Date& rhs);

	int getDay();
	int getMonth();
	int getYear();

	void setDay(int day);
	void setMonth(int month);
	void setYear(int year);

	bool isLeapYear(int year);
	bool checkDate();

	Date& operator += (int d);
	Date& operator ++ ();
	Date& operator ++ (int);

	Date& operator -= (int d);
	Date& operator -- ();
	Date& operator -- (int);

	Date operator+(int d);

	bool operator == (const Date& lhs);
	bool operator <= (const Date& lhs);
	bool operator < (const Date& lhs);
	bool operator >= (const Date& lhs);
	bool operator > (const Date& lhs);
	bool operator != (const Date& lhs);

	void getRealDate();

	friend std::istream& operator >> (std::istream& in, Date& date);
	friend std::ostream& operator << (std::ostream& out, Date& date);

	std::string toString();
};

