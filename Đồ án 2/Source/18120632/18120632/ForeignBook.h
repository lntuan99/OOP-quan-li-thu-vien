#pragma once

#include "Book.h"

class ForeignBook : public Book
{
private:
	string _ISBN;

public:
	//======================================CONSTRUCTOR=======================================//
	ForeignBook();
	ForeignBook(string ID, string name, string authorName, string publishingCompanyName, bool isBorrow, unsigned int price, string ISBN);
	ForeignBook(const ForeignBook& rhs);
	ForeignBook& operator=(const ForeignBook& rhs);

	//========================================SETTER==========================================//
	void setISBN(string ISBN);

	//========================================GETTER==========================================//
	string getISBN();

	//====================================PROCESS METHODs=====================================//
	void addNewBook();
	void writeBookOnDatabase(fstream& Database);
	void writeBookOnConsole();
	void readBookOnDatabase(fstream& Database);
};

