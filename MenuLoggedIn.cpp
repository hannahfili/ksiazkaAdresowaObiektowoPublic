#include "MenuLoggedIn.h"
#include <string>
#include "MenuShowContacts.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "MainMenu.h"
#include "BookFile.h"
using namespace std;

void MenuLoggedIn::showTextMenu(User u) {
	system("cls");
	cout << "KSIAZKA ADRESOWA" << endl << endl;
	cout << "zalogowany jako: " << u.getLogin() << endl;
	cout << "MENU" << endl << endl;
	cout << "1. Wyswietl kontakty" << endl;
	cout << "2. Dodaj osobe do ksiazki" << endl;
	cout << "3. Usun osobe z ksiazki" << endl;
	cout << "4. Edytuj osobe z ksiazki" << endl;
	cout << "5. Zmien haslo" << endl;
	cout << "6. Wyloguj sie" << endl;
	cout << "0. Wyjscie" << endl << endl;

	cout << "Wybierz, co chcesz zrobic: ";
}

IMenu* MenuLoggedIn::display() {
	int choice = 0;
	string newPassword;
	MenuShowContacts menuShowContacts(book);
	BookFile file(book.getBookPath());
	while (true) {
		showTextMenu(book.getUser());
		cin >> choice;
		switch (choice) {
		case 1:
			menuShowContacts.display();
			break;
		case 2:
			if (!book.addContact()) {
				cout << "Problem z dodaniem kontaktu. Nie dodano kontaktu";
				getchar(); getchar();
			}
			break;
		case 3:
			book.deleteContact();
			break;
		case 4:
			book.editContact();
			break;
		case 5:
			newPassword = file.changePasswordAndSaveToFile(book.getUser(), book.getUsersPath());
			if (newPassword != "") book.setUserNewPassword(newPassword);
			else {
				cout << "Problem ze zmiana hasla. Haslo nie zostalo zmienione";
				getchar();
			}
			break;
		case 6:
			return this;
		case 0:
			exit(0);
		default:
			cout << "Wybrano wartosc spoza zakresu, sprobuj jeszcze raz" << endl;
			Sleep(2000);
			break;
		}
		
	}
	return this;
}