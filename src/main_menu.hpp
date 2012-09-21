/*
 * main_menu.hpp
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
#ifndef _main_menu_h_
#	define _main_menu_h_
	
#	include <SFML/Graphics.hpp>
	
	class MainMenu
	{
		public:
			MainMenu();
			~MainMenu();
			
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
			int process_event(sf::Event event); /* Called in Game::process_events() */
			/*
			 * Get menuitem:
			*/
			sf::RectangleShape get_menuitem(void);
		private:
			int m_sizes_menuitem_width;
			int m_sizes_menuitem_xoffset;
	};
#endif // _main_menu_h_
