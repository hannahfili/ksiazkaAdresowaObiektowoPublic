#pragma once
#include "AddressBook.h"
#include "Contact.h"
#include "User.h"
#include <string>
#include <fstream>
#include <iostream>
#include "Helper.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "EditionMenu.h"
#include "BookFile.h"

using namespace std;

AddressBook::AddressBook(string bookP, string usersP, User u) {

	bookPath = bookP;
	usersPath = usersP;
	user = u;

	fstream bookFileStream;
	string bookFileLine;
	string data;
	Contact contact(0, user.getUserId());

	bookFileStream.open(bookPath, ios::in);
	if (bookFileStream.good()) {

		while (getline(bookFileStream, bookFileLine)) {

			data = bookFileLine;

			contact.divideData(data, true);
			if (contact.getContactId() != 0) book.push_back(contact);


		}
		bookFileStream.close();
		createdCorrectly = true;
	}
	else {
		createdCorrectly = false;
	}
	//cout << book.size();
}

bool AddressBook::addContact() {
	string name, surname, address, friendStatusStr, email, phoneNumber;
	int id = 0;
	bool friendStatus = false, contactIsNew = false;
	cin.ignore();
	cout << "Podaj imie: ";	getline(cin, name);
	cout << "\nPodaj nazwisko: ";	getline(cin, surname);
	cout << "\nPodaj numer telefonu: ";	getline(cin, phoneNumber);
	cout << "\nPodaj adres e-mail: ";	getline(cin, email);
	cout << "\nPodaj adres: ";	getline(cin, address);
	cout << "\nDodac etykiete \"przyjaciel\"? t/n: ";	getline(cin, friendStatusStr);

	if (friendStatusStr == "t" || friendStatusStr == "T") friendStatus = true;
	else friendStatus = false;

	Contact contact(name, surname, address, phoneNumber, email, friendStatus, user.getUserId());

	Helper helper;
	int lastId = helper.getLastContactId(this);
	if (lastId != -1) contact.setContactId(lastId + 1);
	else return -1;

	if (book.size() > 0) {
		if (!helper.checkIfContactAlreadyExists(book, contact)) contactIsNew = true;
		else {
			cout << "!!! Nie dodano kontaktu, kontakt juz istnieje !!!\n\n";
			Sleep(2000);
		}
	}
	else contactIsNew = true;

	if (contactIsNew) {
		book.push_back(contact);
		cout << "Pomyslnie dodano kontakt. Szczegoly kontaktu:\n\n";
		contact.displayContactData();
		cin.ignore();
		BookFile bookFile(this->getBookPath());
		bookFile.saveContactToFile(contact);

		getchar();
		return true;
	}
	return false;
}

void AddressBook::deleteContact() {
	int contactToDeleteIdFromVector = -1;
	string choice = "";
	Contact contactToDelete;
	Helper helper;
	cout << "USUN OSOBE Z KONTAKTOW - WYBIERZ ID OSOBY" << endl << endl;
	if (book.size() == 0) {
		cout << "Ksiazka adresowa jest pusta - wcisnij dowolny przycisk, aby powrocic do glownego Menu";
		cin.ignore();
		getchar();
		return;
	}
	displayAllContactsData("Wybierz ID osoby, ktora chcesz usunac z ksiazki");

	cin >> choice; cout << endl;
	if (!helper.isNumber(choice)) {
		cout << "Podano niepoprawne dane" << endl;
		Sleep(2000); system("cls"); return;
	}
	
	for (int i = 0; i < book.size(); i++) {
		if (book[i].getContactId() == stoi(choice)) {
			contactToDeleteIdFromVector = i;
			contactToDelete = book[i];
			break;
		}
	}

	if (contactToDeleteIdFromVector != -1) {
		if (deleteContactFromVector(contactToDeleteIdFromVector)) {
			BookFile bookFile(this->getBookPath());
			bookFile.saveBookAfterContactDeleteOrEdition(contactToDelete, "usuniecie");
		}
	}
	else {
		cout << "-------------------------" << endl;
		cout << "Brak kontaktu o podanym ID." << endl;
		cout << "Kontakt nie zostal usuniety." << endl;
		cout << "Nacisnij dowolny klawisz, aby wrocic do glownego Menu" << endl;
		cout << "-------------------------" << endl;
	}

	cin.ignore();
	getchar();
	return;
}
void AddressBook::displayAllContactsData(string message) {
	for (int i = 0; i < book.size(); i++) {
		book[i].displayContactData();
		cout << "-------------------------" << endl << endl;
	}
	cout << message << endl;
}

bool AddressBook::deleteContactFromVector(int indexInVector) {
	string choiceStr = "";
	cout << "Czy na pewno chcesz usunac ponizszy kontakt? t/n" << endl << endl;

	cout << "-------------------------" << endl;
	book[indexInVector].displayContactData();
	cout << "-------------------------" << endl << endl;
	cin >> choiceStr;
	if (choiceStr == "t") {
		book.erase(book.begin() + indexInVector);
		system("cls");
		cout << "Pomyslnie usunieto kontakt. Nacisnij dowolny klawisz, aby wrocic do glownego menu.";
		return true;
	}
	else {
		cout << "-------------------------" << endl;
		cout << "Kontakt nie zostal usuniety" << endl;
		cout << "Nacisnij dowolny klawisz, aby wrocic do glownego Menu" << endl;
		cout << "-------------------------" << endl;
		return false;
	}
}

void AddressBook::editContact() {
	int chosenContactIndex = 0;
	string optionChosen = "", IDchosen = "";
	Helper helper;

	if (book.empty()) {
		helper.displayInfoNoDataInBookAddress();
		return;
	}
	cout << "EDYTUJ OSOBE Z KONTAKTOW - WYBIERZ ID OSOBY" << endl << endl;
	displayAllContactsData("Wybierz ID osoby, ktorej dane chcesz edytowac");
	cin >> IDchosen; cout << endl;
	if (!helper.isNumber(IDchosen)) {
		cout << "Wprowadzono niepoprawne dane" << endl; Sleep(2000); return;
	}
	chosenContactIndex = helper.returnContactIndexIfExists(book, stoi(IDchosen));

	if (chosenContactIndex == -1) {
		helper.displayInfoNoSuchContactInAddressBook();
		return;
	}
	else {
		EditionMenu editionMenu(*this, chosenContactIndex);
		editionMenu.display();
		
	}
}

