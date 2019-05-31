#include "MainMenu.h"



MainMenu::MainMenu()
{
}

MainMenu::MainMenu(sf::Font* font, int width, int height)
{
	//font_local = font;
	//set_font(font_local);

	int p_character_size = width / 12;

	Label label = Label("LL", "Play", *font, p_character_size, selected_color, sf::Text::Regular, sf::Vector2f((width / 2) - ((p_character_size / 2) * 2), (height / 2) - ((p_character_size / 2) * 2)));
	Label exit_label = Label("Exit", "Exit", *font, p_character_size, default_color, sf::Text::Regular, sf::Vector2f((width / 2) - ((p_character_size / 2) * 2), (height / 2) + 15));
	labels.push_back(label);
	labels.push_back(exit_label);
	//initialize();
}

void MainMenu::initialize()
{
	Label label = Label("P", "Play", font_local, 24, sf::Color::White, sf::Text::Regular, sf::Vector2f(50, 50));
	//labels.push_back(label);
}
