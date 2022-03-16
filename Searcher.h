#pragma once
#include "AddressBook.h"
class Searcher
{
	AddressBook& book;
public:
	Searcher(AddressBook& book) : book(book) {}
	void searchByNameOrSurname(string param);
	void searchFriends();
};

