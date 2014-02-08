/*
 * cursor.hpp
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
#ifndef CURSOR_HPP
#	define CURSOR_HPP
	
#	include <iostream>
#	include <SFML/Graphics.hpp>
#	include "globals.hpp"
#	include "dataloader.hpp"
	
	class Cursor
	{
		public:
			Cursor();
			virtual ~Cursor();
			
			/*
			 * Init cursor:
			*/
			int init(void);
			/*
			 * Set mouse position:
			*/
			void set_mouse_position(int x, int y);
			/*
			 * Get mouse position:
			*/
			int get_mouse_position_x(void);
			int get_mouse_position_y(void);
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(int w, int h);
			/*
			 * Draw cursor:
			*/
			sf::Sprite get_drawable(int w, int h);
			/*
			 * (De)Activate action cursor:
			*/
			void activate_action_cursor(void);
			void deactivate_action_cursor(void);
		private:
			/*
			 * Internal variables:
			*/
			int m_cursorsize;
			int m_mouse_x;
			int m_mouse_y;
			sf::Texture m_cursor_texture;
			sf::Sprite m_sprite;
	};
#endif // CURSOR_HPP
