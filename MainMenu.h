#pragma once
#include "IMenu.h"
#include <string>

using namespace std;


class MainMenu : public IMenu {
private:
	string bookPath;
	string usersPath;
public:
	MainMenu(string bookPath, string usersPath) : bookPath(bookPath), usersPath(usersPath) {};
	IMenu* display() override;
	void Register();
};

