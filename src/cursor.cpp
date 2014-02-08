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

Cursor::Cursor()
{
	
}
Cursor::~Cursor()
{
	
}
int Cursor::init(void)
{
	/*
	 * Load cursor:
	*/
	if (!m_cursor_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "cursor.png")))
		return 1;
	/*
	 * Init sprite:
	*/
	m_sprite.setTexture(m_cursor_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	return 0;
}
void Cursor::set_mouse_position(int x, int y)
{
	m_mouse_x = x;
	m_mouse_y = y;
	m_sprite.setPosition((int)(m_mouse_x-m_cursorsize/2.), (int)(m_mouse_y-m_cursorsize/2.));
}
int Cursor::get_mouse_position_x(void)
{
	return m_mouse_x;
}
int Cursor::get_mouse_position_y(void)
{
	return m_mouse_y;
}
int Cursor::calculate_sizes(int w, int h)
{
	m_cursorsize = h*(SIZE_CURSOR/100.);
	m_sprite.setScale(m_cursorsize/16., m_cursorsize/16.);
	return 0;
}
sf::Sprite Cursor::get_drawable(int w, int h)
{
	return m_sprite;
}
void Cursor::activate_action_cursor(void)
{
	m_sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
}
void Cursor::deactivate_action_cursor(void)
{
	m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}
