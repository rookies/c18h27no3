/*
 * config_common.hpp
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
#ifndef _config_common_hpp_
#	define _config_common_hpp_
	
#	include <string>
#	include "globals.hpp"
	
#	define CONFIGVAR_TYPE_INTEGER 1
#	define CONFIGVAR_TYPE_BOOLEAN 2
#	define CONFIGVAR_TYPE_STRING 3
	
	class ConfigVariable
	{
		public:
			ConfigVariable();
			~ConfigVariable();
			
			/*
			 * Type
			*/
			int type;
			/*
			 * Index
			*/
			std::string index;
			/*
			 * Integer Value
			*/
			int value_int;
			/*
			 * Boolean Value
			*/
			bool value_bool;
			/*
			 * String Value
			*/
			std::string value_string;
		private:
			
	};
#endif // _config_common_hpp_
