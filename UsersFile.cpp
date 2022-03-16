#include "UsersFile.h"
#include "User.h"
#include <fstream>
#include <iostream>
using namespace std;

bool UsersFile::loginIsOccupied(string login) {
	fstream file;
	file.open(usersPath, ios::in);
	string fileLine, part;
	User u;
	if (file.good()) {
		//cout << "good";
		while (getline(file, fileLine)) {
			u = u.loadUserData(fileLine);
			if (login == u.getLogin()) return true;
		}
		file.close();
		return false;
	}
	else return false;
}
int UsersFile::loadLastUsersId() {
	ifstream ifs;
	char c;
	int id = -1;
	string idStr = "";

	ifs.open(usersPath);
	if (!ifs) return 0;
	if (ifs.peek() == ifstream::traits_type::eof()) return 0;

	ifs.seekg(-1, ios::end);

	int pos = ifs.tellg();

	while (true) {
		ifs.seekg(pos);
		ifs.get(c);
		if (pos == 0) {
			while (true) {
				ifs.seekg(pos);
				ifs.get(c);
				if (c == '|') {
					id = stoi(idStr); break;
				}
				idStr.push_back(c);
				pos++;
			}
			break;
		}
		if (char(c) == '\n') {
			ifs >> id;
			break;
		}
		pos--;
	}
	ifs.close();
	return id;
}
void UsersFile::saveUserToFile(User u) {
	ofstream file;
	file.open(usersPath, ios_base::app);
	if (u.getUserId() != 1) file << "\n";
	file << u.getUserId() << "|" << u.getLogin() << "|" << u.getPassword() << "|";
	file.close();
}