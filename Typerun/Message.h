#pragma once
#include <string>
#include <chrono>
#include "SFML/Graphics/Font.hpp"
#include "Label.h"

class Message
{
public:
	std::string data;
	std::chrono::high_resolution_clock::time_point creation_time;
	bool is_alive;
	Label label;
private:
	int duration;
	int x_pos;
	int y_pos;
public:
	Message(std::string message, int duration, sf::Font& font, sf::Vector2f position);
	void update();
	void displace();
};

