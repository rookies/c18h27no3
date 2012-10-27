/*
 * dataloader.hpp
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
#ifndef DATALOADER_HPP
#	define DATALOADER_HPP
	
#	include <string>
#	include <iostream>
#	include <fstream>
#	include <sstream>
#	include "globals.hpp"

#	define DATALOADER_TYPE_IMG 1
#	define DATALOADER_TYPE_FONT 2
#	define DATALOADER_TYPE_LOCALE 3
	
	std::string get_data_path(int type, std::string fname, bool append_fname=true);
#endif // DATALOADER_HPP
