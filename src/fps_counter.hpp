/*
 * fps_counter.hpp
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
#ifndef _fps_counter_h_
#	define _fps_counter_h_
	
#	include <iostream>
#	include <string>
#	include <sstream>
#	include <cmath>
#	include <SFML/System.hpp>
#	include <SFML/Graphics.hpp>
#	include "globals.hpp" 
	
	class FPScounter
	{
		public:
			FPScounter();
			~FPScounter();
			
			/*
			 * Init:
			*/
			int init(void);
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(int w, int h);
			/*
			 * Get drawable:
			*/
			sf::Text get_drawable(void);
			/*
			 * Restart clock:
			*/
			void restart(void);
		private:
			sf::Text m_txt;
			sf::String m_txt_str;
			std::ostringstream m_txt_float;
			sf::Clock m_clock;
			int m_frames;
	};
#endif // _fps_counter_h_
