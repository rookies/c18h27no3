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
#	include <libintl.h>
#	include "../event_processor_return.hpp"
#	include "../universal_drawable.hpp"
#	include "../dataloader.hpp"
#	include "../widestring.hpp"
#	include "../gamemode.hpp"
#	include "../fireanimation.hpp"

	class ControlKeySetting
	{
		public:
			ControlKeySetting();
			virtual ~ControlKeySetting();

			/*
			 * Get / Set config key:
			*/
			std::string get_config_key(void);
			void set_config_key(std::string key);
			/*
			 * Get / Set value:
			*/
			int get_value(void);
			void set_value(int value);
			/*
			 * Get / Set caption:
			*/
			std::string get_caption(void);
			void set_caption(std::string caption);
		private:
			std::string m_config_key;
			int m_value;
			std::string m_caption;
	};
	
	class SettingsControlMenu : public Gamemode
	{
		public:
			SettingsControlMenu();
			virtual ~SettingsControlMenu();

			/*
			 * Get string for keycode:
			*/
			std::string keycode2string(int code);
			/*
			 * (Re)init control key settings:
			*/
			void init_controlkey_settings(void);
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
			 * Process events:
			*/
			void process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret); /* Called in Game::process_events() */
			/*
			 * Reset *_over variables:
			*/
			void reset_menuitem_over(void);
			/*
			 * Get drawable items:
			*/
			UniversalDrawableArray get_drawables(void);
		private:
			int m_w, m_h;
			ControlKeySetting *m_controlkeys;
			int m_controlkeys_offset;
			int m_controlkeys_showc;
			int m_controlkeys_editable;
			bool m_warning_keyused;
			sf::Clock m_warning_keyused_clock;
			sf::Font m_font1;
			sf::Font m_font2;
			sf::Texture m_arrow_left;
			sf::Texture m_arrow_right;
			sf::Sprite m_arrow_left6_sprite;
			sf::Sprite m_arrow_right6_sprite;
			sf::RectangleShape m_menuitem1;
			sf::RectangleShape m_menuitem2;
			sf::RectangleShape m_menuitem3;
			sf::RectangleShape m_menuitem4;
			sf::RectangleShape m_menuitem5;
			sf::RectangleShape m_menuitem6;
			sf::RectangleShape m_menuitem7;
			sf::RectangleShape m_menuitem8;
			sf::Text m_menuitem1_caption;
			sf::Text m_menuitem2_caption;
			sf::Text m_menuitem3_caption;
			sf::Text m_menuitem4_caption;
			sf::Text m_menuitem5_caption;
			sf::Text m_menuitem1_value;
			sf::Text m_menuitem2_value;
			sf::Text m_menuitem3_value;
			sf::Text m_menuitem4_value;
			sf::Text m_menuitem5_value;
			sf::Text m_menuitem6_txt;
			sf::Text m_menuitem6_txt_alt;
			sf::Text m_menuitem7_txt;
			sf::Text m_menuitem8_txt;
			bool m_menuitem1_over;
			bool m_menuitem2_over;
			bool m_menuitem3_over;
			bool m_menuitem4_over;
			bool m_menuitem5_over;
			bool m_menuitem7_over;
			bool m_menuitem8_over;
			bool m_arrow_left6_over;
			bool m_arrow_right6_over;
			FireAnimation m_fire;
	};
#endif // SETTINGS_CONTROL_MENU_HPP
