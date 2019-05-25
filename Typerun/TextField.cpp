#include "TextField.h"



TextField::TextField()
{
}

TextField::TextField(sf::Vector2f position, sf::Color text_color, sf::Font& font) : text_color{text_color}, font{font}
{
	label = Label("TextField", "Hello", font, 22, text_color, sf::Text::Regular, position);
}


void TextField::add_character(char character)
{
	std::string temp = label.get_drawable().getString().toAnsiString();
	temp += character;
	label.set_text(temp);
}

void TextField::remove_last_character()
{
	std::string temp = label.get_drawable().getString().toAnsiString();
	if (temp != "")
	{
		temp.pop_back();
		label.set_text(temp);
	}
}

std::string TextField::get_text()
{
	return label.get_drawable().getString().toAnsiString();
}

sf::Text & TextField::get_drawable()
{
	return label.get_drawable();
}
