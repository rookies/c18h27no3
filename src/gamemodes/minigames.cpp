/*
 * minigames.cpp
 * 
 * Copyright 2014 Robert Knauer <robert@capsaicin-dev.de>
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
#include "minigames.hpp"

Minigames::Minigames() : 	m_player_xaction(0),
							m_playerx(PLAYERPOS_X),
							m_backwards(false),
							m_player_texture_c(0),
							m_player_texturecounter(0),
							m_casinoframe(0),
							m_door_num(0)
{

}
Minigames::~Minigames()
{

}
int Minigames::init(Config conf, std::string arg)
{
	/*
	 * Variable declarations:
	*/
	unsigned int i;
	/*
	 * Load grass block:
	*/
	if (!m_grass_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "blocks/grass.png")))
		return 1;
	m_grass_texture.setRepeated(true);
	m_grass.setTexture(m_grass_texture);
	m_grass.setTextureRect(sf::IntRect(0, 0, 18*32, 16));
	/*
	 * Load player texture:
	*/
	if (!m_player_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player.png")))
		return 1;
	m_player.setTexture(m_player_texture);
	m_player_textures = m_player_texture.getSize().x/(m_player_texture.getSize().y/3.);
	m_player.setTextureRect(sf::IntRect(0, 0, m_player_texture.getSize().y/3, m_player_texture.getSize().y));
	/*
	 * Load door texture:
	*/
	if (!m_door.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "door.png")))
		return 1;
	for (i=0; i < MINIGAMES_DOORNUM; i++)
		m_doors[i].setTexture(m_door);
	/*
	 * Read argument (door number):
	*/
	if (arg.compare("") != 0)
	{
		i = atoi(arg.c_str());
		m_playerx = (SIZE_MINIGAMES_DOOR_FIRST_XOFFSET+(i*SIZE_MINIGAMES_DOOR_XGAP + 2*(i+.25)*(SIZE_MINIGAMES_DOOR_HEIGHT/m_door.getSize().y*m_door.getSize().x)))/100.*(1920/(1080/20*2));
	};
	/*
	 * Load exit texture:
	*/
	if (!m_exit_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "exit.png")))
		return 1;
	m_exit.setTexture(m_exit_texture);
	/*
	 * Load casino texture:
	*/
	if (!m_casino_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "casino.png")))
		return 1;
	m_casino.setTexture(m_casino_texture);
	m_casino.setTextureRect(sf::IntRect(0, 0, m_casino_texture.getSize().x, m_casino_texture.getSize().y/MINIGAMES_CASINOSIGN_IMGNUM));
	/*
	 * Set key values:
	*/
	m_key_goleft = conf.get("CONTROL__KEY_GOLEFT").value_int;
	m_key_goright = conf.get("CONTROL__KEY_GORIGHT").value_int;
	/*
	 * Init timers:
	*/
	m_actiontimer.restart();
	m_playertimer.restart();
	m_casinotimer.restart();
	return 0;
}
int Minigames::uninit(void)
{
	return 0;
}
int Minigames::calculate_sizes(int w, int h)
{
	/*
	 * Variable declarations:
	*/
	float scale;
	unsigned int i;
	/*
	 * Calculate block sizes:
	*/
	m_blockh = h/VERTICAL_BLOCK_NUMBER;
	m_blockw = 2*m_blockh;
	/*
	 * Set grass properties:
	*/
	scale = h/20./16.;
	m_grass.setScale(scale, scale);
	m_grass.setPosition(0, h/20.*19.5);
	/*
	 * Set player properties:
	*/
	scale = (h/VERTICAL_BLOCK_NUMBER*3)/24;
	m_player.setScale(scale, scale);
	place_player();
	/*
	 * Set door properties:
	*/
	for (i=0; i < MINIGAMES_DOORNUM; i++)
	{
		scale = ((h*SIZE_MINIGAMES_DOOR_HEIGHT)/100.)/m_door.getSize().y;
		m_doors[i].setScale(scale, scale);
		m_doors[i].setPosition(((SIZE_MINIGAMES_DOOR_FIRST_XOFFSET+(i*SIZE_MINIGAMES_DOOR_XGAP))*w)/100., h/20.*19.5-m_doors[i].getGlobalBounds().height);
	}
	/*
	 * Set exit properties:
	*/
	scale = ((w*SIZE_MINIGAMES_SIGN_WIDTH)/100.)/m_exit_texture.getSize().y;
	m_exit.setScale(scale, scale);
	m_exit.setPosition(m_doors[0].getPosition().x+(m_doors[0].getGlobalBounds().width-m_exit.getGlobalBounds().width)/2., (SIZE_MINIGAMES_SIGN_YOFFSET*h)/100.-m_exit.getGlobalBounds().height);
	/*
	 * Set casino sign properties:
	*/
	scale = ((w*SIZE_MINIGAMES_CASINOSIGN_WIDTH)/100.)/m_casino_texture.getSize().y;
	m_casino.setScale(scale, scale);
	m_casino.setPosition((w-m_casino.getGlobalBounds().width)/2., (h*SIZE_MINIGAMES_CASINOSIGN_YOFFSET)/100.);
	return 0;
}
void Minigames::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(9); // go to levelchooser
					break;
				case sf::Keyboard::Return:
					switch (m_door_num)
					{
						case 1:
							ret->set_gamemode(9); // go to levelchooser
							break;
						case 2:
							ret->set_gamemode(14); // go to flappy falkenstone
							break;
					}
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
UniversalDrawableArray Minigames::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	unsigned int i;
	double multip, ssize;
	unsigned int intersects;
	/*
	 * Perform player actions:
	*/
	multip = m_actiontimer.getElapsedTime().asMilliseconds()/12.;
	ssize = PLAYER_XSTEPSIZE*multip;
	/*
	 * Perform X actions (running):
	*/
	switch (m_player_xaction)
	{
		case PLAYER_RUNNING_LEFT:
			if (m_playerx-ssize >= 0)
			{
				m_playerx -= ssize;
				m_backwards = true;
				toggle_playertexture();
				place_player();
			};
			break;
		case PLAYER_RUNNING_RIGHT:
			if (m_playerx <= 34)
			{
				m_playerx += ssize;
				m_backwards = false;
				toggle_playertexture();
				place_player();
			};
			break;
	}
	/*
	 * Check for door interaction:
	*/
	intersects = 0;
	for (i=0; i < MINIGAMES_DOORNUM; i++)
	{
		if (m_doors[i].getGlobalBounds().intersects(m_player.getGlobalBounds()))
		{
			intersects = i+1;
			break;
		};
	}
	if (intersects != m_door_num)
		m_door_num = intersects;
	/*
	 * Change casino sign frame:
	*/
	if (m_casinotimer.getElapsedTime().asMilliseconds() >= MINIGAMES_CASINOSIGN_BLINK_MS)
	{
		m_casinoframe++;
		if (m_casinoframe == MINIGAMES_CASINOSIGN_IMGNUM)
			m_casinoframe = 0;
		m_casino.setTextureRect(sf::IntRect(0, (m_casino_texture.getSize().y/MINIGAMES_CASINOSIGN_IMGNUM)*m_casinoframe, m_casino_texture.getSize().x, m_casino_texture.getSize().y/MINIGAMES_CASINOSIGN_IMGNUM));
		m_casinotimer.restart();
	};
	/*
	 * Reset timer:
	*/
	m_actiontimer.restart();
	/*
	 * Add elements:
	*/
	arr.init(4+MINIGAMES_DOORNUM);
	arr.add_sprite(m_grass);
	for (i=0; i < MINIGAMES_DOORNUM; i++)
		arr.add_sprite(m_doors[i]);
	arr.add_sprite(m_exit);
	arr.add_sprite(m_player);
	arr.add_sprite(m_casino);
	/*
	 * Return array:
	*/
	return arr;
}
void Minigames::toggle_playertexture(void)
{
	/*
	 * Variable declarations:
	*/
	unsigned int width;
	/*
	 * Check if we have to toggle:
	*/
	if (m_playertimer.getElapsedTime().asMilliseconds() < 100)
		return;
	if (m_player_texturecounter < 5)
	{
		m_player_texturecounter++;
		return;
	};
	/*
	 * Yes, toggle:
	*/
	if (m_player_texture_c == m_player_textures-1)
		m_player_texture_c = 0;
	else
		m_player_texture_c++;
	/*
	 * If we're running backwards, flip the texture:
	*/
	width = m_player_texture.getSize().x/m_player_textures;
	if (m_backwards)
		m_player.setTextureRect(sf::IntRect(width*(m_player_texture_c+1), 0, -width, m_player_texture.getSize().y));
	else
		m_player.setTextureRect(sf::IntRect(width*m_player_texture_c, 0, width, m_player_texture.getSize().y));
	/*
	 * Reset counter & clock:
	*/
	m_player_texturecounter = 0;
	m_playertimer.restart();
}
void Minigames::place_player(void)
{
	m_player.setPosition(m_playerx*m_blockw/2., m_blockh*16.5);
}
