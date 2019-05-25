#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "MessageCenter.h"
#include "Word.h"
#include "Label.h"
#include "WordManager.h"
#include "TextField.h"

class EngineCore
{
public:
	const std::string version = "0.1.1";
	MessageCenter message_center;
	std::vector<Word> words;
private:
	int width;
	int height;
	int score;
	int misses;
	int maximum_misses;
	int score_increment;
	double average_onscreen_time;
	bool display_debug_messages;
	bool paused;
	sf::RenderWindow window;
	sf::Font font;
	sf::Color background_color;
	sf::Color initial_word_color;
	sf::Color horizontal_bar_color;
	sf::Color ui_text_color;
	sf::RectangleShape ui_horizontal_bar;
	Label ui_left_arrow;
	Label ui_right_arrow;
	Label ui_score_label;
	Label ui_misses_label;
	TextField ui_text_field;
	WordManager word_manager;

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
	void update_ui();
	void display_messages();
	void display_words();
	void display_ui();
	void query_input();
	void parse_keyboard_input(sf::Event::KeyEvent key_event);
};

