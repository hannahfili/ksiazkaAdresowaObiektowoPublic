#pragma once
#include <string>
using namespace std;
class User
{
private:
	int userId;
	string login;
	string password;
public:
	User() : User(-1, "", "") {};
	User(string login, string password) :login(login), password(password) {};
	User(int userId, string login, string password) : userId(userId), login(login), password(password) {};
	
	bool checkLoginAndPassword(string log, string pas);
	User loadUserData(string fileLine);
	User logIn(string usersPath);
	
	void setUserPassword(string p) { password = p; }
	void setUserId(int id) { userId = id; }

	
	
	int getUserId() { return userId; }
	string getLogin() { return login; }
	string getPassword() { return password; };
};

