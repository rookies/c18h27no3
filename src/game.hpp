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
#ifndef GAME_HPP
#	define GAME_HPP
	
#	include <iostream>
#	include <SFML/Window.hpp>
#	include <SFML/Audio.hpp>
#	ifdef _WIN32
#		include <windows.h>
#	endif // _WIN32
#	include <libintl.h>
#	include "dataloader.hpp"
#	include "padding_data_calculator.hpp"
#	include "cursor.hpp"
#	include "config.hpp"
#	include "fps_counter.hpp"
#	include "gamemodes/main_menu.hpp"
#	include "gamemodes/settings_menu.hpp"
#	include "gamemodes/settings_general_menu.hpp"
#	include "gamemodes/settings_graphics_menu.hpp"
#	include "gamemodes/settings_control_menu.hpp"
#	include "gamemodes/settings_sound_menu.hpp"
#	include "gamemodes/singleplayer.hpp"
#	include "gamemodes/credits.hpp"
#	include "gamemodes/levelchooser.hpp"
#	include "gamemodes/loadgame.hpp"
#	include "gamemodes/newgame.hpp"
#	include "event_processor_return.hpp"
#	include "universal_drawable.hpp"
#	include "gamemode.hpp"
	
	class Game
	{
		public:
			Game();
			virtual ~Game();
			
			/*
			 * (Un)Init game:
			*/
			int init(int gamemode=1, std::string arg="");
			int uninit(void);
			/*
			 * Draw everything:
			*/
			void draw(void);
			/*
			 * Start main loop:
			*/
			int loop(void);
		private:
			/*
			 * Set environment variable:
			*/
			int set_envvar(std::string name, std::string value);
			/*
			 * Init locale:
			*/
			int init_locale(void);
			/*
			 * Set language:
			*/
			int set_language(std::string lang, bool reload=true);
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
			int set_gamemode(int gamemode, std::string arg="");
			/*
			 * (Un)init game mode:
			*/
			int init_gamemode(int gamemode, std::string arg);
			int uninit_gamemode(void);
			/*
			 * Toggle menu sound:
			*/
			bool set_menusound(bool state);
			/*
			 * Toggle cursor:
			*/
			bool set_cursor(bool state);
				
			/*
			 * Internal variables:
			*/
			int m_screen_w;
			int m_screen_h;
			int m_screen_bits;
			int m_framerate_frames;
			bool m_window_has_focus;
			sf::RenderWindow m_window;
			sf::RenderTexture m_texture;
			sf::Sprite m_texture_sprite;
			PaddingDataCalculator m_padding_data_calculator;
			Cursor m_cursor;
			Config m_config;
			FPScounter m_fps_counter;
			Gamemode *m_gamemode_class;
			/*
			 * Game mode:
			 *  0 - undefined
			 *  1 - main menu
			 *  2 - settings menu
			 *  3 - settings general menu
			 *  4 - settings graphics menu
			 *  5 - settings control menu
			 *  6 - settings sound menu
			 *  7 - singleplayer
			 *  8 - credits
			 *  9 - level chooser
			 * 10 - load game
			 * 11 - new game
			*/
			int m_gamemode;
			bool m_menusound_state;
			bool m_menusound_initialized;
			bool m_cursor_state;
			sf::SoundBuffer m_menusound_buffer;
			sf::Sound m_menusound;
	};
#endif // GAME_HPP
