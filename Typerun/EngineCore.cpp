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
	score_increment = 20;
	maximum_misses = 15;

	//theme = Themes::GameTheme::Default;
	theme = Themes::GameTheme::Noir;

	initialize_font();
	apply_theme();
	initialize_ui();
	initialize_message_center();
	initialize_word_manager();

	main_menu = MainMenu(&font, width, height);
	state = GameState::Play;
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

//--------------------------------------------------------------------------
// Initializes UI elements
//--------------------------------------------------------------------------
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
	
	ui_text_field = TextField(sf::Vector2f(35, height - 40), ui_text_color, font);
	
}

void EngineCore::initialize_message_center()
{
	message_center = MessageCenter(font, height);
	message_center.post_message("Starting engine");
	message_center.post_message("Height: " + std::to_string(height));
	message_center.post_message("Width: " + std::to_string(width));
}

void EngineCore::initialize_word_manager()
{
	word_manager = WordManager(font, initial_word_color, &message_center, width, ui_horizontal_bar.getPosition().y - 50, shift_word_color);
	word_manager.average_onscreen_time = &average_onscreen_time;
	word_manager.score = &score;
	word_manager.misses = &misses;
}

void EngineCore::apply_theme()
{
	if (theme == Themes::GameTheme::Default)
	{
		Themes::DefaultTheme default_theme;
		background_color = default_theme.background_color;
		initial_word_color = default_theme.initial_word_color;
		horizontal_bar_color = default_theme.horizontal_bar_color;
		ui_text_color = default_theme.ui_text_color;
		shift_word_color = default_theme.shift_word_color;
	}
	else if (theme == Themes::GameTheme::Noir)
	{
		Themes::NoirTheme noir_theme;
		background_color = noir_theme.background_color;
		initial_word_color = noir_theme.initial_word_color;
		horizontal_bar_color = noir_theme.horizontal_bar_color;
		ui_text_color = noir_theme.ui_text_color;
		shift_word_color = noir_theme.shift_word_color;
	}
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

	/*Word word = Word("dexterity", sf::Vector2f(50, 50), initial_word_color, font);
	Word word2 = Word("destiny", sf::Vector2f(25, 75), initial_word_color, font);
	word.viewport_width = width;
	word2.viewport_width = width;
	word2.speed = 3;
	words.push_back(word);
	words.push_back(word2);*/

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				parse_keyboard_input(event.key);
			}
		}

		//- New update loop start
		window.clear();
		if (state == GameState::Menu)
		{
			main_menu.update();
			display_main_menu();
		}
		else if (state == GameState::Play)
		{
			update();
			window.draw(shape); // For debugging purposes
			display_words();
			update_ui();
			display_ui();
		}
		else if (state == GameState::Paused)
		{
			display_words();
			display_ui();
		}
		message_center.update();
		display_messages();
		window.display();
		//- New update loop end

		/*if (!paused)
		{
			update();
		}
		main_menu.update();
		message_center.update();
		window.clear(background_color);
		display_main_menu();
		display_messages();
		update_ui();
		window.draw(shape);
		display_words();
		display_ui();
		window.display();*/
	}

}

//--------------------------------------------------------------------------
// Updates the game (Does not update messages)
//--------------------------------------------------------------------------
void EngineCore::update()
{
	update_words();
	if (misses >= maximum_misses)
	{
		// The game is over
		paused = true;
	}
}

//--------------------------------------------------------------------------
// Updates all currently alive words
//--------------------------------------------------------------------------
void EngineCore::update_words()
{
	word_manager.update();
}

