#include "VietNameseBook.h"
#include <fstream>
#include <iostream>

//=====================================CONSTRUCTOR==========================================//
VietNameseBook::VietNameseBook() : Book() {
	_kind = 1;
}

VietNameseBook::VietNameseBook(string ID, string name, string authorName, string publishingCompanyName, bool isBorrow, unsigned int price): Book(ID, name, authorName, publishingCompanyName, isBorrow, price){
	_kind = 1;
}

VietNameseBook::VietNameseBook(const VietNameseBook& rhs) : Book(rhs){
	_kind = rhs._kind;
	_isBorrow = rhs._isBorrow;
}

VietNameseBook& VietNameseBook::operator=(const VietNameseBook& rhs) {
	_ID = rhs._ID;
	_name = rhs._name;
	_authorName = rhs._authorName;
	_publishingCompanyName = rhs._publishingCompanyName;
	_price = rhs._price;
	_kind = rhs._kind;
	return *this;
}

//===================================PROCESS METHODs========================================//
void VietNameseBook::addNewBook() {
	Book::addNewBook();
}

void VietNameseBook::writeBookOnDatabase(fstream& Database) {
	Database << _kind << endl;
	Book::writeBookOnDatabase(Database);
}

void VietNameseBook::writeBookOnConsole() {
	cout << "The loai sach: Tieng Viet" << endl;
	Book::writeBookOnConsole();
}

void VietNameseBook::readBookOnDatabase(fstream& Database) {
	Book::readBookOnDatabase(Database);
}

