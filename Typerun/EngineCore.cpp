#include "EngineCore.h"


//--------------------------------------------------------------------------
// EngineCore constructor
//--------------------------------------------------------------------------
EngineCore::EngineCore()
{
	// Set default settings
	display_debug_messages = false;
	width = sf::VideoMode::getDesktopMode().width / 1.5;
	height = sf::VideoMode::getDesktopMode().height / 1.5;

	paused = false;

	initialize_font();
	initialize_colors();
	initialize_ui();

	message_center = MessageCenter(font, height);
	message_center.post_message("Engine initialized");
	message_center.post_message("Height: " + std::to_string(height));
	message_center.post_message("Width: " + std::to_string(width));

	word_manager = WordManager(font, initial_word_color, &message_center, width, height);
}


EngineCore::~EngineCore()
{
}

//--------------------------------------------------------------------------
// EngineCore::start()
// Starts the game
//--------------------------------------------------------------------------
void EngineCore::start()
{
	game_loop();
}

//--------------------------------------------------------------------------
// Reads the font into memory and prepares it for use
//--------------------------------------------------------------------------
void EngineCore::initialize_font()
{

	// Lighter font: GeosansLight.ttf
	// Thicker font: Vera.ttf
	if (!font.loadFromFile("Vera.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
}

//--------------------------------------------------------------------------
// Sets the colors used by the game
//--------------------------------------------------------------------------
void EngineCore::initialize_colors()
{
	background_color = sf::Color::Black;
	initial_word_color = sf::Color(0, 255, 0);
	horizontal_bar_color = sf::Color(205, 0, 205);
	ui_text_color = sf::Color(0, 206, 205);
}

void EngineCore::initialize_ui()
{
	// Horizontal bar
	ui_horizontal_bar.setFillColor(horizontal_bar_color);
	ui_horizontal_bar.setSize(sf::Vector2f(width,2));
	ui_horizontal_bar.setPosition(sf::Vector2f(0, height - 50));

	// Left and right arrows
	ui_left_arrow = Label("LA", ">", font, 24, horizontal_bar_color, sf::Text::Regular, sf::Vector2f(10, height - 40));
	ui_right_arrow = Label("RA", "<", font, 24, horizontal_bar_color, sf::Text::Regular, sf::Vector2f(300, height - 40));

	ui_score_label = Label("UISC", "Score: ", font, 24, ui_text_color, sf::Text::Regular, sf::Vector2f((width / 2) - 150, height - 40));
	ui_misses_label = Label("UIML", "Misses: ", font, 24, ui_text_color, sf::Text::Regular, sf::Vector2f((width / 2) + 50, height - 40));
}

//--------------------------------------------------------------------------
// The main game loop
//--------------------------------------------------------------------------
void EngineCore::game_loop()
{
	window.create(sf::VideoMode(width, height), "Typerun - " + version);
	window.setVerticalSyncEnabled(true);

	// For debug purposes
	sf::CircleShape shape(5.f);
	shape.setFillColor(sf::Color::Green);

	Word word = Word("dexterity", sf::Vector2f(50, 50), initial_word_color, font);
	Word word2 = Word("destiny", sf::Vector2f(25, 75), initial_word_color, font);
	word.viewport_width = width;
	word2.viewport_width = width;
	word2.speed = 3;
	words.push_back(word);
	words.push_back(word2);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

		}

		if (!paused)
		{
			update();
		}
		message_center.update();
		window.clear();
		display_messages();
		window.draw(shape);
		display_words();
		display_ui();
		window.display();
	}

}

//--------------------------------------------------------------------------
// Updates the game (Does not update messages)
//--------------------------------------------------------------------------
void EngineCore::update()
{
	update_words();
}

void EngineCore::update_words()
{
	word_manager.update();
}

//--------------------------------------------------------------------------
// Displays all alive messages
//--------------------------------------------------------------------------
void EngineCore::display_messages()
{
	for (Message& message : message_center.messages)
	{
		window.draw(message.label.get_drawable());
	}
}

void EngineCore::display_words()
{
	for (Word& word : word_manager.words)
	{
		window.draw(word.get_drawable());
	}
}

void EngineCore::display_ui()
{
	window.draw(ui_horizontal_bar);
	window.draw(ui_left_arrow.get_drawable());
	window.draw(ui_right_arrow.get_drawable());
	window.draw(ui_score_label.get_drawable());
	window.draw(ui_misses_label.get_drawable());
}
