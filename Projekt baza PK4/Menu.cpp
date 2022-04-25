#include "Menu.h"

Menu::Menu() {
	database = make_unique<Database>();
	database->readFromFiles();
	option = 0;
	currentUser = new Guest;
}

void Menu::menuMain() {

	//system("cls");
	cout << "------------------------------------" << endl;
	cout << "     Baza przepisow kucharskich" << endl;
	cout << "------------------------------------" << endl;
	if (currentUser->getLoggedIn() == true) {
		cout << "1. Wyszukaj\n";
		cout << "2. Wyswietl wszystko\n";
		cout << "3. Zarzadzaj\n";
		cout << "4. Wyloguj\n";
		cout << "--------------\n";
		cout << "[ESC] Wyjdz\n";
		//cout << "Wybierz opcje:";
		while (true) {
			option = _getch();
			switch (option) {
			case 49:
				system("cls");
				menuSearch();
				break;
			case 50:
				system("cls");
				menuDisplayAll();
				break;
			case 51:
				system("cls");
				menuManage();
				break;
			case 52:
				delete currentUser;
				currentUser = new Guest;
				system("cls");
				menuMain();
			case 27:
				exit(0);
				break;
			default:
				cout << "\nWybrana opcja nie jest prawidlowa";
				break;
			}
		}
	}
	else {
		cout << "1. Zaloguj\n";
		cout << "2. Wyszukaj\n";
		cout << "3. Wyswietl wszystko\n";
		cout << "--------------\n";
		cout << "[ESC] Wyjdz\n";

		while (true) {
			option = _getch();
			switch (option) {
			case 49:
				menuLogin();
				break;
			case 50:
				system("cls");
				menuSearch();
				break;
			case 51:
				menuDisplayAll();
				break;
			case 27:
				exit(0);
				break;
			default:
				cout << "Wybrana opcja nie jest prawidlowa\n";
				break;
			}
		}
	}
}


void Menu::menuLogin() {
	string login, password;
	system("cls");
	cout << "------------------------------------" << endl;
	cout << "        Prosze o zalogowanie        " << endl;
	cout << "------------------------------------" << endl;

	cout << "\nPodaj login: ";
	cin >> login;
	cout << "Podaj haslo: ";
	cin >> password;
	switch (database->verifyUser(login, password)) {
	case 0:
		system("cls");
		cout << "Niepoprawna weryfikacja" << endl;
		menuMain();
		break;
	case 1:
		delete currentUser;
		currentUser = new Regular(login, password, 1);
		system("cls");
		cout << "Pomyslne logowanie regular" << endl;
		break;
	case 2:
		delete currentUser;
		currentUser = new Admin(login, password, 2);
		system("cls");
		cout << "Pomyslne logowanie admin" << endl;
		break;
	default:
		cout << "sth wrong" << endl;
		break;
	}

	currentUser->login();
	if (currentUser->getLoggedIn() == true)
		menuMain();
}

void Menu::menuDisplayAll() {
	system("cls");
	cout << "------------------------------------" << endl;
	cout << "         Wszystkie przepisy         " << endl;
	cout << "------------------------------------" << endl;
	cout << "Lp.  Nazwa" << endl;
	database->displayAllRecepies();
	cout << "\n\nWybrany przepis: ";
	while (true) {
		cin >> option;
		if (option - 1 >= (int)database->recepieVector.size())
			cout << "\nNiepoprawny przepis";
		else
			menuDisplayRecepie(option - 1);
	}
}

