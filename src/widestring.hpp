/*
 * widestring.hpp
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
#ifndef WIDESTRING_HPP
#	define WIDESTRING_HPP
	
#	include <iostream>
#	include <string>
#	include <vector>
#	include <cassert>
#	include <cstdlib>
#	include <cwchar>
#	include <cerrno>
#	include <SFML/System.hpp>
	
	std::wstring get_wstring(const std::string &str);
	sf::String get_string_from_utf32buf(char *buf, size_t len);
#endif // WIDESTRING_HPP
