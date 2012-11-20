/*
 * gamemode.hpp
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
#ifndef GAMEMODE_HPP
#	define GAMEMODE_HPP
	
#	include "universal_drawable.hpp"
#	include "config_common.hpp"
#	include "event_processor_return.hpp"
	
	class Gamemode
	{
		public:
			virtual UniversalDrawableArray get_drawables(void) = 0;
			virtual void process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret) = 0;
			virtual int calculate_sizes(int w, int h) = 0;
			virtual int init(Config conf) = 0;
			virtual int uninit(void) = 0;
	};
#endif // GAMEMODE_HPP
