#pragma once
#include "Contact.h"
#include "User.h"
#include <string>

using namespace std;

class AddressBook
{
private:
	vector<Contact> book;
	string bookPath;
	string usersPath;
	User user;

public:
	bool createdCorrectly;

	AddressBook(string bookPath, string usersPath, User user);
	bool addContact();
	void deleteContact();
	void displayAllContactsData(string message = "Twoj wybor: ");
	bool deleteContactFromVector(int indexInVector);
	void editContact();
	void setBookElement(int bookIndex, Contact contact) { book[bookIndex] = contact; }
	void setUserNewPassword(string newPassword) { user.setUserPassword(newPassword); }

	vector<Contact> getVector() { return book; }
	string getBookPath() { return bookPath; }
	string getUsersPath() { return usersPath; }
	User getUser() { return user; }
};

