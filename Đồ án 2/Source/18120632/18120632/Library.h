#pragma once

#include "Book.h"
#include "VietNameseBook.h"
#include "ForeignBook.h"
#include "Reader.h"
#include "Util.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <list>

#define DATABASE_BOOK "database-book.dat"
#define DATABASE_READER "database-reader.dat"
#define DATABASE_BORROW_BOOK "database-borrow-book.dat"

using namespace std;

class Library
{
private:
	list<Book*> _books;
	list<Reader*> _readers;
	
	list<Book*> _booksBorrow;
	list<Reader*> _readerBorrowBook;

	Util util;

	void clearBookList();
	void clearReaderList();
public:
	/*
		CONSTRUCTOR
	*/
	Library();
	
	/*
		METHOD FOR BOOKs
	*/
	void readBookFromDatabase();
	void writeBookToDatabase();
	void printBookListOnConsole();

	//=========================ADD_NEW_BOOK==========================//
	void addBook();

	//=======================FIND_BOOK_METHOD========================//
	void findBook();
	Book* findBookByID(string ID);
	Book* findBookByISBN(string ISBN);
	list<Book*> findBookByName(string name);
	list<Book*> findBookByAuthorName(string authorName);
	list<Book*> findBookByPublishingCompanyName(string publishingCompanyName);
	list<Book*> findBookByPrice(int min, int max);
	list<Book*> findBookByBorrow(bool isBorrow);

	//=========================REMOVE_BOOK===========================//
	void removeBook();

	//==========================EDIT_BOOK============================//
	void editBook();

	/*
		METHOD FOR READERs
	*/
	void readReaderFromDatabase();
	void writeReaderToDatabase();
	void printReaderListOnConsole();

	//=========================ADD_NEW_READER==========================//
	void addReader();

	//=======================FIND_READER_METHOD========================//
	void findReader();
	Reader* findReaderByID(string ID);
	Reader* findReaderByIdentityCard(string identityCard);
	list<Reader*> findReaderByName(string name);
	list<Reader*> findReaderByJob(string job);
	list<Reader*> findReaderByGender(string gender);
	list<Reader*> findReaderByBirthDay(Date birthday);

	//=========================REMOVE_READER===========================//
	void removeReader();

	//==========================EDIT_READER============================//
	void editReader();

	//==========================BORROW_BOOK============================//
	void getBorrower();
	void getBookBorrow();
	void borrowBook();
	void showListBorrower();
	void showListBookBorrow();
	void showListBorrowerLateForReturnBook();
	void showListBookLateForReturn();
	void returnBook();
	
	void writeBallotBorrowBook(string filePath, Reader* reader, Book* book);
	void removeFileBallotBorrowBook(string filePath);

	/*
		DESTRUCTOR
	*/
	~Library();
};
