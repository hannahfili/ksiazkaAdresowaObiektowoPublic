#pragma once
#include "EditionMenu.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Helper.h"
#include "BookFile.h"
#include "Contact.h"
void EditionMenu::showTextMenu(int contactIndex) {
	system("cls");
	book.getVector()[contactIndex].displayContactData();
	cout << endl << endl;
	cout << "KSIAZKA ADRESOWA" << endl;
	cout << "---edycja---" << endl;
	cout << "1. imie" << endl;
	cout << "2. nazwisko" << endl;
	cout << "3. numer telefonu" << endl;
	cout << "4. email" << endl;
	cout << "5. adres" << endl;
	cout << "6. etykieta przyjaciel" << endl;
	cout << "7. powrot do glownego menu" << endl;
	cout << "0. Wyjscie" << endl << endl;
	cout << "Wybierz, ktora dana chcesz edytowac: ";
}


IMenu* EditionMenu::display() {
	string chosenOption = "";
	Helper helper;
	Contact contactToEdit;
	while (true) {
		showTextMenu(chosenContactIndex);
		cin >> chosenOption;
		if (helper.isNumber(chosenOption)) {
			contactToEdit = book.getVector()[chosenContactIndex];
			if(realizeChosenEditionOption(contactToEdit, stoi(chosenOption))) return this;
		}
		else cout << "Podano niepoprawne dane" << endl;
		Sleep(1000);
		system("cls");
	}
}

bool EditionMenu::realizeChosenEditionOption(Contact contactToEdit, int chosenOption) {
	enum comeBack { exit, returnToMainMenu, none };
	comeBack back = none;
	switch (chosenOption) {
	case 1:
		contactToEdit = editNameOrSurname(contactToEdit, "name");
		break;
	case 2:
		contactToEdit = editNameOrSurname(contactToEdit, "surname");
		break;
	case 3:
		contactToEdit = editPhoneOrEmailOrAddress(contactToEdit, "phoneNumber");
		break;
	case 4:
		contactToEdit = editPhoneOrEmailOrAddress(contactToEdit, "email");
		break;
	case 5:
		contactToEdit = editPhoneOrEmailOrAddress(contactToEdit, "address");
		break;
	case 6:
		contactToEdit = editFriendStatus(contactToEdit);
		break;
	case 7:
		back = returnToMainMenu;
		break;
	case 0:
		back = exit;
		break;
	default:
		cout << "Wybrano wartosc spoza zakresu, sprobuj jeszcze raz" << endl;
		Sleep(2000);
		break;
	}

	book.setBookElement(chosenContactIndex, contactToEdit);
	BookFile bookFile(book.getBookPath());
	bookFile.saveBookAfterContactDeleteOrEdition(contactToEdit, "edycja");
	if (back == exit) std::exit(0);
	if (back == returnToMainMenu) return true;
	return false;

}
Contact EditionMenu::editNameOrSurname(Contact contact, string attribute) {
	string choice = "";
	string field;
	attribute == "imie" ? field = contact.getName() : field = contact.getSurname();

	system("cls");
	cout << "--edycja--!!!" << endl;
	cout << "Rodzaj danej do zmiany: " + attribute << endl;
	cout << "Stare " + attribute + ": " + field;
	cout << endl << "Wprowadz nowe " + attribute + ": ";

	cin.ignore();
	getline(cin, choice);
	cout << endl << endl << "Nowe " + attribute + ": " + choice << endl;
	Sleep(1000);

	if (attribute == "name")  contact.setName(choice);
	else contact.setSurname(choice);
	return contact;

}
Contact EditionMenu::editPhoneOrEmailOrAddress(Contact contact, string attribute) {

	string choice = "";
	string field;
	if (attribute == "email") field = contact.getEmail();
	else if (attribute == "phoneNumber") field = contact.getPhoneNumber();
	else field = contact.getAddress();

	system("cls");
	cout << "--edycja--" << endl;
	cout << "Stary " + attribute + ": " + field << endl;
	cout << endl << "Wprowadz nowy " + attribute + ": ";

	cin.ignore();
	getline(cin, choice);

	cout << endl << endl << "Nowy " + attribute + ": " + choice << endl;
	Sleep(1000);

	if (attribute == "email") contact.setEmail(choice);
	else if (attribute == "phoneNumber") contact.setPhoneNumber(choice);
	else contact.setAddress(choice);
	return contact;
}
Contact EditionMenu::editFriendStatus(Contact contact) {
	string choice = "";
	system("cls");
	cout << "--edycja--" << endl;
	cout << "Stary status przyjaciela: ";
	if (contact.getFriendStatus()==true) cout << "przyjaciel";
	else cout << "znajomy";
	cout << "\nCzy chcesz zmienic status przyjaciela? t/n" << endl;
	cout << "Twoj wybor: ";
	cin.ignore();
	getline(cin, choice);

	if (choice == "t") {
		contact.setFriendStatus(!contact.getFriendStatus());
		cout << endl << endl << "Nowy status przyjaciela: ";
		if (contact.getFriendStatus() == true) cout << "przyjaciel";
		else cout << "znajomy";
	}
	else cout << endl << endl << "Nie zmieniono statusu przyjaciela ";

	Sleep(1000);

	return contact;
}