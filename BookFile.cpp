#include "BookFile.h"
#include "User.h"
#include "Helper.h"
#include <fstream>

string BookFile::changePasswordAndSaveToFile(User userToChange, string usersPath) {
	Helper helper;
	string newPassword = helper.getNewPassword(userToChange);
	getchar();getchar();
	User user;
	fstream originalFile;
	ofstream temporaryFile;
	string fileLine, temporaryUsersPath = "uzytkownicy_tymczas.txt";
	char* char_arr_originalPath = &usersPath[0];
	char* char_arr_temporaryPath = &temporaryUsersPath[0];

	int readLineNumber = 0;
	originalFile.open(usersPath, ios::in);
	temporaryFile.open(temporaryUsersPath);

	if (originalFile.good()) {
		while (getline(originalFile, fileLine)) {
			readLineNumber++;
			user = user.loadUserData(fileLine);
			if (readLineNumber != 1) temporaryFile << endl;
			temporaryFile << user.getUserId() << "|" << user.getLogin() << "|";
			if (user.getUserId() == userToChange.getUserId()) temporaryFile << newPassword << "|";
			else temporaryFile << user.getPassword()<< "|";
		}
		temporaryFile.close();
		originalFile.close();
		remove(char_arr_originalPath);
		rename(char_arr_temporaryPath, char_arr_originalPath);
		return newPassword;
	}

	else return "";
}
void BookFile::saveContactToFile(Contact contact) {
	fstream file;

	file.open(path, ios_base::app);
	if (contact.getContactId() != 1) file << "\n";
	file << contact.getContactId() << "|";
	file << contact.getUserId() << "|";
	file << contact.getName() << "|";
	file << contact.getSurname() << "|";
	file << contact.getPhoneNumber() << "|";
	file << contact.getEmail() << "|";
	file << contact.getAddress() << "|";
	if (contact.getFriendStatus())
		file << "tak" << "|";
	else
		file << "nie" << "|";

	file.close();
}
bool BookFile::saveBookAfterContactDeleteOrEdition(Contact contactToDeleteOrEdit, string mode) {
	fstream originalFile;
	ofstream temporaryFile;
	string temporaryFilePath = "KsiazkaAdresowa_tymczas.txt", line;
	Contact contact(0);
	char* char_arr_originalPath = &path[0];
	char* char_arr_temporaryPath = &temporaryFilePath[0];

	int lineReadNumber = 0;
	originalFile.open(path, ios::in);
	temporaryFile.open(temporaryFilePath);

	if (originalFile.good()) {

		while (getline(originalFile, line)) {
			lineReadNumber++;
			contact.divideData(line);
			if (mode == "usuniecie") {
				if (!contactToDeleteOrEdit.Equals(contact, true)) {
					if (lineReadNumber != 1) temporaryFile << endl;
					temporaryFile << line;
				}
			}
			else if (mode == "edycja") {
				if (lineReadNumber != 1) temporaryFile << endl;
				if (contact.EqualsById(contactToDeleteOrEdit)) {
					temporaryFile << contactToDeleteOrEdit.getContactId() << "|";
					temporaryFile << contactToDeleteOrEdit.getUserId() << "|";
					temporaryFile << contactToDeleteOrEdit.getName() << "|";
					temporaryFile << contactToDeleteOrEdit.getSurname() << "|";
					temporaryFile << contactToDeleteOrEdit.getPhoneNumber() << "|";
					temporaryFile << contactToDeleteOrEdit.getEmail() << "|";
					temporaryFile << contactToDeleteOrEdit.getAddress() << "|";
					if (contactToDeleteOrEdit.getFriendStatus())
						temporaryFile << "tak" << "|";
					else
						temporaryFile << "nie" << "|";
				}
				else temporaryFile << line;
			}

		}
		temporaryFile.close();
		originalFile.close();
		remove(char_arr_originalPath);
		rename(char_arr_temporaryPath, char_arr_originalPath);
		return true;
	}
	else return false;
}
