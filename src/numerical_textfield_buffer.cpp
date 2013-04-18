/*
 * numerical_textfield_buffer.cpp
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
#include "numerical_textfield_buffer.hpp"

NumericalTextfieldBuffer::NumericalTextfieldBuffer()
{
	
}
NumericalTextfieldBuffer::~NumericalTextfieldBuffer()
{
	
}
void NumericalTextfieldBuffer::init(int maxlen)
{
	m_maxlen = maxlen;
}
void NumericalTextfieldBuffer::set(int value)
{
	m_value = value;
}
std::string NumericalTextfieldBuffer::get_string(void)
{
	/*
	 * Variable declarations:
	*/
	std::ostringstream txt;
	
	txt << m_value;
	return txt.str();
}
int NumericalTextfieldBuffer::get_int(void)
{
	return m_value;
}
void NumericalTextfieldBuffer::handle_keypress(sf::Event event)
{
	/*
	 * Variable definitions:
	*/
	std::string tmp = get_string();
	/*
	 * Check if it is a keypress event:
	*/
	if (event.type != sf::Event::KeyPressed)
		return;
	/*
	 * Check if backspace is pressed:
	*/
	if (event.key.code == sf::Keyboard::BackSpace)
	{
		/*
		 * Check if we have an empty buffer:
		*/
		if (tmp.length() == 0)
			return;
		/*
		 * Delete last character:
		*/
		tmp.erase(tmp.length()-1);
		/*
		 * And update value:
		*/
		set(atoi(tmp.c_str()));
		return;
	};
	/*
	 * Check if we have already the maximum length:
	*/
	if (tmp.length() == m_maxlen)
		return;
	/*
	 * Check if a modifier is pressed:
	*/
	if (event.key.alt || event.key.control || event.key.shift || event.key.system)
		return;
	/*
	 * Check if it is a number key:
	*/
	switch (event.key.code)
	{
		case sf::Keyboard::Num0:
		case sf::Keyboard::Numpad0:
			tmp.append("0");
			break;
		case sf::Keyboard::Num1:
		case sf::Keyboard::Numpad1:
			tmp.append("1");
			break;
		case sf::Keyboard::Num2:
		case sf::Keyboard::Numpad2:
			tmp.append("2");
			break;
		case sf::Keyboard::Num3:
		case sf::Keyboard::Numpad3:
			tmp.append("3");
			break;
		case sf::Keyboard::Num4:
		case sf::Keyboard::Numpad4:
			tmp.append("4");
			break;
		case sf::Keyboard::Num5:
		case sf::Keyboard::Numpad5:
			tmp.append("5");
			break;
		case sf::Keyboard::Num6:
		case sf::Keyboard::Numpad6:
			tmp.append("6");
			break;
		case sf::Keyboard::Num7:
		case sf::Keyboard::Numpad7:
			tmp.append("7");
			break;
		case sf::Keyboard::Num8:
		case sf::Keyboard::Numpad8:
			tmp.append("8");
			break;
		case sf::Keyboard::Num9:
		case sf::Keyboard::Numpad9:
			tmp.append("9");
			break;
	}
	set(atoi(tmp.c_str()));
}
