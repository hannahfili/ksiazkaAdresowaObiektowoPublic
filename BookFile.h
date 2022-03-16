#pragma once
#include <string>
#include "User.h"
#include "Contact.h"
using namespace std;
class BookFile
{
private:
	string path;

public:
	BookFile(string path) : path(path) {};
	string changePasswordAndSaveToFile(User user, string usersPath);
	void saveContactToFile(Contact contact);
	bool saveBookAfterContactDeleteOrEdition(Contact contactToDeleteOrEdit, string mode);
};

