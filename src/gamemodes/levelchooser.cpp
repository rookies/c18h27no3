/*
 * levelchooser.cpp
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
#include "levelchooser.hpp"

LevelChooser::LevelChooser()
{

}
LevelChooser::~LevelChooser()
{

}
int LevelChooser::init(Config conf, std::string arg)
{
	/*
	 * Variable declaration:
	*/
	unsigned int i;
	/*
	 * Init frames:
	*/
	if (!m_frame.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "levelchooser_frame.png")))
		return 1;
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
		m_frame_sprite[i].setTexture(m_frame);
	/*
	 * Init testlevel:
	*/
	if (!m_testlevel.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "testlevel.png")))
		return 1;
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
	{
		m_level_sprite[i].setTexture(m_testlevel);
		if (i > 0)
			m_level_sprite[i].setColor(COLOR_LEVELCHOOSER_LEVEL_MASK_INACTIVE);
	}
	/*
	 * Init locks:
	*/
	if (!m_lock.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "lock.png")))
		return 1;
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
		m_lock_sprite[i].setTexture(m_lock);
	/*
	 * Init level backgrounds:
	*/
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
	{
		if (i == 0)
			m_level_bg[i].setFillColor(COLOR_LEVELCHOOSER_LEVEL_BACKGROUND_HOVER);
		else
			m_level_bg[i].setFillColor(COLOR_LEVELCHOOSER_LEVEL_BACKGROUND);
	}
	return 0;
}
int LevelChooser::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int LevelChooser::calculate_sizes(int w, int h)
{
	m_fire.calculate_sizes(w,h);
	/*
	 * Variable declaration:
	*/
	unsigned int i;
	double multip;
	unsigned long pos1, pos2;
	/*
	 * Resize & position frames, level images, locks & level backgrounds:
	*/
	multip = w/1920.;
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
	{
		pos1 = (i % 4)*(60+SIZE_LEVELCHOOSER_FRAME_IMGWIDTH*5)+170;
		pos2 = int(i/4)*(60+SIZE_LEVELCHOOSER_FRAME_IMGHEIGHT*5)+120;
		// Frames:
		m_frame_sprite[i].setScale(5*multip, 5*multip);
		m_frame_sprite[i].setPosition(pos1*multip, pos2*multip);
		// Level Images:
		m_level_sprite[i].setScale(0.63*multip, 0.63*multip); // div 8 * 5 + tolerance
		m_level_sprite[i].setPosition((pos1+20)*multip, (pos2+20)*multip);
		// Locks:
		m_lock_sprite[i].setScale(5*multip, 5*multip);
		m_lock_sprite[i].setPosition((pos1+112.5)*multip, (pos2+17.5)*multip); // 22.5*5 ; 3.5*5
		// Level Backgrounds:
		m_level_bg[i].setSize(sf::Vector2f(SIZE_LEVELCHOOSER_LVLIMG_IMGWIDTH*0.63*multip, SIZE_LEVELCHOOSER_LVLIMG_IMGHEIGHT*0.63*multip));
		m_level_bg[i].setPosition((pos1+20)*multip, (pos2+20)*multip);
	}
	return 0;
}
void LevelChooser::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(1);
					break;
			}
			break;
		case sf::Event::MouseMoved:
			if (m_level_sprite[0].getGlobalBounds().contains(mouse_x, mouse_y))
				m_level_sprite[0].setColor(COLOR_LEVELCHOOSER_LEVEL_MASK_HOVER);
			else
				m_level_sprite[0].setColor(COLOR_LEVELCHOOSER_LEVEL_MASK);
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_level_sprite[0].getGlobalBounds().contains(mouse_x, mouse_y))
						ret->set_gamemode(7); // go to singleplayer
					break;
			}
			break;
	}
}
UniversalDrawableArray LevelChooser::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	unsigned int i;
	/*
	 * Add elements:
	*/
	//arr.init(49);
	arr.init(48);
	arr.add_sprite(m_fire.get_sprite());
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
	{
		arr.add_rectshape(m_level_bg[i]);
		arr.add_sprite(m_level_sprite[i]);
		arr.add_sprite(m_frame_sprite[i]);
		if (i > 0)
			arr.add_sprite(m_lock_sprite[i]);
	}
	return arr;
}