void Menu::menuDisplayRecepie(int option) {
	string name, mealType, descript;
	int prepTime = 0;
	int defaultOption = option;

	system("cls");
	cout << "------------------------------------" << endl;
	cout << database->recepieVector[option]->getName() << endl;
	cout << "------------------------------------" << endl;
	cout << "\nCzas: " << database->recepieVector[option]->getPrepTime();
	cout << "\tMeal type: " << database->recepieVector[option]->getMealType();
	cout << "\n\nLiczba kalorii: " << database->calculateCalories(option);
	cout << "\n\nJak ostre?: " << database->calculateSpicy(option);
	cout << "\n\nSkladniki: \n";
	for (auto& tmpProduct : database->productsRecepie[option])
		cout << "\t" << setw(10) << tmpProduct.first.getName() << "\t" << setw(5) << tmpProduct.second << endl;
	cout << "\nDescription: \n";
	cout << database->recepieVector[option]->getDescription();
	//for (int chars = 0; chars < description.size();) {
	//	for (int i = 0; i < 60; i++){
	//			cout << description[chars];
	//			chars++;
	//			if (chars % 60 == 0)
	//				cout << endl;
	//	}
	//}

	cout << "\n\n1. Generuj\n";
	if (currentUser->getPermissionLvl() == 2) {
		cout << "2. Usun";
		cout << "\n3. Modyfikuj\n";
	}
	cout << "--------------\n";
	cout << "[RETURN] Wroc\n";
	while (true) {
		option = _getch();
		switch (option) {
		case 49:
			menuGenerate(defaultOption);
			break;
		case 50:
			database->deleteRecepie(defaultOption);
			cout << option;
			break;
		case 51:
			currentUser->modifyRecepie(option);
			switch (option)
			{
			case 49:
				cout << "Podaj nowa nazwe: ";
				//cin.ignore();
				//getline(cin, name);
				cin >> name;
				database->modifyRecepie(name, prepTime, descript, mealType, defaultOption);
				menuDisplayRecepie(defaultOption);
				break;
			case 50:
				cout << "Podaj nowy czas przygotowania: ";
				cin >> prepTime;
				database->modifyRecepie(name, prepTime, descript, mealType, defaultOption);
				menuDisplayRecepie(defaultOption);
				break;
			case 51:
				cout << "Podaj nowy opis: ";
				getline(cin, descript);
				database->modifyRecepie(name, prepTime, descript, mealType, defaultOption);
				menuDisplayRecepie(defaultOption);
				break;
			case 52:
				cout << "Podaj nowy typ: ";
				cin >> mealType;
				database->modifyRecepie(name, prepTime, descript, mealType, defaultOption);
				menuDisplayRecepie(defaultOption);
				break;
			case 8:
				menuDisplayRecepie(defaultOption);
				break;
			default:
				break;
			}
			break;
		case 8:
			system("cls");
			menuMain();
			break;
		default:
			cout << "Zla opcja";
			break;
		}
	}

}

void Menu::menuGenerate(int defaultOption) {
	system("cls");
	string fileName;

	cout << "------------------------------------" << endl;
	cout << "        Co chcesz generowac?        " << endl;
	cout << "------------------------------------" << endl;
	cout << "1.Recepture\n";
	cout << "2.Liste zakupow\n";
	cout << "--------------\n";
	cout << "[RETURN] Wroc\n";
	option = _getch();
	if (option == 8) {
		system("cls");
		menuDisplayRecepie(defaultOption);
	}
	cout << "\nPodaj nazwe pliku do wygenerowania: ";
	cin >> fileName;
	//fileName = "generates/" + fileName + ".txt";
	while (true) {
		switch (option) {
		case 49:
			database->generateRecepie(fileName, defaultOption);
			menuDisplayRecepie(defaultOption);
			break;
		case 50:
			database->generateList(fileName, defaultOption);
			menuDisplayRecepie(defaultOption);
			break;
		default:
			cout << "Zla opcja";
			break;
		}
	}

}


void Menu::menuSearch() {
	string name;
	currentUser->search(option);
	while (true) {
		switch (option)
		{
		case 49:
			cout << "\nPodaj nazwe: ";
			cin >> name;
			if (database->searchByName(name)) {
				cout << "Wybierz recepture: ";
				cin >> option;
				menuDisplayRecepie(option - 1);
			}
			else {
				system("cls");
				cout << "Nie znaleziono takiego przepisu\n";
				menuSearch();
			}

			break;
		case 50:
			if (database->searchByProduct()) {
				cout << "Wybierz recepture: ";
				cin >> option;
				menuDisplayRecepie(option - 1);
			}
			else {
				system("cls");
				cout << "Nie znaleziono takiego przepisu\n";
				menuSearch();
			}
			break;
		case 8:
			system("cls");
			menuMain();
			break;
		default:
			break;
		}
	}

}

