#include "Message.h"


//--------------------------------------------------------------------------
// Message constructor
//--------------------------------------------------------------------------
Message::Message(std::string message, int duration, sf::Font& font, sf::Vector2f position) : data{message}, duration{duration}, is_alive{true}
{
	x_pos = position.x;
	y_pos = position.y;

	label = Label("Message", message, font, 15, sf::Color::White, sf::Text::Regular, position);

	creation_time = std::chrono::high_resolution_clock::now();
}

//--------------------------------------------------------------------------
// Checks to see whether or not the Message should be removed from the queue
//--------------------------------------------------------------------------
void Message::update()
{
	std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<int> time_span = std::chrono::duration_cast<std::chrono::duration<int>>(current_time - creation_time);

	if (time_span.count() >= duration)
	{
		is_alive = false;
	}
}

//--------------------------------------------------------------------------
// Displaces the Message to allow room for a new Message
//--------------------------------------------------------------------------
void Message::displace()
{
	y_pos -= 30;
	label.set_position(sf::Vector2f(x_pos, y_pos));
}
