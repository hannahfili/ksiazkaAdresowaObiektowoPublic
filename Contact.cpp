#include "Contact.h"
#include <iostream>

bool Contact::Equals(Contact testContact, bool checkAlsoId) {
	bool idsSame = false;
	bool dataSame = false;
	
	if (testContact.getName() == name
		&& testContact.getSurname() == surname
		&& testContact.getAddress() == address
		&& testContact.getEmail()== email
		&& testContact.getPhoneNumber()== phoneNumber)
		dataSame=true;
	if (checkAlsoId) {
		if (testContact.contactId == contactId && testContact.userId == userId) idsSame = true;
		if (idsSame && dataSame) return true;
		else return false;
	}
	if (dataSame) return true;
	return false;
}
bool Contact::EqualsById(Contact contactTest) {
	if (contactTest.getContactId() == contactId) return true;
	return false;
}
void Contact::displayContactData() {
	cout << "Id: " << contactId << endl;
	cout << "Imie: " << name << endl;
	cout << "Nazwisko: " << surname << endl;
	cout << "Adres: " << address << endl;
	cout << "Numer telefonu: " << phoneNumber << endl;
	cout << "E-mail: " << email << endl;
	if (friendStatus) {
		cout << "Kategoria: przyjaciel" << endl;
	}
	else {
		cout << "Kategoria: brak" << endl;
	}
}

void Contact::divideData(string data, bool onlyDataForParticularUser) {
	string part = "";
	string name, surname, phoneNumber, email, address;
	bool friendStatus;
	int separatorNumber = 1;
	int contactId = 0;
	int userIdFromFile = 0;

	for (int i = 0; i < data.size(); i++) {
		if (data[i] != '|') {
			part += data[i];
		}
		else {
			switch (separatorNumber) {
			case 1:
				this->contactId = atoi(part.c_str());
				break;
			case 2:
				userIdFromFile = atoi(part.c_str());
				if (userIdFromFile != userId && onlyDataForParticularUser) {
					this->contactId = 0;
					return;
				}
				else {
					userId = userIdFromFile;
				}
				break;
			case 3:
				this->name = part;
				break;
			case 4:
				this->surname = part;
				break;
			case 5:
				this->phoneNumber = part;
				break;
			case 6:
				this->email = part;
				break;
			case 7:
				this->address = part;
				break;
			case 8:
				if (part == "tak") {
					this->friendStatus = true;
				}
				else
					this->friendStatus = false;
				break;
			}
			separatorNumber++;
			part = "";
		}


	}
	
}
