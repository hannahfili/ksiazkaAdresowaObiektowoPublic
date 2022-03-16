#pragma once
#include "IMenu.h"
#include <string>
#include "AddressBook.h"
using namespace std;

class MenuLoggedIn : public IMenu {
private:
	AddressBook& book;
public:
	MenuLoggedIn(AddressBook& b) : book(b) {};
	IMenu* display() override;
	
	void showTextMenu(User u);
};

