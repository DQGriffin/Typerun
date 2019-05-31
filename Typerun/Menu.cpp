#include "Menu.h"



Menu::Menu()
{
	selected_color = sf::Color::Cyan;
	default_color = sf::Color::White;
	selection_box_color = sf::Color::White;
	background_color = sf::Color::Black;
	selection_box = sf::RectangleShape();
	selection_box.setFillColor(selection_box_color);
}

//Menu::Menu(sf::Font & font) : font{font}
//{
//	selected_color = sf::Color::Cyan;
//	default_color = sf::Color::White;
//	std::cout << "Menu constructor called" << std::endl;
//}

void Menu::move_next()
{
	if (selected_index != labels.size() - 1)
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
	int width = labels[selected_index].get_drawable().getString().getSize() * (labels[selected_index].get_drawable().getCharacterSize() / 2) + 10;
	int height = labels[selected_index].get_drawable().getCharacterSize();
	int x = labels[selected_index].get_drawable().getPosition().x;
	int y = labels[selected_index].get_drawable().getPosition().y + (height / 6);

	selection_box.setSize(sf::Vector2f(width, height));
	selection_box.setPosition(sf::Vector2f(x, y));

	for (int i = 0; i < labels.size(); i++)
	{
		if (i == selected_index)
		{
			labels[i].set_color(background_color);
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
