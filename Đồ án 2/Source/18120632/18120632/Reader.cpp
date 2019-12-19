#include "Reader.h"

void Reader::standardized() {
	util.standardizedUPPERCASE(_ID);
	util.standardized(_name);

	if (_job.compare("DOC GIA KHONG CUNG CAP THONG TIN NAY") != 0)
		util.standardized(_job);
}

//==========================CONSTRUCTOR==============================//
Reader::Reader() {
	_ID = _identityCard = _name = _job = "";
	_birthDay = Date();
}

Reader::Reader(string ID, string identityCard, string name, string job, string gender, Date birthDay) {
	_ID = ID;
	_identityCard = identityCard;
	_name = name;
	_job = job;
	_gender = gender;
	_birthDay = birthDay;
}

Reader::Reader(const Reader& rhs) {
	_ID = rhs._ID;
	_identityCard = rhs._identityCard;
	_name = rhs._name;
	_job = rhs._job;
	_gender = rhs._gender;
	_birthDay = rhs._birthDay;
}

Reader& Reader::operator= (const Reader& rhs) {
	_ID = rhs._ID;
	_identityCard = rhs._identityCard;
	_name = rhs._name;
	_job = rhs._job;
	_gender = rhs._gender;
	_birthDay = rhs._birthDay;

	return *this;
}
//====================================SETTER=====================================//
void Reader::setID(string ID) {
	_ID = ID;
}

void Reader::setIdentityCard(string identityCard) {
	_identityCard = identityCard;
}

void Reader::setName(string name) {
	_name = name;
}

void Reader::setJob(string job) {
	_job = job;
}

void Reader::setGender(string gender) {
	_gender = gender;
}

void Reader::setBirthDay(const Date& birthDay) {
	_birthDay = birthDay;
}

//====================================GETTER=====================================//
string Reader::getID() {
	return _ID;
}

string Reader::getIdentityCard() {
	return _identityCard;
}

string Reader::getName() {
	return _name;
}

string Reader::getJob() {
	return _job;
}

string Reader::getGender() {
	return _gender;
}

Date Reader::getBirthDay() {
	return _birthDay;
}

//=================================PROCESS_METHOD================================//
void Reader::addNewReader() {
	rewind(stdin);
	cout << "Ma doc gia: ";
	getline(cin, _ID);

	if (_ID.empty())
		throw "ERROR: Thong tin ID khong duoc phep bo trong";
	util.standardizedUPPERCASE(_ID);

	rewind(stdin);
	cout << "So can cuoc/Chung minh nhan dan (Neu co): ";
	getline(cin, _identityCard);

	util.standardizedUPPERCASE(_identityCard);

	if (!_identityCard.empty()) {
		if (!util.isIdentityCard(_identityCard))
			throw "ERROR: So can cuoc/Chung minh nhan dan phai la 1 day so chi gom cac so tu 0-9";
	}
	else
		_identityCard = "DOC GIA KHONG CUNG CAP THONG TIN NAY";
		
	rewind(stdin);
	cout << "Ten doc gia: ";
	getline(cin, _name);

	if (_name.empty())
		throw "ERROR: Thong tin ten doc gia khong duoc phep bo trong";

	rewind(stdin);
	cout << "Nghe nghiep doc gia (Neu co): ";
	getline(cin, _job);
	
	if (_job.empty())
		_job = "DOC GIA KHONG CUNG CAP THONG TIN NAY";

	rewind(stdin);
	cout << "Nhap vao gioi tinh (Chi co the nhap nam hoac nu): ";
	getline(cin, _gender);

	if (_gender.empty())
		throw "ERROR: Thong tin gioi tinh khong duoc phep bo trong";

	util.standardized(_gender);

	if (_gender.compare("Nam") != 0 && _gender.compare("Nu") != 0)
		throw "ERROR: Gioi tinh nhap vao chi co the la nam hoac nu!!";

	int day, month, year;
	cout << "Ngay thang nam sinh: " << endl;
	
	cout << "Nhap ngay sinh: ";
	if (!(cin >> day) || day < 0)
		throw "ERROR: Ngay sinh phai la mot so duong";

	cout << "Nhap thang sinh: ";
	if (!(cin >> month) || month < 0)
		throw "ERROR: Thang sinh phai la mot so duong";

	cout << "Nhap nam sinh: ";
	if (!(cin >> year) || year < 0)
		throw "ERROR: Nam sinh phai la mot so duong";

	_birthDay.setDay(day);
	_birthDay.setMonth(month);
	_birthDay.setYear(year);

	if (!_birthDay.checkDate())
		throw "ERROR: Ngay thang nam sinh khong hop le";
}

