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

Minigames::Minigames()
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
	m_player.setTextureRect(sf::IntRect(0, 0, m_player_texture.getSize().y/3, m_player_texture.getSize().y));
	/*
	 * Load door texture:
	*/
	if (!m_door.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "door.png")))
		return 1;
	for (i=0; i < MINIGAMES_DOORNUM; i++)
		m_doors[i].setTexture(m_door);
	/*
	 * Load exit texture:
	*/
	if (!m_exit_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "exit.png")))
		return 1;
	m_exit.setTexture(m_exit_texture);
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
	m_player.setPosition(h/20.*2*1, h/20.*16.5);
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
			}
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
	/*
	 * Add elements:
	*/
	arr.init(3+MINIGAMES_DOORNUM);
	arr.add_sprite(m_grass);
	for (i=0; i < MINIGAMES_DOORNUM; i++)
		arr.add_sprite(m_doors[i]);
	arr.add_sprite(m_exit);
	arr.add_sprite(m_player);
	/*
	 * Return array:
	*/
	return arr;
}
