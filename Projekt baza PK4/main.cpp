// Baza przepisow.cpp : Ten plik zawiera funkcj� �main�. W nim rozpoczyna si� i ko�czy wykonywanie programu.
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


