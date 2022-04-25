#include "Database.h"

void Database::readFromFiles() {
	Database::readFromFile("Users");
	Database::readFromFile("Products");
	Database::readFromFile("Recipies");
}

void Database::readFromFile(std::string type) {
	std::ifstream file;
	json jsonFile;
	if (type == "Recipies") {
		//std::cout << fileRecepie;
		file.open(fileRecepie);
		
		file >> jsonFile;
		for (json& jsonRecepie : jsonFile) {
			for (json& jsonProduct : jsonRecepie["products"]) {
				tmpProducts.push_back(
					std::make_pair(
						Product(jsonProduct["name"]),
						jsonProduct["number"]
					)
				);
			}
			productsRecepie.push_back(tmpProducts);

			recepieVector.push_back(
				std::make_unique<Recepie>(
					jsonRecepie["name"],
					jsonRecepie["prepTime"],
					jsonRecepie["mealType"],
					jsonRecepie["description"],
					tmpProducts
					)
			);
			tmpProducts.clear();
		}
		//std::cout << "read recepie success";
		file.close();
	}
	else if (type == "Products") {
		//std::cout << fileRecepie;
		file.open(fileProducts);
		file >> jsonFile;
		for (json& jsonProduct : jsonFile) {
			productVector.push_back(
				std::make_unique<Product>(
					jsonProduct["name"],
					jsonProduct["calories"],
					jsonProduct["spiciness"]
					)
			);
		}
		//std::cout << "read product success";
		file.close();
	}
	else if (type == "Users") {
		//std::cout << fileRecepie;
		file.open(fileUsers);
		file >> jsonFile;
		for (json& jsonUser : jsonFile) {
			switch ((int)jsonUser["permissionLvl"]) {
			case 0:
				userVector.push_back(
					std::make_unique<Guest>(
						jsonUser["username"],
						jsonUser["password"],
						jsonUser["permissionLvl"]
						)
				);
				break;
			case 1:
				userVector.push_back(
					std::make_unique<Regular>(
						jsonUser["username"],
						jsonUser["password"],
						jsonUser["permissionLvl"]
						)
				);
				break;
			case 2:
				userVector.push_back(
					std::make_unique<Admin>(
						jsonUser["username"],
						jsonUser["password"],
						jsonUser["permissionLvl"]
						)
				);
				break;
			}

		}
		//std::cout << "read user success";
		file.close();
	}
}

void Database::saveToFiles() {
	Database::saveToFile("Products");
	Database::saveToFile("Users");
	Database::saveToFile("Recepies");
}

void Database::saveToFile(std::string type) {
	std::ofstream file;
	json jsonFile = json::array();
	if (type == "Recepies") {
		for (auto& recepie : recepieVector) {
			json jsonProduct = json::array();
			for (auto& product : recepie->products) {
				jsonProduct.push_back(
					{
						{"name", product.first.getName()},
						{"number",product.second}
					}
				);
			}
			jsonFile.push_back(
				{
					{"name", recepie->getName()},
					{"prepTime", recepie->getPrepTime()},
					{"mealType", recepie->getMealType()},
					{"description", recepie->getDescription()},
					{"products", jsonProduct}
				}
			);
		}
		file.open(fileRecepie);
		file << std::setw(4) << jsonFile << std::endl;
		file.close();
	}
	else if (type == "Products") {
		for (auto& product : productVector) {
			jsonFile.push_back(
				{
					{"name", product->getName()},
					{"calories", product->getCalories()},
					{"spiciness", product->getSpiciness()}
				}
			);
		}

		file.open(fileProducts);
		file << std::setw(4) << jsonFile << std::endl;
		file.close();
		std::cout << "Pomyslnie zapisano produkt";
	}
	else if (type == "Users") {
		for (auto& user : userVector) {
			jsonFile.push_back(
				{
					{"username", user->getUserLogin()},
					{"password", user->getUserPassword()},
					{"permissionLvl", user->getPermissionLvl()}
				}
			);
		}
		file.open(fileUsers);
		file << std::setw(4) << jsonFile << std::endl;
		file.close();
		std::cout << "Pomyslnie zapisano usera\n";
	}
}

