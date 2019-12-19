#include "Book.h"
#include <iostream>

//=========================================UTILITIES=======================================//
void Book::standardized() {
	util.standardizedUPPERCASE(_ID);
	util.standardizedUPPERCASE(_name);
	util.standardized(_authorName);
	util.standardizedUPPERCASE(_publishingCompanyName);
}

//========================================CONSTRUCTOR======================================//
Book::Book() {
	_ID = _name = _authorName = _publishingCompanyName = "";
	_price = 0;
	_kind = 0;
	_isBorrow = false;
}

Book::Book(string ID, string name, string authorName, string publishingCompanyName, bool isBorrow, unsigned int price) {
	_ID = ID;
	_name = name;
	_authorName = authorName;
	_publishingCompanyName = publishingCompanyName;
	_isBorrow = isBorrow;
	_price = price;
}

Book::Book(const Book& rhs) {
	_ID = rhs._ID;
	_name = rhs._name;
	_authorName = rhs._authorName;
	_publishingCompanyName = rhs._publishingCompanyName;
	_isBorrow = rhs._isBorrow;
	_price = rhs._price;
}

Book& Book::operator=(const Book& rhs) {
	_ID = rhs._ID;
	_name = rhs._name;
	_authorName = rhs._authorName;
	_publishingCompanyName = rhs._publishingCompanyName;
	_isBorrow = rhs._isBorrow;
	_price = rhs._price;

	return *this;
}

//===========================================SETTER=========================================//
void Book::setID(string ID) {
	_ID = ID;
}

void Book::setName(string name) {
	_name = name;
}

void Book::setAuthorName(string authorName) {
	_authorName = authorName;
}

void Book::setPublishingCompanyName(string publishingCompanyName) {
	_publishingCompanyName = publishingCompanyName;
}

void Book::setBorrow(bool isBorrow) {
	_isBorrow = isBorrow;
}

void Book::setPrice(unsigned int price) {
	_price = price;
}

void Book::setKind(int kind) {
	_kind = kind;
}

//===========================================GETTER=========================================//
string Book::getID() {
	return _ID;
}

string Book::getName() {
	return _name;
}

string Book::getAuthorName() {
	return _authorName;
}

string Book::getPublishingCompanyName() {
	return _publishingCompanyName;
}

bool Book::getBorrow() {
	return _isBorrow;
}

unsigned int Book::getPrice() {
	return _price;
}

int Book::getKind() {
	return _kind;
}

//=======================================PROCESS METHODs=====================================//
void Book::addNewBook() {
	rewind(stdin);
	cout << "Ma sach: ";
	getline(cin, _ID);

	if (_ID.empty())
		throw "ERROR: Thong tin ID khong duoc phep bo trong!!";

	rewind(stdin);
	cout << "Ten sach: ";
	getline(cin, _name);

	if (_name.empty())
		throw "ERROR: Thong tin ten sach khong duoc phep bo trong!!";

	rewind(stdin);
	cout << "Ten tac gia: ";
	getline(cin, _authorName);

	if (_authorName.empty())
		throw "ERROR: Thong tin ten tac gia khong duoc phep bo trong!!";

	rewind(stdin);
	cout << "Ten nha xuat ban: ";
	getline(cin, _publishingCompanyName);

	if (_publishingCompanyName.empty())
		throw "ERROR: Thong tin ten nha xuat ban khong duoc phep bo trong!!";

	cout << "Gia sach: ";

	long long price = 0;
	if (!(cin >> price)) {
		rewind(stdin);
		cin.clear();
		throw "ERROR: Gia sach phai la so lon hon 0";
	}

	if (price <= 0) {
		throw "ERROR: Gia sach phai la so lon hon 0";
	}

	_price = (unsigned int)price;

	standardized();
}

void Book::writeBookOnDatabase(fstream& Database) {
	standardized();
	Database << _ID << endl;
	Database << _name << endl; 
	Database << _authorName << endl;
	Database << _publishingCompanyName << endl;
	Database << _price << endl;
	Database << _isBorrow << endl;
	
	if (_isBorrow) {
		Database << _borrower << endl;
		Database << _dateBorrow.toString() << endl;
	}
		
}

void Book::writeBookOnConsole() {
	cout << "Ma sach: " << _ID << endl;
	cout << "Ten sach: " << _name << endl;
	cout << "Ten tac gia: " << _authorName << endl;
	cout << "Ten nha xuat ban: " << _publishingCompanyName << endl;
	cout << "Tinh trang cho muon: " << _isBorrow << endl;
	cout << "Gia sach: " << _price << endl << endl;
}

void Book::readBookOnDatabase(fstream& Database) {
	char temp[10000];

	Database.getline(temp, 1000);
	_ID = temp;

	Database.getline(temp, 1000);
	_name = temp;

	Database.getline(temp, 1000);
	_authorName = temp;

	Database.getline(temp, 1000);
	_publishingCompanyName = temp;

	Database >> _price;
	Database >> _isBorrow;
	
	if (_isBorrow) {
		char s;
		int day, month, year;

		Database >> _borrower;

		Database >> day;
		Database.get(s);
		Database >> month;
		Database.get(s);
		Database >> year;

		Date temp(day, month, year);

		_dateBorrow = temp;
	}
		
}

//==========================================BORROWER=========================================//
void Book::addBorrower(string borrowerID) {
	_borrower = borrowerID;
}

string Book::getBorrower() {
	return _borrower;
} 

void Book::addDateBorrow(Date date) {
	_dateBorrow = date;
}

Date Book::getDateBorrow() {
	return _dateBorrow;

}

bool Book::checkLate() {
	Date today;
	today.getRealDate();

	if ((_dateBorrow + 7) < today)
		return true;

	return false;
}

void Book::returnBook() {
	_isBorrow = false;
	_borrower = "";
	_dateBorrow.setDay(0);
	_dateBorrow.setMonth(0);
	_dateBorrow.setYear(0);
}