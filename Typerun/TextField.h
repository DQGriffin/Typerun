#pragma once
#include "Label.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/Vector2.hpp"

class TextField
{
private:
	Label label;
	sf::Color text_color;
	sf::Font font;
public:
	TextField();
	TextField(sf::Vector2f position, sf::Color text_color, sf::Font& font);
	void add_character(char character);
	void remove_last_character();
	std::string get_text();
	sf::Text& get_drawable();
};

