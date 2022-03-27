#pragma once
#include "Recepie.h"

#include "Regular.h"
#include "Admin.h"
#include "User.h"
#include "Guest.h"
#include "Database.h"
#include <iostream>
#include <conio.h>

using namespace std;

class Menu
{
	int option;
	//Recepie* recepie;
	User* currentUser;
	unique_ptr<Database> database;

public:
	Menu();
	void menuLogin();
	void menuMain();
	void menuSearch();
	void menuManage();
	void menuUsers();
	void menuRecepie();
	void menuProducts();
	void menuDisplayAll();
	void menuDisplayRecepie(int);
	void menuGenerate(int);
	//void menuAskFile();
};


