#pragma once
#include <fstream>
#include <vector>
#include "json.hpp"
#include <iomanip>
#include <memory>
#include <algorithm>

#include "Recepie.h"
import Product;
#include "Guest.h"
#include "Admin.h"
#include "Regular.h"
#include "User.h"


using json = nlohmann::json;

class Database
{

	std::string fileRecepie = "Recepies.json";
	std::string fileProducts = "Products.json";
	std::string fileUsers = "Users.json";
public:
	std::vector<std::unique_ptr<Recepie>> recepieVector;
	std::vector<std::unique_ptr<Product>> productVector;
	std::vector<std::unique_ptr<User>> userVector;
	std::vector<std::pair<Product, int>> tmpProducts;
	std::vector<std::vector<std::pair<Product, int>>> productsRecepie;
	User* getUserPointerByUsername(std::string);
	Product* getProductPointerByName(std::string);
	Recepie* getRecepiePointerByName(std::string);
	void readFromFiles();
	void readFromFile(std::string);
	void saveToFiles();
	void displayAllRecepies();
	void displayAllUsers();
	void modifyRecepie(std::string, int, std::string, std::string, int);
	void displayAllProducts();
	void saveToFile(std::string);
	int verifyUser(std::string, std::string);
	bool searchByName(std::string);
	bool searchByProduct();
	void generateRecepie(std::string, int);
	void generateList(std::string, int);
	int calculateCalories(int);
	void addUser(std::string, std::string, int);
	void deleteUser(int);
	void addProduct(std::string, int, int);
	void deleteProduct(int);
	void addRecepie(std::string, int, std::string, std::string, std::vector<std::pair<Product, int>>);
	void deleteRecepie(int);
	std::string calculateSpicy(int);
	/*friend int operator+= (int &rhs, std::vector<std::pair<Product, int>>& lhs);*/

};

//int operator+= (int& rhs, std::vector<std::unique_ptr<Product>>& lhs) {
//	for (auto& var : lhs)
//		rhs = rhs + var->getCalories();
//	return rhs;
//}


