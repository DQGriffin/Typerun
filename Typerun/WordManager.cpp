#include "WordManager.h"


WordManager::WordManager()
{
}

WordManager::WordManager(sf::Font& font, sf::Color initial_color, MessageCenter* message_center, int width, int height) : font{font}, message_center{message_center}, viewport_width{width}, viewport_height{height}
{
	this->initial_color = initial_color;
	dictionary_path = "dict.txt";

	max_word_cache_size = 80000;
	word_transfer_threshold = 10;
	min_word_speed = 1;
	max_word_speed = 4;

	populate_word_cache();
}

void WordManager::update()
{
	if (words.size() < word_transfer_threshold)
	{
		transfer_words(word_transfer_threshold - words.size());
	}

	for (Word& word : words)
	{
		word.update();
	}
}

void WordManager::populate_word_cache()
{
	std::ifstream input_stream(dictionary_path, std::ios::in);
	if (!input_stream)
	{
		std::cout << "Failed to open dictionary file" << std::endl;
	}

	std::string word;

	for (int i = 0; i != max_word_cache_size; i++)
	{
		std::getline(input_stream, word, '\n');

		if (word != "")
		{
			word_cache.push_back(word);
		}
	}

	message_center->post_message("Word cache built");
	message_center->post_message(std::to_string(word_cache.size()) + " words cached");
	shuffle_word_cache();
}

void WordManager::shuffle_word_cache()
{
	message_center->post_message("Shuffling words");

	// Obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(word_cache.begin(), word_cache.end(), std::default_random_engine(seed));

	message_center->post_message("Finished shuffling words");
}

void WordManager::transfer_words(int max)
{
	message_center->post_message("Transfering " + std::to_string(max) + " words");
	for (int i = 0; i < max; i++)
	{
		Word word = Word(word_cache.back(), sf::Vector2f(-50 * (random_width() * 0.03), random_height()), initial_color, font);
		word.viewport_width = viewport_width;
		word.speed = random_speed();
		words.push_back(word);
		word_cache.pop_back();
	}
}

int WordManager::random_width()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, viewport_width);
	int result = uniform_dist(e1);
	return result;
}

int WordManager::random_height()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, viewport_height);
	int result = uniform_dist(e1);
	return result;
}

int WordManager::random_speed()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(min_word_speed, max_word_speed);
	int result = uniform_dist(e1);
	return result;
}