void Reader::readReaderFromDatabase(fstream& Database) {
	char temp[1000];
	char s;

	Database.get(s);
	Database.getline(temp, 1000);
	_ID = temp;

	Database.getline(temp, 1000);
	_identityCard = temp;

	Database.getline(temp, 1000);
	_name = temp;

	Database.getline(temp, 1000);
	_job = temp;

	Database.getline(temp, 1000);
	_gender = temp;

	int day, month, year;
	
	Database >> day;
	Database.get(s);
	Database >> month;
	Database.get(s);
	Database >> year;
	Database.get(s);

	_birthDay.setDay(day);
	_birthDay.setMonth(month);
	_birthDay.setYear(year);

	int n;
	string bookID;

	Database >> n;
	for (int i = 0; i < n; ++i) {
		Database >> bookID;
		_booksBorrow.push_back(bookID);
	}

	for (int i = 0; i < n; ++i) {
		Database >> day;
		Database.get(s);
		Database >> month;
		Database.get(s);
		Database >> year;

		Date temp(day, month, year);

		_datesBorrow.push_back(temp); 
	}
}

void Reader::writeReaderToDatabase(fstream& Database) {
	standardized();

	Database << _ID << endl;
	Database << _identityCard << endl;
	Database << _name << endl;
	Database << _job << endl;
	Database << _gender << endl;
	Database << _birthDay.toString() << endl;
	Database << _booksBorrow.size() << endl;
	for (auto ID : _booksBorrow)
		Database << ID << endl;

	for (auto date : _datesBorrow)
		Database << date.toString() << endl;
}

void Reader::writeReaderOnConsole() {
	cout << "Ma doc gia: " << _ID << endl;
	cout << "So can cuoc/Chung minh nhan dan: " << _identityCard << endl;
	cout << "Ten doc gia: " << _name << endl;
	cout << "Nghe nghiep: " << _job << endl;
	cout << "Gioi tinh: " << _gender << endl;
	cout << "Ngay thang nam sinh: " << _birthDay.toString() << endl << endl;
}

//==================================BORROW_BOOK==================================//
void Reader::addBookToBorrow(string bookID) {
	_booksBorrow.push_back(bookID);
}

int Reader::getNumberOfBookToBorrw() {
	return _booksBorrow.size();
}

void Reader::addDateBorrow(Date date) {
	_datesBorrow.push_back(date);
}

Date Reader::getDateBorrow(string bookID) {
	int i = 0;
	for (auto& book : _booksBorrow)
		if (book.compare(bookID) == 0) 
			return _datesBorrow[i];
		else
			++i;
}

list<string> Reader::getBookListBorrow() {
	return _booksBorrow;
}

bool Reader::checkLate() {
	Date today;
	today.getRealDate();

	for (auto date : _datesBorrow)
		if ((date + 7) < today)
			return true;

	return false;
}

void Reader::returnBook(string bookID) {
	int i = 0;
	for (auto book : _booksBorrow)
		if (book.compare(bookID) == 0)
			break;
		else
			++i;

	_booksBorrow.remove(bookID);
	
	vector<Date> temp;

	for (int j = 0; j < _datesBorrow.size(); ++j) {
		if (j != i)
			temp.push_back(_datesBorrow[j]);
	}

	_datesBorrow = temp;
}