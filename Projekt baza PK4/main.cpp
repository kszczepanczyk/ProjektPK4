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
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
	Menu menu;
	menu.menuMain();
	return 0;
}


