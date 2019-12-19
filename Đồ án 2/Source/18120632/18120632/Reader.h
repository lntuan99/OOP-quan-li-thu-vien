#pragma once

#include <string>
#include "Book.h"
#include "Date.h"
#include "Util.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#define MAX_BOOK_CAN_BORROW 5

using namespace std;

class Reader
{
private:
	string _ID;
	string _identityCard;
	string _name;
	string _job; 
	string _gender;
	Date _birthDay;

	list<string> _booksBorrow;
	vector<Date> _datesBorrow;

	Util util;
	
public:
	void standardized();

	/*
		CONSTRUCTOR
	*/
	Reader();
	Reader(string ID, string identityCard, string name, string job, string gender, Date birthDay);
	Reader(const Reader& rhs);
	Reader& operator = (const Reader& rhs);

	//====================================SETTER=====================================//
	void setID(string ID);
	void setIdentityCard(string identityCard);
	void setName(string name);
	void setJob(string job);
	void setBirthDay(const Date& birthDay);
	void setGender(string gender);

	//====================================GETTER=====================================//
	string getID();
	string getIdentityCard();
	string getName();
	string getJob();
	string getGender();
	Date getBirthDay();

	//=================================PROCESS_METHOD================================//
	void addNewReader();
	void readReaderFromDatabase(fstream& Database);
	void writeReaderToDatabase(fstream& Database);
	void writeReaderOnConsole();

	//==================================BORROW_BOOK==================================//
	void addBookToBorrow(string bookID);
	int getNumberOfBookToBorrw();
	void addDateBorrow(Date date);
	Date getDateBorrow(string bookID);
	list<string> getBookListBorrow();
	bool checkLate();
	void returnBook(string bookID);
};

