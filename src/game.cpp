#include "game.hpp"

Game::Game()
{
	
}
Game::~Game()
{
	
}
int Game::init(int w, int h, int fullscreen)
{
	/*
	 * Variable declarations:
	*/
	int i;
	int w_;
	int h_;
	sf::VideoMode videomode;
	/*
	 * Get video info:
	*/
	std::cout << "Getting video mode...";
	videomode = sf::VideoMode::getDesktopMode();
	std::cout << "[DONE]" << std::endl;
	std::cout << "  Screen Resolution: " << videomode.width << "x" << videomode.height << "x" << videomode.bitsPerPixel << std::endl;
	m_screen_bits = videomode.bitsPerPixel;
	/*
	 * Check forced screen width:
	*/
	if (w == -1)
	{
		m_screen_w = videomode.width;
	}
	else
	{
		m_screen_w = w;
		std::cout << "  Forced Screen Width: " << w << std::endl;
	};
	/*
	 * Check forced screen height:
	*/
	if (h == -1)
	{
		m_screen_h = videomode.height;
	}
	else
	{
		m_screen_h = h;
		std::cout << "  Forced Screen Height: " << h << std::endl;
	};
	/*
	 * Create window:
	*/
	std::cout << "Creating window (" << m_screen_w << "x" << m_screen_h << "x" << m_screen_bits << ")... ";
	if (fullscreen == 1)
		m_window.create(videomode, "Game", sf::Style::Fullscreen);
	else
		m_window.create(sf::VideoMode(m_screen_w, m_screen_h, m_screen_bits), "Game");
	std::cout << "[DONE]" << std::endl;
	m_window_has_focus = 1;
	/*
	 * Calculate padding data:
	*/
	m_padding_data_calculator.set_screen_w(m_screen_w);
	m_padding_data_calculator.set_screen_h(m_screen_h);
	m_padding_data_calculator.calculate();
	/*
	 * Create padded texture:
	*/
	std::cout << "Creating padded texture... ";
	if (!m_texture.create(m_padding_data_calculator.get_usable_w(), m_padding_data_calculator.get_usable_h()))
	{
		std::cout << "[FAIL]" << std::endl;
		return 1;
	};
	std::cout << "[DONE]" << std::endl;
	/*
	 * Init cursor:
	*/
	m_window.setMouseCursorVisible(false);
	if (m_cursor.init() == 1)
		return 1;
	m_cursor.set_mouse_position(
		sf::Mouse::getPosition().x,
		sf::Mouse::getPosition().y
	);
	/*
	 * Finish successful:
	*/
	return EXIT_SUCCESS;
}
int Game::uninit(void)
{
	m_window.close();
	return EXIT_SUCCESS;
}
int Game::loop(void)
{
	/*
	 * Variable definitons:
	*/
	int done = 0;
	sf::Sprite sprite;
	sf::Texture img1;
	sf::Sprite img1_sprite;
	sf::Text text1;
	sf::String text1_str;
	std::ostringstream text1_float;
	/*
	 * Load img1:
	*/
	img1.loadFromFile("data/grass.png");
	img1_sprite.setTexture(img1);
	img1_sprite.setPosition(10, 10);
	img1_sprite.setColor(sf::Color(255, 255, 255, 255));
	img1_sprite.setScale(10, 10);
	/*
	 * Load text1:
	*/
	text1.setCharacterSize(20);
	text1.setColor(sf::Color::Red);
	text1.setPosition(10, m_padding_data_calculator.get_usable_h()-30);
	/*
	 * Reset framerate clock:
	*/
	m_framerate_clock.restart();
	m_framerate_frames = 0;
	/*
	 * Main loop:
	*/
	while (done == 0)
	{
		/*
		 * Process events:
		*/
		done = process_events();
		/*
		 * Check if we have to draw the stuff:
		*/
		if (m_window_has_focus == 1)
		{
			/*
			 * Clean window and padded texture:
			*/
			m_window.clear();
			m_texture.clear(sf::Color::White);
			/*
			 * Draw everything on padded texture and show it:
			*/
			m_texture.draw(img1_sprite);
			m_texture.draw(text1);
			m_texture.draw(m_cursor.get_drawable());
			m_texture.display();
			/*
			 * Draw padded texture on window and show it:
			*/
			sprite = sf::Sprite();
			sprite.setTexture(m_texture.getTexture());
			sprite.setPosition(
				m_padding_data_calculator.get_padding_x(),
				m_padding_data_calculator.get_padding_y()
			);
			m_window.draw(sprite);
			m_window.display();
			/*
			 * Calculate framerate:
			*/
			if (m_framerate_frames == 500)
			{
				std::cout << (m_framerate_frames/m_framerate_clock.getElapsedTime().asSeconds()) << " fps" << std::endl;
				text1_float.str("");
				text1_float << (m_framerate_frames/m_framerate_clock.getElapsedTime().asSeconds());
				text1_str = text1_float.str();
				text1_str += " fps";
				text1.setString(text1_str);
				m_framerate_clock.restart();
				m_framerate_frames = 0;
			}
			else
				m_framerate_frames++;
		}
		else
		{
			/*
			 * We have no focus, so we sleep:
			*/
			if (wait_for_focus() == 1)
				return 1;
		};
	}
	return done;
}
int Game::wait_for_focus(void)
{
	/*
	 * Variable declarations:
	*/
	sf::Event event;
	/*
	 * Wait for events:
	*/
	while (m_window.waitEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::GainedFocus:
				std::cout << "GainedFocus" << std::endl;
				m_window_has_focus = 1;
				m_framerate_clock.restart();
				m_framerate_frames = 0;
				return 0;
				break;
			case sf::Event::Closed:
				std::cout << "QUIT signal received." << std::endl;
				return 1;
				break;
		}
	}
}
int Game::process_events(void)
{
	/*
	 * Variable declarations:
	*/
	sf::Event event;
	int x, y;
	/*
	 * Check for events:
	*/
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				std::cout << "QUIT signal received." << std::endl;
				return 1;
				break;
			case sf::Event::KeyPressed:
				std::cout << "KeyPressed " << event.key.code << std::endl;
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						std::cout << "ESCAPE key pressed." << std::endl;
						return 1;
						break;
					case sf::Keyboard::F1:
						std::cout << "F1 key pressed." << std::endl;
						return 2;
						break;
				}
				break;
			case sf::Event::MouseMoved:
				/*
				 * Calculate new mouse position:
				*/
				x = event.mouseMove.x-m_padding_data_calculator.get_padding_x();
				y = event.mouseMove.y-m_padding_data_calculator.get_padding_y();
				if (x < 0)
					x = 0;
				else if (x > m_padding_data_calculator.get_usable_w())
					x = m_padding_data_calculator.get_usable_w();
				if (y < 0)
					y = 0;
				else if (y > m_padding_data_calculator.get_usable_h())
					y = m_padding_data_calculator.get_usable_h();
				/*
				 * Set mouse position:
				*/
				m_cursor.set_mouse_position(x, y);
				break;
			case sf::Event::MouseButtonPressed:
				std::cout << "MouseButtonPressed ";
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						std::cout << "LEFT";
						m_cursor.activate_action_cursor();
						break;
					case sf::Mouse::Middle:
						std::cout << "MIDDLE";
						break;
					case sf::Mouse::Right:
						std::cout << "RIGHT";
						break;
				}
				x = event.mouseButton.x-m_padding_data_calculator.get_padding_x();
				y = event.mouseButton.y-m_padding_data_calculator.get_padding_y();
				if (x < 0)
					x = 0;
				else if (x > m_padding_data_calculator.get_usable_w())
					x = m_padding_data_calculator.get_usable_w();
				if (y < 0)
					y = 0;
				else if (y > m_padding_data_calculator.get_usable_h())
					y = m_padding_data_calculator.get_usable_h();
				std::cout << " @ (" << x << "," << y << ")" << std::endl;
				break;
			case sf::Event::MouseButtonReleased:
				std::cout << "MouseButtonReleased ";
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						std::cout << "LEFT";
						m_cursor.deactivate_action_cursor();
						break;
					case sf::Mouse::Middle:
						std::cout << "MIDDLE";
						break;
					case sf::Mouse::Right:
						std::cout << "RIGHT";
						break;
				}
				x = event.mouseButton.x-m_padding_data_calculator.get_padding_x();
				y = event.mouseButton.y-m_padding_data_calculator.get_padding_y();
				if (x < 0)
					x = 0;
				else if (x > m_padding_data_calculator.get_usable_w())
					x = m_padding_data_calculator.get_usable_w();
				if (y < 0)
					y = 0;
				else if (y > m_padding_data_calculator.get_usable_h())
					y = m_padding_data_calculator.get_usable_h();
				std::cout << " @ (" << x << "," << y << ")" << std::endl;
				break;
			case sf::Event::LostFocus:
				std::cout << "LostFocus" << std::endl;
				m_window_has_focus = 0;
				break;
			case sf::Event::GainedFocus:
				std::cout << "GainedFocus" << std::endl;
				m_window_has_focus = 1;
				m_framerate_clock.restart();
				m_framerate_frames = 0;
				break;
		}
	}
	/*
	 * Finish successful:
	*/
	return EXIT_SUCCESS;
}
int Game::calculate_sizes(void)
{
	
}
