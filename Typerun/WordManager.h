#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include "Word.h"
#include "MessageCenter.h"
#include "SFML/Graphics/Font.hpp"

class WordManager
{
public:
	std::vector<Word> words;
	MessageCenter* message_center;
private:
	std::string dictionary_path;
	int max_word_cache_size;
	int word_transfer_threshold;
	int viewport_width;
	int viewport_height;
	std::vector<std::string> word_cache;
	sf::Font font;
	sf::Color initial_color;
public:
	WordManager();
	WordManager(sf::Font& font, sf::Color initial_color, MessageCenter* message_center, int width, int height);
	void update();
private:
	void populate_word_cache();
	void shuffle_word_cache();
	void transfer_words(int max);
	int random_width();
	int random_height();
};

