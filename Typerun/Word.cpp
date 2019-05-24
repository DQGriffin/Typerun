#include "Word.h"


//--------------------------------------------------------------------------
// Word constructor
//--------------------------------------------------------------------------
Word::Word(std::string value, sf::Vector2f position, sf::Color initial_color, sf::Font& font)
{
	label = Label(value, value, font, 24, initial_color, sf::Text::Regular, position);
	id = generate_id();
}

//--------------------------------------------------------------------------
// Notifies the Word that it should update
//--------------------------------------------------------------------------
void Word::update()
{
	if (label.get_drawable().getPosition().x < viewport_width)
	{
		update_position();
		update_color();
	}
}

//--------------------------------------------------------------------------
// Returns a reference to the sf::Text object used for drawing
//--------------------------------------------------------------------------
sf::Text& Word::get_drawable()
{
	return label.get_drawable();
}

//--------------------------------------------------------------------------
// Returns the Word's ID as an integer
//--------------------------------------------------------------------------
int Word::get_id()
{
	return id;
}

//--------------------------------------------------------------------------
// Updates the Word's position
//--------------------------------------------------------------------------
void Word::update_position()
{
	int x_pos = label.get_drawable().getPosition().x + speed;
	int y_pos = label.get_drawable().getPosition().y;
	label.get_drawable().setPosition(sf::Vector2f(x_pos, y_pos));
}

//--------------------------------------------------------------------------
// Updates the Word's color
//--------------------------------------------------------------------------
void Word::update_color()
{
	int r = label.get_drawable().getFillColor().r;
	int g = label.get_drawable().getFillColor().g;
	int b = label.get_drawable().getFillColor().b;

	if (r < 255 && get_drawable().getPosition().x > 0)
	{
		r = (label.get_drawable().getPosition().x * 5) * 0.06;
		//g = 255 - ((label.get_drawable().getPosition().x * 5) * 0.04);
	}
	else if (g > 0)
	{
		//g = 255 - ((label.get_drawable().getPosition().x * 2) * 0.08);
		//g -= 1;
		g -= (label.get_drawable().getPosition().x / 255) * (0.09 * speed);
	}

	//message_center->post_message("R: " + std::to_string(r));
	//message_center->post_message("G: " + std::to_string(g));

	label.get_drawable().setFillColor(sf::Color(r, g, b));
}

//--------------------------------------------------------------------------
// Generates a (hopfully) unique ID
//--------------------------------------------------------------------------
int Word::generate_id()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(min_id, max_id);
	int result = uniform_dist(e1);
	return result;
}

