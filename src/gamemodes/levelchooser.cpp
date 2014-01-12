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
	for (i=0; i < 12; i++)
		m_frame_sprite[i].setTexture(m_frame);
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
	/*
	 * Variable declaration:
	*/
	unsigned int i;
	double multip;
	/*
	 * Resize & position frames:
	*/
	multip = w/1920.;
	for (i=0; i < 12; i++)
	{
		m_frame_sprite[i].setScale(5*multip, 5*multip);
		m_frame_sprite[i].setPosition(((i % 4)*(60+SIZE_LEVELCHOOSER_FRAME_IMGWIDTH*5)+170)*multip, (int(i/4)*(60+SIZE_LEVELCHOOSER_FRAME_IMGHEIGHT*5)+120)*multip);
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
	arr.init(12);
	for (i=0; i < 12; i++)
		arr.add_sprite(m_frame_sprite[i]);
	return arr;
}
