/*
 * game.hpp
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
#ifndef _game_hpp_
#	define _game_hpp_
	
#	include <iostream>
#	include <SFML/Window.hpp>
#	include "padding_data_calculator.hpp"
#	include "cursor.hpp"
#	include "video_sequence.hpp"
#	include "config.hpp"
#	include "fps_counter.hpp"
#	include "main_menu.hpp"
#	include "settings_menu.hpp"
#	include "settings_graphics_menu.hpp"
#	include "settings_control_menu.hpp"
#	include "settings_sound_menu.hpp"
	
	class Game
	{
		public:
			Game();
			~Game();
			
			/*
			 * (Un)Init game:
			*/
			int init(int w, int h, int fullscreen);
			int uninit(void);
			/*
			 * Start main loop:
			*/
			int loop(void);
		private:
			/*
			 * Wait for focus:
			*/
			int wait_for_focus(void);
			/*
			 * Process events:
			*/
			int process_events(void);
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(void);
			/*
			 * Set game mode:
			*/
			int set_gamemode(int gamemode);
			/*
			 * (Un)init game mode:
			*/
			int init_gamemode(int gamemode);
			int uninit_gamemode(int gamemode);
			/*
			 * Draw functions:
			*/
			void draw_main_menu(void);
			void draw_settings_menu(void);
			void draw_settings_graphics_menu(void);
			void draw_settings_control_menu(void);
			void draw_settings_sound_menu(void);
			
			/*
			 * Internal variables:
			*/
			int m_screen_w;
			int m_screen_h;
			int m_screen_bits;
			int m_framerate_frames;
			int m_window_has_focus;
			sf::RenderWindow m_window;
			sf::RenderTexture m_texture;
			PaddingDataCalculator m_padding_data_calculator;
			Cursor m_cursor;
			VideoSequence m_video_sequence;
			Config m_config;
			FPScounter m_fps_counter;
			MainMenu *m_main_menu;
			SettingsMenu *m_settings_menu;
			SettingsGraphicsMenu *m_settings_graphics_menu;
			SettingsControlMenu *m_settings_control_menu;
			SettingsSoundMenu *m_settings_sound_menu;
			/*
			 * Game mode:
			 *  0 - undefined
			 *  1 - main menu
			 *  2 - settings menu
			 *  3 - settings graphics menu
			 *  4 - settings control menu
			 *  5 - settings sound menu
			*/
			int m_gamemode;
	};
#endif // _game_hpp_
