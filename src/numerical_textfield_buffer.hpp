/*
 * numerical_textfield_buffer.hpp
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
#ifndef _numerical_textfield_buffer_hpp_
#	define _numerical_textfield_buffer_hpp_
	
#	include <string>
#	include <sstream>
#	include <SFML/Window.hpp>
#	include <iostream>
	
	class NumericalTextfieldBuffer
	{
		public:
			NumericalTextfieldBuffer();
			~NumericalTextfieldBuffer();
			
			void init(int maxlen);
			void set(int value);
			std::string get_string(void);
			int get_int(void);
			void handle_keypress(sf::Event event);
		private:
			int m_maxlen;
			int m_value;
	};
#endif // _numerical_textfield_buffer_hpp_