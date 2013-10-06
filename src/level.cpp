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

LevelMetadata::LevelMetadata()
{
	
}
LevelMetadata::~LevelMetadata()
{

}
void LevelMetadata::set_key(std::string key)
{
	m_key = key;
}
void LevelMetadata::set_value(std::string value)
{
	m_value = value;
}
std::string LevelMetadata::get_key(void)
{
	return m_key;
}
std::string LevelMetadata::get_value(void)
{
	return m_value;
}

LevelBlockdef::LevelBlockdef()
{

}
LevelBlockdef::~LevelBlockdef()
{

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

LevelColumn::LevelColumn() : m_blockoffset(-1), m_itemoffset(-1)
{

}
LevelColumn::~LevelColumn()
{
	if (m_blockoffset >= 0)
		delete[] m_blocks;
	if (m_itemoffset >= 0)
		delete[] m_items;
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

Level::Level() : m_has_bgimg(false)
{

}
Level::~Level()
{

}
bool Level::load_from_file(std::string file)
{
	/*
	 * Variable declarations:
	*/
	unsigned short i, j;
	std::ifstream f;
	char *buf;
	std::string buf_;
	unsigned short tmp, tmp2, tmp3, tmp4;
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
	std::cerr << "LevelLoader: Opened level file '" << file << "'!" << std::endl;
#endif
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
	std::cerr << "LevelLoader: Found CAPSAICIN header!" << std::endl;
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
	std::cerr << "LevelLoader: Compatible level versions! (v" << tmp << ")" << std::endl;
#endif
	delete[] buf;
	/*
	 * Read level width:
	*/
	buf = new char[2];
	f.read(buf, 2);
	m_levelwidth = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
#ifdef LVL_DEBUG
	std::cerr << "LevelLoader: Level_Width = " << m_levelwidth << std::endl;
#endif
	delete[] buf;
	/*
	 * Read metadata number:
	*/
	buf = new char[1];
	f.read(buf, 1);
	m_metadata_number = (unsigned short)buf[0];
#ifdef LVL_DEBUG
	std::cerr << "LevelLoader: Metadata_Number = " << m_metadata_number << std::endl;
#endif
	delete[] buf;
	/*
	 * Read metadata:
	*/
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
		buf = new char[tmp+1];
		f.read(buf, tmp);
		buf[tmp] = '\0';
		m_metadata[i].set_value(buf);
		delete[] buf;
		/*
		 * Print status message:
		*/
#ifdef LVL_DEBUG
		std::cerr << "LevelLoader: Metadata '" << m_metadata[i].get_key() << "' = '" << m_metadata[i].get_value() << "'" << std::endl;
#endif
	}
	/*
	 * Read blockdefs number:
	*/
	buf = new char[2];
	f.read(buf, 2);
	m_blockdefs_number = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
#ifdef LVL_DEBUG
	std::cerr << "LevelLoader: Blockdefs_Number = " << m_blockdefs_number << std::endl;
#endif
	delete[] buf;
	/*
	 * Read blockdefs:
	*/
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
#ifdef LVL_DEBUG
		std::cerr << "LevelLoader: Blockdef #" << m_blockdefs[i].get_id() << "; type=" << m_blockdefs[i].get_type() << "; arg='" << m_blockdefs[i].get_arg() << "'" << std::endl;
#endif
	}
	/*
	 * Finally: Read columns
	*/
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
#ifdef LVL_DEBUG
			std::cerr << "LevelLoader: Block x=" << i << "; y=" << tmp2 << "; blockdef=" << tmp3 << std::endl;
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
			 * Read blockdef ID:
			*/
			buf = new char[1];
			f.read(buf, 1);
			tmp3 = (unsigned char)buf[0];
			delete[] buf;
			/*
			 * Write into array:
			*/
			m_columns[i].add_item(tmp2, tmp3);
#ifdef LVL_DEBUG
			std::cerr << "LevelLoader: Item x=" << i << "; y=" << tmp2 << "; id=" << tmp3 << std::endl;
#endif
		}
	}
	/*
	 * Read extensions number:
	*/
	buf = new char[2];
	f.read(buf, 2);
	tmp = (unsigned char)buf[0]+(256*(unsigned char)buf[1]);
	delete[] buf;
#ifdef LVL_DEBUG
	std::cerr << "LevelLoader: Extensions_Number = " << tmp << std::endl;
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
			std::cerr << "LevelLoader: _bgimg extension found." << std::endl;
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
			std::cerr << " -> Data: " << buf_ << std::endl;
#endif
		}
		else if (buf_.compare("_bgmusic") == 0)
		{
#ifdef LVL_DEBUG
			std::cerr << "LevelLoader: _bgmusic extension found." << std::endl;
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
			std::cerr << " -> Data: " << buf_ << std::endl;
#endif
		}
		else
		{
			std::cerr << "LevelLoader: Unknown extension found: " << buf_ << std::endl;
		};
	}
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
