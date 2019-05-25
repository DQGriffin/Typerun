#include "TextField.h"



TextField::TextField()
{
}


TextField::~TextField()
{
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
	temp.pop_back();
	label.set_text(temp);
}

std::string TextField::get_text()
{
	return label.get_drawable().getString().toAnsiString();
}
