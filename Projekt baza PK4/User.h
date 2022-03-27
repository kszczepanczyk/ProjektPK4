#pragma once
import <string>;
#include <iostream>
#include <conio.h>
#include <vector>
import Product;

class User {
protected:
	bool loggedIn;
	//Database database;
	std::string userLogin;
	std::string userPassword;
	int permissionLvl;
public:
	User() = default;
	User(std::string, std::string, int);
	std::string getUserLogin();
	std::string getUserPassword();
	int getPermissionLvl();
	//normal
	virtual bool getLoggedIn() = 0;
	//regular
	virtual void addRecepie(std::string&, int&, std::string&, std::string&, std::vector<std::pair<Product, int>>&);
	virtual void login();
	virtual void logout();
	//admin
	virtual void deleteRecepie(int&);
	virtual void modifyRecepie(int&);
	virtual void addProduct(std::string&, int&, int&);
	virtual void deleteProduct(int&);
	virtual void addUser(std::string&, std::string&, int&);
	virtual void deleteUser(int&);
	virtual void search(int&);
};


