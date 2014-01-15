/*
 * fireanimation.cpp
 * 
 * Copyright 2014 Robert Knauer <robert@privatdemail.net>
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
#include "fireanimation.hpp"

FireAnimation::FireAnimation() : m_backwards(false)
{
	/*
	 * Variable declaration:
	*/
	unsigned int i;
	std::stringstream tmp;
	/*
	 * Init background:
	*/
	for (i=0; i < FIRE_FRAMES; i++)
	{
		tmp.str("");
		tmp << "fire";
		tmp << i;
		tmp << ".png";
		m_fire[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, tmp.str()));
	}
	m_fireframe = 0;
	m_fireclock.restart();
	m_fire_sprite.setTexture(m_fire[0]);
}
FireAnimation::~FireAnimation()
{

}
void FireAnimation::calculate_sizes(int w, int h)
{
	m_fire_sprite.setScale(w/SIZE_MENU_BG_IMGWIDTH, w/SIZE_MENU_BG_IMGWIDTH);
}
sf::Sprite FireAnimation::get_sprite(void)
{
	if (m_fireclock.getElapsedTime().asMilliseconds() >= FIRE_FRAMELENGTH_MS)
	{
		// Switch direction if necessary:
		if (!m_backwards && m_fireframe == FIRE_FRAMES-1)
			m_backwards = true;
		else if (m_backwards && m_fireframe == 0)
			m_backwards = false;
		// Increase or decrease framenumber:
		if (m_backwards)
			m_fireframe--;
		else
			m_fireframe++;
		// Update frame & restart clock:
		m_fire_sprite.setTexture(m_fire[m_fireframe]);
		m_fireclock.restart();
	};
	return m_fire_sprite;
}
