#pragma once
#include <string>
#include "IMenu.h"
#include "AddressBook.h"
using namespace std;

class EditionMenu : public IMenu {
private:
	AddressBook& book;
	int chosenContactIndex;
public:
	EditionMenu(AddressBook& book, int index) : book(book), chosenContactIndex(index) {};
	IMenu* display() override;
	void showTextMenu(int indexContact);
	bool realizeChosenEditionOption(Contact contactToEdit, int chosenOption);
	Contact editNameOrSurname(Contact contact, string attribute);
	Contact editPhoneOrEmailOrAddress(Contact contact, string attribute);
	Contact editFriendStatus(Contact contact);
};

