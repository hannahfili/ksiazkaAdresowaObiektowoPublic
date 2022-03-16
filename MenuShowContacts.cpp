#include "MenuShowContacts.h"
#include "Searcher.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void MenuShowContacts::showTextMenu() {
	system("cls");
	cout << "KSIAZKA ADRESOWA" << endl << endl;
	cout << "---wyswietl kontakty---" << endl << endl;
	cout << "1. Wyswietl wszystkie kontakty" << endl;
	cout << "2. Wyszukaj konktakty po imieniu" << endl;
	cout << "3. Wyszukaj kontakty po nazwisku" << endl;
	cout << "4. Wyswietl przyjaciol" << endl;
	cout << "5. Wroc do glownego Menu" << endl;
	cout << "0. Wyjscie" << endl << endl;

	cout << "Wybierz, co chcesz zrobic: ";
}
IMenu* MenuShowContacts::display() {
	Searcher searcher(book);
	int wybor = 0;
	if (book.getVector().size()>0) {
		while (true) {
			showTextMenu();
			cin >> wybor;

			switch (wybor) {
			case 1:
				displayAllContacts();
				cin.ignore();
				getchar();
				break;
			case 2:
				searcher.searchByNameOrSurname("imie");
				break;
			case 3:
				searcher.searchByNameOrSurname("nazwisko");
				break;
			case 4:
				searcher.searchFriends();
				break;
			case 5:
				return this;
			case 0:
				exit(0);
				break;
			default:
				cout << "Wybrano wartosc spoza zakresu, sprobuj jeszcze raz" << endl;
				Sleep(2000);
				break;
			}
		}

	}
	else {
		cout << "W ksiazce kontaktowej nie ma jeszcze zadnych danych!" << endl << endl;
		cout << "Wcisnij dowolny przycisk, aby powrocic do glownego Menu" << endl;
		cin.ignore();
		getchar();

	}
	return this;
}
void MenuShowContacts::displayAllContacts() {
	for (int i = 0; i < book.getVector().size(); i++) {
		book.getVector()[i].displayContactData();
		cout << "-------------------------" << endl << endl;
	}
}

