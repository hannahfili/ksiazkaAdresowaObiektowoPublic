#pragma once
#include "AddressBook.h"
#include "IMenu.h"
#include "User.h"
class MenuShowContacts:public IMenu
{
private:
	AddressBook& book;
public:
	MenuShowContacts(AddressBook& book) :book(book) {};
	
	virtual IMenu* display() override;
	void showTextMenu();
	void displayAllContacts();

};

