#pragma once
#include <vector>
#include "Label.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Vector2.hpp"

class Menu
{
public:
	std::vector<Label> labels;
private:
	int selected_index = 0;
	sf::Color selected_color;
	sf::Color default_color;
	sf::Font font;
public:
	Menu();
	Menu(sf::Font& font);
	~Menu();
	void move_next();
	void move_previous();
	void update();
protected:
	int get_selected_index();
};

