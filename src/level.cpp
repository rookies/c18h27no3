/*
 * level.cpp
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
#include "level.hpp"

void LevelMetadata::set_key(std::string key)
{
	m_key = key;
}
void LevelMetadata::set_value(sf::String value)
{
	m_value = value;
}
std::string LevelMetadata::get_key(void)
{
	return m_key;
}
sf::String LevelMetadata::get_value(void)
{
	return m_value;
}

void LevelBlockdef::set_id(unsigned short id)
{
	m_id = id;
}
void LevelBlockdef::set_type(unsigned short type)
{
	m_type = type;
}
void LevelBlockdef::set_arg(std::string arg)
{
	m_arg = arg;
}
unsigned short LevelBlockdef::get_id(void)
{
	return m_id;
}
unsigned short LevelBlockdef::get_type(void)
{
	return m_type;
}
std::string LevelBlockdef::get_arg(void)
{
	return m_arg;
}

LevelItem::LevelItem() : collected(false)
{
	
}

LevelColumn::LevelColumn() : m_blockoffset(-1), m_itemoffset(-1), m_opponentoffset(-1)
{

}
LevelColumn::~LevelColumn()
{
	if (m_blockoffset >= 0)
		delete[] m_blocks;
	if (m_itemoffset >= 0)
		delete[] m_items;
	if (m_opponentoffset >= 0)
		delete[] m_opponents;
}
void LevelColumn::set_blocknumber(unsigned short number)
{
	if (m_blockoffset < 0)
	{
		m_blocknumber = number;
		m_blocks = new LevelBlock[m_blocknumber];
		m_blockoffset = 0;
	};
}
void LevelColumn::add_block(unsigned short position, unsigned short blockdef)
{
	if (m_blockoffset < 0)
		return;
	m_blocks[m_blockoffset].position = position;
	m_blocks[m_blockoffset].blockdef = blockdef;
	m_blockoffset++;
}
unsigned short LevelColumn::get_blocknumber(void)
{
	if (m_blockoffset < 0)
		return 0;
	return m_blocknumber;
}
LevelBlock *LevelColumn::get_block(unsigned short index)
{
	return &m_blocks[index];
}
void LevelColumn::set_itemnumber(unsigned short number)
{
	if (m_itemoffset < 0)
	{
		m_itemnumber = number;
		m_items = new LevelItem[m_itemnumber];
		m_itemoffset = 0;
	};
}
void LevelColumn::add_item(unsigned short position, unsigned short id)
{
	if (m_itemoffset < 0)
		return;
	m_items[m_itemoffset].position = position;
	m_items[m_itemoffset].id = id;
	m_itemoffset++;
}
unsigned short LevelColumn::get_itemnumber(void)
{
	if (m_itemoffset < 0)
		return 0;
	return m_itemnumber;
}
LevelItem *LevelColumn::get_item(unsigned short index)
{
	return &m_items[index];
}
void LevelColumn::set_opponentnumber(unsigned short number)
{
	if (m_opponentoffset < 0)
	{
		m_opponentnumber = number;
		m_opponents = new LevelOpponent[m_opponentnumber];
		m_opponentoffset = 0;
	};
}
void LevelColumn::add_opponent(unsigned short position, unsigned short id)
{
	if (m_opponentoffset < 0)
		return;
	m_opponents[m_opponentoffset].position = position;
	m_opponents[m_opponentoffset].id = id;
	m_opponentoffset++;
}
unsigned short LevelColumn::get_opponentnumber(void)
{
	if (m_opponentoffset < 0)
		return 0;
	return m_opponentnumber;
}
LevelOpponent *LevelColumn::get_opponent(unsigned short index)
{
	return &m_opponents[index];
}

Level::Level() :	m_has_bgimg(false),
					m_has_bgmusic(false),
					m_has_thumbnail(false),
					m_has_background(false),
					m_has_music(false),
					m_ctextures_count(0)
{

}
Level::~Level()
{
	if (m_metadata_number > 0)
		delete[] m_metadata;
	if (m_blockdefs_number > 0)
		delete[] m_blockdefs;
	if (m_levelwidth > 0)
		delete[] m_columns;
	if (m_ctextures_count > 0)
		delete[] m_ctextures;
	std::cout << "DEALLOCATE LEVEL" << std::endl;
}
bool Level::load_from_file(std::string file, unsigned int flags)
{
	/*
	 * Variable declarations:
	*/
	unsigned short i, j;
	std::ifstream f;
	char *buf, *buf2;
	std::string buf_;
	unsigned short tmp, tmp2, tmp3, tmp4, tmp5;
	std::streampos fsize;
	unsigned char chksum[32];
	struct archive *arc;
	struct archive_entry *arc_entry;
	size_t size;
	CustomTexture *ctextures;
	/*
	 * Open file:
	*/
	f.open(file.c_str(), std::ifstream::in | std::ifstream::binary);
	if (!f.is_open())
	{
		std::cerr << "LevelLoader: Failed to open level file!" << std::endl;
		return false;
	};
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Opened level file '" << file << "'." << std::endl;
#endif
	/*
	 * Get file size:
	*/
	f.seekg(0, std::ios::end);
	fsize = f.tellg();
	f.seekg(0, std::ios::beg);
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Filesize = " << fsize << " bytes" << std::endl;
#endif
	/*
	 * Calculate checksum:
	*/
	buf = new char[fsize];
	f.read(buf, fsize);
	for (i=13; i < 45; i++)
		buf[i] = 0;
	sha256((const unsigned char *)buf, fsize, chksum, 0);
	delete[] buf;
	f.seekg(0, std::ios::beg);
	/*
	 * Read CAPSAICIN header:
	*/
	buf = new char[9];
	f.read(buf, 9);
	buf_ = std::string(buf).substr(0,9);
	if (buf_.compare("CAPSAICIN") != 0)
	{
		std::cerr << "LevelLoader: CAPSAICIN header not found!" << std::endl;
		return false;
	};
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Found CAPSAICIN header." << std::endl;
#endif
	delete[] buf;
	/*
	 * Read version:
	*/
	buf = new char[2];
	f.read(buf, 2);
	tmp = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
	if (tmp != VERSION_LEVELFORMAT)
	{
		std::cerr << "LevelLoader: Incompatible level versions! (game=" << VERSION_LEVELFORMAT << "; file=" << tmp << ")" << std::endl;
		return false;
	};
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Compatible level versions. (v" << tmp << ")" << std::endl;
#endif
	delete[] buf;
	/*
	 * Read level width:
	*/
	buf = new char[2];
	f.read(buf, 2);
	m_levelwidth = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Level_Width = " << m_levelwidth << std::endl;
