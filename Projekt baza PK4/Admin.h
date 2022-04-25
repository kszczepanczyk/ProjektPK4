#pragma once
#include "Regular.h"
#include <regex>

class Admin : public Regular {
public:
	Admin(std::string, std::string, int);

	bool getLoggedIn();

	void deleteRecepie(int&);
	void modifyRecepie(int&);
	void addUser(std::string&, std::string&, int&);
	void deleteUser(int&);
	void addProduct(std::string&, int&, int&);
	void deleteProduct(int&);
};


