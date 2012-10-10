/*
 * game.cpp
 * 
 * Copyright 2012 Robert Knauer <robert@privatdemail.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include "game.hpp"

Game::Game()
{
	
}
Game::~Game()
{
	
}
int Game::init(void)
{
	std::cout << "========== INIT START ==========" << std::endl;
	/*
	 * Variable declarations:
	*/
	sf::VideoMode videomode;
	sf::Image icon;
	/*
	 * Load configuration:
	*/
	m_config.load();
	m_config.dump();
	if (!m_config.write())
		return 1;
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
	if (m_config.get("GRAPHICS__RESOLUTION_X").value_int == 0)
	{
		m_screen_w = videomode.width;
	}
	else
	{
		m_screen_w = m_config.get("GRAPHICS__RESOLUTION_X").value_int;
		std::cout << "  Forced Screen Width: " << m_screen_w << std::endl;
	};
	/*
	 * Check forced screen height:
	*/
	if (m_config.get("GRAPHICS__RESOLUTION_Y").value_int == 0)
	{
		m_screen_h = videomode.height;
	}
	else
	{
		m_screen_h = m_config.get("GRAPHICS__RESOLUTION_Y").value_int;
		std::cout << "  Forced Screen Height: " << m_screen_h << std::endl;
	};
	/*
	 * Init locale:
	*/
	if (init_locale() == 1)
		return 1;
	/*
	 * Create window:
	*/
	std::cout << "Creating window (" << m_screen_w << "x" << m_screen_h << "x" << m_screen_bits << ")... ";
	if (m_config.get("GRAPHICS__FULLSCREEN").value_bool)
		m_window.create(videomode, "Game", sf::Style::Fullscreen);
	else
		m_window.create(sf::VideoMode(m_screen_w, m_screen_h, m_screen_bits), "Game");
	std::cout << "[DONE]" << std::endl;
	m_window_has_focus = 1;
	/*
	 * Set window icon:
	*/
	std::cout << "Setting window icon... ";
	if (!icon.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "icon.png")))
	{
		std::cout << "[FAIL]" << std::endl;
		return 1;
	};
	m_window.setIcon(
		icon.getSize().x,
		icon.getSize().y,
		icon.getPixelsPtr()
	);
	std::cout << "[DONE]" << std::endl;
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
	 * Init framecounter:
	*/
	m_fps_counter.init();
	/*
	 * Show main menu:
	*/
	m_gamemode = 0;
	if (set_gamemode(1) == 1)
		return 1;
	/*
	 * Finish successful:
	*/
	std::cout << "========== INIT DONE ==========" << std::endl;
	return 0;
}
int Game::uninit(void)
{
	uninit_gamemode(m_gamemode);
	m_window.close();
	return EXIT_SUCCESS;
}
void Game::draw(void)
{
	/*
	 * Variable declarations:
	*/
	int i;
	UniversalDrawableArray drawables;
	UniversalDrawable drawable;
	sf::Sprite sprite;
	/*
	 * Clean window and padded texture:
	*/
	m_window.clear();
	m_texture.clear(COLOR_MENU_BACKGROUND);
	/*
	 * Get drawables from the GameMode classes:
	*/
	switch (m_gamemode)
	{
		case 1:
			/*
			 * Main Menu
			*/
			drawables = m_main_menu->get_drawables();
			break;
		case 2:
			/*
			 * Settings Menu
			*/
			drawables = m_settings_menu->get_drawables();
			break;
		case 3:
			/*
			 * Settings General Menu
			*/
			drawables = m_settings_general_menu->get_drawables();
			break;
		case 4:
			/*
			 * Settings Graphics Menu
			*/
			drawables = m_settings_graphics_menu->get_drawables();
			break;
		case 5:
			/*
			 * Settings Control Menu
			*/
			drawables = m_settings_control_menu->get_drawables();
			break;
		case 6:
			/*
			 * Settings Sound Menu
			*/
			drawables = m_settings_sound_menu->get_drawables();
			break;
	}
	/*
	 * Run through drawables:
	*/
	for (i=0; i < drawables.get_count(); i++)
	{
		/*
		 * ... and draw them:
		*/
		drawable = drawables.get(i);
		switch (drawable.type)
		{
			case UNIVERSAL_DRAWABLE_TYPE_TEXT:
				m_texture.draw(drawable.value_text);
				break;
			case UNIVERSAL_DRAWABLE_TYPE_RECTSHAPE:
				m_texture.draw(drawable.value_rectshape);
				break;
			case UNIVERSAL_DRAWABLE_TYPE_SPRITE:
				m_texture.draw(drawable.value_sprite);
				break;
		}
	}
	/*
	 * IMPORTANT: Uninit UniversalDrawableArray to prevent memory leaks:
	*/
	drawables.uninit();
	/*
	 * Draw cursor:
	*/
	m_texture.draw(m_cursor.get_drawable(
		m_padding_data_calculator.get_usable_w(),
		m_padding_data_calculator.get_usable_h()
	));
	/*
	 * Draw FPS counter:
	*/
	if (m_config.get("GENERAL__FPSCOUNTER").value_bool)
		m_texture.draw(m_fps_counter.get_drawable());
	/*
	 * Show everything on padded texture:
	*/
	m_texture.display();
	/*
	 * Draw padded texture on window:
	*/
	sprite.setTexture(m_texture.getTexture());
	sprite.setPosition(
		m_padding_data_calculator.get_padding_x(),
		m_padding_data_calculator.get_padding_y()
	);
	m_window.draw(sprite);
	/*
	 * Show window:
	*/
	m_window.display();
}
int Game::loop(void)
{
	/*
	 * Variable definitons:
	*/
	int done = 0;
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
			draw();
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
/*
 * See:
 * https://www.gnu.org/software/gettext/FAQ.html#windows_setenv
*/
int Game::set_envvar(std::string name, std::string value)
{
#ifdef _WIN32
	/*
	 * SetEnvironmentVariableA():
	 * (Windows only)
	*/
	if (!SetEnvironmentVariableA(name.c_str(), value.c_str()))
	{
		std::cout << "SetEnvironmentVariableA(" << name << ", " << value << ") failed." << std::endl;
		return 1;
	};
#endif // _WIN32
#if defined(HAVE_SETENV)
	/*
	 * setenv():
	*/
	return setenv(name.c_str(), value.c_str(), 1);
#elif defined(HAVE_PUTENV)
	/*
	 * putenv():
	*/
	std::stringstream buffer;
	buffer.str("");
	buffer << name;
	buffer << "=";
	buffer << value;
	return putenv((char *)buffer.str().c_str());
#else
	/*
	 * Nothing, compiler error:
	*/
#	error "FATAL: No putenv() or setenv() found."
#endif // HAVE_PUTENV; HAVE_SETENV
}
int Game::init_locale(void)
{
	if (set_envvar("LANGUAGE", m_config.get("GENERAL__LANGUAGE").value_string) == 1)
		return 1;
	setlocale(LC_ALL, "");
	bindtextdomain(PROJECTNAME, "./locale");
	textdomain(PROJECTNAME);
	return 0;
}
int Game::set_language(std::string lang, bool reload)
{
	/*
	 * Set environment variable:
	*/
	if (set_envvar("LANGUAGE", lang) == 1)
		return 1;
	/*
	 * Make it public:
	*/
	{
		extern int _nl_msg_cat_cntr;
		++_nl_msg_cat_cntr;
	}
	/*
	 * Reload menu:
	*/
	if (reload)
		if (set_gamemode(m_gamemode) == 1)
			return 1;
	return 0;
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
				m_fps_counter.restart();
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
	 * Variable definitions:
	*/
	sf::Event event;
	int x, y;
	int i;
	EventProcessorReturn event_processor_return;
	/*
	 * Check for events:
	*/
	while (m_window.pollEvent(event))
	{
		/*
		 * Handle important events:
		*/
		switch (event.type)
		{
			case sf::Event::Closed:
				std::cout << "QUIT signal received." << std::endl;
				return 1; // exit
				break;
			case sf::Event::KeyPressed:
				std::cout << "KeyPressed " << event.key.code << std::endl;
				switch (event.key.code)
				{
					case sf::Keyboard::F1:
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
				//std::cout << "MouseButtonPressed ";
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						//std::cout << "LEFT";
						m_cursor.activate_action_cursor();
						break;
					case sf::Mouse::Middle:
						//std::cout << "MIDDLE";
						break;
					case sf::Mouse::Right:
						//std::cout << "RIGHT";
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
				//std::cout << " @ (" << x << "," << y << ")" << std::endl;
				break;
			case sf::Event::MouseButtonReleased:
				//std::cout << "MouseButtonReleased ";
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						//std::cout << "LEFT";
						m_cursor.deactivate_action_cursor();
						break;
					case sf::Mouse::Middle:
						//std::cout << "MIDDLE";
						break;
					case sf::Mouse::Right:
						//std::cout << "RIGHT";
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
				//std::cout << " @ (" << x << "," << y << ")" << std::endl;
				break;
			case sf::Event::LostFocus:
				std::cout << "LostFocus" << std::endl;
				m_window_has_focus = 0;
				break;
			case sf::Event::GainedFocus:
				std::cout << "GainedFocus" << std::endl;
				m_window_has_focus = 1;
				m_fps_counter.restart();
				break;
		}
		/*
		 * And then let the gamemode classes handle them:
		*/
		switch (m_gamemode)
		{
			case 1:
				/*
				 * Main Menu
				*/
				event_processor_return = m_main_menu->process_event(
					event,
					m_cursor.get_mouse_position_x(),
					m_cursor.get_mouse_position_y()
				);
				break;
			case 2:
				/*
				 * Settings Menu
				*/
				event_processor_return = m_settings_menu->process_event(
					event,
					m_cursor.get_mouse_position_x(),
					m_cursor.get_mouse_position_y()
				);
				break;
			case 3:
				/*
				 * Settings General Menu
				*/
				event_processor_return = m_settings_general_menu->process_event(
					event,
					m_cursor.get_mouse_position_x(),
					m_cursor.get_mouse_position_y()
				);
				break;
			case 4:
				/*
				 * Settings Graphics Menu
				*/
				event_processor_return = m_settings_graphics_menu->process_event(
					event,
					m_cursor.get_mouse_position_x(),
					m_cursor.get_mouse_position_y()
				);
				break;
			case 5:
				/*
				 * Settings Control Menu
				*/
				event_processor_return = m_settings_control_menu->process_event(
					event,
					m_cursor.get_mouse_position_x(),
					m_cursor.get_mouse_position_y()
				);
				break;
			case 6:
				/*
				 * Settings Sound Menu
				*/
				event_processor_return = m_settings_sound_menu->process_event(
					event,
					m_cursor.get_mouse_position_x(),
					m_cursor.get_mouse_position_y()
				);
				break;
		}
		/*
		 * Set config variables?
		*/
		if (event_processor_return.are_confvars_initialized())
		{
			for (i=0; i < event_processor_return.get_confvars_count(); i++)
			{
				if (!m_config.set(event_processor_return.get_confvar(i)))
					return 1; // setting configvar failed, exit
			}
			if (!m_config.write())
				return 1; // writing config failed, exit
		};
		/*
		 * Set language?
		*/
		if (event_processor_return.get_language().compare("") != 0)
			if (set_language(event_processor_return.get_language(), false) == 1)
				return 1; // setting language failed, exit
		/*
		 * Change GameMode?
		*/
		if (event_processor_return.get_gamemode() != 0)
			if (set_gamemode(event_processor_return.get_gamemode()) == 1) // set gamemode
				return 1; // setting gamemode failed, exit
		/*
		 * Reload?
		*/
		if (event_processor_return.get_reload())
			return 2; // reload
		/*
		 * Exit?
		*/
		if (event_processor_return.get_exit())
			return 1; // exit
		/*
		 * IMPORTANT: Uninit EventProcessorReturn to prevent memory leaks:
		*/
		event_processor_return.uninit();
	}
	/*
	 * Finish successful:
	*/
	return 0;
}
int Game::calculate_sizes(void)
{
	/*
	 * Cursor:
	*/
	m_cursor.calculate_sizes(
		m_padding_data_calculator.get_usable_w(),
		m_padding_data_calculator.get_usable_h()
	);
	/*
	 * FPS counter:
	*/
	m_fps_counter.calculate_sizes(
		m_padding_data_calculator.get_usable_w(),
		m_padding_data_calculator.get_usable_h()
	);
	/*
	 * Game Modes:
	*/
	switch (m_gamemode)
	{
		case 1:
			/*
			 * Main Menu
			*/
			if (m_main_menu->calculate_sizes(
				m_padding_data_calculator.get_usable_w(),
				m_padding_data_calculator.get_usable_h()
			) == 1)
				return 1;
			break;
		case 2:
			/*
			 * Settings Menu
			*/
			if (m_settings_menu->calculate_sizes(
				m_padding_data_calculator.get_usable_w(),
				m_padding_data_calculator.get_usable_h()
			) == 1)
				return 1;
			break;
		case 3:
			/*
			 * Settings General Menu
			*/
			if (m_settings_general_menu->calculate_sizes(
				m_padding_data_calculator.get_usable_w(),
				m_padding_data_calculator.get_usable_h()
			) == 1)
				return 1;
			break;
		case 4:
			/*
			 * Settings Graphics Menu
			*/
			if (m_settings_graphics_menu->calculate_sizes(
				m_padding_data_calculator.get_usable_w(),
				m_padding_data_calculator.get_usable_h()
			) == 1)
				return 1;
			break;
		case 5:
			/*
			 * Settings Control Menu
			*/
			if (m_settings_control_menu->calculate_sizes(
				m_padding_data_calculator.get_usable_w(),
				m_padding_data_calculator.get_usable_h()
			) == 1)
				return 1;
			break;
		case 6:
			/*
			 * Settings Sound Menu
			*/
			if (m_settings_sound_menu->calculate_sizes(
				m_padding_data_calculator.get_usable_w(),
				m_padding_data_calculator.get_usable_h()
			) == 1)
				return 1;
			break;
	}
	return 0;
}
int Game::set_gamemode(int gamemode)
{
	std::cout << ">>>> ENTERING GAMEMODE [" << gamemode << "]" << std::endl;
	/*
	 * Uninit old game mode:
	*/
	if (uninit_gamemode(m_gamemode) == 1)
		return 1;
	/*
	 * Init new game mode:
	*/
	if (init_gamemode(gamemode) == 1)
		return 1;
	/*
	 * Set new game mode variable:
	*/
	m_gamemode = gamemode;
	/*
	 * Calculate sizes:
	*/
	calculate_sizes();
	/*
	 * Print status message:
	*/
	std::cout << ">>>> ENTERED GAMEMODE  [" << m_gamemode << "]" << std::endl;
}
int Game::init_gamemode(int gamemode)
{
	switch (gamemode)
	{
		case 1:
			/*
			 * Main Menu
			*/
			m_main_menu = new MainMenu;
			if (m_main_menu->init() == 1)
				return 1;
			break;
		case 2:
			/*
			 * Settings Menu
			*/
			m_settings_menu = new SettingsMenu;
			if (m_settings_menu->init() == 1)
				return 1;
			break;
		case 3:
			/*
			 * Settings General Menu
			*/
			m_settings_general_menu = new SettingsGeneralMenu;
			if (m_settings_general_menu->init(
				m_config.get("GENERAL__LANGUAGE").value_string,
				m_config.get("GENERAL__FPSCOUNTER").value_bool
			) == 1)
				return 1;
			break;
		case 4:
			/*
			 * Settings Graphics Menu
			*/
			m_settings_graphics_menu = new SettingsGraphicsMenu;
			if (m_settings_graphics_menu->init(
				m_config.get("GRAPHICS__FULLSCREEN").value_bool,
				m_config.get("GRAPHICS__RESOLUTION_X").value_int,
				m_config.get("GRAPHICS__RESOLUTION_Y").value_int
			) == 1)
				return 1;
			break;
		case 5:
			/*
			 * Settings Control Menu
			*/
			m_settings_control_menu = new SettingsControlMenu;
			if (m_settings_control_menu->init() == 1)
				return 1;
			break;
		case 6:
			/*
			 * Settings Sound Menu
			*/
			m_settings_sound_menu = new SettingsSoundMenu;
			if (m_settings_sound_menu->init() == 1)
				return 1;
			break;
		default:
			std::cout << "Invalid gamemode passed to init_gamemode(): " << gamemode << std::endl;
			return 1;
			break;
	}
	return 0;
}
int Game::uninit_gamemode(int gamemode)
{
	switch (gamemode)
	{
		case 1:
			/*
			 * Main Menu
			*/
			if (m_main_menu->uninit() == 1)
				return 1;
			delete m_main_menu;
			break;
		case 2:
			/*
			 * Settings Menu
			*/
			if (m_settings_menu->uninit() == 1)
				return 1;
			delete m_settings_menu;
			break;
		case 3:
			/*
			 * Settings General Menu
			*/
			if (m_settings_general_menu->uninit() == 1)
				return 1;
			delete m_settings_general_menu;
			break;
		case 4:
			/*
			 * Settings Graphics Menu
			*/
			if (m_settings_graphics_menu->uninit() == 1)
				return 1;
			delete m_settings_graphics_menu;
			break;
		case 5:
			/*
			 * Settings Control Menu
			*/
			if (m_settings_control_menu->uninit() == 1)
				return 1;
			delete m_settings_control_menu;
			break;
		case 6:
			/*
			 * Settings Sound Menu
			*/
			if (m_settings_sound_menu->uninit() == 1)
				return 1;
			delete m_settings_sound_menu;
			break;
		default:
			std::cout << "Invalid gamemode passed to uninit_gamemode(): " << gamemode << std::endl;
			break;
	}
	return 0;
}
