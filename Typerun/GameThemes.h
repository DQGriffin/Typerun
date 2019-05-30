#pragma once
#include "SFML/Graphics/Color.hpp"

namespace Themes
{
	enum class GameTheme {Default, Noir};

	struct DefaultTheme {
		sf::Color background_color = sf::Color(1, 1, 1);
		sf::Color initial_word_color = sf::Color(0, 255, 0);
		sf::Color horizontal_bar_color = sf::Color(205, 0, 205);
		sf::Color ui_text_color = sf::Color(0, 206, 205);
		bool shift_word_color = true;
	};

	struct NoirTheme {
		 sf::Color background_color = sf::Color(41, 40, 39);
		sf::Color initial_word_color = sf::Color(255, 255, 255);
		sf::Color horizontal_bar_color = sf::Color(255, 255, 255);
		sf::Color ui_text_color = sf::Color(255, 255, 255);
		bool shift_word_color = false;
	};
}