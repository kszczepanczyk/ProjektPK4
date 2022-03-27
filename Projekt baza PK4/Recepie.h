#pragma once
import <string>;
#include <iostream>
#include <vector>
#include <utility>

import Product;

class Recepie {

	friend class Database;
protected:
	std::string name;
	std::string mealType;
	std::string description;
	std::vector<std::vector<std::pair<Product, int>>> tmpProducts;
	std::vector<std::pair<Product, int>> products;
	int calSum;
	int prepTime;
public:

	Recepie() {};
	Recepie(std::string name, int prepTime, std::string mealType, std::string description, std::vector<std::vector<std::pair<Product, int>>> productsRecepie);
	Recepie(std::string name, int prepTime, std::string mealType, std::string description, std::vector<std::pair<Product, int>> products);
	std::string getName();
	std::string getMealType();
	std::string getDescription();
	int getPrepTime();
	void setName(std::string);
	void setTime(int);
	void setType(std::string);
	void setDescription(std::string);


};

