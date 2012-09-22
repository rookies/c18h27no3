/*
 * cursor.cpp
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
#include "cursor.hpp"

using namespace std;

Cursor::Cursor()
{
	m_actioncursor_active = 0;
}
Cursor::~Cursor()
{
	
}
int Cursor::init(void)
{
	/*
	 * Load cursor1:
	*/
	cout << "Loading cursor1... ";
	if (!m_cursor1_texture.loadFromFile("data/cursor1.png"))
	{
		cout << "[FAIL]" << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	/*
	 * Load cursor2:
	*/
	cout << "Loading cursor2... ";
	if (!m_cursor2_texture.loadFromFile("data/cursor2.png"))
	{
		cout << "[FAIL]" << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	return 0;
}
void Cursor::set_mouse_position(int x, int y)
{
	m_mouse_x = x;
	m_mouse_y = y;
}
int Cursor::get_mouse_position_x(void)
{
	return m_mouse_x;
}
int Cursor::get_mouse_position_y(void)
{
	return m_mouse_y;
}
sf::Sprite Cursor::get_drawable(int w, int h)
{
	/*
	 * Variable declarations:
	*/
	sf::Sprite sprite;
	/*
	 * Check if actioncursor is active:
	*/
	if (m_actioncursor_active == 1)
		sprite.setTexture(m_cursor2_texture);
	else
		sprite.setTexture(m_cursor1_texture);
	/*
	 * Set position:
	*/
	//sprite.setScale(w*(1/100.0), h*(1/100.0));
	sprite.setPosition(m_mouse_x-CURSOR_WIDTH/2, m_mouse_y-CURSOR_HEIGHT/2);
	/*
	 * Set color:
	*/
	sprite.setColor(sf::Color(255, 255, 255, 255));
	return sprite;
}
void Cursor::activate_action_cursor(void)
{
	if (m_actioncursor_active == 0)
	{
		m_actioncursor_active = 1;
	};
}
void Cursor::deactivate_action_cursor(void)
{
	if (m_actioncursor_active == 1)
	{
		m_actioncursor_active = 0;
	};
}
