#include "Label.h"


Label::Label()
{
}

//--------------------------------------------------------------------------
// Label constructor
//--------------------------------------------------------------------------
Label::Label(std::string name, std::string text, sf::Font & font, int character_size, sf::Color color, sf::Text::Style style, sf::Vector2f position)
{
	this->name = name;
	sf_text.setFont(font);
	sf_text.setString(text);
	sf_text.setCharacterSize(character_size);
	sf_text.setFillColor(color);
	sf_text.setStyle(style);
	sf_text.setPosition(position);
}

//--------------------------------------------------------------------------
// Returns a reference to the sf::Text object used for drawing
//--------------------------------------------------------------------------
sf::Text& Label::get_drawable()
{
	return sf_text;
}

//--------------------------------------------------------------------------
// Sets the text of the Label
//--------------------------------------------------------------------------
void Label::set_text(std::string text)
{
	sf_text.setString(text);
}

//--------------------------------------------------------------------------
// Sets the character size of the text. Note that this is measured in
// pixels, not points
//--------------------------------------------------------------------------
void Label::set_character_size(int character_size)
{
	sf_text.setCharacterSize(character_size);
}

//--------------------------------------------------------------------------
// Sets the position of the Label
//--------------------------------------------------------------------------
void Label::set_position(sf::Vector2f position)
{
	sf_text.setPosition(position);
}

void Label::set_color(sf::Color color)
{
	sf_text.setFillColor(color);
}

