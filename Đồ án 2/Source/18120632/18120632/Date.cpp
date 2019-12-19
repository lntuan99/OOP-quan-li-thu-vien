#include "Date.h"
#pragma warning(disable: 4996)

const int Date::noDay[] = { 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date() {
	_day = 0;
	_month = 0;
	_year = 0;
}

Date::Date(int d, int m, int y) {
	_day = d;
	_month = m;
	_year = y;
}

Date::Date(const Date& otherDate) {
	_day = otherDate._day;
	_month = otherDate._month;
	_year = otherDate._year;
}

Date& Date::operator=(const Date& rhs) {
	_day = rhs._day;
	_month = rhs._month;
	_year = rhs._year;

	return *this;
}

int Date::getDay() {
	return _day;
}

int Date::getMonth() {
	return _month;
}

int Date::getYear() {
	return _year;
}

void Date::setDay(int d) {
	_day = d;
}

void Date::setMonth(int m) {
	_month = m;
}

void Date::setYear(int y) {
	_year = y;
}

Date& Date::operator += (int n) {
	for (int i = 1; i <= n; ++i) {
		++_day;

		if (_month == 2 && isLeapYear(_year))
			if (_day > 29) {
				_day = 1;
				_month = 3;
				continue;
			}

		if (_day > noDay[_month]) {
			_day = 1;
			++_month;

			if (_month > 12) {
				++_year;
				_month = 1;
			}
		}
	}

	return *this;
}

bool Date::isLeapYear(int year) {
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400));
}

Date& Date::operator++() {
	++_day;

	if (_month == 2 && isLeapYear(_year))
		if (_day > 29) {
			_day = 1;
			_month = 3;

			return *this;
		}

	if (_day > noDay[_month]) {
		_day = 1;
		++_month;

		if (_month > 12) {
			++_year;
			_month = 1;
		}
	}

	return *this;
}

Date& Date::operator++(int) {
	++_day;

	if (_month == 2 && isLeapYear(_year))
		if (_day > 29) {
			_day = 1;
			_month = 3;
			return *this;
		}

	if (_day > noDay[_month]) {
		_day = 1;
		++_month;

		if (_month > 12) {
			++_year;
			_month = 1;
		}
	}

	return *this;
}

Date Date::operator+(int d) {
	Date temp(*this);

	for (int i = 1; i <= d; ++i) {
		++temp._day;

		if (temp._month == 2 && isLeapYear(temp._year))
			if (temp._day > 29) {
				temp._day = 1;
				temp._month = 3;
				continue;
			}

		if (temp._day > noDay[temp._month]) {
			temp._day = 1;
			++temp._month;

			if (temp._month > 12) {
				++_year;
				temp._month = 1;
			}
		}
	}

	return temp;
}

Date& Date::operator-=(int n) {
	for (int i = 1; i <= n; ++i) {
		--_day;

		if (_month == 3 && isLeapYear(_year))
			if (_day == 0) {
				_day = 29;
				_month = 2;
				continue;
			}

		if (_day == 0) {
			_day = noDay[_month - 1];
			--_month;

			if (_month == 0) {
				--_year;
				_month = 12;
			}
		}
	}

	return *this;
}

Date& Date::operator--() {
	--_day;

	if (_month == 3 && isLeapYear(_year))
		if (_day == 0) {
			_day = 29;
			_month = 2;

			return *this;
		}

	if (_day == 0) {
		_day = noDay[_month - 1];
		--_month;

		if (_month == 0) {
			--_year;
			_month = 12;
		}
	}

	return *this;
}

Date& Date::operator--(int) {
	--_day;

	if (_month == 3 && isLeapYear(_year))
		if (_day == 0) {
			_day = 29;
			_month = 2;

			return *this;
		}

	if (_day == 0) {
		_day = noDay[_month - 1];
		--_month;

		if (_month == 0) {
			--_year;
			_month = 12;
		}
	}

	return *this;
}

bool Date::operator<=(const Date& otherDate) {
	if (_year < otherDate._year)
		return true;

	if (_year == otherDate._year)
		if (_month < otherDate._month)
			return true;

	if (_year == otherDate._year)
		if (_month == otherDate._month)
			if (_day <= otherDate._day)
				return true;

	return false;
}

bool Date::operator<(const Date& otherDate) {
	if (_year < otherDate._year)
		return true;

	if (_year == otherDate._year)
		if (_month < otherDate._month)
			return true;

	if (_year == otherDate._year)
		if (_month == otherDate._month)
			if (_day < otherDate._day)
				return true;

	return false;
}

bool Date::operator>=(const Date& otherDate) {
	if (_year > otherDate._year)
		return true;

	if (_year == otherDate._year)
		if (_month > otherDate._month)
			return true;

	if (_year == otherDate._year)
		if (_month == otherDate._month)
			if (_day >= otherDate._day)
				return true;

	return false;
}

bool Date::operator>(const Date& otherDate) {
	if (_year > otherDate._year)
		return true;

	if (_year == otherDate._year)
		if (_month > otherDate._month)
			return true;

	if (_year == otherDate._year)
		if (_month == otherDate._month)
			if (_day > otherDate._day)
				return true;

	return false;
}

bool Date::operator == (const Date& lhs) {
	return (_day == lhs._day && _month == lhs._month && _year == lhs._year);
}

bool Date::operator != (const Date& lhs) {
	return (_day != lhs._day || _month != lhs._month || _year != lhs._year);
}

std::istream& operator>>(std::istream& in, Date& date) {
	std::cout << "Nhap ngay: "; in >> date._day;

	std::cout << "Nhap thang: "; in >> date._month;
	std::cout << "Nhap nam: "; in >> date._year;

	return in;
}

std::ostream& operator<<(std::ostream& out, Date& date) {
	out << date.toString();

	return out;
}

std::string Date::toString() {
	std::string s = "";

	s += (std::to_string(_day) + "/");
	s += (std::to_string(_month) + "/");
	s += (std::to_string(_year));

	return s;
}

bool Date::checkDate() {
	time_t now = time(0);
	tm* ltm = localtime(&now);

	if (_year < 1900)
		return false;

	if (_month < 1 || _month > 12)
		return false;

	if (isLeapYear(_year))
		if (_month == 2)
			if (_day < 1 || _day > 29)
				return false;

	if (_day < 1 || _day > noDay[_month])
		return false;

	Date nowDate(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
	
	if (*this > nowDate)
		return false;

	return true;
}

void Date::getRealDate() {
	time_t now = time(0);
	tm* ltm = localtime(&now);

	_day = ltm->tm_mday;
	_month = ltm->tm_mon + 1;
	_year = ltm->tm_year + 1900;
}