#pragma once
#include <string>
#include "User.h"

using namespace std;

class UsersFile
{
private:
	string usersPath;
public:
	UsersFile(string usersPath) :usersPath(usersPath) {};
	bool loginIsOccupied(string login);
	int loadLastUsersId();
	void saveUserToFile(User u);
};

