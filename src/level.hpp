/*
 * level.hpp
 * 
 * Copyright 2013 Robert Knauer <robert@privatdemail.net>
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
#ifndef LEVEL_HPP
#	define LEVEL_HPP

#	include <string>
#	include <fstream>
#	include <iostream>
#	include "globals.hpp"

	class LevelMetadata
	{
		public:
			LevelMetadata();
			virtual ~LevelMetadata();
			void set_key(std::string key);
			void set_value(std::string value);
			std::string get_key(void);
			std::string get_value(void);
		private:
			std::string m_key;
			std::string m_value;
	};

	class LevelBlockdef
	{
		public:
			LevelBlockdef();
			virtual ~LevelBlockdef();
			void set_id(unsigned short id);
			void set_type(unsigned short type);
			void set_arg(std::string arg);
			unsigned short get_id(void);
			unsigned short get_type(void);
			std::string get_arg(void);
		private:
			unsigned short m_id;
			unsigned short m_type;
			std::string m_arg;
	};

	class Level
	{
		public:
			Level();
			virtual ~Level();
			/*
			 * Load from file:
			*/
			bool load_from_file(std::string file);
		private:
			unsigned short m_levelwidth;
			unsigned short m_metadata_number;
			LevelMetadata *m_metadata;
			unsigned short m_blockdefs_number;
			LevelBlockdef *m_blockdefs;
	};
#endif // LEVEL_HPP
