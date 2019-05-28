#include "Menu.h"



Menu::Menu()
{
	selected_color = sf::Color::Cyan;
	default_color = sf::Color::White;
}

//Menu::Menu(sf::Font & font) : font{font}
//{
//	selected_color = sf::Color::Cyan;
//	default_color = sf::Color::White;
//	std::cout << "Menu constructor called" << std::endl;
//}

void Menu::move_next()
{
	if (selected_index < labels.size())
	{
		selected_index++;
	}
}

void Menu::move_previous()
{
	if (selected_index != 0)
	{
		selected_index--;
	}
}

void Menu::update()
{
	for (int i = 0; i < labels.size(); i++)
	{
		if (i == selected_index)
		{
			labels[i].set_color(selected_color);
		}
		else
		{
			labels[i].set_color(default_color);
		}
	}
}

int Menu::get_selected_index()
{
	return selected_index;
}

//void Menu::set_font(sf::Font & font)
//{
//	this->font = font;
//}
