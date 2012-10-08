/*
 * settings_general_menu.hpp
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
#ifndef SETTINGS_GENERAL_MENU_HPP
#	define SETTINGS_GENERAL_MENU_HPP
	
#	include <iostream>
#	include <SFML/Graphics.hpp>
#	include <libintl.h>
#	include "globals.hpp"
#	include "../widestring.hpp"
#	include "../config_chooser.hpp"
#	include "../config_common.hpp"
#	include "../event_processor_return.hpp"
#	include "../universal_drawable.hpp"
#	include "../dataloader.hpp"
	
	class SettingsGeneralMenu
	{
		public:
			SettingsGeneralMenu();
			virtual ~SettingsGeneralMenu();
			
			/*
			 * (Un)init:
			*/
			int init(std::string language, bool fpscounter); /* Called in Game::init_gamemode() */
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
			UniversalDrawableArray get_drawables(void);
		private:
			int m_w, m_h;
			ConfigChooser m_config_chooser1;
			ConfigChooser m_config_chooser2;
			int m_sizes_menuitem_width;
			int m_sizes_menuitem_height;
			int m_sizes_menuitem_height2;
			int m_sizes_menuitem_xoffset;
			int m_sizes_menuitem_first_yoffset;
			int m_sizes_menuitem_gap;
			int m_sizes_arrow_height;
			int m_sizes_arrow_xgap;
			int m_sizes_arrow_ygap;
			sf::Font m_font1;
			sf::Font m_font2;
			sf::RectangleShape m_menuitem1;
			sf::RectangleShape m_menuitem2;
			sf::RectangleShape m_menuitem3;
			sf::RectangleShape m_menuitem4;
			sf::Texture m_arrow_left;
			sf::Texture m_arrow_right;
			sf::Sprite m_arrow_left1_sprite;
			sf::Sprite m_arrow_left2_sprite;
			sf::Sprite m_arrow_right1_sprite;
			sf::Sprite m_arrow_right2_sprite;
			sf::Text m_menuitem1_header;
			sf::Text m_menuitem2_header;
			sf::Text m_menuitem1_value;
			sf::Text m_menuitem2_value;
			sf::Text m_menuitem3_txt;
			sf::Text m_menuitem4_txt;
			int m_menuitem3_over;
			int m_menuitem4_over;
			int m_arrow_left1_over;
			int m_arrow_left2_over;
			int m_arrow_right1_over;
			int m_arrow_right2_over;
	};
#endif // SETTINGS_GENERAL_MENU_HPP