#endif
	delete[] buf;
	/*
	 * Read checksum:
	*/
	buf = new char[32];
	f.read(buf, 32);
	for (i=0; i < 32; i++)
	{
		if ((unsigned char)buf[i] != chksum[i])
		{
			std::cerr << "LevelLoader: Invalid checksum!" << std::endl;
			return false;
		};
	}
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Valid checksum." << std::endl;
#endif
	delete[] buf;
	/*
	 * Read metadata number:
	*/
	buf = new char[1];
	f.read(buf, 1);
	m_metadata_number = (unsigned short)buf[0];
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Metadata_Number = " << m_metadata_number << std::endl;
#endif
	delete[] buf;
	/*
	 * Read metadata:
	*/
	if (m_metadata_number > 0)
	{
		m_metadata = new LevelMetadata[m_metadata_number];
		for (i=0; i < m_metadata_number; i++)
		{
			/*
			 * Read key length:
			*/
			buf = new char[2];
			f.read(buf, 2);
			tmp = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
			delete[] buf;
			/*
			 * Read key:
			*/
			buf = new char[tmp+1];
			f.read(buf, tmp);
			buf[tmp] = '\0';
			m_metadata[i].set_key(buf);
			delete[] buf;
			/*
			 * Read value length:
			*/
			buf = new char[2];
			f.read(buf, 2);
			tmp = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
			delete[] buf;
			/*
			 * Read value:
			*/
			buf = new char[tmp];
			f.read(buf, tmp);
			m_metadata[i].set_value(get_string_from_utf32buf(buf, tmp));
			delete[] buf;
			/*
			 * Print status message:
			*/
#ifdef LVL_DEBUG
			std::cout << "LevelLoader: Metadata '" << m_metadata[i].get_key() << "' = '";
			std::wcout << m_metadata[i].get_value().toWideString();
			std::cout << "'" << std::endl;
#endif
		}
	};
	/*
	 * Read blockdefs number:
	*/
	buf = new char[2];
	f.read(buf, 2);
	m_blockdefs_number = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Blockdefs_Number = " << m_blockdefs_number << std::endl;
