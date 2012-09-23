/*
 * settings_general_menu.cpp
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
#include "settings_general_menu.hpp"
SettingsGeneralMenu::SettingsGeneralMenu()
{
	
}
SettingsGeneralMenu::~SettingsGeneralMenu()
{
	
}
int SettingsGeneralMenu::init(void)
{
	return 0;
}
int SettingsGeneralMenu::uninit(void)
{
	return 0;
}
int SettingsGeneralMenu::calculate_sizes(int w, int h)
{
	return 0;
}
int SettingsGeneralMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					return 2; // back to settings menu
					break;
			}
			break;
	}
	return 0;
}
