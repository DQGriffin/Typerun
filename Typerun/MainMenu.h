#pragma once
#include "Menu.h"
#include <iostream>
#include <vector>

class MainMenu : public Menu
{
private:
	sf::Font font_local;
public:
	MainMenu();
	MainMenu(sf::Font* font);
private:
	void initialize();
};

