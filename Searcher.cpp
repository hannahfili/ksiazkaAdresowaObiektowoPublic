#include "Searcher.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

void Searcher::searchByNameOrSurname(string param) {
	int count = 0;
	string dataToSearch = "", dataFromAddressBook = "", answer = "n";
	while (answer != "t") {
		cout << "Wpisz " << param << ": ";
		cin >> dataToSearch;

		cout << "\nCzy na pewno wyswietlic wszystkie konktakty ";
		param == "imie"? cout << "o imieniu ": cout << "o nazwisku ";
		/*if (param == "imie") cout << "o imieniu " << dataToSearch << " ? t / n ";
		else cout << "o nazwisku ";*/
		cout << dataToSearch << "? t / n ";
		cin >> answer;
		cout << endl;
	}

	transform(dataToSearch.begin(), dataToSearch.end(), dataToSearch.begin(), ::toupper);

	for (int i = 0; i < book.getVector().size(); i++) {
		param == "imie" ? dataFromAddressBook = book.getVector()[i].getName() :
			dataFromAddressBook = book.getVector()[i].getSurname();
		/*if (parametr == "imie") dataFromAddressBook = ksiazkaAdresowa[i].imie;
		else dataFromAddressBook = ksiazkaAdresowa[i].nazwisko;*/

		transform(dataFromAddressBook.begin(), dataFromAddressBook.end(), dataFromAddressBook.begin(), ::toupper);
		if (dataToSearch == dataFromAddressBook) {
			cout << "------------------" << endl << endl;
			book.getVector()[i].displayContactData();
			cout << endl;

			count++;
		}
	}
	if (count == 0) {
		if (param == "imie") cout << "Brak w ksiazce osoby o imieniu " << dataToSearch;
		else cout << "Brak w ksiazce osoby o nazwisku " << dataToSearch;
	}

	cin.ignore();
	getchar();
}
void Searcher::searchFriends() {
	int count = 0;

	for (int i = 0; i < book.getVector().size(); i++) {
		if (book.getVector()[i].getFriendStatus()) {
			cout << "------------------" << endl << endl;
			book.getVector()[i].displayContactData();
			cout << endl;
			count++;
		}
	}
	if (count == 0) {
		cout << "Brak w ksiazce osob o etykiecie \"przyjaciel\"";
	}
	cin.ignore();
	getchar();
}

