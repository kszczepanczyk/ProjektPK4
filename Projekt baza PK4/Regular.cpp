#include "Regular.h"

Regular::Regular(std::string login, std::string password, int permission) {
	loggedIn = false;
	userLogin = login;
	userPassword = password;
	permissionLvl = permission;
}

void Regular::addRecepie(std::string& _name, int& _prepTime, std::string& _mealType, std::string& _description, std::vector<std::pair<Product, int>>& prodVec)
{
	int number = 0, prodNum = 0;
	std::string prodName;

	std::cout << "Podaj nazwe: ";
	std::cin.ignore();
	getline(std::cin, _name);
	//std::cin >> _name;

	std::cout << "Podaj ilosc czasu: ";
	std::cin >> _prepTime;

	std::cout << "Podaj typ posilku: ";
	std::cin.ignore();
	getline(std::cin, _mealType);
	//std::cin >> _mealType;

	std::cout << "Podaj opis przygotowania: ";
	std::cin.ignore();
	getline(std::cin, _description);

	std::cout << "Podaj ilosc produktow: ";
	std::cin >> number;
	for (int i = 0; i < number; i++) {
		std::cout << i << ". Nazwa produktu: ";
		std::cin.ignore();
		getline(std::cin, prodName);
		std::cout << i << ". Ilosc: ";
		std::cin >> prodNum;
		prodVec.push_back(std::make_pair(Product(prodName), prodNum));
	}
}

void Regular::login() {
	//std::cout << "regular sie loguje es" << std::endl;
	loggedIn = true;
}

void Regular::logout()
{
	std::cout << "regular sie wyloguje es" << std::endl;
	loggedIn = false;
}

//void Regular::deleteRecepie() {
//	std::cout << "regular nie usuwa recepie es" << std::endl;
//}

//void Regular::modifyRecepie()
//{
//	std::cout << "regular nie modyfikuje recepie" << std::endl;
//}
//
//void Regular::addUser()
//{
//	std::cout << "regular nie dodaje userow" << std::endl;
//}
//
//void Regular::deleteUser()
//{
//	std::cout << "regular nie usuwa userow" << std::endl;
//}

bool Regular::getLoggedIn() {
	return loggedIn;
}