#pragma once
#include <vector>
#include <iostream>
#include "Label.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Menu
{
public:
	std::vector<Label> labels;
	sf::RectangleShape selection_box;
	sf::Color selection_box_color;
	sf::Color background_color;
private:
	int selected_index = 0;
protected:
	sf::Color selected_color;
	sf::Color default_color;
	//sf::Font font;
public:
	Menu();
	//Menu(sf::Font& font);
	void move_next();
	void move_previous();
	void update();
protected:
	int get_selected_index();
	//void set_font(sf::Font& font);
};

