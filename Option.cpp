#include "Option.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <fstream>
#include "UsersFile.h"
#include "AddressBook.h"



User Option::logIn() {
	string login = "", password = "";
	UsersFile usersFile(usersPath);

	cout << endl << "Podaj login: ";
	cin.ignore();
	getline(cin, login);
	while (login == "") {
		cout << "Podano pusty ciag. Podaj login: ";
		getline(cin, login);
	}
	cin.ignore();
	while (password == "") {
		cout << endl << "Podaj haslo: ";
		getline(cin, password);
	}

	fstream usersFileStream;
	string fileLine;
	User user;
	usersFileStream.open(usersPath, ios::in);
	if (usersFileStream.good()) {
		while (getline(usersFileStream, fileLine)) {
			user = user.loadUserData(fileLine);
			if (user.checkLoginAndPassword(login, password)) {
				return user;
				break;
			}
		}
		usersFileStream.close();
	}
	user.setUserId(0);
	return user;
}


