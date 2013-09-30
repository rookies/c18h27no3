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

#	define BLOCKDEF_TYPE_BUILTIN 1
#	define BLOCKDEF_TYPE_BUILTIN_SPECIAL 2
#	define BLOCKDEF_TYPE_SPECIAL 3

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

	class LevelBlock
	{
		public:
			unsigned short position;
			unsigned short blockdef;
	};
	
	class LevelItem
	{
		public:
			unsigned short position;
			unsigned short id;
	};

	class LevelColumn
	{
		public:
			LevelColumn();
			virtual ~LevelColumn();
			void set_blocknumber(unsigned short number);
			void add_block(unsigned short position, unsigned short blockdef);
			unsigned short get_blocknumber(void);
			LevelBlock *get_block(unsigned short index);
			
			void set_itemnumber(unsigned short number);
			void add_item(unsigned short position, unsigned short id);
			unsigned short get_itemnumber(void);
			LevelItem *get_item(unsigned short index);
		private:
			unsigned short m_blocknumber;
			unsigned short m_itemnumber;
			int m_blockoffset;
			int m_itemoffset;
			LevelBlock *m_blocks;
			LevelItem *m_items;
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
			unsigned short get_blockdefs_number(void);
			LevelBlockdef get_blockdef(unsigned short index);
			LevelColumn *get_column(unsigned short index);
			unsigned short get_levelwidth(void);
		private:
			unsigned short m_levelwidth;
			unsigned short m_metadata_number;
			LevelMetadata *m_metadata;
			unsigned short m_blockdefs_number;
			LevelBlockdef *m_blockdefs;
			LevelColumn *m_columns;
	};
#endif // LEVEL_HPP
