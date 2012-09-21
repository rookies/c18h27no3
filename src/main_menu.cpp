/*
 * main_menu.cpp
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
#include "main_menu.hpp"

MainMenu::MainMenu()
{
	
}
MainMenu::~MainMenu()
{
	
}
int MainMenu::init(void)
{
	return 0;
}
int MainMenu::uninit(void)
{
	return 0;
}
int MainMenu::calculate_sizes(int w, int h)
{
	/*
	 * Menuitem width = 50%
	*/
	m_sizes_menuitem_width = w/2;
	/*
	 * Menuitem offset
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2;
	return 0;
}
int MainMenu::process_event(sf::Event event)
{
	return 0;
}
sf::RectangleShape MainMenu::get_menuitem(void)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_sizes_menuitem_width, 30));
	shape.setPosition(m_sizes_menuitem_xoffset, 10);
	shape.setFillColor(sf::Color::Red);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5);
	return shape;
}
