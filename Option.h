#pragma once
#include <string>
#include "User.h"
using namespace std;
class Option
{
private:
	string usersPath;

public:
	Option(string u) : usersPath(u) {};
	User logIn();
};

