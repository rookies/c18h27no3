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
	
#	include <iostream>
#	include <SFML/Graphics.hpp>
#	include <libintl.h>
#	include "globals.hpp"
#	include "widestring.hpp"
#	include "event_processor_return.hpp"
	
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
			EventProcessorReturn process_event(sf::Event event, int mouse_x, int mouse_y); /* Called in Game::process_events() */
			/*
			 * Reset menuitemX_over variables:
			*/
			void reset_menuitem_over(void);
			/*
			 * Get drawable items:
			*/
			sf::Sprite get_grassblock(void);
			sf::RectangleShape get_menuitem1(void);
			sf::RectangleShape get_menuitem2(void);
			sf::RectangleShape get_menuitem3(void);
			sf::RectangleShape get_menuitem4(void);
			sf::RectangleShape get_menuitem5(void);
			sf::RectangleShape get_menuitem6(void);
			sf::Text get_menuitem1_txt(void);
			sf::Text get_menuitem2_txt(void);
			sf::Text get_menuitem3_txt(void);
			sf::Text get_menuitem4_txt(void);
			sf::Text get_menuitem5_txt(void);
			sf::Text get_menuitem6_txt(void);
		private:
			int m_sizes_menuitem_width;
			int m_sizes_menuitem_height;
			int m_sizes_menuitem_xoffset;
			int m_sizes_menuitem_first_yoffset;
			int m_sizes_menuitem_gap;
			int m_menuitem1_over;
			int m_menuitem2_over;
			int m_menuitem3_over;
			int m_menuitem4_over;
			int m_menuitem5_over;
			int m_menuitem6_over;
			sf::RectangleShape m_menuitem1;
			sf::RectangleShape m_menuitem2;
			sf::RectangleShape m_menuitem3;
			sf::RectangleShape m_menuitem4;
			sf::RectangleShape m_menuitem5;
			sf::RectangleShape m_menuitem6;
			sf::Text m_menuitem1_txt;
			sf::Text m_menuitem2_txt;
			sf::Text m_menuitem3_txt;
			sf::Text m_menuitem4_txt;
			sf::Text m_menuitem5_txt;
			sf::Text m_menuitem6_txt;
			sf::Texture m_img1;
			sf::Sprite m_img1_sprite;
	};
#endif // _main_menu_h_
