/*
 * singleplayer.cpp
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
#include "singleplayer.hpp"

SinglePlayer::SinglePlayer() : m_player_xaction(0), m_player_texture2_en(false), m_player_texturecounter(0), m_initialized(false)
{

}
SinglePlayer::~SinglePlayer()
{
	if (m_initialized)
		delete[] m_block_textures;
}
int SinglePlayer::init(Config conf, std::string arg)
{
	/*
	 * Variable declarations:
	*/
	int i;
	std::string fname;
	/*
	 * Load player textures:
	*/
	if (!m_player_texture1.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_frame1.png")))
		return 1;
	if (!m_player_texture2.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_frame2.png")))
		return 1;
	/*
	 * Set player properties:
	*/
	m_player.setTexture(m_player_texture1);
	/*
	 * Set key values:
	*/
	m_key_goleft = conf.get("CONTROL__KEY_GOLEFT").value_int;
	m_key_goright = conf.get("CONTROL__KEY_GORIGHT").value_int;
	/*
	 * Load level from file:
	*/
	if (arg.compare("") == 0)
	{
		if (!m_level.load_from_file("level1.dat"))
			return 1;
	}
	else
	{
		if (!m_level.load_from_file(arg))
			return 1;
	};
	/*
	 * Load block textures:
	*/
	m_block_textures = new sf::Texture[m_level.get_blockdefs_number()];
	m_initialized = true;
	for (i=0; i < m_level.get_blockdefs_number(); i++)
	{
		if (m_level.get_blockdef(i).get_type() == BLOCKDEF_TYPE_BUILTIN)
		{
			fname = "";
			fname.append("blocks/");
			fname.append(m_level.get_blockdef(i).get_arg());
			fname.append(".png");
			if (!m_block_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, fname)))
			{
				if (!m_block_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "block_not_found.png")))
					return 1;
			};
		}
		else
		{
			if (!m_block_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "block_not_found.png")))
				return 1;
		};
	}
	/*
	 * Init timers:
	*/
	m_actiontimer.restart();
	m_playertimer.restart();
	return 0;
}
int SinglePlayer::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int SinglePlayer::calculate_sizes(int w, int h)
{
	/*
	 * Variable declarations:
	*/
	int i, j, k;
	/*
	 * Calculate block sizes:
	*/
	m_blockh = h/VERTICAL_BLOCK_NUMBER;
	m_blockw = 2*m_blockh;
	/*
	 * Calculate width in blocks:
	*/
	m_width_in_blocks = ceil(w/float(m_blockw));
	if (m_width_in_blocks > m_level.get_levelwidth()*2)
		m_width_in_blocks = floor(m_level.get_levelwidth()/2.);
	/*
	 * Calculate visible block number:
	*/
	m_visible_block_number = 0;
	for (i=0; i < m_width_in_blocks*2; i++)
	{
		m_visible_block_number += m_level.get_column(i)->get_blocknumber();
	}
	std::cout << "Visible block number: " << m_visible_block_number << std::endl;
	/*
	 * Create block sprites:
	*/
	m_blocks = new sf::Sprite[m_visible_block_number];
	k = 0;
	for (i=0; i < m_width_in_blocks*2; i++)
	{
		for (j=0; j < m_level.get_column(i)->get_blocknumber(); j++)
		{
			m_blocks[k].setPosition(sf::Vector2f(i*m_blockw/2., h-(((m_level.get_column(i)->get_block(j)->position/2.)+0.5)*m_blockh)));
			m_blocks[k].setScale(m_blockw/32., m_blockh/16.);
			m_blocks[k].setTexture(m_block_textures[m_level.get_column(i)->get_block(j)->blockdef]);
			k++;
		}
	}
	/*
	 * Set player properties:
	*/
	m_player.scale((m_blockw)/16, (m_blockh*3)/24);
	m_playerx = 1;
	m_playery = 35;
	place_player();
	return 0;
}
void SinglePlayer::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(1);
					break;
				default:
					if (event.key.code == m_key_goleft)
						m_player_xaction = PLAYER_RUNNING_LEFT;
					else if (event.key.code == m_key_goright)
						m_player_xaction = PLAYER_RUNNING_RIGHT;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == m_key_goleft && m_player_xaction == PLAYER_RUNNING_LEFT)
				m_player_xaction = 0;
			else if (event.key.code == m_key_goright && m_player_xaction == PLAYER_RUNNING_RIGHT)
				m_player_xaction = 0;
			break;
	}
}
UniversalDrawableArray SinglePlayer::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	int i, j;
	UniversalDrawableArray arr;
	LevelColumn *col;
	double highest;
	/*
	 * Perform player actions:
	*/
	if (m_actiontimer.getElapsedTime().asMilliseconds() >= 10)
	{
		/*switch (m_player_xaction)
		{
			case PLAYER_RUNNING_LEFT:
				if (m_player.getGlobalBounds().left >= m_startpos_x)
				{
					m_player.move(sf::Vector2f(-m_stepwidth, 0));
					toggle_playertexture();
				}
				else
					m_player_action = 0;
				break;
			case PLAYER_RUNNING_RIGHT:
				if (m_player.getGlobalBounds().left <= m_endpos_x)
				{
					m_player.move(sf::Vector2f(m_stepwidth, 0));
					toggle_playertexture();
				}
				else
					m_player_action = 0;
				break;
		}*/
		/*
		 * Check if we're falling:
		*/
		highest = 0;
		for (i=-1; i < 2; i++)
		{
			col = m_level.get_column(floor(m_playerx)+i);
			for (j=0; j < col->get_blocknumber(); j++)
			{
				if (col->get_block(j)->position > highest)
					highest = col->get_block(j)->position;
			}
		}
		highest += 0.5;
		if (m_playery > highest)
		{
			/*
			 * Too high!
			*/
			if (m_playery-highest < 0.1)
				m_playery -= (m_playery-highest);
			else
				m_playery -= 0.1;
			place_player();
		};
		m_actiontimer.restart();
	};
	/*
	 * Fill array:
	*/
	arr.init(1+m_visible_block_number);
	for (i=0; i < m_visible_block_number; i++)
	{
		arr.add_sprite(m_blocks[i]);
	}
	arr.add_sprite(m_player);
	return arr;
}
void SinglePlayer::toggle_playertexture(void)
{
	if (m_playertimer.getElapsedTime().asMilliseconds() < 100)
		return;
	if (m_player_texturecounter < 5)
	{
		m_player_texturecounter++;
		return;
	};
	if (m_player_texture2_en)
	{
		m_player.setTexture(m_player_texture1);
		m_player_texture2_en = false;
	}
	else
	{
		m_player.setTexture(m_player_texture2);
		m_player_texture2_en = true;
	};
	m_player_texturecounter = 0;
	m_playertimer.restart();
}
void SinglePlayer::place_player(void)
{
	m_player.setPosition(sf::Vector2f(m_playerx*m_blockw/2., (VERTICAL_BLOCK_NUMBER-3-(m_playery/2.))*m_blockh));
}
