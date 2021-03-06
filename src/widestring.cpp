/*
 * widestring.cpp
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
#include "widestring.hpp"

/*
 * Thanks to:
 *  http://stackoverflow.com/questions/7141260/compare-stdwstring-and-stdstring/7159944#7159944
*/
std::wstring get_wstring(const std::string &str)
{
	const char *cstr = str.c_str();
#ifdef _WIN32
	const size_t wn = std::mbstowcs(NULL, cstr, 0);
#else
	const size_t wn = std::mbsrtowcs(NULL, &cstr, 0, NULL);
#endif
	
	if (wn == size_t(-1))
	{
		std::cout << "Error in mbs(r)towcs(): " << errno << std::endl;
		return L"";
	}
	
	std::vector<wchar_t> buf(wn + 1);
#ifdef _WIN32
	const size_t wn_again = std::mbstowcs(buf.data(), cstr, wn+1);
#else
	const size_t wn_again = std::mbsrtowcs(buf.data(), &cstr, wn+1, NULL);
#endif
	
	if (wn_again == size_t(-1))
	{
		std::cout << "Error in mbs(r)towcs(): " << errno << std::endl;
		return L"";
	}
	
#ifndef _WIN32
	assert(cstr == NULL);
#endif
	
	return std::wstring(buf.data(), wn);
}

sf::String get_string_from_utf32buf(char *buf, size_t len)
{
	/*
	 * Variable declarations:
	*/
	size_t i;
	sf::String str;
	sf::Uint32 *strdata;
	/*
	 * Check input buffer length:
	*/
	assert(len % 4 == 0);
	/*
	 * Allocate temporary buffer:
	*/
	strdata = new sf::Uint32[(len/4)+1];
	/*
	 * Run through buffer & convert:
	*/
	for (i=0; i*4 < len; i++)
		strdata[i] = buf[(i*4)] + 256*buf[(i*4)+1] + 65536*buf[(i*4)+2] + 16777216*buf[(i*4)+3];
	/*
	 * Terminate temporary buffer:
	*/
	strdata[(len/4)] = 0;
	/*
	 * Create SFML string:
	*/
	str = sf::String(strdata);
	/*
	 * Free temporary buffer:
	*/
	delete[] strdata;
	/*
	 * Return string:
	*/
	return str;
}
