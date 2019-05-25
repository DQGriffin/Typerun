#include "WordManager.h"


WordManager::WordManager()
{
}

//--------------------------------------------------------------------------
// WordManager constructor
//--------------------------------------------------------------------------
WordManager::WordManager(sf::Font& font, sf::Color initial_color, MessageCenter* message_center, int width, int height) : font{font}, message_center{message_center}, viewport_width{width}, viewport_height{height}
{
	this->initial_color = initial_color;
	dictionary_path = "dict.txt";

	max_word_cache_size = 80000;
	word_transfer_threshold = 10;
	min_word_speed = 1;
	max_word_speed = 1;

	populate_word_cache();
}

//--------------------------------------------------------------------------
// Transfers words from the cache if neccessary and updates all alive words
//--------------------------------------------------------------------------
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

	for (Word& word : words)
	{
		if (word.get_drawable().getPosition().x > viewport_width)
		{
			// The word is off-screen, notify the engine and remove the word from the vector
			*misses += 1;
			remove_word(word.get_id());
		}
	}
}

//--------------------------------------------------------------------------
// Compares a given input to all live Words. Removes the word if it is found
//--------------------------------------------------------------------------
bool WordManager::query(std::string query)
{
	for (int index = 0; index < words.size(); index++)
	{
		if (words[index].get_drawable().getString().toAnsiString() == query)
		{
			remove_word(words[index].get_id());
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------------
// Reads words from the dictionary file into the std::vector
//--------------------------------------------------------------------------
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

//--------------------------------------------------------------------------
// Shuffles the words in the std::vector
//--------------------------------------------------------------------------
void WordManager::shuffle_word_cache()
{
	message_center->post_message("Shuffling words");

	// Obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(word_cache.begin(), word_cache.end(), std::default_random_engine(seed));

	message_center->post_message("Finished shuffling words");
}

//--------------------------------------------------------------------------
// Transfer words from the cache to the Word vector
//--------------------------------------------------------------------------
void WordManager::transfer_words(int max)
{
	for (int i = 0; i < max; i++)
	{
		Word word = Word(word_cache.back(), sf::Vector2f(-50 * (random_x_pos() * 0.03), random_y_pos()), initial_color, font);
		word.viewport_width = viewport_width;
		word.speed = random_speed();
		words.push_back(word);
		word_cache.pop_back();
	}
}

//--------------------------------------------------------------------------
// Generates and returns a random x-position
//--------------------------------------------------------------------------
int WordManager::random_x_pos()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, viewport_width);
	int result = uniform_dist(e1);
	return result;
}

//--------------------------------------------------------------------------
// Generates and returns a random y_position
//--------------------------------------------------------------------------
int WordManager::random_y_pos()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, viewport_height);
	int result = uniform_dist(e1);
	return result;
}

//--------------------------------------------------------------------------
// Generates and returns a random speed
//--------------------------------------------------------------------------
int WordManager::random_speed()
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(min_word_speed, max_word_speed);
	int result = uniform_dist(e1);
	return result;
}

void WordManager::remove_word(int id)
{
	for (int index = 0; index <= words.size(); index++)
	{
		if (words[index].get_id() == id)
		{
			// The word has been found, remove it
			words.erase(words.begin() + index);
			break;
		}
	}

}
