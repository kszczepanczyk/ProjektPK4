// Baza przepisow.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"
#include "Menu.h"



using namespace std;
using json = nlohmann::json;

int main()
{
	Menu menu;
	menu.menuMain();
	return 0;
}


