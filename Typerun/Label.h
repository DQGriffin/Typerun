#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

class Label
{
public:
	std::string name;
	sf::Text sf_text;
private:
	//sf::Text sf_text;
public:
	Label();
	Label(std::string name, std::string text, sf::Font& font, int character_size, sf::Color color, sf::Text::Style style, sf::Vector2f position);
	sf::Text& get_drawable();
	void set_text(std::string text);
	void set_character_size(int character_size);
	void set_position(sf::Vector2f position);
	void set_color(sf::Color color);
};

