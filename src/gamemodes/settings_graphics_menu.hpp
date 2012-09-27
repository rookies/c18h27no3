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
#	include "../widestring.hpp"
#	include "../event_processor_return.hpp"
#	include "../config_chooser.hpp"
	
	class SettingsGraphicsMenu
	{
		public:
			SettingsGraphicsMenu();
			~SettingsGraphicsMenu();
			
			/*
			 * (Un)init:
			*/
			int init(bool fullscreen); /* Called in Game::init_gamemode() */
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
			sf::RectangleShape get_menuitem1(void);
			sf::RectangleShape get_menuitem2(void);
			sf::RectangleShape get_menuitem3(void);
			sf::RectangleShape get_menuitem4(void);
			sf::Text get_menuitem1_header(void);
			sf::Text get_menuitem2_header(void);
			sf::Text get_menuitem1_value(void);
			sf::Text get_menuitem2_value(void);
			sf::Text get_menuitem3_txt(void);
			sf::Text get_menuitem4_txt(void);
			sf::RectangleShape get_textfield1_1(void);
			sf::RectangleShape get_textfield1_2(void);
			sf::Sprite get_arrow_left2(void);
			sf::Sprite get_arrow_right2(void);
		private:
			int m_w;
			int m_h;
			ConfigChooser m_config_chooser2;
			int m_sizes_menuitem_width;
			int m_sizes_menuitem_height;
			int m_sizes_menuitem_height2;
			int m_sizes_menuitem_xoffset;
			int m_sizes_menuitem_first_yoffset;
			int m_sizes_menuitem_gap;
			int m_sizes_textfield_width;
			int m_sizes_textfield_height;
			int m_sizes_textfield_xgap;
			int m_sizes_textfield_ygap;
			int m_sizes_arrow_height;
			int m_sizes_arrow_xgap;
			int m_sizes_arrow_ygap;
			sf::RectangleShape m_menuitem1;
			sf::RectangleShape m_menuitem2;
			sf::RectangleShape m_menuitem3;
			sf::RectangleShape m_menuitem4;
			sf::Texture m_arrow_left;
			sf::Texture m_arrow_right;
			sf::RectangleShape m_textfield1_1;
			sf::RectangleShape m_textfield1_2;
			sf::Sprite m_arrow_left2_sprite;
			sf::Sprite m_arrow_right2_sprite;
			sf::Text m_menuitem1_header;
			sf::Text m_menuitem2_header;
			sf::Text m_menuitem1_value;
			sf::Text m_menuitem2_value;
			sf::Text m_menuitem3_txt;
			sf::Text m_menuitem4_txt;
			int m_textfield1_1_over;
			int m_textfield1_2_over;
			int m_arrow_left2_over;
			int m_arrow_right2_over;
			int m_menuitem3_over;
			int m_menuitem4_over;
	};
#endif // _settings_graphics_menu_hpp_
