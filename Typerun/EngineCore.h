#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "MessageCenter.h"
#include "Word.h"
#include "Label.h"

class EngineCore
{
public:
	const std::string version = "0.1.0";
	MessageCenter message_center;
	std::vector<Word> words;
private:
	int width;
	int height;
	int score;
	int misses;
	int maximum_misses;
	bool display_debug_messages;
	bool paused;
	sf::RenderWindow window;
	sf::Font font;
	sf::Color background_color;
	sf::Color initial_word_color;
	sf::Color horizontal_bar_color;
	sf::RectangleShape ui_horizontal_bar;
	Label ui_left_arrow;
	Label ui_right_arrow;

public:
	EngineCore();
	~EngineCore();
	void start();
private:
	void initialize_font();
	void initialize_colors();
	void initialize_ui();
	void game_loop();
	void update();
	void update_words();
	void display_messages();
	void display_words();
	void display_ui();
};

