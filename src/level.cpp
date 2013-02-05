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

LevelColumn::LevelColumn() : m_offset(-1)
{

}
LevelColumn::~LevelColumn()
{
	if (m_offset >= 0)
		delete[] m_blocks;
}
void LevelColumn::set_blocknumber(unsigned short number)
{
	if (m_offset < 0)
	{
		m_blocknumber = number;
		m_blocks = new LevelBlock[m_blocknumber];
		m_offset = 0;
	};
}
void LevelColumn::add_block(unsigned short position, unsigned short blockdef)
{
	if (m_offset < 0)
		return;
	m_blocks[m_offset].position = position;
	m_blocks[m_offset].blockdef = blockdef;
	m_offset++;
}
unsigned short LevelColumn::get_blocknumber(void)
{
	return m_blocknumber;
}
LevelBlock *LevelColumn::get_block(unsigned short index)
{
	return &m_blocks[index];
}

Level::Level()
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
	unsigned short tmp, tmp2, tmp3;
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
	std::cerr << "LevelLoader: Opened level file!" << std::endl;
#endif
	/*
	 * Read CAPSAICIN header:
	*/
	buf = new char[9];
	f.read(buf, 9);
	if (std::string(buf).compare("CAPSAICIN") != 0)
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
		 * Read Y number:
		*/
		buf = new char[1];
		f.read(buf, 1);
		tmp = (unsigned short)buf[0];
		delete[] buf;
		/*
		 * Run through Y blocks:
		*/
		m_columns[i].set_blocknumber(tmp);
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
