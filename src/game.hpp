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
#ifndef _game_h_
#	define _game_h_
	
#	include <iostream>
#	include <string>
#	include <sstream>
#	include <SFML/Window.hpp>
#	include "padding_data_calculator.hpp"
#	include "cursor.hpp"
#	include "video_sequence.hpp"
#	include "config.hpp"
	
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
			 * Internal variables:
			*/
			int m_screen_w;
			int m_screen_h;
			int m_screen_bits;
			int m_framerate_frames;
			sf::RenderWindow m_window;
			sf::RenderTexture m_texture;
			sf::Clock m_framerate_clock;
			PaddingDataCalculator m_padding_data_calculator;
			Cursor m_cursor;
			//VideoSequence m_video_sequence;
			//Config m_config;
			int m_frames;
			int m_window_has_focus;
			/*
			 * Game mode:
			 *  0 - undefined
			 *  ...
			*/
			int m_gamemode;
	};
#endif // _game_h_
