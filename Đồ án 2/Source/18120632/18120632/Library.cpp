#include "Library.h"

//==============================CONSTRUCTOR================================//
Library::Library() {
	readBookFromDatabase();
	readReaderFromDatabase();
	getBorrower();
	getBookBorrow();
}

//===============================UTILITIES=================================//
void Library::clearBookList() {
	for (auto& book : _books)
		delete book;

	_books.clear();
}

void Library::clearReaderList() {
	for (auto& reader : _readers)
		delete reader;

	_readers.clear();
}
//===============================DESTRUCTOR================================//
Library::~Library() {
	for (auto& book : _books)
		delete book;

	for (auto& reader : _readers)
		delete reader;
}

//=================================BOOKs===================================//
void Library::readBookFromDatabase() {
	fstream database(DATABASE_BOOK, ios::in);

	clearBookList();
	_books.clear();

	int n;
	database >> n;

	for (int i = 0; i < n; ++i) {
		Book* book = NULL;
		int option;
		char c;

		database >> option;
		database.get(c);
		
		if (option == 1)
			book = new VietNameseBook;
		else if (option == 2)
			book = new ForeignBook;

		book->readBookOnDatabase(database);
		_books.push_back(book);
	}

	database.close();
}

void Library::writeBookToDatabase() {
	fstream database(DATABASE_BOOK, ios::out);

	database << _books.size() << endl;

	for (auto book : _books)
		book->writeBookOnDatabase(database);

	database.close();
}

void Library::addBook() {
	Book* book = NULL;

	int option = 0;

	try {
		cout << "1. Them sach Tieng Viet" << endl;
		cout << "2. Them sach Ngoai Van" << endl;
		cout << "\tNhap vao lua chon cua ban: ";
		
		if (!(cin >> option)) {
			cin.clear();
			throw "ERROR: Lua chon nhap vao phai la mot so!!";
		}

		if (option < 1 || option > 2) {
			throw "ERROR: Lua chon nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2!!!";
		}

		if(option == 1)
			book = new VietNameseBook;
		else if (option == 2)
			book = new ForeignBook;

		try {
			if (option == 1) {
				book->addNewBook();
				Book* temp = findBookByID(book->getID());
				if (temp == NULL) {
					_books.push_back(book);
					cout << "THEM SACH MOI THANH CONG!!!" << endl;
				}
				else {
					cout << "ID sach da ton tai trong thu vien!!!" << endl;
					cout << "THEM SACH MOI KHONG THANH CONG!!!" << endl;
					delete book;
				}
			}
			else if (option == 2) {
				book->addNewBook();
				Book* temp1 = findBookByID(book->getID());
				Book* temp2 = findBookByISBN(((ForeignBook*)book)->getISBN());

				if (temp1 == NULL && temp2 == NULL) {
					_books.push_back(book);
					cout << "THEM SACH MOI THANH CONG!!!" << endl;
				}
				else if (temp1 != NULL) {
					cout << "ID sach da ton tai trong thu vien!!!" << endl;
					cout << "THEM SACH MOI KHONG THANH CONG!!!" << endl;
					delete book;
				} 
				else if (temp2 != NULL) {
					cout << "ISBN sach da ton tai trong thu vien!!!" << endl;
					cout << "THEM SACH MOI KHONG THANH CONG!!!" << endl;
					delete book;
				}
			}
		}
		catch (const char* message) {
			cout << message << endl;
			cout << "THEM SACH MOI KHONG THANH CONG!!!" << endl;
		}

		writeBookToDatabase();
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "THEM SACH MOI KHONG THANH CONG!!!" << endl;
	}
}

void Library::printBookListOnConsole() {
	cout << "So sach trong thu vien: " << _books.size() << endl << endl;
	for (auto book : _books)
		book->writeBookOnConsole();
}

