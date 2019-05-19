#include "MessageCenter.h"

//--------------------------------------------------------------------------
// Default constructor
//
// The MessageCenter relies on the font initialized by the EngineCore,
// Hence the need for a default constructor.
// See: EngineCore::EngineCore()
//--------------------------------------------------------------------------
MessageCenter::MessageCenter()
{
}

//--------------------------------------------------------------------------
// MessageCenter constructor
//--------------------------------------------------------------------------
MessageCenter::MessageCenter(sf::Font& font, int height)
{
	this->font = font;
	first_message_height = height - 30;
}

//--------------------------------------------------------------------------
// Posts a message to the meessage queue
//--------------------------------------------------------------------------
void MessageCenter::post_message(std::string message)
{
	int x_pos = 15;
	int y_pos;
	int y_pos_addative = 0;

	y_pos = first_message_height - 50;

	Message new_message = Message("> " + message, message_duration, font, sf::Vector2f(x_pos, y_pos));

	if (messages.size() != 0)
	{
		displace_messages();
	}

	messages.push_back(new_message);
}

//--------------------------------------------------------------------------
// Deprecated
//
// Sets the font used to display messages
//--------------------------------------------------------------------------
void MessageCenter::set_font(sf::Font font)
{
	this->font = font;
}

//--------------------------------------------------------------------------
// Deprecated
//
// Sets the height of the viewport
//--------------------------------------------------------------------------
void MessageCenter::set_height(int height)
{
	first_message_height = height - 50;
}

//--------------------------------------------------------------------------
// Updates all messages in the message queue
//--------------------------------------------------------------------------
void MessageCenter::update()
{
	for (Message& message : messages)
	{
		message.update();
	}

	for (int index = 0; index < messages.size(); index++)
	{
		if (!messages[index].is_alive)
		{
			messages.erase(messages.begin() + index);
		}
	}

}

//--------------------------------------------------------------------------
// Displaces all messages in the queue to allow room for a new message
//--------------------------------------------------------------------------
void MessageCenter::displace_messages()
{
	for (Message& message : messages)
	{
		message.displace();
	}
}