#endif
	delete[] buf;
	/*
	 * Read blockdefs:
	*/
	if (m_blockdefs_number > 0)
	{
		m_blockdefs = new LevelBlockdef[m_blockdefs_number];
		for (i=0; i < m_blockdefs_number; i++)
		{
			/*
			 * Read id:
			*/
			buf = new char[2];
			f.read(buf, 2);
			tmp = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
			m_blockdefs[i].set_id(tmp);
			delete[] buf;
			/*
			 * Read type:
			*/
			buf = new char[1];
			f.read(buf, 1);
			tmp = (unsigned short)buf[0];
			m_blockdefs[i].set_type(tmp);
			delete[] buf;
			/*
			 * Read argument length:
			*/
			buf = new char[1];
			f.read(buf, 1);
			tmp = (unsigned short)buf[0];
			delete[] buf;
			/*
			 * Read argument:
			*/
			buf = new char[tmp+1];
			f.read(buf, tmp);
			buf[tmp] = '\0';
			m_blockdefs[i].set_arg(buf);
			delete[] buf;
			/*
			 * Print status message:
			*/
#ifdef LVL_VERBOSE
			std::cout << "LevelLoader: Blockdef #" << m_blockdefs[i].get_id() << "; type=" << m_blockdefs[i].get_type() << "; arg='" << m_blockdefs[i].get_arg() << "'" << std::endl;
#endif
		}
	};
	/*
	 * Finally: Read columns
	*/
	if (m_levelwidth > 0)
	{
		m_columns = new LevelColumn[m_levelwidth];
		i = 0;
		while (i < m_levelwidth-1)
		{
			/*
			 * Read X coordinate:
			*/
			buf = new char[2];
			f.read(buf, 2);
			i = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
			delete[] buf;
			/*
			 * Read Y block number:
			*/
			buf = new char[1];
			f.read(buf, 1);
			tmp = (unsigned short)buf[0];
			delete[] buf;
			m_columns[i].set_blocknumber(tmp);
			/*
			 * Read Y item number:
			*/
			buf = new char[1];
			f.read(buf, 1);
			tmp4 = (unsigned short)buf[0];
			delete[] buf;
			m_columns[i].set_itemnumber(tmp4);
			/*
			 * Read Y opponent number:
			*/
			buf = new char[1];
			f.read(buf, 1);
			tmp5 = (unsigned short)buf[0];
			delete[] buf;
			m_columns[i].set_opponentnumber(tmp5);
			/*
			 * Run through Y blocks:
			*/
			for (j=0; j < tmp; j++)
			{
				/*
				 * Read Y coordinate:
				*/
				buf = new char[1];
				f.read(buf, 1);
				tmp2 = (unsigned short)buf[0];
				delete[] buf;
				/*
				 * Read blockdef ID:
				*/
				buf = new char[2];
				f.read(buf, 2);
				tmp3 = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
				delete[] buf;
				/*
				 * Write into array:
				*/
				m_columns[i].add_block(tmp2, tmp3);
#ifdef LVL_VERBOSE
				std::cout << "LevelLoader: Block x=" << i << "; y=" << tmp2 << "; blockdef=" << tmp3 << std::endl;
#endif
			}
			/*
			 * Run through Y items:
			*/
			for (j=0; j < tmp4; j++)
			{
				/*
				 * Read Y coordinate:
				*/
				buf = new char[1];
				f.read(buf, 1);
				tmp2 = (unsigned short)buf[0];
				delete[] buf;
				/*
				 * Read item ID:
				*/
				buf = new char[1];
				f.read(buf, 1);
				tmp3 = (unsigned char)buf[0];
				delete[] buf;
				/*
				 * Write into array:
				*/
				m_columns[i].add_item(tmp2, tmp3);
#ifdef LVL_VERBOSE
				std::cout << "LevelLoader: Item x=" << i << "; y=" << tmp2 << "; id=" << tmp3 << std::endl;
#endif
			}
			/*
			 * Run through Y opponents:
			*/
			for (j=0; j < tmp5; j++)
			{
				/*
				 * Read Y coordinate:
				*/
				buf = new char[1];
				f.read(buf, 1);
				tmp2 = (unsigned short)buf[0];
				delete[] buf;
				/*
				 * Read opponent ID:
				*/
				buf = new char[1];
				f.read(buf, 1);
				tmp3 = (unsigned char)buf[0];
				delete[] buf;
				/*
				 * Write into array:
				*/
				m_columns[i].add_opponent(tmp2, tmp3);
#ifdef LVL_VERBOSE
				std::cout << "LevelLoader: Opponent x=" << i << "; y=" << tmp2 << "; id=" << tmp3 << std::endl;
#endif
			}
		}
	};
	/*
	 * Read extensions number:
	*/
	buf = new char[2];
	f.read(buf, 2);
	tmp = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
	delete[] buf;
