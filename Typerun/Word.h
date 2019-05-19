#pragma once
#include <string>
#include "Label.h"
#include "MessageCenter.h"

class Word
{
public:
	MessageCenter* message_center;
	int speed = 1;
	int viewport_width;
private:
	Label label;
public:
	Word(std::string value, sf::Vector2f position, sf::Color initial_color, sf::Font& font);
	void update();
	sf::Text& get_drawable();
private:
	void update_position();
	void update_color();
};

