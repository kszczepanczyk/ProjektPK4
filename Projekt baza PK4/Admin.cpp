#include "Admin.h"

Admin::Admin(std::string login, std::string password, int permission) {
	loggedIn = false;
	userLogin = login;
	userPassword = password;
	permissionLvl = permission;
}

void Admin::deleteRecepie(int& option) {
	std::cout << "\nWpisz zero aby powrocic";
	std::cout << "\n\nWybrany przepis: ";
	std::cin >> option;
}

void Admin::modifyRecepie(int& option)
{
	system("cls");
	std::cout << "Co chcesz modyfikowac?" << std::endl;
	std::cout << "1. Nazwa" << std::endl;
	std::cout << "2. Czas przygotowania" << std::endl;
	std::cout << "3. Opis" << std::endl;
	std::cout << "4. Typ posilku" << std::endl;
	std::cout << "[RETURN] Wroc" << std::endl;
	option = _getch();
}

void Admin::addUser(std::string& _login, std::string& _password, int& _permissionLvl)
{
	system("cls");
	std::regex regPass("^(?=.*?[A-Z])(?=.*?[a-z])(?=.*?[0-9]).{8,}$");
	std::cout << "Podaj login: ";
	std::cin >> _login;
	while (true) {
		std::cout << "Podaj haslo: ";
		std::cin >> _password;
		if (std::regex_match(_password, regPass)) {
			break;
		}
		else {
			std::cout << "\nHaslo powinno sie skladac z minimum 8 znakow, jedna duza i jedna mala litera oraz jedna cyfra\n";
		}
	}
	
	while (true) {
		std::cout << "Podaj poziom uprawnien 0-2: ";
		std::cin >> _permissionLvl;
		if (_permissionLvl >= 0 && _permissionLvl <= 2)
			break;
		else
			std::cout << "\nNiepoprawny poziom uprawnien\n";
	}

}

void Admin::deleteUser(int& _option)
{
	std::cout << "\nWpisz zero aby powrocic";
	std::cout << "\n\nWybrany user: ";
	std::cin >> _option;
}

bool Admin::getLoggedIn() {
	return loggedIn;
}

void Admin::addProduct(std::string& _name, int& _calories, int& _spiciness) {
	system("cls");
	std::cout << "Podaj nazwe produktu: ";
	std::cin >> _name;
	std::cout << "Podaj ilosc kalorii na gram lub sztuke: ";
	std::cin >> _calories;
	std::cout << "Podaj jak ostry jest produkt [0-5]: ";
	std::cin >> _spiciness;
}

void Admin::deleteProduct(int& _option) {
	std::cout << "\nWpisz zero aby powrocic";
	std::cout << "\n\nWybrany produkt: ";
	std::cin >> _option;
}
