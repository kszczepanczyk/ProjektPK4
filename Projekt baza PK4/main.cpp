#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
import <string>;

#include "json.hpp"
#include "Menu.h"

using json = nlohmann::json;
namespace fs = std::filesystem;


int main()
{
	Menu menu;
	menu.menuMain();
	return 0;
}


