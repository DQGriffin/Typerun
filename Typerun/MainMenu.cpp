#include "MainMenu.h"



MainMenu::MainMenu()
{
}

MainMenu::MainMenu(sf::Font* font)
{
	//font_local = font;
	//set_font(font_local);

	Label label = Label("LL", "Play", *font, 36, selected_color, sf::Text::Regular, sf::Vector2f(100, 100));
	labels.push_back(label);

	//initialize();
}

void MainMenu::initialize()
{
	Label label = Label("P", "Play", font_local, 24, sf::Color::White, sf::Text::Regular, sf::Vector2f(50, 50));
	//labels.push_back(label);
}
