#pragma once
#include <string>
#include <random>
#include "Label.h"
#include "MessageCenter.h"

class Word
{
public:
	int speed = 1;
	int viewport_width;
private:
	Label label;
	int id;
	const int min_id = 11111;
	const int max_id = 99999;
	bool alive;
public:
	Word(std::string value, sf::Vector2f position, sf::Color initial_color, sf::Font& font);
	Word& operator=(Word w);
	void update();
	sf::Text& get_drawable();
	int get_id();
	bool is_alive();
private:
	void update_position();
	void update_color();
	int generate_id();
};

