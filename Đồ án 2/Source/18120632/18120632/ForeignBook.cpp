#include "ForeignBook.h"
#include <iostream>
#include <fstream>

//========================================CONSTRUCTOR======================================//
ForeignBook::ForeignBook() : Book() {
	_kind = 2;
	_ISBN = "";
}

ForeignBook::ForeignBook(string ID, string name, string authorName, string publishingCompanyName, bool isBorrow, unsigned int price, string ISBN) : Book(ID, name, authorName, publishingCompanyName, isBorrow, price) {
	_kind = 2;
	_ISBN = ISBN;
}

ForeignBook::ForeignBook(const ForeignBook& rhs) : Book(rhs) {
	_kind = rhs._kind;
	_ISBN = rhs._ISBN;
}

ForeignBook& ForeignBook::operator=(const ForeignBook& rhs) {
	_ID = rhs._ID;
	_name = rhs._name;
	_authorName = rhs._authorName;
	_publishingCompanyName = rhs._publishingCompanyName;
	_price = rhs._price;
	_isBorrow = rhs._isBorrow;
	_ISBN = rhs._ISBN;
	_kind = rhs._kind;

	return *this;
}

//=========================================SETTER==========================================//
void ForeignBook::setISBN(string ISBN) {
	_ISBN = ISBN;
}

//=========================================GETTER==========================================//
string ForeignBook::getISBN() {
	return _ISBN;
}

//=====================================PROCESS METHODs=====================================//
void ForeignBook::addNewBook() {
	rewind(stdin);
	cout << "Nhap vao ma ISBN: ";
	getline(cin, _ISBN);

	util.standardizedUPPERCASE(_ISBN);

	Book::addNewBook();
}

void ForeignBook::writeBookOnDatabase(fstream& Database) {
	Database << _kind << endl;
	Database << _ISBN << endl;
	Book::writeBookOnDatabase(Database);
}

void ForeignBook::writeBookOnConsole() {
	cout << "The loai sach: Ngoai van" << endl;
	cout << "ISBN: " << _ISBN << endl;
	Book::writeBookOnConsole();
}

void ForeignBook::readBookOnDatabase(fstream& Database) {
	char temp[10000];

	Database.getline(temp, 10000);
	_ISBN = temp;

	Book::readBookOnDatabase(Database);
}