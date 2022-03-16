#include "User.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

User User::logIn(string usersPath) {
	string login = "", password = "";

	cout << endl << "Podaj login: ";
	cin >> login;
	while (login == "") {
		cout << "Podano pusty ciag. Podaj login: ";
		cin >> login;
	}
	while (password == "") {
		cout << endl << "Podaj haslo: ";
		cin >> password;
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

bool User::checkLoginAndPassword(string log, string pas) {
	if (login == log && password == pas) return true;
	return false;
}

User User::loadUserData(string fileLine) {
	int id;
	string login, password;
	string part;

	int numerSeparatora = 0;

	for (int i = 0; i < fileLine.size(); i++) {

		if (fileLine[i] != '|') {
			part += fileLine[i];
		}
		else {
			numerSeparatora++;
			switch (numerSeparatora) {
			case 1:
				id = stoi(part);
				part = "";
				break;

			case 2:
				login = part;
				part = "";
				break;
			case 3:
				password = part;
				part = "";
				break;
			}
		}
	}
	User user(id, login, password);
	return user;
}





