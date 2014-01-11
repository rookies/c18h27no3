/*
 * levelchooser.cpp
 * 
 * Copyright 2014 Robert Knauer <robert@privatdemail.net>
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
#include "levelchooser.hpp"

LevelChooser::LevelChooser()
{

}
LevelChooser::~LevelChooser()
{

}
int LevelChooser::init(Config conf, std::string arg)
{
	/*
	 * ...
	*/
	return 0;
}
int LevelChooser::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int LevelChooser::calculate_sizes(int w, int h)
{
	/*
	 * ...
	*/
	return 0;
}
void LevelChooser::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(1);
					break;
			}
			break;
	}
}
UniversalDrawableArray LevelChooser::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * ...
	*/
	arr.init(0);
	return arr;
}
