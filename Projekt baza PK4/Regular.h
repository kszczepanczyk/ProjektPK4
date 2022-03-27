#pragma once

#include "Guest.h"

class Regular : public Guest {
public:
	Regular() = default;
	Regular(std::string, std::string, int);

	bool getLoggedIn();

	//regular
	void addRecepie(std::string&, int&, std::string&, std::string&, std::vector<std::pair<Product, int>>&);
	void login();
	void logout();
	//admin
	//void deleteRecepie();
	//void modifyRecepie();

	//void addUser();
	//void deleteUser();
};

