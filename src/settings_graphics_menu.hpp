/*
 * settings_graphics_menu.hpp
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
#ifndef _settings_graphics_menu_hpp_
#	define _settings_graphics_menu_hpp_
	
#	include <iostream>
#	include <SFML/Graphics.hpp>
#	include "globals.hpp"
#	include "widestring.hpp"
	
	class SettingsGraphicsMenu
	{
		public:
			SettingsGraphicsMenu();
			~SettingsGraphicsMenu();
			
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
			int process_event(sf::Event event, int mouse_x, int mouse_y); /* Called in Game::process_events() */
			/*
			 * Get drawable items:
			*/
			sf::RectangleShape get_menuitem1(void);
			sf::RectangleShape get_menuitem2(void);
			sf::Text get_menuitem1_header(void);
			sf::Text get_menuitem2_header(void);
		private:
			int m_sizes_menuitem_width;
			int m_sizes_menuitem_height;
			int m_sizes_menuitem_xoffset;
			int m_sizes_menuitem_first_yoffset;
			int m_sizes_menuitem_gap;
			sf::RectangleShape m_menuitem1;
			sf::RectangleShape m_menuitem2;
			sf::Text m_menuitem1_header;
			sf::Text m_menuitem2_header;
	};
#endif // _settings_graphics_menu_hpp_
