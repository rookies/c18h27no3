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

#	define BLOCKDEF_TYPE_BUILTIN            1
#	define BLOCKDEF_TYPE_BUILTIN_SPECIAL    2
#	define BLOCKDEF_TYPE_SPECIAL            3

#	define LEVELLOADER_NOTHUMBNAIL          1
#	define LEVELLOADER_NOBACKGROUND         2
#	define LEVELLOADER_NOMUSIC              4
#	define LEVELLOADER_NOTEXTURES           8

#	include <string>
#	include <fstream>
#	include <iostream>
#	include <SFML/System.hpp>
#	include <SFML/Graphics.hpp>
#	include <SFML/Audio.hpp>
#	include <archive.h>
#	include <archive_entry.h>
#	include "globals.hpp"
#	include "widestring.hpp"
#	include "external/sha256.h"

	class LevelMetadata
	{
		public:
			LevelMetadata();
			virtual ~LevelMetadata();
			void set_key(std::string key);
			void set_value(sf::String value);
			std::string get_key(void);
			sf::String get_value(void);
		private:
			std::string m_key;
			sf::String m_value;
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
			unsigned int offset;
	};
	
	class LevelItem
	{
		public:
			LevelItem();
			
			unsigned short position;
			unsigned short id;
			unsigned int offset;
			bool collected;
	};
	
	class LevelOpponent
	{
		public:
			unsigned short position;
			unsigned short id;
			unsigned int offset;
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
			
			void set_opponentnumber(unsigned short number);
			void add_opponent(unsigned short position, unsigned short id);
			unsigned short get_opponentnumber(void);
			LevelOpponent *get_opponent(unsigned short index);
		private:
			unsigned short m_blocknumber;
			unsigned short m_itemnumber;
			unsigned short m_opponentnumber;
			int m_blockoffset;
			int m_itemoffset;
			int m_opponentoffset;
			LevelBlock *m_blocks;
			LevelItem *m_items;
			LevelOpponent *m_opponents;
	};

	class Level
	{
		public:
			Level();
			virtual ~Level();
			/*
			 * Load from file:
			*/
			bool load_from_file(std::string file, unsigned int flags);
			unsigned short get_blockdefs_number(void);
			LevelBlockdef get_blockdef(unsigned short index);
			LevelColumn *get_column(unsigned short index);
			unsigned short get_levelwidth(void);
			/*
			 * Extensions:
			*/
			bool has_bgimg(void);
			std::string get_bgimg(void);
			bool has_bgmusic(void);
			std::string get_bgmusic(void);
			/*
			 * Zip entries:
			*/
			bool has_thumbnail(void);
			sf::Texture get_thumbnail(void);
			bool has_background(void);
			sf::Image get_background(void);
			bool has_music(void);
			sf::SoundBuffer get_music(void);
		private:
			unsigned short m_levelwidth;
			unsigned short m_metadata_number;
			LevelMetadata *m_metadata;
			unsigned short m_blockdefs_number;
			LevelBlockdef *m_blockdefs;
			LevelColumn *m_columns;
			/*
			 * Extensions:
			*/
			bool m_has_bgimg;
			std::string m_bgimg;
			bool m_has_bgmusic;
			std::string m_bgmusic;
			/*
			 * Zip entries:
			*/
			bool m_has_thumbnail;
			sf::Texture m_thumbnail;
			bool m_has_background;
			sf::Image m_background;
			bool m_has_music;
			sf::SoundBuffer m_music;
	};
#endif // LEVEL_HPP
