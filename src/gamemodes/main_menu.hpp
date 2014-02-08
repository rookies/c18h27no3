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
#ifndef MAIN_MENU_HPP
#	define MAIN_MENU_HPP
	
#	include <iostream>
#	include <SFML/Graphics.hpp>
#	include <SFML/Network.hpp>
#	include <libintl.h>
#	include <sstream>
#	ifdef OS_WINDOWS
#		include <windows.h>
#	endif // OS_WINDOWS
#	include "globals.hpp"
#	include "../widestring.hpp"
#	include "../event_processor_return.hpp"
#	include "../universal_drawable.hpp"
#	include "../dataloader.hpp"
#	include "../gamemode.hpp"
#	include "../fireanimation.hpp"
	
	class MainMenu : public Gamemode
	{
		public:
			MainMenu();
			virtual ~MainMenu();
			
			/*
			 * (Un)init:
			*/
			int init(Config conf, std::string arg); /* Called in Game::init_gamemode() */
			int uninit(void); /* Called in Game::uninit_gamemode() */
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(int w, int h); /* Called in Game::calculate_sizes() */
			/*
			 * Load menuitem:
			*/
			void load_menuitem(int i);
			/*
			 * Process events:
			*/
			void process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret); /* Called in Game::process_events() */
			/*
			 * Get drawable items:
			*/
			UniversalDrawableArray get_drawables(void);
			/*
			 * Update thread:
			*/
			void updater(void);
		private:
			int m_w;
			int m_h;
			int m_menuitem_over;
			int m_menuitem_loaded;
			sf::Texture m_img1;
			sf::Texture m_img2;
			sf::Sprite m_img1_sprite;
			sf::Sprite m_img2_sprite;
			unsigned int m_menu_a[MAINMENU_COUNT+1] = {0,62,121,203,270,330,404};
			unsigned int m_menu_x[MAINMENU_COUNT] = {82,82,85,69,51,37};
			unsigned int m_menu_y[MAINMENU_COUNT] = {369,359,355,329,339,407};
			unsigned int m_menu_h[MAINMENU_COUNT] = {62,59,56,67,60,74};
			unsigned int m_menuc_a[MAINMENU_COUNT+1];
			unsigned int m_menuc_x[MAINMENU_COUNT];
			unsigned int m_menuc_y[MAINMENU_COUNT];
			unsigned int m_menuc_h[MAINMENU_COUNT];
			int m_logo_xoffset;
			int m_logo_yoffset;
			sf::Thread *m_update_thread;
			sf::Font m_font1;
			sf::Font m_font2;
			bool m_updates;
			bool m_updatetext_changed;
			std::string m_updatetext;
			std::string m_updatelink;
			float m_activewidth;
			FireAnimation m_fire;
			sf::RectangleShape m_update_bg;
			sf::Text m_update_text;
			sf::Text m_update_heading;
	};
#endif // MAIN_MENU_HPP
