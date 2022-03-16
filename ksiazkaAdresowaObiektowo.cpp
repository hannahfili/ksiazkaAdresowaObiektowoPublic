
#include <iostream>
#include <string>
#include "UsersFile.h"
#include "Option.h"
#include "MainMenu.h"

using namespace std;

int main()
{
    string bookAddressPath = "KsiazkaAdresowa.txt";
    string usersPath = "uzytkownicy.txt";

    IMenu* currentMenu = new MainMenu (bookAddressPath, usersPath);

    while (currentMenu != NULL) {
        //IMenu* previousMenu = currentMenu;
        currentMenu = currentMenu->display();
        //delete previousMenu;
    }

    return 0;

}

