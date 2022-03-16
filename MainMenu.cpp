#include "MainMenu.h"
#include <string>
#include <iostream>
#include "User.h"
#include "Option.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "MenuLoggedIn.h"
#include "Helper.h"
#include "UsersFile.h"


using namespace std;

IMenu* MainMenu::display() {
	int choice = 0;
	string afterLogging = "";
	User user;

	system("cls");
	cout << "1. Logowanie" << endl;
	cout << "2. Rejestracja" << endl;
	cout << "0. Zamknij program" << endl;

	while (true) {
		cin >> choice;
		switch (choice) {
		case 1:
			user = user.logIn(usersPath);
			if (user.getUserId() != 0) {
				cout << "---Zalogowano---";
				Sleep(1000);
				AddressBook book(bookPath, usersPath, user);
				if (book.createdCorrectly) {
					MenuLoggedIn menuLoggedIn(book);
					menuLoggedIn.display();
				}

				else cout << "Nie udalo sie zaladowac danych do ksiazki adresowej" << endl;
			}
			else {
				cout << "Brak uzytkownika w systemie. Zarejestruj sie";
				Sleep(1000);
				break;
			}
			break;
		case 2:
			Register();
			cout << "---Pomyslnie zarejestrowano uzytkownika---";
			Sleep(1000);
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Wybrano wartosc spoza zakresu, sprobuj jeszcze raz" << endl;
			Sleep(1000);
			break;
		}
		break;
	}
	return this;
}

void MainMenu::Register() {
	string login = "";
	string password = "";

	cout << endl << "Podaj login: ";
	cin.ignore();
	getline(cin, login);
	UsersFile usersFile(usersPath);

	while (usersFile.loginIsOccupied(login) || login == "") {
		cout << "Podany login jest juz zajety / podano pusty ciag. Podaj nowy login: ";
		getline(cin, login);
	}

	while (password == "") {
		cout << endl << "Podaj haslo: ";
		getline(cin, password);
	}

	int lastId = usersFile.loadLastUsersId();
	if (lastId == -1) return;

	User newUser(lastId + 1, login, password);

	usersFile.saveUserToFile(newUser);

}