int Database::verifyUser(std::string login, std::string password) {

	for (auto& user : userVector) {
		if (user->getUserLogin() == login && user->getUserPassword() == password) {
			return user->getPermissionLvl();
		}
	}
	return 0;
};

void Database::displayAllRecepies() {
	int i = 0;
	for (auto& recepie : recepieVector) {
		std::cout << i + 1 << ".   " << recepie->getName() << std::endl;
		i++;
	}
	//return i;
}

void Database::generateList(std::string fileName, int option) {
	fs::path path = fs::current_path() / "Lists";
	path.append(fileName);
	//std::cout << fileName;
	std::ofstream file;
	file.open(path);
	for (auto& product : productsRecepie[option])
		file << product.first.getName() << "\t" << product.second << "\n";
	file.close();
	std::cout << "Pomyslnie stworzono plik";
}

void Database::generateRecepie(std::string fileName, int option) {
	fs::path path = fs::current_path() / "Recipes";
	path.append(fileName);
	std::ofstream file;
	file.open(path);
	file << recepieVector[option]->getName() << "\n";
	file << recepieVector[option]->getPrepTime() << " | " << recepieVector[option]->getMealType() << "\n";
	for (auto& tmpProduct : productsRecepie[option])
		file << tmpProduct.first.getName() << "\t" << tmpProduct.second << "\n";
	file << recepieVector[option]->getDescription();
	file.close();
	std::cout << "Pomyslnie stworzono plik";
}

int Database::calculateCalories(int option) {
	int suma = 0;
	for (auto& var : productsRecepie[option]) {
		for (auto& product : productVector) {
			if (var.first.getName() == product->getName())
				suma = suma + (product->getCalories() * var.second);
		}
	}
	return suma;
}

bool Database::searchByName(std::string name) {
	int i = 0;
	bool isFound = false;
	for (auto& var : recepieVector) {
		if (var->getName().find(name) != std::string::npos) {
			std::cout << i + 1 << ".   " << var->getName() << std::endl;
			isFound = true;
		}
		i++;
	}
	if (isFound)
		return true;
	else
		return false;
}

bool Database::searchByProduct() {
	int number;
	int j = 0;
	int iterator = 0;
	bool isFound = false;
	std::cout << "\nPodaj liczbe produktow: ";
	std::cin >> number;
	std::string* products = new std::string[number];
	std::cout << "\nPodaj produkty: ";
	for (int i = 0; i < number; i++) {
		std::cin >> products[i];
	}
	for (auto& var : productsRecepie) {
		for (int i = 0; i < number; i++) {
			for (auto& var2 : var) {
				if (var2.first.getName() == products[i]) {
					iterator++;
				}
				if (iterator == number) {
					std::cout << j + 1 << ".   " << recepieVector[j]->getName() << std::endl;
					isFound = true;
					break;
				}
			}
			if (iterator == number)
				break;
		}
		iterator = 0;
		j++;
	}
	if (isFound)
		return true;
	else
		return false;
	delete[] products;
}

std::string Database::calculateSpicy(int option) {
	std::string howSpicy;
	int spicyFactor = 0;
	for (auto& var : productsRecepie[option]) {
		for (auto& product : productVector) {
			if (var.first.getName() == product->getName())
				spicyFactor += var.second * product->getSpiciness();
		}
	}
	if (spicyFactor < 5)
		return "lagodne";
	else if (spicyFactor >= 5 && spicyFactor < 10)
		return "ostre";
	else if (spicyFactor >= 10)
		return "bardzo ostre";
}

User* Database::getUserPointerByUsername(std::string _name) {
	for (auto& user : userVector) {
		if (user->getUserLogin() == _name) {
			return user.get();
		}
	}
	return nullptr;
}

