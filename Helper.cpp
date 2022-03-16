#include "Helper.h"
#include "User.h"
#include <fstream>
#include <iostream>
using namespace std;

int Helper::getLastContactId(AddressBook* book) {
	ifstream ifs;
	char c;
	int id = -1;
	string idStr = "";

	ifs.open(book->getBookPath());
	if (!ifs) return 0;
	if (ifs.peek() == ifstream::traits_type::eof()) return 0;
	
	ifs.seekg(-1, ios::end);

	int pos = ifs.tellg();

	while (true) {
		ifs.seekg(pos);
		ifs.get(c);
		if (pos == 0) {
			while (true) {
				ifs.seekg(pos);
				ifs.get(c);
				if (c == '|') {
					id = stoi(idStr); break;
				}
				idStr.push_back(c);
				pos++;
			}
			break;
		}
		if (char(c) == '\n') {
			ifs >> id;
			break;
		}
		pos--;
	}
	ifs.close();
	cout << "ID: " << id;
	return id;
}
bool Helper::checkIfContactAlreadyExists(vector<Contact> bookVector, Contact test) {
	Contact contact;

	for (int i = 0; i < bookVector.size(); i++) {
		contact = bookVector[i];

		if(contact.Equals(test)) return true;
	}
	return false;
}
bool Helper::isNumber(string text) {
	for (int i = 0; i < text.length(); i++) {
		if (isdigit(text[i]) == 0) return false;
	}
	return true;
}
void Helper::displayInfoNoDataInBookAddress() {
	cout << "W ksiazce kontaktowej nie ma jeszcze zadnych danych!" << endl << endl;
	cout << "Wcisnij dowolny przycisk, aby powrocic do glownego Menu" << endl;
	cin.ignore();
	getchar();
}
int Helper::returnContactIndexIfExists(vector<Contact> bookVector, int idChosen) {
	int contactIndex = -1;

	for (int i = 0; i < bookVector.size(); i++) {
		if (idChosen == bookVector[i].getContactId()) {
			contactIndex = i;
			break;
		}
	}
	return contactIndex;
}
void Helper::displayInfoNoSuchContactInAddressBook() {
	cout << "-------------------------" << endl;
	cout << "Brak kontaktu o podanym ID." << endl;
	cout << "-------------------------" << endl;
	cin.ignore();
	getchar();
}
string Helper::getNewPassword(User user){
	string password = "";
	string oldPassword = "";
	cout << "--ZMIANA HASLA--" << endl;
	cout << "Aby ustawic nowe haslo, najpierw prosze podac stare haslo" << endl;
	while (oldPassword != user.getPassword()) {
		cout << endl << "Podaj stare haslo: ";
		cin.ignore(); getline(cin, oldPassword);
		if (oldPassword != user.getPassword()) cout << "Wprowadzono niepoprawne stare haslo. Sprobuj jeszcze raz" << endl;
	}
	cout << "Poprawnie wprowadzono stare haslo" << endl;
	while (password == "") {
		cout << endl << "Podaj nowe haslo: ";
		getline(cin, password);
	}
	return password;
}


