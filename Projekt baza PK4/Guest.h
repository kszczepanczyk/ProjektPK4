#pragma once

#include "User.h"

#include <iostream>

class Guest : public User {
public:
	Guest() = default;
	Guest(std::string, std::string, int);

	bool getLoggedIn();
	void search(int&);
};
