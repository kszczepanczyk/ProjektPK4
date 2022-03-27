#include "User.h"
User::User(std::string login, std::string password, int permission) {
	loggedIn = false;
	userLogin = login;
	userPassword = password;
	permissionLvl = permission;
}
std::string User::getUserLogin()
{
	return userLogin;
}
std::string User::getUserPassword()
{
	return userPassword;
}
int User::getPermissionLvl()
{
	return permissionLvl;
}
void User::addRecepie(std::string& name, int& preptime, std::string& mealtype, std::string& decription, std::vector<std::pair<Product, int>>&)
{
	std::cout << "addRecepie User" << std::endl;
}

void User::login() {
	std::cout << "User sie loguje" << std::endl;
}

void User::logout()
{
	std::cout << "User sie logoutuje" << std::endl;
}

void User::deleteRecepie(int& option) {
	std::cout << "Brak uprawnien " << std::endl;
}

void User::modifyRecepie(int& option)
{
	std::cout << "User modyfikuje recepie" << std::endl;
}

void User::addUser(std::string& _login, std::string& _password, int& _permissionLvl)
{
	std::cout << "User dodaje userow" << std::endl;
}

void User::deleteUser(int& _option)
{
	std::cout << "User usuwa userow" << std::endl;
}

void User::search(int& _option) {
	std::cout << "user searchuje";
}



bool User::getLoggedIn() {
	return loggedIn;
}

void User::addProduct(std::string& name, int& calories, int& spiciness) {
	std::cout << "User dodaje product" << std::endl;
}

void User::deleteProduct(int& _option) {
	std::cout << "User usuwa product" << std::endl;
}


//bool operator== (User& lhs, User& rhs)
//{
//	if (lhs.userLogin == rhs.userLogin && lhs.userPassword == rhs.userPassword) {
//		return true;
//	}
//	return false;
//}
