#include "Guest.h"

Guest::Guest(std::string login, std::string password, int permission) {
	loggedIn = false;
	userLogin = "";
	userPassword = "";
	permissionLvl = 0;
}

void Guest::search(int& _option) {
	std::cout << "------------------------------------" << std::endl;
	std::cout << "       Po czym chcesz wyszukac?     " << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << "1.Nazwa receptury\n";
	std::cout << "2.Po produktach\n";
	std::cout << "--------------\n";
	std::cout << "[RETURN] Wroc\n";
}

bool Guest::getLoggedIn() {
	return loggedIn;
}