Product* Database::getProductPointerByName(std::string _name) {
	for (auto& product : productVector) {
		if (product->getName() == _name) {
			return product.get();
		}
	}
	return nullptr;
}

Recepie* Database::getRecepiePointerByName(std::string _name) {
	for (auto& recepie : recepieVector) {
		if (recepie->getName() == _name) {
			return recepie.get();
		}
	}
	return nullptr;
}


void Database::addUser(std::string login, std::string password, int permissionLvl) {
	if (!login.empty() && !password.empty() && permissionLvl <= 2) {
		switch (permissionLvl) {
		case 0:
			if (getUserPointerByUsername(login) == nullptr) {
				userVector.push_back(
					std::make_unique<Guest>(
						login,
						password,
						permissionLvl
						)
				);
				saveToFile("Users");
			}
			else
				std::cout << "User juz istnieje\n";
			break;
		case 1:
			if (getUserPointerByUsername(login) == nullptr) {
				userVector.push_back(
					std::make_unique<Regular>(
						login,
						password,
						permissionLvl
						)
				);
				saveToFile("Users");
			}
			else
				std::cout << "User juz istnieje\n";
			break;
		case 2:
			if (getUserPointerByUsername(login) == nullptr) {
				userVector.push_back(
					std::make_unique<Regular>(
						login,
						password,
						permissionLvl
						)
				);
				saveToFile("Users");
			}
			else
				std::cout << "User juz istnieje\n";
			break;
		}
	}
}

void Database::addProduct(std::string _name, int _calories, int _spiciness) {
	if (!_name.empty() && _calories != 0 && _spiciness != 0) {
		if (getProductPointerByName(_name) == nullptr) {
			productVector.push_back(
				std::make_unique<Product>(
					_name,
					_calories,
					_spiciness
					)
			);
			saveToFile("Products");
		}
		else
			std::cout << "Produkt juz istnieje\n";
	}
}

void Database::displayAllUsers() {
	int i = 0;
	std::cout << std::endl;
	for (auto& user : userVector) {
		std::cout << i + 1 << ".   " << user->getUserLogin() << std::endl;
		i++;
	}
}

void Database::displayAllProducts() {
	int i = 0;
	std::cout << std::endl;
	for (auto& product : productVector) {
		std::cout << i + 1 << ".   " << product->getName() << std::endl;
		i++;
	}
}

void Database::deleteUser(int _indeks) {
	userVector.erase(userVector.begin() + _indeks);
	saveToFile("Users");
}

void Database::deleteProduct(int _indeks) {
	productVector.erase(productVector.begin() + _indeks);
	saveToFile("Products");
}

void Database::addRecepie(std::string name, int prepTime, std::string mealType, std::string description, std::vector<std::pair<Product, int>> prodVec) {
	if (!name.empty() && !mealType.empty() && !description.empty() && prepTime != 0) {
		if (getRecepiePointerByName(name) == nullptr) {
			recepieVector.push_back(
				std::make_unique<Recepie>(
					name,
					prepTime,
					mealType,
					description,
					prodVec
					)
			);
			saveToFile("Recepies");
		}
		else
			std::cout << "Receptura juz istnieje\n";
	}
}

void Database::modifyRecepie(std::string name, int prepTime, std::string description, std::string mealType, int option) {
	if (!name.empty()) {
		recepieVector[option]->setName(name);
	}
	else if (prepTime != 0) {
		recepieVector[option]->setTime(prepTime);
	}
	else if (!description.empty()) {
		recepieVector[option]->setDescription(description);
	}
	else if (!mealType.empty()) {
		recepieVector[option]->setType(mealType);
	}
	saveToFile("Recepies");
}

void Database::deleteRecepie(int option) {
	recepieVector.erase(recepieVector.begin() + option);
	saveToFile("Recepie");
}





