/*
 * settings_control_menu.hpp
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
#ifndef SETTINGS_CONTROL_MENU_HPP
#	define SETTINGS_CONTROL_MENU_HPP
	
#	include <iostream>
#	include <SFML/Graphics.hpp>
#	include "../event_processor_return.hpp"
#	include "../universal_drawable.hpp"
#	include "../dataloader.hpp"
#	include "../widestring.hpp"
	
	class SettingsControlMenu
	{
		public:
			SettingsControlMenu();
			virtual ~SettingsControlMenu();

			/*
			 * Get string for keycode:
			*/
			std::string keycode2string(sf::Keyboard::Key code);
			/*
			 * (Un)init:
			*/
			int init(void); /* Called in Game::init_gamemode() */
			int uninit(void); /* Called in Game::uninit_gamemode() */
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(int w, int h); /* Called in Game::calculate_sizes() */
			/*
			 * Process events:
			*/
			EventProcessorReturn process_event(sf::Event event, int mouse_x, int mouse_y); /* Called in Game::process_events() */
			/*
			 * Reset *_over variables:
			*/
			void reset_menuitem_over(void);
			/*
			 * Get drawable items:
			*/
			UniversalDrawableArray get_drawables(void);
		private:
			sf::Font m_font1;
			sf::RectangleShape m_menuitem1;
			sf::RectangleShape m_menuitem2;
			sf::RectangleShape m_menuitem3;
			sf::RectangleShape m_menuitem4;
			sf::RectangleShape m_menuitem5;
			sf::RectangleShape m_menuitem6;
			sf::RectangleShape m_menuitem7;
			sf::RectangleShape m_menuitem8;
			sf::Text m_menuitem7_txt;
			sf::Text m_menuitem8_txt;
			bool m_menuitem1_over;
			bool m_menuitem2_over;
			bool m_menuitem3_over;
			bool m_menuitem4_over;
			bool m_menuitem5_over;
			bool m_menuitem7_over;
			bool m_menuitem8_over;
	};
#endif // SETTINGS_CONTROL_MENU_HPP
