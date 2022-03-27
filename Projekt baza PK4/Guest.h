#pragma once

#include "User.h"

#include <iostream>

class Guest : public User {
public:
	Guest() = default;
	Guest(std::string, std::string, int);

	bool getLoggedIn();
	void search(int&);

	//regular
	//void addRecepie();
	//void login();
	//void logout();
	//admin
	//bool deleteRecepie(int);
	//void modifyRecepie();

	//void addUser();
	//void deleteUser();
};