void EngineCore::update_ui()
{
	ui_score_label.set_text("Score: " + std::to_string(score));
	ui_misses_label.set_text("Missed: " + std::to_string(misses));
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

//--------------------------------------------------------------------------
// Displays all alive words
//--------------------------------------------------------------------------
void EngineCore::display_words()
{
	for (Word& word : word_manager.words)
	{
		window.draw(word.get_drawable());
	}
}

//--------------------------------------------------------------------------
// Displays UI elements
//--------------------------------------------------------------------------
void EngineCore::display_ui()
{
	window.draw(ui_horizontal_bar);
	window.draw(ui_left_arrow.get_drawable());
	window.draw(ui_right_arrow.get_drawable());
	window.draw(ui_score_label.get_drawable());
	window.draw(ui_misses_label.get_drawable());
	window.draw(ui_text_field.get_drawable());
}

void EngineCore::display_main_menu()
{
	for (Label& label : main_menu.labels)
	{
		window.draw(label.get_drawable());
	}
}

void EngineCore::query_input()
{
	bool result = word_manager.query(ui_text_field.get_text());
	ui_text_field.clear();
	if (result)
	{
		score += score_increment;
		message_center.post_message("The correct word was entered");
	}
	else
	{
		message_center.post_message("The input was not correct");
	}
}

void EngineCore::parse_keyboard_input(sf::Event::KeyEvent key_event)
{
	switch (key_event.code)
	{
	default:
		break;
	case sf::Keyboard::Backspace:
		ui_text_field.remove_last_character();
		break;
	case sf::Keyboard::Enter:
		query_input();
		break;
	case sf::Keyboard::Escape:
		state == GameState::Play ? state = GameState::Paused : state = GameState::Play;
		break;
	case sf::Keyboard::Pause:
		state == GameState::Play ? state = GameState::Paused : state = GameState::Play;
		break;
	case sf::Keyboard::End:
		std::exit(0);
		break;
	case sf::Keyboard::Up:
		main_menu.move_previous();
		break;
	case sf::Keyboard::Down:
		main_menu.move_next();
		break;
	case sf::Keyboard::A:
		ui_text_field.add_character('a');
		break;
	case sf::Keyboard::B:
		ui_text_field.add_character('b');
		break;
	case sf::Keyboard::C:
		ui_text_field.add_character('c');
		break;
	case sf::Keyboard::D:
		ui_text_field.add_character('d');
		break;
	case sf::Keyboard::E:
		ui_text_field.add_character('e');
		break;
	case sf::Keyboard::F:
		ui_text_field.add_character('f');
		break;
	case sf::Keyboard::G:
		ui_text_field.add_character('g');
		break;
	case sf::Keyboard::H:
		ui_text_field.add_character('h');
		break;
	case sf::Keyboard::I:
		ui_text_field.add_character('i');
		break;
	case sf::Keyboard::J:
		ui_text_field.add_character('j');
		break;
	case sf::Keyboard::K:
		ui_text_field.add_character('k');
		break;
	case sf::Keyboard::L:
		ui_text_field.add_character('l');
		break;
	case sf::Keyboard::M:
		ui_text_field.add_character('m');
		break;
	case sf::Keyboard::N:
		ui_text_field.add_character('n');
		break;
	case sf::Keyboard::O:
		ui_text_field.add_character('o');
		break;
	case sf::Keyboard::P:
		ui_text_field.add_character('p');
		break;
	case sf::Keyboard::Q:
		ui_text_field.add_character('q');
		break;
	case sf::Keyboard::R:
		ui_text_field.add_character('r');
		break;
	case sf::Keyboard::S:
		ui_text_field.add_character('s');
		break;
	case sf::Keyboard::T:
		ui_text_field.add_character('t');
		break;
	case sf::Keyboard::U:
		ui_text_field.add_character('u');
		break;
	case sf::Keyboard::V:
		ui_text_field.add_character('v');
		break;
	case sf::Keyboard::W:
		ui_text_field.add_character('w');
		break;
	case sf::Keyboard::X:
		ui_text_field.add_character('x');
		break;
	case sf::Keyboard::Y:
		ui_text_field.add_character('y');
		break;
	case sf::Keyboard::Z:
		ui_text_field.add_character('z');
		break;
	case sf::Keyboard::Hyphen:
		ui_text_field.add_character('-');
		break;
	}
}