void Menu::menuManage() {
	system("cls");
	string name, mealType, description;
	int prepTime = 0;
	vector<pair<Product, int>> prodVec;
	if (currentUser->getPermissionLvl() == 1) {
		cout << "Dodaj przepis: \n";
		currentUser->addRecepie(name, prepTime, mealType, description, prodVec);
		database->addRecepie(name, prepTime, mealType, description, prodVec);
		system("cls");
		cout << "Pomyslnie dodano " << name << endl;
		menuMain();
	}
	cout << "------------------------------------" << endl;
	cout << "      Co chcesz zmodyfikowac?\n";
	cout << "------------------------------------" << endl;
	cout << "1. Uzytkownicy\n";
	cout << "2. Receptury\n";
	cout << "3. Skladniki\n\n";
	cout << "----------------\n";
	cout << "[RETURN] Wroc\n ";
	cout << "Wybierz opcje:";
	while (true) {
		option = _getch();
		switch (option) {
		case 49:
			system("cls");
			menuUsers();
			break;
		case 50:
			system("cls");
			menuRecepie();
			break;
		case 51:
			system("cls");
			menuProducts();
			break;
		case 8:
			system("cls");
			menuMain();
		default:
			cout << "zla opcja";
			break;
		}
	}

}

void Menu::menuUsers() {
	string login, password;
	int permissionLvl = 0, option = 0;
	system("cls");
	cout << "------------------------------------" << endl;
	cout << "     Co chcesz zrobic z userem?\n";
	cout << "------------------------------------" << endl;
	cout << "1. Dodawanie\n";
	cout << "2. Usuwanie\n";
	cout << "--------------\n";
	cout << "[RETURN] Wroc\n";
	cout << "Wybierz opcje:";
	while (true) {
		option = _getch();
		switch (option) {
		case 49:
			currentUser->addUser(login, password, permissionLvl);
			database->addUser(login, password, permissionLvl);
			menuUsers();
			break;
		case 50:
			database->displayAllUsers();
			currentUser->deleteUser(option);
			if (option == 0)
				menuUsers();
			else {
				database->deleteUser(option - 1);
				menuUsers();
			}
			break;
		case 8:
			menuManage();
			break;
		default:
			break;
		}
	}
}

void Menu::menuRecepie() {
	int prepTime = 0, number = 0;
	string name, mealType, description;
	vector<pair<Product, int>> prodVec;
	cout << "------------------------------------" << endl;
	cout << "   Co chcesz zrobic z recepturami?\n";
	cout << "------------------------------------" << endl;
	cout << "1. Dodawanie\n";
	cout << "2. Usuwanie\n";
	cout << "-------------\n";
	cout << "[RETURN] Wroc\n";
	cout << "Wybierz opcje:";
	while (true) {
		option = _getch();
		cout << endl;
		switch (option) {
		case 49:
			currentUser->addRecepie(name, prepTime, mealType, description, prodVec);
			database->addRecepie(name, prepTime, mealType, description, prodVec);
			system("cls");
			cout << "Pomyslnie dodano " << name << endl;
			menuRecepie();
			break;
		case 50:
			database->displayAllRecepies();
			currentUser->deleteRecepie(option);
			if (option == 0) {
				system("cls");
				menuRecepie();
			}
			else {
				database->deleteRecepie(option - 1);
				system("cls");
				menuRecepie();
			}
			break;
		case 8:
			menuManage();
			break;
		default:
			break;
		}
	}
}

void Menu::menuProducts() {
	string name;
	system("cls");
	int calories = 0, spiciness = 0, option = 0;
	cout << "------------------------------------" << endl;
	cout << "   Co chcesz zrobic z produktami?\n";
	cout << "------------------------------------" << endl;
	cout << "1. Dodawanie\n";
	cout << "2. Usuwanie\n";
	cout << "--------------\n";
	cout << "[RETURN] Wroc\n";
	cout << "Wybierz opcje:";
	while (true) {
		option = _getch();
		switch (option) {
		case 49:
			currentUser->addProduct(name, calories, spiciness);
			database->addProduct(name, calories, spiciness);
			system("cls");
			menuProducts();
			break;
		case 50:
			database->displayAllProducts();
			currentUser->deleteProduct(option);
			if (option == 0)
				menuProducts();
			else {
				database->deleteProduct(option - 1);
				menuProducts();
			}
			break;
		case 8:
			menuManage();
			break;
		default:
			break;
		}
	}
}
