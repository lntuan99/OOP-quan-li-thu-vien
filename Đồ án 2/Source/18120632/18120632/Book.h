#pragma once

//#include "Reader.h"
#include "Util.h"
#include "Date.h"
#include <string>
#include <fstream>

#define VIETNAMESE_BOOK_FINE 10000
#define FOREIGN_BOOK_FINE 20000

using namespace std;

class Book
{
protected:
	int _kind;
	string _ID;
	string _name;
	string _authorName;
	string _publishingCompanyName;
	unsigned int _price;
	bool _isBorrow;
	string _borrower;
	Date _dateBorrow;

	Util util;

public:
	//===================================UTILITIES=================================//
	void standardized();

	//==================================CONSTRUCTOR================================//
	Book();
	Book(string ID, string name, string authorName, string publishingCompanyName, bool isBorrow, unsigned int price);
	Book(const Book& rhs);
	Book& operator=(const Book& rhs);

	//=====================================SETTER==================================//
	void setID(string ID);
	void setName(string name);
	void setAuthorName(string authorName);
	void setPublishingCompanyName(string publishingCompanyName);
	void setPrice(unsigned int Price);
	void setBorrow(bool isBorrow);
	void setKind(int kind);

	//=====================================GETTER===================================//
	string getID();
	string getName();
	string getAuthorName();
	string getPublishingCompanyName();
	bool getBorrow();
	unsigned int getPrice();
	int getKind();

	//==================================PROCESS METHODs===============================//
	virtual void addNewBook();
	virtual void writeBookOnDatabase(fstream& Database);
	virtual void writeBookOnConsole();
	virtual void readBookOnDatabase(fstream& Database);

	//=====================================BORROWER===================================// 
	void addBorrower(string borrowerID);
	string getBorrower();

	void addDateBorrow(Date date);
	Date getDateBorrow();

	bool checkLate();

	void returnBook();
	//====================================DESTRUCTOR==================================//
	virtual ~Book() {};
};

