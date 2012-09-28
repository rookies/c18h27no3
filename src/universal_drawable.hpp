/*
 * universal_drawable.hpp
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
#ifndef _universal_drawable_hpp_
#	define _universal_drawable_hpp_
	
#	include <SFML/Graphics.hpp>
	
#	define UNIVERSAL_DRAWABLE_TYPE_TEXT 1
#	define UNIVERSAL_DRAWABLE_TYPE_RECTSHAPE 2
#	define UNIVERSAL_DRAWABLE_TYPE_SPRITE 3
	
	class UniversalDrawable
	{
		public:
			UniversalDrawable();
			~UniversalDrawable();
			
			/*
			 * Type:
			*/
			int type;
			/*
			 * Values:
			*/
			sf::Text value_text;
			sf::RectangleShape value_rectshape;
			sf::Sprite value_sprite;
		private:
			
	};
	class UniversalDrawableArray
	{
		public:
			UniversalDrawableArray();
			~UniversalDrawableArray();
			
			void init(int count);
			void uninit(void);
			UniversalDrawable get(int index);
			int get_count(void);
			void set(int index, UniversalDrawable value);
			/*
			 * Shortcuts:
			*/
			void set_text(int index, sf::Text value);
			void set_rectshape(int index, sf::RectangleShape value);
			void set_sprite(int index, sf::Sprite value);
		private:
			int m_count;
			UniversalDrawable *m_values;
			bool m_values_initialized;
	};
#endif // _universal_drawable_hpp_
