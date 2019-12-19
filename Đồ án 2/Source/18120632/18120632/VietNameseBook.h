#pragma once

#include "Book.h"

class VietNameseBook : public Book
{
public:
	//======================================CONSTRUCTOR========================================//
	VietNameseBook();
	VietNameseBook(string ID, string name, string authorName, string publishingCompanyName, bool isBorrow, unsigned int price);
	VietNameseBook(const VietNameseBook& rhs);
	VietNameseBook& operator=(const VietNameseBook& rhs);

	//====================================PROCESS METHODs======================================//
	void addNewBook();
	void writeBookOnDatabase(fstream& Database);
	void writeBookOnConsole();
	void readBookOnDatabase(fstream& Database);
};

