#pragma once

#include <string>
#include <vector>
using namespace std;

class Contact
{
private:
	int contactId;
	int userId;
	string name, surname, address, phoneNumber, email;
	bool friendStatus;
public:
	Contact(string name, string surname, string address, string phoneNumber,
		string email, bool friendStatus, int userId) : name(name), surname(surname), address(address),
		phoneNumber(phoneNumber), email(email), friendStatus(friendStatus), userId(userId) {};
	Contact(int contactId) : contactId(contactId) {};
	Contact() {};
	Contact(int contactId, int userId):contactId(contactId), userId(userId) {};

	void setContactId(int id) { contactId = id; }
	void setName(string n) { name = n; }
	void setSurname(string n) { surname = n; }
	void setEmail(string n) { email = n; }
	void setPhoneNumber(string n) { phoneNumber = n; }
	void setAddress(string n) { address = n; }
	void setFriendStatus(bool s) { friendStatus = s; }

	void divideData(string data, bool onlyDataForParticularUser=false);
	void displayContactData();

	int getContactId(){ return contactId; }
	int getUserId(){ return userId; }
	string getName() { return name; }
	string getSurname() { return surname; }
	string getAddress() { return address; }
	string getPhoneNumber() { return phoneNumber; }
	string getEmail() { return email; }
	bool getFriendStatus() { return friendStatus; }

	bool Equals(Contact contact, bool checkAlsoId=false);
	bool EqualsById(Contact contactTest);
};

