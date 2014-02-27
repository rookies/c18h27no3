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
	 * Load grass block:
	*/
	if (!m_grass_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "blocks/grass.png")))
		return 1;
	m_grass_texture.setRepeated(true);
	m_grass.setTexture(m_grass_texture);
	m_grass.setTextureRect(sf::IntRect(0, 0, 18*32, 16));
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
	/*
	 * Set grass properties:
	*/
	scale = h/20./16.;
	m_grass.setScale(scale, scale);
	m_grass.setPosition(0, h/20.*19.5);
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
					//ret->set_gamemode(1);
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
	/*
	 * Add elements:
	*/
	arr.init(1);
	arr.add_sprite(m_grass);
	/*
	 * Return array:
	*/
	return arr;
}
