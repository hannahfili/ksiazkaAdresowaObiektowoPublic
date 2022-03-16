#pragma once
#include <string>
#include "AddressBook.h"
#include <vector>
#include "User.h"
using namespace std;

class Helper
{
public:
	bool isNumber(string text);
	int getLastContactId(AddressBook* book);
	bool checkIfContactAlreadyExists(vector<Contact> bookVector, Contact test);
	void displayInfoNoDataInBookAddress();
	int returnContactIndexIfExists(vector<Contact> bookVector, int idChosen);
	void displayInfoNoSuchContactInAddressBook();
	string getNewPassword(User user);

};