//============================FIND_BOOK_METHOD=============================//
void Library::findBook() {
	int option = 0;
	try {
		cout << "1. Tim sach theo ID" << endl;
		cout << "2. Tim sach theo ten sach" << endl;
		cout << "3. Tim sach theo ten tac gia" << endl;
		cout << "4. Tim sach theo ten nha xuat ban" << endl;
		cout << "5. Tim sach theo gia thanh" << endl;
		cout << "6. Tim sach theo tinh trang cho muon" << endl;
		cout << "7. Tim sach theo ISBN (Chi danh cho sach ngoai van)" << endl;
		cout << "\tNhap vao lua chon cua ban: ";
		if (!(cin >> option)) {
			rewind(stdin);
			cin.clear();
			throw "ERROR: Lua chon phai la mot so!!";
		}

		if (option < 1 || option > 7) {
			rewind(stdin);
			cin.clear();
			option = 0;
			throw "ERROR: Lua chon phai la mot so lon hon hoac bang 1 va nho hon hoac bang 7!!";
		}

		switch (option) {
		case 1: {
			string ID;
			rewind(stdin);
			cout << "Nhap vao ID sach can tim: ";
			getline(cin, ID);

			util.standardizedUPPERCASE(ID);
			Book* res = findBookByID(ID);

			if (res != NULL) {
				cout << "Thong tin sach can tim: \n";
				res->writeBookOnConsole();
			}
			else
				cout << "Khong tim thay sach co ID: " << ID << "!!!" << endl;

			break;
		}
		case 2: {
			string name;
			rewind(stdin);
			cout << "Nhap vao ten sach can tim: ";
			getline(cin, name);

			util.standardizedUPPERCASE(name);
			list<Book*> res = findBookByName(name);

			if (res.size() != 0) {
				cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
				cout << "Danh sach cac sach co ten can tim: \n";

				for (auto book : res)
					book->writeBookOnConsole();
			}
			else
				cout << "Khong tim thay sach co ten " << name << "!!" << endl;

			break;
		}
		case 3: {
			string authorName;
			rewind(stdin);
			cout << "Nhap vao ten tac gia can tim: ";
			getline(cin, authorName);

			util.standardized(authorName);
			list<Book*> res = findBookByAuthorName(authorName);

			if (res.size() != 0) {
				cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
				cout << "Danh sach cac sach cua tac gia can tim: \n";

				for (auto book : res)
					book->writeBookOnConsole();
			}
			else
				cout << "Khong co sach cua tac gia " << authorName << "!!!" << endl;
			break;
		}
		case 4: {
			string publishingCompanyName;
			rewind(stdin);
			cout << "Nhap vao ten tac gia can tim: ";
			getline(cin, publishingCompanyName);

			util.standardizedUPPERCASE(publishingCompanyName);
			list<Book*> res = findBookByPublishingCompanyName(publishingCompanyName);

			if (res.size() != 0) {
				cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
				cout << "Danh sach cac sach cua nha xuat ban can tim: \n";

				for (auto book : res)
					book->writeBookOnConsole();
			}
			else
				cout << "Khong co sach cua nha xuat ban " << publishingCompanyName << "!!!" << endl;
			break;
		}
		case 5: {
			int min, max;
			try {
				try {
					cout << "Nhap vao gia tien thap nhat: ";
					if (!(cin >> min) || min < 0) {
						rewind(stdin);
						cin.clear();
						throw "ERRROR: Gia tien phai la so lon hon 0!!";
					}
				}
				catch (const char* message) {
					cout << message << endl;
					cout << "TIM KIEM KHONG THANH CONG!!!" << endl;
				}

				try {
					cout << "Nhap vao gia tien thap nhat: ";
					if (!(cin >> max) || max < 0) {
						rewind(stdin);
						cin.clear();
						throw "ERRROR: Gia tien phai la so lon hon 0!!";
					}
				}
				catch (const char* message) {
					cout << message << endl;
					cout << "TIM KIEM KHONG THANH CONG!!!" << endl;
				}

				if (min > max) {
					throw "ERROR: MIN phai nho hon hoac bang MAX";
				}

				list<Book*> res = findBookByPrice(min, max);

				if (res.size() != 0) {
					cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
					cout << "Danh sach cac sach co gia trong khoang " << min << " - " << max << ": " << endl;

					for (auto book : res)
						book->writeBookOnConsole();
				}
				else
					cout << "Khong co sach co gia trong khoang " << min << " - " << max << " !!!" << endl;
			}
			catch (const char* message) {
				cout << message << endl;
				cout << "TIM KIEM KHONG THANH CONG!!!" << endl;
			}

			break;
		}
		case 6: {
			bool isBorrow = false;
			int choose = 0;
			try {
				cout << "1. Sach da cho muon" << endl;
				cout << "2. Sach chua cho muon" << endl;
				cout << "\tNhap vao lua chon cua ban: ";

				if (!(cin >> choose)) {
					rewind(stdin);
					cin.clear();
					throw "ERROR: Lua chon phai la mot so!!";
				}
				else if (choose < 1 || choose > 2) {
					rewind(stdin);
					cin.clear();
					choose = 0;
					throw "ERROR: Lua chon phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2!!";
				}

				if (choose == 1)
					isBorrow = true;
				else if (choose == 2)
					isBorrow = false;

				list<Book*> res = findBookByBorrow(isBorrow);

				if (res.size() != 0) {
					cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
					if (isBorrow)
						cout << "Danh sach cac sach da cho muon: " << endl;
					else
						cout << "Danh sach cac sach chua cho muon: " << endl;

					for (auto book : res)
						book->writeBookOnConsole();
				}
				else if(isBorrow)
					cout << "Danh sach sach da cho muon rong!!!" << endl;
				else 
					cout << "Danh sach sach chua cho muon rong!!!" << endl;

			}
			catch (const char* message) {
				cout << message << endl;
				cout << "TIM KIM KHONG THANH CONG!!!" << endl;
			}
			break;
		}
		case 7: {
			string ISBN;
			rewind(stdin);
			cout << "Nhap vao ISBN sach can tim: ";
			getline(cin, ISBN);

			util.standardizedUPPERCASE(ISBN);
			Book* res = findBookByISBN(ISBN);

			if (res != NULL) {
				cout << "Thong tin sach can tim: \n";
				res->writeBookOnConsole();
			}
			else
				cout << "Khong tim thay sach co ISBN: " << ISBN << "!!!" << endl;

			break;
		}
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "Nhap lua chon khong thanh cong!!" << endl;
	}
}

Book* Library::findBookByID(string ID) {
	for (auto& book : _books)
		if (book->getID().compare(ID) == 0)
			return book;

	return NULL;
}

Book* Library::findBookByISBN(string ISBN) {
	for (auto& book : _books)
		if (book->getKind() == 2)
			if (((ForeignBook*)book)->getISBN().compare(ISBN) == 0)
			return book;

	return NULL;
}

list<Book*> Library::findBookByName(string name) {
	list<Book*> res;
	for (auto& book : _books)
		if (book->getName().compare(name) == 0)
			res.push_back(book);

	return res;
}

list<Book*> Library::findBookByAuthorName(string authorName) {
	list<Book*> res;
	for (auto& book : _books)
		if (book->getAuthorName().compare(authorName) == 0)
			res.push_back(book);

	return res;
}

list<Book*> Library::findBookByPublishingCompanyName(string publishingCompanyName) {
	list<Book*> res;
	for (auto& book : _books)
		if (book->getPublishingCompanyName().compare(publishingCompanyName) == 0)
			res.push_back(book);

	return res;
}

list<Book*> Library::findBookByPrice(int min, int max) {
	list<Book*> res;
	for (auto& book : _books)
		if (book->getPrice() >= min && book->getPrice() <= max)
			res.push_back(book);

	return res;
}

list<Book*> Library::findBookByBorrow(bool isBorrow) {
	list<Book*> res;

	for (auto& book : _books)
		if (book->getBorrow() == isBorrow)
			res.push_back(book);

	return res;
}

//==============================REMOVE_BOOKs==============================//
void Library::removeBook() {
	int option = 0;

	try {
		cout << "1. Xoa sach theo ID" << endl;
		cout << "2. Xoa sach theo ISBN (Chi danh cho sach ngoai van)" << endl;
		cout << "\tNhap vao lua chon cua ban: ";

		if (!(cin >> option)) {
			cin.clear();
			throw "Lua chon nhap vao phai la mot so";
		}

		if (option < 1 || option > 2)
			throw "Lua chon nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";

		Book* res = NULL;

		if (option == 1) {
			string ID;
			rewind(stdin);
			cout << "Nhap vao ID cua sach can xoa: ";
			getline(cin, ID);

			util.standardizedUPPERCASE(ID);

			res = findBookByID(ID);
		}

		else if (option == 2) {
			string ISBN;
			rewind(stdin);
			cout << "Nhap vao ISBN cua sach can xoa: ";
			getline(cin, ISBN);

			util.standardizedUPPERCASE(ISBN);

			res = findBookByISBN(ISBN);
		}

		if (res == NULL) {
			cout << "KHONG TIM THAY SACH CAN XOA!!" << endl;
			return;
		}

		cout << "Thong tin sach can xoa: " << endl;
		res->writeBookOnConsole();

		cout << "Ban co chac muon xoa sach nay khoi database? " << endl;
		int choose;

		try {
			cout << "1. Co" << endl;
			cout << "2. Khong" << endl;
			cout << "\tNhap vao lua chon cua ban: ";
			if (!(cin >> choose)) {
				cin.clear();
				throw "ERROR: Lua chon nhap vao phai la mot so";
			}

			if (choose < 1 || choose > 2) {
				throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";
			}

			if (choose == 1) {
				_books.remove(res);
				writeBookToDatabase();

				cout << "Xoa sach thanh cong!!" << endl;

				delete res;
			}
			else if (choose == 2) {
				cout << "Thao tac da bi huy" << endl;
			}
		}
		catch (const char* message) {
			cout << message << endl;
			cout << "XOA SACH KHONG THANH CONG!!" << endl;
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "XOA SACH KHONG THANH CONG!!!" << endl;
	}
}

//===============================EDIT_BOOK================================//
void Library::editBook() {
	int option = 0;

	try {
		cout << "1. Chinh sua sach theo ID" << endl;
		cout << "2. Chinh sua sach theo ISBN (Chi danh cho sach ngoai van)" << endl;
		cout << "\tNhap vao lua chon cua ban: ";

		if (!(cin >> option)) {
			cin.clear();
			throw "Lua chon nhap vao phai la mot so";
		}

		if (option < 1 || option > 2)
			throw "Lua chon nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";

		Book* res = NULL;

		if (option == 1) {
			string ID;
			rewind(stdin);
			cout << "Nhap vao ID cua sach can chinh sua thong tin: ";
			getline(cin, ID);

			res = findBookByID(ID);

			if (res == NULL) {
				cout << "KHONG TIM THAY SACH CAN CHINH SUA THONG TIN!!" << endl;
				return;
			}
		}
		else if (option == 2) {
			string ISBN;
			rewind(stdin);
			cout << "Nhap vao ISBN cua sach can chinh sua thong tin: ";
			getline(cin, ISBN);

			util.standardizedUPPERCASE(ISBN);

			res = findBookByISBN(ISBN);

			if (res == NULL) {
				cout << "KHONG TIM THAY SACH CAN CHINH SUA THONG TIN!!" << endl;
				return;
			}
		}

		cout << "Thong tin sach can chinh sua: " << endl;
		res->writeBookOnConsole();

		if (res->getKind() == 1) {
			cout << "Ban co chac muon chinh sua sach nay?" << endl;
			int choose;

			try {
				cout << "1. Co" << endl;
				cout << "2. Khong" << endl;
				cout << "\tNhap vao lua chon cua ban: ";
				if (!(cin >> choose)) {
					cin.clear();
					throw "ERROR: Lua chon nhap vao phai la mot so";
				}

				if (choose < 1 || choose > 2) {
					throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";
				}

				if (choose == 1) {
					int choice = 0;
					try {
						cout << "1. Sua ID" << endl;
						cout << "2. Sua ten sach" << endl;
						cout << "3. Sua ten tac gia" << endl;
						cout << "4. Sua ten nha xuat ban" << endl;
						cout << "5. Sua gia tien sach" << endl;
						cout << "\tNhap vao lua chon cua ban" << endl;

						if (!(cin >> choice)) {
							cin.clear();
							throw "ERROR: Lua chon nhap vao phai la mot so";
						}

						if (choice < 1 || choice > 5) {
							throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 5";
						}

						try {
							switch (choice) {
							case 1: {
								rewind(stdin);
								string newID;
								cout << "Nhap vao ID moi cua sach: ";
								getline(cin, newID);

								if (newID.empty())
									throw "ERROR: Thong tin ID khong duoc phep bo trong!!!";

								util.standardizedUPPERCASE(newID);

								Book* temp = findBookByID(newID);

								if (temp != NULL) {
									cout << "Da co sach so huu ID nay!!!!" << endl;
									cout << "Moi sach chi so huu mot ID duy nhat!!!" << endl;
									cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!!" << endl;
								}

								else {
									res->setID(newID);
									cout << "Chinh sua thanh cong" << endl;
								}

								break;
							}
							case 2: {
								rewind(stdin);
								string newName;
								cout << "Nhap vao ten moi cua sach: ";
								getline(cin, newName);

								if (newName.empty())
									throw "ERROR: Thong tin ten sach khong duoc phep bo trong!!!";

								util.standardizedUPPERCASE(newName);

								res->setName(newName);
								cout << "Chinh sua thanh cong" << endl;
								break;
							}
							case 3: {
								rewind(stdin);
								string newAuthorName;
								cout << "Nhap vao ten moi cua tac gia: ";
								getline(cin, newAuthorName);

								if (newAuthorName.empty())
									throw "ERROR: Thong tin ten tac gia khong duoc phep bo trong!!!";

								util.standardized(newAuthorName);

								res->setAuthorName(newAuthorName);
								cout << "Chinh sua thanh cong" << endl;
								break;
							}
							case 4: {
								rewind(stdin);
								string newPublishingCompanyName;
								cout << "Nhap vao ten moi cua nha xuat ban: ";
								getline(cin, newPublishingCompanyName);

								if (newPublishingCompanyName.empty())
									throw "ERROR: Thong tin ten nha xuat ban khong duoc phep bo trong!!!";

								util.standardizedUPPERCASE(newPublishingCompanyName);

								res->setPublishingCompanyName(newPublishingCompanyName);
								cout << "Chinh sua thanh cong" << endl;
								break;
							}
							case 5: {
								long long newPrice;
								try {
									cout << "Nhap vao gia moi cua sach: ";

									if (!(cin >> newPrice)) {
										cin.clear();
										throw "ERROR: gia tien phai la mot so lon hon 0";
									}

									if (newPrice <= 0)
										throw "ERROR: gia tien phai la mot so lon hon 0";

									res->setPrice((unsigned int)newPrice);
									cout << "Chinh sua thanh cong" << endl;
								}
								catch (const char* message) {
									cout << message << endl;
									cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG" << endl;
								}
								break;
							}
							}
						}
						catch(const char* message) {
							cout << message << endl;
							cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!!" << endl;
						}
					}
					catch (const char* message) {
						cout << message << endl;
						cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!!" << endl;
					}

					writeBookToDatabase();
				}
				else if (choose == 2)
					cout << "Thao tac da bi huy!!" << endl;
			}
			catch (const char* message) {
				cout << message << endl;
				cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!" << endl;
			}
		}

		else if (res->getKind() == 2) {
			cout << "Ban co chac muon chinh sua sach nay?" << endl;
			int choose;

			try {
				cout << "1. Co" << endl;
				cout << "2. Khong" << endl;
				cout << "\tNhap vao lua chon cua ban: ";
				if (!(cin >> choose)) {
					cin.clear();
					throw "ERROR: Lua chon nhap vao phai la mot so";
				}

				if (choose < 1 || choose > 2) {
					throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";
				}

				if (choose == 1) {
					int choice = 0;
					try {
						cout << "1. Sua ID" << endl;
						cout << "2. Sua ten sach" << endl;
						cout << "3. Sua ten tac gia" << endl;
						cout << "4. Sua ten nha xuat ban" << endl;
						cout << "5. Sua gia tien sach" << endl;
						cout << "6. Sua ISBN sach" << endl;
						cout << "\tNhap vao lua chon cua ban" << endl;

						if (!(cin >> choice)) {
							cin.clear();
							throw "ERROR: Lua chon nhap vao phai la mot so";
						}

						if (choice < 1 || choice > 6) {
							throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 6";
						}

						switch (choice) {
						case 1: {
							rewind(stdin);
							string newID;
							cout << "Nhap vao ID moi cua sach: ";
							getline(cin, newID);

							if (newID.empty())
								throw "ERROR: Thong tin ID khong duoc phep bo trong!!!";

							util.standardizedUPPERCASE(newID);

							Book* temp = findBookByID(newID);

							if (temp != NULL) {
								cout << "Da co sach so huu ID nay!!!!" << endl;
								cout << "Moi sach chi so huu mot ID duy nhat!!!" << endl;
								cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!!" << endl;
							}

							else {
								res->setID(newID);
								cout << "Chinh sua thanh cong" << endl;
							}

							break;
						}
						case 2: {
							rewind(stdin);
							string newName;
							cout << "Nhap vao ten moi cua sach: ";
							getline(cin, newName);

							if (newName.empty())
								throw "ERROR: Thong tin ten sach khong duoc phep bo trong!!!";

							util.standardizedUPPERCASE(newName);

							res->setName(newName);
							cout << "Chinh sua thanh cong" << endl;
							break;
						}
						case 3: {
							rewind(stdin);
							string newAuthorName;
							cout << "Nhap vao ten moi cua tac gia: ";
							getline(cin, newAuthorName);

							if (newAuthorName.empty())
								throw "ERROR: Thong tin ten tac gia khong duoc phep bo trong!!!";

							util.standardized(newAuthorName);

							res->setAuthorName(newAuthorName);
							cout << "Chinh sua thanh cong" << endl;
							break;
						}
						case 4: {
							rewind(stdin);
							string newPublishingCompanyName;
							cout << "Nhap vao ten moi cua sach: ";
							getline(cin, newPublishingCompanyName);

							if (newPublishingCompanyName.empty())
								throw "ERROR: Thong tin ten nha xuat ban khong duoc phep bo trong!!!";

							util.standardizedUPPERCASE(newPublishingCompanyName);

							res->setPublishingCompanyName(newPublishingCompanyName);
							cout << "Chinh sua thanh cong" << endl;
							break;
						}
						case 5: {
							long long newPrice;
							try {
								cout << "Nhap vao gia moi cua sach: ";

								if (!(cin >> newPrice)) {
									cin.clear();
									throw "ERROR: gia tien phai la mot so lon hon 0";
								}

								if (newPrice <= 0)
									throw "ERROR: gia tien phai la mot so lon hon 0";

								res->setPrice((unsigned int)newPrice);
								cout << "Chinh sua thanh cong" << endl;
							}
							catch (const char* message) {
								cout << message << endl;
								cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG" << endl;
							}
							break;
						}
						case 6: {
							rewind(stdin);
							string newISBN;
							cout << "Nhap vao ten moi cua sach: ";
							getline(cin, newISBN);

							if (newISBN.empty())
								throw "ERROR: Thong tin ISBN khong duoc phep bo trong!!!";

							util.standardizedUPPERCASE(newISBN);

							Book* temp = findBookByISBN(newISBN);

							if (temp != NULL) {
								cout << "Da co sach so huu ISBN nay!!!!" << endl;
								cout << "Moi sach chi so huu mot ISBN duy nhat!!!" << endl;
								cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!!" << endl;
							}

							else {
								((ForeignBook*)res)->setISBN(newISBN);
								cout << "Chinh sua thanh cong" << endl;
							}

							break;
						}
						}
					}
					catch (const char* message) {
						cout << message << endl;
						cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!!" << endl;
					}

					writeBookToDatabase();
				}
				else if (choose == 2)
					cout << "Thao tac da bi huy!!" << endl;
			}
			catch (const char* message) {
				cout << message << endl;
				cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!" << endl;
			}
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "CHINH SUA THONG TIN SACH KHONG THANH CONG!!!" << endl;
	}
}

//===========================METHOD FOR READERs===========================//
void Library::readReaderFromDatabase() {
	fstream database(DATABASE_READER, ios::in);

	clearReaderList();
	
	int n;
	database >> n;

	for (int i = 0; i < n; ++i) {
		Reader* reader = new Reader;

		reader->readReaderFromDatabase(database);
		_readers.push_back(reader);
	}

	database.close();
}

void Library::writeReaderToDatabase() {
	fstream database(DATABASE_READER, ios::out);

	database << _readers.size() << endl;

	for (auto reader : _readers)
		reader->writeReaderToDatabase(database);

	database.close();
};

void Library::printReaderListOnConsole() {
	cout << "So doc gia da dang ki trong thu vien: " << _readers.size() << endl << endl;
	for (auto reader : _readers)
		reader->writeReaderOnConsole();
};

//=============================ADD_NEW_READER=============================//
void Library::addReader() {
	Reader* reader = NULL; 

	try {
		reader = new Reader;

		reader->addNewReader();
		
		Reader* temp1 = findReaderByID(reader->getID());

		if (temp1 != NULL) {
			cout << "Da ton tai ID doc gia tren trong database" << endl;
			cout << "Moi doc gia chi co 1 ID ton tai duy nhat" << endl;
			cout << "THEM DOC GIA KHONG THANH CONG" << endl;

			delete reader;
			return;
		}
		
		else if (reader->getIdentityCard().compare("DOC GIA KHONG CUNG CAP THONG TIN NAY") != 0) {
			Reader* temp2 = findReaderByIdentityCard(reader->getIdentityCard());

			if (temp2 != NULL) {
				cout << "Da ton tai so can cuoc/chung minh nhan dan doc gia tren trong database" << endl;
				cout << "Moi doc gia chi co 1 so can cuoc/chung minh nhan dan duy nhat" << endl;
				cout << "THEM DOC GIA KHONG THANH CONG" << endl;

				delete reader;
				return;
			}
		}
		
		cout << "THEM DOC GIA THANH CONG" << endl;
		_readers.push_back(reader);
	
			
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "THEM DOC GIA KHONG THANH CONG!!!" << endl;
	}

	writeReaderToDatabase();
};

//===========================FIND_READER_METHOD===========================//
void Library::findReader() {
	int option = 0;
	try {
		cout << "1. Tim doc gia theo ID" << endl;
		cout << "2. Tim doc gia theo so can cuoc/chung minh nhan dan" << endl;
		cout << "3. Tim doc gia theo ten" << endl;
		cout << "4. Tim doc gia theo nghe nghiep" << endl;
		cout << "5. Tim doc gia theo gioi tinh" << endl;
		cout << "6. Tim doc gia theo ngay/thang/nam sinh" << endl;
		
		cout << "\tNhap vao lua chon cua ban: ";
		if (!(cin >> option)) {
			rewind(stdin);
			cin.clear();
			throw "ERROR: Lua chon phai la mot so!!";
		}

		if (option < 1 || option > 7) {
			rewind(stdin);
			cin.clear();
			option = 0;
			throw "ERROR: Lua chon phai la mot so lon hon hoac bang 1 va nho hon hoac bang 6!!";
		}

		switch (option) {
		case 1: {
			string ID;
			rewind(stdin);
			cout << "Nhap vao ID doc gia can tim: ";
			getline(cin, ID);

			util.standardizedUPPERCASE(ID);
			Reader* res = findReaderByID(ID);

			if (res != NULL) {
				cout << "Thong tin doc gia can tim: \n";
				res->writeReaderOnConsole();
			}
			else
				cout << "Khong tim thay doc gia co ID: " << ID << "!!!" << endl;

			break;
		}
		case 2: {
			try {
				string identityCard;
				rewind(stdin);
				cout << "Nhap vao so can cuoc/chung minh nhan dan doc gia can tim: ";
				getline(cin, identityCard);

				if (!util.isIdentityCard(identityCard))
					throw "ERROR: So can cuoc/Chung minh nhan dan phai la 1 day so chi gom cac so tu 0-9";

				Reader* res = findReaderByIdentityCard(identityCard);

				if (res != NULL) {
					cout << "Thong tin doc gia can tim: \n";
					res->writeReaderOnConsole();
				}
				else
					cout << "Khong tim thay doc gia co so can cuoc/chung minh nhan dan: " << identityCard << "!!!" << endl;
			}
			catch (const char* message) {
				cout << message << endl;
				cout << "TIM KIEM KHONG THANH CONG" << endl;
			}
			
			break;
		}
		case 3: {
			string name;
			rewind(stdin);
			cout << "Nhap vao ten doc gia can tim: ";
			getline(cin, name);

			util.standardized(name);

			list<Reader*> res = findReaderByName(name);

			if (res.size() != 0) {
				cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
				cout << "Danh sach cac doc gia can tim: \n";

				for (auto reader : res)
					reader->writeReaderOnConsole();
			}
			else
				cout << "Khong co doc gia co ten " << name << "!!!" << endl;
			break;
		}
		case 4: {
			string job;
			rewind(stdin);
			cout << "Nhap vao nghe nghiep cua doc gia can tim: ";
			getline(cin, job);

			util.standardized(job);
			list<Reader*> res = findReaderByJob(job);

			if (res.size() != 0) {
				cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
				cout << "Danh sach cac doc giac can tim: \n";

				for (auto reader : res)
					reader->writeReaderOnConsole();
			}
			else
				cout << "Khong co doc gia co nghe nghiep " << job << "!!!" << endl;
			break;
		}
		case 5: {
			try {
				string gender;
				rewind(stdin);
				cout << "Nhap vao gioi tinh cua doc gia can tim: ";
				getline(cin, gender);

				util.standardized(gender);

				if (gender.compare("Nam") != 0 && gender.compare("Nu") != 0)
					throw "ERROR: Gioi tinh nhap vao chi co the la nam hoac nu";

				list<Reader*> res = findReaderByGender(gender);

				if (res.size() != 0) {
					cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
					cout << "Danh sach cac doc giac can tim: \n";

					for (auto reader : res)
						reader->writeReaderOnConsole();
				}
				else
					cout << "Khong co doc gia co gioi tinh " << gender << "!!!" << endl;
				break;
			}
			catch (const char* message) {
				cout << message << endl;
				cout << "TIM KIEM KHONG THANH CONG!!!" << endl;
			}
		}
		case 6: {
			int day, month, year;
			Date birthday;
			try {
				cout << "Nhap ngay sinh: ";
				if (!(cin >> day) || day < 0)
					throw "ERROR: Ngay sinh phai la mot so duong";

				cout << "Nhap thang sinh: ";
				if (!(cin >> month) || month < 0)
					throw "ERROR: Thang sinh phai la mot so duong";

				cout << "Nhap nam sinh: ";
				if (!(cin >> year) || year < 0)
					throw "ERROR: Nam sinh phai la mot so duong";

				birthday.setDay(day);
				birthday.setMonth(month);
				birthday.setYear(year);

				if (!birthday.checkDate())
					throw "ERROR: Ngay thang nam sinh nhap vao khong hop le!!!";

				list<Reader*> res = findReaderByBirthDay(birthday);

				if (res.size() != 0) {
					cout << "Co " << res.size() << " ket qua tim kiem: " << endl;
					cout << "Danh sach cac doc giac can tim: \n";

					for (auto reader : res)
						reader->writeReaderOnConsole();
				}
				else
					cout << "Khong co doc gia co ngay sinh " << birthday.toString() << "!!!" << endl;

			}
			catch (const char* message) {
				cout << message << endl;
				cout << "TIM KIEM KHONG THANH CONG!!!" << endl;
			}
		}
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "Nhap lua chon khong thanh cong!!" << endl;
	}
};

Reader* Library::findReaderByID(string ID) {
	for (auto& reader : _readers)
		if (reader->getID().compare(ID) == 0)
			return reader;

	return NULL;
}

Reader* Library::findReaderByIdentityCard(string identityCard) {
	for (auto& reader : _readers)
		if (reader->getIdentityCard().compare(identityCard) == 0)
			return reader;

	return NULL;
}

list<Reader*> Library::findReaderByName(string name) {
	list<Reader*> res;

	for (auto& reader : _readers)
		if (reader->getName().compare(name) == 0)
			res.push_back(reader);

	return res;
}

list<Reader*> Library::findReaderByJob(string job) {
	list<Reader*> res;

	for (auto& reader : _readers)
		if (reader->getJob().compare(job) == 0)
			res.push_back(reader);

	return res;
}

list<Reader*> Library::findReaderByGender(string gender) {
	list<Reader*> res;

	for (auto& reader : _readers)
		if (reader->getGender().compare(gender) == 0)
			res.push_back(reader);

	return res;
}

list<Reader*> Library::findReaderByBirthDay(Date birthday) {
	list<Reader*> res;

	for (auto& reader : _readers)
		if (reader->getBirthDay() ==  birthday)
			res.push_back(reader);

	return res;
}

//=============================REMOVE_READER==============================//
void Library::removeReader() {
	int option = 0;

	try {
		cout << "1. Xoa doc gia theo ID" << endl;
		cout << "2. Xoa doc gia theo so can cuoc/chung minh nhan dan" << endl;
		cout << "\tNhap vao lua chon cua ban: ";

		if (!(cin >> option)) {
			cin.clear();
			throw "Lua chon nhap vao phai la mot so";
		}

		if (option < 1 || option > 2)
			throw "Lua chon nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";

		Reader* res = NULL;

		if (option == 1) {
			string ID;
			rewind(stdin);
			cout << "Nhap vao ID cua doc gia can xoa: ";
			getline(cin, ID);

			util.standardizedUPPERCASE(ID);

			res = findReaderByID(ID);
		}

		else if (option == 2) {
			try {
				string identityCard;
				rewind(stdin);
				cout << "Nhap vao so can cuoc/chung minh nhan dan cua doc gia can xoa: ";
				getline(cin, identityCard);

				util.standardized(identityCard);

				if (!util.isIdentityCard(identityCard))
					throw "ERROR: So can cuoc/Chung minh nhan dan phai la 1 day so chi gom cac so tu 0-9";

				res = findReaderByIdentityCard(identityCard);
			}
			catch (const char* message) {
				cout << message << endl;
				cout << "XOA DOC GIA KHONG THANH CONG!!!" << endl;
			}
			
		}

		if (res == NULL) {
			cout << "KHONG TIM THAY DOC GIA CAN XOA!!" << endl;
			return;
		}

		cout << "Thong tin doc gia can xoa: " << endl;
		res->writeReaderOnConsole();

		cout << "Ban co chac muon xoa doc gia nay khoi database? " << endl;
		int choose;

		try {
			cout << "1. Co" << endl;
			cout << "2. Khong" << endl;
			cout << "\tNhap vao lua chon cua ban: ";
			if (!(cin >> choose)) {
				cin.clear();
				throw "ERROR: Lua chon nhap vao phai la mot so";
			}

			if (choose < 1 || choose > 2) {
				throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";
			}

			if (choose == 1) {
				_readers.remove(res);
				writeBookToDatabase();

				cout << "Xoa sach thanh cong!!" << endl;

				delete res;
			}
			else if (choose == 2) {
				cout << "Thao tac da bi huy" << endl;
			}
		}
		catch (const char* message) {
			cout << message << endl;
			cout << "XOA SACH KHONG THANH CONG!!" << endl;
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "XOA SACH KHONG THANH CONG!!!" << endl;
	}

	writeReaderToDatabase();
};

//==============================EDIT_READER===============================//
void Library::editReader() {
	int option = 0;

	try {
		cout << "1. Chinh sua doc gia theo ID" << endl;
		cout << "2. Chinh sua doc gia theo so can cuoc/chung minh nhan dan" << endl;
		cout << "\tNhap vao lua chon cua ban: ";

		if (!(cin >> option)) {
			cin.clear();
			throw "Lua chon nhap vao phai la mot so";
		}

		if (option < 1 || option > 2)
			throw "Lua chon nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";

		Reader* res = NULL;

		if (option == 1) {
			string ID;
			rewind(stdin);
			cout << "Nhap vao ID cua doc gia can chinh sua thong tin: ";
			getline(cin, ID);

			util.standardizedUPPERCASE(ID);

			res = findReaderByID(ID);

			if (res == NULL) {
				cout << "KHONG TIM THAY DOC GIA CAN CHINH SUA THONG TIN!!" << endl;
				return;
			}
		}
		else if (option == 2) {
			string identityCard;
			rewind(stdin);
			cout << "Nhap vao so can cuoc/chung minh nhan dan cua doc gia can chinh sua thong tin: ";
			getline(cin, identityCard);

			if (!util.isIdentityCard(identityCard))
				throw "ERROR: So can cuoc/Chung minh nhan dan phai la 1 day so chi gom cac so tu 0-9";

			res = findReaderByIdentityCard(identityCard);

			if (res == NULL) {
				cout << "KHONG TIM THAY DOC GIA CAN CHINH SUA THONG TIN!!" << endl;
				return;
			}
		}

		cout << "Thong tin doc gia can chinh sua: " << endl;
		res->writeReaderOnConsole();

		try {
			int choose;

			cout << "1. Co" << endl;
			cout << "2. Khong" << endl;
			cout << "\tNhap vao lua chon cua ban: ";

			if (!(cin >> choose)) {
				cin.clear();
				throw "ERROR: Lua chon nhap vao phai la mot so";
			}

			if (choose < 1 || choose > 2) {
				throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";
			}

			if (choose == 1) {
				int choice = 0;
				try {
					cout << "1. Sua ID" << endl;
					cout << "2. Sua so can cuoc/chung minh nhan dan" << endl;
					cout << "3. Sua ten doc gia" << endl;
					cout << "4. Sua nghe nghiep" << endl;
					cout << "5. Sua gioi tinh" << endl;
					cout << "6. Sua ngay thang nam sinh" << endl;
					cout << "\tNhap vao lua chon cua ban" << endl;

					if (!(cin >> choice)) {
						cin.clear();
						throw "ERROR: Lua chon nhap vao phai la mot so";
					}

					if (choice < 1 || choice > 6) {
						throw "ERROR: Lua cho nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 5";
					}

					try {
						switch (choice) {
						case 1: {
							rewind(stdin);
							string newID;
							cout << "Nhap vao ID moi cua doc gia: ";
							getline(cin, newID);

							if (newID.empty())
								throw "ERROR: Thong tin ID khong duoc phep bo trong!!!";

							util.standardizedUPPERCASE(newID);

							Reader* temp = findReaderByID(newID);

							if (temp != NULL) {
								cout << "Da co doc gia so huu ID nay!!!!" << endl;
								cout << "Moi doc gia chi so huu mot ID duy nhat!!!" << endl;
								cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG!!!" << endl;
							}

							else {
								res->setID(newID);
								cout << "Chinh sua thanh cong" << endl;
							}

							break;
						}
						case 2: {
							try {
								rewind(stdin);
								string newIdentityCard;
								cout << "Nhap vao ten moi cua sach: ";
								getline(cin, newIdentityCard);

								if (!util.isIdentityCard(newIdentityCard))
									throw "ERROR: So can cuoc/Chung minh nhan dan phai la 1 day so chi gom cac so tu 0-9";


								Reader* temp = findReaderByIdentityCard(newIdentityCard);

								if (temp != NULL) {
									cout << "Da co doc gia so huu so can cuoc/chung minh nhan dan nay!!!!" << endl;
									cout << "Moi doc gia chi so huu mot so can cuoc/chung minh nhan dan duy nhat!!!" << endl;
									cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG!!!" << endl;
								}

								else {
									res->setIdentityCard(newIdentityCard);
									cout << "Chinh sua thanh cong" << endl;
								}
							}
							catch (const char* message) {
								cout << message << endl;
								cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG" << endl;
							}

							break;
						}
						case 3: {
							rewind(stdin);
							string newName;
							cout << "Nhap vao ten moi cua doc gia: ";
							getline(cin, newName);

							if (newName.empty())
								throw "ERROR: Thong tin ten doc gia khong duoc phep bo trong!!!";

							util.standardized(newName);

							res->setName(newName);
							cout << "Chinh sua thanh cong" << endl;
							break;
						}
						case 4: {
							rewind(stdin);
							string newJob;
							cout << "Nhap vao nghe nghiep moi cua doc gia: ";
							getline(cin, newJob);

							util.standardized(newJob);

							res->setJob(newJob);
							cout << "Chinh sua thanh cong" << endl;
							break;
						}
						case 5: {
							rewind(stdin);
							string newGender;
							cout << "Nhap vao gioi tinh moi cua doc gia: ";
							getline(cin, newGender);

							if (newGender.empty())
								throw "ERROR: Thong tin gioi tinh doc gia khong duoc phep bo trong!!!";

							util.standardized(newGender);
							if (newGender.compare("Nam") != 0 && newGender.compare("Nu") != 0)
								throw "ERROR: Gioi tinh nhap vao chi co the la nam hoac nu";

							res->setGender(newGender);
							cout << "Chinh sua thanh cong" << endl;
							break;
						}
						case 6: {
							int day, month, year;
							Date newBirthday;
							try {
								cout << "Nhap ngay sinh: ";
								if (!(cin >> day) || day < 0)
									throw "ERROR: Ngay sinh phai la mot so duong";

								cout << "Nhap thang sinh: ";
								if (!(cin >> month) || month < 0)
									throw "ERROR: Thang sinh phai la mot so duong";

								cout << "Nhap nam sinh: ";
								if (!(cin >> year) || year < 0)
									throw "ERROR: Nam sinh phai la mot so duong";

								newBirthday.setDay(day);
								newBirthday.setMonth(month);
								newBirthday.setYear(year);

								if (!newBirthday.checkDate())
									throw "ERROR: Ngay thang nam sinh nhap vao khong hop le!!!";

								res->setBirthDay(newBirthday);
							}
							catch (const char* message) {
								cout << message << endl;
								cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG!!!" << endl;
							}

							break;
						}
						}
					}
					catch (const char* message) {
						cout << message << endl;
						cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG!!!" << endl;
					}
				}
				catch (const char* message) {
					cout << message << endl;
					cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG!!!" << endl;
				}
			}
			else if (choose == 2)
				cout << "Thao tac da bi huy!!" << endl;
		}
		catch (const char* message) {
			cout << message << endl;
			cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG!!" << endl;
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "CHINH SUA THONG TIN DOC GIA KHONG THANH CONG!!!" << endl;
	}

	writeReaderToDatabase();
}

//==============================BORROW_BOOK===============================//
void Library::borrowBook() {
	try {
		string readerID;

		rewind(stdin);
		cout << "Nhap vao ID cua doc gia muon sach: ";
		getline(cin, readerID);

		util.standardizedUPPERCASE(readerID);

		Reader* resReader = findReaderByID(readerID);

		if (resReader == NULL) {
			cout << "Khong tim thay doc gia co ID: " << readerID << endl;
			cout << "THAO TAC KHONG THANH CONG!!!" << endl;
			return;
		}

		if (resReader->getNumberOfBookToBorrw() == 5) {
			cout << "Doc gia da het luot muon sach!!!" << endl;
			cout << "Moi nguoi chi duoc muon toi da 5 quyen sach" << endl;
			return;
		}

		string bookID;
		rewind(stdin);
		cout << "Nhap vao ID cua sach can muon: ";
		getline(cin, bookID);

		util.standardizedUPPERCASE(bookID);

		Book* resBook = findBookByID(bookID);

		if (resBook == NULL) {
			cout << "Khong tim thay sach co ID: " << bookID << endl;
			cout << "THAO TAC KHONG THANH CONG!!!" << endl;
			return;
		}

		if (resBook->getBorrow()) {
			cout << "Sach da duoc muon!!!" << endl;
			cout << "THAO TAC KHONG THANH CONG" << endl;
			return;
		}

		Date today;
		today.getRealDate();

		cout << "Thong tin nguoi muon sach: " << endl;
		resReader->writeReaderOnConsole();

		cout << "Thong tin sach duoc muon: " << endl;
		resBook->writeBookOnConsole();

		cout << "Ngay muon sach: " << today.toString() << endl;
		cout << "Ngay het han muon sach: " << (today + 7).toString() << endl;

		try {
			int option = 0;
			cout << "Tiep tuc muon sach" << endl;
			cout << "1. Co" << endl;
			cout << "2. Khong" << endl;
			cout << "\tNhap vao lua chon cua ban: ";

			if (!(cin >> option)) {
				cin.clear();
				throw "Lua chon nhap vao phai la mot so";
			}

			if (option < 1 || option > 2)
				throw "Lua chon nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";

			if (option == 1) {
				resBook->addBorrower(readerID);
				resBook->setBorrow(true);
				resBook->addDateBorrow(today);

				resReader->addBookToBorrow(bookID);
				resReader->addDateBorrow(today);

				_booksBorrow.push_back(resBook);

				bool flag = false;
				for (auto rd : _readerBorrowBook) {
					if (rd->getID().compare(resReader->getID()) == 0)
						flag = true;
				}

				if (!flag)
					_readerBorrowBook.push_back(resReader);

				string filePath = resReader->getID() + "_" + resReader->getName() + "_" + resBook->getID() + ".txt";

				writeBallotBorrowBook(filePath, resReader, resBook);

				cout << "DA IN PHIEU MUON SACH CO TEN: " << filePath << " TRONG KHO DU LIEU" << endl;
				cout << "MUON SACH THANH CONG!!!" << endl;
			}

			else if (option == 2) {
				cout << "Thao tac da bi huy!!!" << endl;
				cout << "MUON SACH KHONG THANH CONG" << endl;
			}
		}
		catch (const char* message) {
			cout << message << endl;
			cout << "MUON SACH KHONG THANH CONG!!!" << endl;
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "THAO TAC KHONG THANH CONG!!!" << endl;
	}

	writeBookToDatabase();
	writeReaderToDatabase();
}

void Library::getBorrower() {
	_readerBorrowBook.clear();
	
	for (auto& reader : _readers)
		if (reader->getNumberOfBookToBorrw() > 0)
			_readerBorrowBook.push_back(reader);
}

void Library::getBookBorrow() {
	_booksBorrow.clear();

	for (auto& book : _books)
		if (book->getBorrow())
			_booksBorrow.push_back(book);
}

void Library::showListBorrower() {
	cout << "So nguoi muon sach trong thu vien: " << _readerBorrowBook.size() << endl << endl;

	for (auto& reader : _readerBorrowBook) {
		cout << "Nguoi muon sach" << endl;
		cout << "ID: " << reader->getID() << endl;
		cout << "Ten doc gia: " << reader->getName() << endl;
		cout << "So sach muon: " << reader->getNumberOfBookToBorrw() << endl << endl;
	}
}

void Library::showListBookBorrow() {
	cout << "So sach da cho muon: " << _booksBorrow.size() << endl << endl;

	for (auto& book : _booksBorrow) {
		cout << "ID sach: " << book->getID() << endl;
		cout << "Ten sach: " << book->getName() << endl;

		Reader* borrower = findReaderByID(book->getBorrower());
		cout << "ID nguoi muon sach: " << borrower->getID() << endl;
		cout << "Ten nguoi muon sach: " << borrower->getName() << endl;
		cout << "Ngay muon sach: " << borrower->getDateBorrow(book->getID()).toString() << endl;
		cout << "Han tra sach: " << (borrower->getDateBorrow(book->getID()) + 7).toString() << endl << endl;
	}
}

void Library::showListBorrowerLateForReturnBook() {
	int count = 0;
	Date today;
	today.getRealDate();

	for (auto& reader : _readerBorrowBook) {
		if (reader->checkLate())
			++count;
	}

	cout << "So nguoi tre han tra sach: " << count << endl << endl;

	for (auto& reader : _readerBorrowBook) {
		if (reader->checkLate()) {
			int cnt = 1;
			cout << "ID doc gia: " << reader->getID() << endl;
			cout << "Ten doc gia: " << reader->getName() << endl;
			cout << "Cac sach tre han: " << endl;

			for (auto bookID : reader->getBookListBorrow()) {
				Book* book = findBookByID(bookID);
				Date dateDeadline(reader->getDateBorrow(bookID) + 7);

				if (dateDeadline < today) {
					cout << cnt++ << "." << endl;
					int temp = 0;
					int fine;

					if (book->getKind() == 1) {
						cout << "Loai sach: Sach Tieng Viet" << endl;
						fine = VIETNAMESE_BOOK_FINE;
					}
					else {
						cout << "Loai sach: Sach Ngoai Van" << endl;
						fine = FOREIGN_BOOK_FINE;
					}
						
					cout << "ID sach: " << book->getID() << endl;
					cout << "Ten sach: " << book->getName() << endl;

					while (dateDeadline < today) {
						dateDeadline++;
						++temp;
					}

					unsigned long long res = temp * fine;
					cout << "So ngay tre han: " << temp << endl;
					cout << "So tien phat: " << res << endl;
				}
			}
			cout << endl;
		}
	}
}

void Library::showListBookLateForReturn() {
	int count = 0;
	for (auto& book : _booksBorrow) {
		if (book->checkLate())
			++count;
	}

	cout << "So sach tre han: " << count << endl;

	for (auto book : _booksBorrow) {
		if (book->checkLate()) {
			cout << "ID sach: " << book->getID() << endl;
			cout << "Ten sach: " << book->getName() << endl;

			Reader* borrower = findReaderByID(book->getBorrower());

			cout << "ID nguoi muon: " << borrower->getID() << endl;
			cout << "Ten nguoi muon: " << borrower->getName() << endl << endl;
		}
	}
}

void Library::returnBook() {
	try {
		string readerID;

		rewind(stdin);
		cout << "Nhap vao ID cua doc gia tra sach: ";
		getline(cin, readerID);

		util.standardizedUPPERCASE(readerID);

		Reader* resReader = findReaderByID(readerID);

		if (resReader == NULL) {
			cout << "Khong tim thay doc gia co ID: " << readerID << endl;
			cout << "THAO TAC KHONG THANH CONG!!!" << endl;
			return;
		}

		if (resReader->getNumberOfBookToBorrw() == 0) {
			cout << "Doc gia khong muon sach!!!" << endl;
			return;
		}

		Date today;
		today.getRealDate();

		int cnt = 1;
		cout << "Cac sach doc gia dang muon: " << endl;
		for (auto bookID : resReader->getBookListBorrow()) {
			Book* book = findBookByID(bookID);
			Date dateDeadline(resReader->getDateBorrow(bookID) + 7);

			cout << cnt++ << "." << endl;

			int temp = 0;
			int fine;
			if (book->getKind() == 1) {
				cout << "Loai sach: Sach Tieng Viet" << endl;
				fine = VIETNAMESE_BOOK_FINE;
			}
			else {
				cout << "Loai sach: Sach Ngoai Van" << endl;
				fine = FOREIGN_BOOK_FINE;
			}

			if (dateDeadline < today) {
				cout << "ID sach: " << book->getID() << endl;
				cout << "Ten sach: " << book->getName() << endl;

				while (dateDeadline < today) {
					dateDeadline++;
					++temp;
				}
				unsigned long long res = temp * fine;
				cout << "So ngay tre han: " << temp << endl;
				cout << "So tien phat: " << res << endl << endl;
			}

			else {
				cout << "ID sach: " << book->getID() << endl;
				cout << "Ten sach: " << book->getName() << endl;

				while (dateDeadline > today) {
					today++;
					++temp;
				}

				cout << "So ngay con lai: " << temp << endl << endl;
			}
		}

		string bookID;
		rewind(stdin);
		cout << "Nhap vao ID cua sach can tra: ";
		getline(cin, bookID);

		util.standardizedUPPERCASE(bookID);

		Book* resBook = findBookByID(bookID);

		if (resBook == NULL) {
			cout << "Khong tim thay sach co ID: " << bookID << endl;
			cout << "THAO TAC KHONG THANH CONG!!!" << endl;
			return;
		}

		if (!resBook->getBorrow()) {
			cout << "Sach dang trong trang thai khong duoc muon!!!" << endl;
			return;
		}
		
		if (resBook->getBorrower().compare(resReader->getID()) != 0) {
			cout << "Doc gia khong muon sach co ID: " << resBook->getID() << endl;
			return;
		}


		cout << "Thong tin nguoi muon sach: " << endl;
		resReader->writeReaderOnConsole();

		cout << "Thong tin sach duoc muon: " << endl;
		resBook->writeBookOnConsole();
		cout << endl;

		try {
			int option = 0;
			cout << "Tiep tuc tra sach" << endl;
			cout << "1. Co" << endl;
			cout << "2. Khong" << endl;
			cout << "\tNhap vao lua chon cua ban: ";

			if (!(cin >> option)) {
				cin.clear();
				throw "Lua chon nhap vao phai la mot so";
			}

			if (option < 1 || option > 2)
				throw "Lua chon nhap vao phai la mot so lon hon hoac bang 1 va nho hon hoac bang 2";

			if (option == 1) {
				resBook->returnBook();
				resReader->returnBook(bookID);
				getBorrower();
				getBookBorrow();

				string filePath = resReader->getID() + "_" + resReader->getName() + "_" + resBook->getID() + ".txt";
				removeFileBallotBorrowBook(filePath);

				cout << "DA XOA PHIEU MUON SACH CO TEN: " << filePath << " TRONG KHO DU LIEU" << endl;
				cout << "TRA SACH THANH CONG!!!" << endl;
			}

			else if (option == 2) {
				cout << "Thao tac da bi huy!!!" << endl;
				cout << "TRA SACH KHONG THANH CONG" << endl;
			}
		}
		catch (const char* message) {
			cout << message << endl;
			cout << "TRA SACH KHONG THANH CONG!!!" << endl;
		}
	}
	catch (const char* message) {
		cout << message << endl;
		cout << "THAO TAC KHONG THANH CONG!!!" << endl;
	}

	writeBookToDatabase();
	writeReaderToDatabase();
}

void Library::writeBallotBorrowBook(string filePath, Reader* reader, Book* book) {
	fstream database(filePath, ios::out);

	database << "ID nguoi muon: " << reader->getID() << endl;
	database << "Ten nguoi muon: " << reader->getName() << endl;
	database << "ID sach muon: " << book->getID() << endl;
	database << "Ngay muon sach: " << book->getDateBorrow().toString() << endl;
	database << "Han tra sach: " << (book->getDateBorrow() + 7).toString() << endl;
	database.close();
}

void Library::removeFileBallotBorrowBook(string filePath) {
	int res = remove(filePath.c_str());

	if (res != 0)
		cout << "Xoa phieu muon sach khong thanh cong" << endl;
}