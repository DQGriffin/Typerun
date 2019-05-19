#pragma once
#include <vector>
#include <string>
#include "Message.h"
#include <iostream>

class MessageCenter
{
public:
	std::vector<Message> messages;
private:
	int message_duration = 5;
	int first_message_height;
	sf::Font font;
public:
	MessageCenter();
	MessageCenter(sf::Font& font, int height);
	void post_message(std::string message);
	void update();
private:
	void displace_messages();
	void set_font(sf::Font font);
	void set_height(int height);
};