#ifdef LVL_DEBUG
	std::cout << "LevelLoader: Extensions_Number = " << tmp << std::endl;
#endif
	/*
	 * Read extensions:
	*/
	for (i=0; i < tmp; i++)
	{
		/*
		 * Read name length:
		*/
		buf = new char[1];
		f.read(buf, 1);
		tmp2 = (unsigned short)buf[0];
		delete[] buf;
		/*
		 * Read name:
		*/
		buf = new char[tmp2+1];
		f.read(buf, tmp2);
		buf[tmp2] = '\0';
		buf_ = std::string(buf).substr(0,tmp2);
		delete[] buf;
		/*
		 * Analyze name:
		*/
		if (buf_.compare("_bgimg") == 0)
		{
#ifdef LVL_DEBUG
			std::cout << "LevelLoader: _bgimg extension found." << std::endl;
#endif
			/*
			 * Read data length:
			*/
			buf = new char[2];
			f.read(buf, 2);
			tmp2 = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
			delete[] buf;
			/*
			 * Read data:
			*/
			buf = new char[tmp2+1];
			f.read(buf, tmp2);
			buf[tmp2] = '\0';
			buf_ = std::string(buf).substr(0,tmp2);
			delete[] buf;
			m_has_bgimg = true;
			m_bgimg = buf_;
#ifdef LVL_DEBUG
			std::cout << " -> Data: " << buf_ << std::endl;
#endif
		}
		else if (buf_.compare("_bgmusic") == 0)
		{
#ifdef LVL_DEBUG
			std::cout << "LevelLoader: _bgmusic extension found." << std::endl;
#endif
			/*
			 * Read data length:
			*/
			buf = new char[2];
			f.read(buf, 2);
			tmp2 = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
			delete[] buf;
			/*
			 * Read data:
			*/
			buf = new char[tmp2+1];
			f.read(buf, tmp2);
			buf[tmp2] = '\0';
			buf_ = std::string(buf).substr(0,tmp2);
			delete[] buf;
			m_has_bgmusic = true;
			m_bgmusic = buf_;
#ifdef LVL_DEBUG
			std::cout << " -> Data: " << buf_ << std::endl;
#endif
		}
		else
		{
			std::cerr << "LevelLoader: Unknown extension found: " << buf_ << std::endl;
		};
	}
	/*
	 * Check for zip file:
	*/
	if (f.tellg() < fsize)
	{
#ifdef LVL_DEBUG
		std::cout << "LevelLoader: Zip archive found." << std::endl;
#endif
		/*
		 * Init libarchive:
		*/
		arc = archive_read_new();
		archive_read_support_format_zip(arc);
		/*
		 * Read zip data into a buffer:
		*/
		fsize -= f.tellg();
		buf = new char[fsize];
		f.read(buf, fsize);
		/*
		 * Open zip file:
		*/
		if (archive_read_open_memory(arc, buf, fsize) != ARCHIVE_OK)
		{
			std::cerr << "LevelLoader: Failed to open zip archive!" << std::endl;
			return false;
		};
#ifdef LVL_DEBUG
		std::cout << "LevelLoader: Opened zip archive." << std::endl;
#endif
		/*
		 * Read entries:
		*/
		while (archive_read_next_header(arc, &arc_entry) == ARCHIVE_OK)
		{
			buf_ = archive_entry_pathname(arc_entry);
#ifdef LVL_DEBUG
			std::cout << "LevelLoader: Found zip entry '" << buf_ << "'." << std::endl;
#endif
			if (buf_.compare("thumbnail.png") == 0)
			{
				if ((flags & LEVELLOADER_NOTHUMBNAIL) == LEVELLOADER_NOTHUMBNAIL)
				{
#ifdef LVL_DEBUG
					std::cout << " -> Ignoring thumbnail." << std::endl;
#endif
				}
				else
				{
					m_has_thumbnail = true;
					/*
					 * Read data into sf::Texture:
					*/
					size = archive_entry_size(arc_entry);
					buf2 = new char[size];
					if (archive_read_data(arc, buf2, size) < 0)
					{
						std::cerr << "LevelLoader: Failed to read thumbnail!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Read thumbnail." << std::endl;
#endif
					if (!m_thumbnail.loadFromMemory(buf2, size))
					{
						std::cerr << "LevelLoader: Failed to create thumbnail texture!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Created thumbnail texture." << std::endl;
#endif
					/*
					 * Free buffer:
					*/
					delete[] buf2;
				};
			}
			else if (buf_.compare("background.png") == 0)
			{
				if ((flags & LEVELLOADER_NOBACKGROUND) == LEVELLOADER_NOBACKGROUND)
				{
#ifdef LVL_DEBUG
					std::cout << " -> Ignoring custom background image." << std::endl;
#endif
				}
				else
				{
					m_has_background = true;
					/*
					 * Read data into sf::Image:
					*/
					size = archive_entry_size(arc_entry);
					buf2 = new char[size];
					if (archive_read_data(arc, buf2, size) < 0)
					{
						std::cerr << "LevelLoader: Failed to read background!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Read background." << std::endl;
#endif
					if (!m_background.loadFromMemory(buf2, size))
					{
						std::cerr << "LevelLoader: Failed to create background image!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Created background image." << std::endl;
#endif
					/*
					 * Free buffer:
					*/
					delete[] buf2;
				};
			}
			else if (buf_.compare("music.ogg") == 0)
			{
				if ((flags & LEVELLOADER_NOMUSIC) == LEVELLOADER_NOMUSIC)
				{
#ifdef LVL_DEBUG
					std::cout << " -> Ignoring custom background music." << std::endl;
#endif
				}
				else
				{
					m_has_music = true;
					/*
					 * Read data into sf::SoundBuffer:
					*/
					size = archive_entry_size(arc_entry);
					buf2 = new char[size];
					if (archive_read_data(arc, buf2, size) < 0)
					{
						std::cerr << "LevelLoader: Failed to read music!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Read music." << std::endl;
#endif
					if (!m_music.loadFromMemory(buf2, size))
					{
						std::cerr << "LevelLoader: Failed to create music buffer!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Created music buffer." << std::endl;
#endif
					/*
					 * Free buffer:
					*/
					delete[] buf2;
				};
			}
			else if (buf_.substr(0, 9).compare("textures/") == 0)
			{
				if ((flags & LEVELLOADER_NOTEXTURES) == LEVELLOADER_NOTEXTURES)
				{
#ifdef LVL_DEBUG
					std::cout << " -> Ignoring custom texture." << std::endl;
#endif
				}
				else
				{
					/*
					 * Read data into buffer:
					*/
					size = archive_entry_size(arc_entry);
					buf2 = new char[size];
					if (archive_read_data(arc, buf2, size) < 0)
					{
						std::cerr << "LevelLoader: Failed to read custom texture!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Read custom texture." << std::endl;
#endif
					/*
					 * Check ctextures array:
					*/
					if (m_ctextures_count == 0)
					{
						/*
						 * Doesn't exist, create it:
						*/
						m_ctextures_count = 1;
						m_ctextures = new CustomTexture[1];
					}
					else
					{
						/*
						 * Exists, extend it:
						*/
						ctextures = new CustomTexture[m_ctextures_count];
						for (i=0; i < m_ctextures_count; i++)
						{
							ctextures[i].name = m_ctextures[i].name;
							ctextures[i].texture = m_ctextures[i].texture;
						}
						delete[] m_ctextures;
						m_ctextures_count++;
						m_ctextures = new CustomTexture[m_ctextures_count];
						for (i=0; i < m_ctextures_count-1; i++)
						{
							m_ctextures[i].name = ctextures[i].name;
							m_ctextures[i].texture = ctextures[i].texture;
						}
						delete[] ctextures;
					};
					/*
					 * Append the texture:
					*/
					m_ctextures[m_ctextures_count-1].name = buf_.substr(9).substr(0, (buf_.length())-13);
					m_ctextures[m_ctextures_count-1].texture = sf::Texture();
					if (!m_ctextures[m_ctextures_count-1].texture.loadFromMemory(buf2, size))
					{
						std::cerr << "LevelLoader: Failed to create custom texture texture!" << std::endl;
						return false;
					};
#ifdef LVL_DEBUG
					std::cout << " -> Created custom texture texture." << std::endl;
#endif
					/*
					 * Free buffer:
					*/
					delete[] buf2;
				};
			}
			else
			{
				std::cerr << "LevelLoader: Ignoring unknown zip entry '" << buf_ << "'." << std::endl;
			};
		}
		/*
		 * Close zip file:
		*/
		if (archive_read_free(arc) != ARCHIVE_OK)
		{
			std::cerr << "LevelLoader: Failed to close zip archive!" << std::endl;
			return false;
		};
#ifdef LVL_DEBUG
		std::cout << "LevelLoader: Closed zip archive." << std::endl;
#endif
		/*
		 * Free buffer:
		*/
		delete[] buf;
	}
	else
	{
#ifdef LVL_DEBUG
		std::cout << "LevelLoader: No zip archive found." << std::endl;
#endif
	};
	return true;
}
unsigned short Level::get_blockdefs_number(void)
{
	return m_blockdefs_number;
}
LevelBlockdef Level::get_blockdef(unsigned short index)
{
	return m_blockdefs[index];
}
LevelColumn *Level::get_column(unsigned short index)
{
	return &m_columns[index];
}
unsigned short Level::get_levelwidth(void)
{
	return m_levelwidth;
}
bool Level::has_bgimg(void)
{
	return m_has_bgimg;
}
std::string Level::get_bgimg(void)
{
	return m_bgimg;
}
bool Level::has_bgmusic(void)
{
	return m_has_bgmusic;
}
std::string Level::get_bgmusic(void)
{
	return m_bgmusic;
}
bool Level::has_thumbnail(void)
{
	return m_has_thumbnail;
}
sf::Texture & Level::get_thumbnail(void)
{
	return m_thumbnail;
}
bool Level::has_background(void)
{
	return m_has_background;
}
sf::Image Level::get_background(void)
{
	return m_background;
}
bool Level::has_music(void)
{
	return m_has_music;
}
sf::SoundBuffer Level::get_music(void)
{
	return m_music;
}
sf::Texture Level::get_custom_texture(std::string name)
{
	unsigned int i;
	for (i=0; i < m_ctextures_count; i++)
	{
		if (m_ctextures[i].name == name)
			return m_ctextures[i].texture;
	}
}
