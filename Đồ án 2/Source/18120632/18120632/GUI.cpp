#include "GUI.h"
#include <iostream>
#include <conio.h>

#pragma warning(disable: 4996)

using namespace std;

void GUI::brand() {
	cout << "********************************************************\n";
	cout << "*         DO AN 2 - LAP TRINH HUONG DOI TUONG          *\n";
	cout << "*              PHAN MEM QUAN LI THU VIEN               *\n";
	cout << "*              CLASS      : 18CTT5                     *\n";
	cout << "*              AUTHOR     : LE NHAT TUAN               *\n";
	cout << "*              STUDENT ID : 18120632                   *\n";
	cout << "*              INSTRUCTOR : MR. NGUYEN THANH AN        *\n";
	cout << "********************************************************\n";
}

void GUI::mainScene() {
	Library library;

	while (1) {
		char ch;
		try {
			system("cls");
			brand();
			int option;
			cout << "1. Quan li sach" << endl;
			cout << "2. Quan li doc gia" << endl;
			cout << "3. Quan li muon/tra sach" << endl;
			cout << "0. Thoat" << endl;
			cout << "Nhap vao lua chon cua ban: " << endl;

			if (!(cin >> option)) {
				cin.clear();
				throw  "Lua chon nhap vao phai la mot so lon hon hoac bang 0 va nho hon hoac bang 3!!!\nNHAN ENTER DE TIEP TUC!!!";
			}

			else if (option < 0 || option > 3) 
				throw  "Lua chon nhap vao phai la mot so lon hon hoac bang 0 va nho hon hoac bang 3!!!\nNHAN ENTER DE TIEP TUC!!!";
			
			else {
				switch (option) {
				case 1: {
					try {
						system("cls");
						brand();
						int choose;
						cout << "1. Xem danh sach cac sach trong thu vien" << endl;
						cout << "2. Them sach moi" << endl;
						cout << "3. Tim kiem sach" << endl;
						cout << "4. Chinh sua thong tin sach" << endl;
						cout << "5. Xoa sach" << endl;
						cout << "0. Quay tro lai" << endl;
						cout << "Nhap vao lua chon cua ban: " << endl;

						if (!(cin >> choose))
							throw "ERROR: Lua chon nhap vao phai la mot so";

						if (choose < 0 || choose > 5)
							throw "ERROR: Lua chon nhap vao phai la mot so lon hon hoac bang 0 va nho hon hoac bang 5";

						system("cls");
						brand();

						switch (choose) {
						case 1:
							library.printBookListOnConsole();
							break;
						case 2:
							library.addBook();
							break;
						case 3:
							library.findBook();
							break;
						case 4:
							library.editBook();
							break;
						case 5:
							library.removeBook();
							break;
						case 0:
							break;
						}

						if (choose != 0) {
							cout << "NHAN ENTER DE TIEP TUC!!!";
							while (_getch() != 13);
						}
						break;
					}
					catch (const char* message) {
						cout << message << endl;
						cout << "NHAN ENTER DE TIEP TUC!!!";
						rewind(stdin);
						while (_getch() != 13);
					}
					break;
				}
				case 2: {
					try {
						system("cls");
						brand();
						int choose;
						cout << "1. Xem danh sach cac doc gia trong thu vien" << endl;
						cout << "2. Them doc gia moi" << endl;
						cout << "3. Tim kiem doc gia" << endl;
						cout << "4. Chinh sua thong tin doc gia" << endl;
						cout << "5. Xoa doc gia" << endl;
						cout << "0. Quay tro lai" << endl;
						cout << "Nhap vao lua chon cua ban: " << endl;

						if (!(cin >> choose))
							throw "ERROR: Lua chon nhap vao phai la mot so";

						if (choose < 0 || choose > 5)
							throw "ERROR: Lua chon nhap vao phai la mot so lon hon hoac bang 0 va nho hon hoac bang 5";

						system("cls");
						brand();

						switch (choose) {
						case 1:
							library.printReaderListOnConsole();
							break;
						case 2:
							library.addReader();
							break;
						case 3:
							library.findReader();
							break;
						case 4:
							library.editReader();
							break;
						case 5:
							library.removeReader();
							break;
						case 0:
							break;
						}

						if (choose != 0) {
							cout << "NHAN ENTER DE TIEP TUC!!!";
							while (_getch() != 13);
						}
						break;
					}
					catch (const char* message) {
						cout << message << endl;
						cout << "NHAN ENTER DE TIEP TUC!!!";
						rewind(stdin);
						while (_getch() != 13);
					}
					break;
				}
				case 3: {
					try {
						system("cls");
						brand();
						int choose;
						cout << "1. Xem danh sach cac doc gia da muon sach trong thu vien" << endl;
						cout << "2. Xem danh sach cac sach da duoc muon" << endl;
						cout << "3. Xem danh sach cac doc gia qua han tra sach" << endl;
						cout << "4. Xem danh sach cac sach qua han tra sach" << endl;
						cout << "5. Them nguoi muon sach" << endl;
						cout << "6. Tra sach" << endl;
						cout << "0. Quay tro lai" << endl;
						cout << "Nhap vao lua chon cua ban: " << endl;

						if (!(cin >> choose))
							throw "ERROR: Lua chon nhap vao phai la mot so";

						if (choose < 0 || choose > 6)
							throw "ERROR: Lua chon nhap vao phai la mot so lon hon hoac bang 0 va nho hon hoac bang 6";

						system("cls");
						brand();

						switch (choose) {
						case 1:
							library.showListBorrower();
							break;
						case 2:
							library.showListBookBorrow();
							break;
						case 3:
							library.showListBorrowerLateForReturnBook();
							break;
						case 4:
							library.showListBookLateForReturn();
							break;
						case 5:
							library.borrowBook();
							break;
						case 6:
							library.returnBook();
							break;
						case 0:
							break;
						}

						if (choose != 0) {
							cout << "NHAN ENTER DE TIEP TUC!!!";
							while (_getch() != 13);
						}
						break;
					}
					catch (const char* message) {
						cout << message << endl;
						cout << "NHAN ENTER DE TIEP TUC!!!";
						rewind(stdin);
						while (_getch() != 13);
					}
					break;
				}
				}

				if (option == 0)
					break;
			}
		}
		catch (const char* message) {
			cout << message << endl;
			rewind(stdin);
			while (_getch() != 13);
		}
	}
}