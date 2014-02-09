/*
 * newgame.cpp
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
#include "newgame.hpp"

NewGame::NewGame()
{

}
NewGame::~NewGame()
{

}
int NewGame::init(Config conf, std::string arg)
{
	/*
	 * Init arrows:
	*/
	if (!m_arrow.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "arrow_red.png")))
		return 1;
	m_arrow_left.setTexture(m_arrow);
	m_arrow_right.setTexture(m_arrow);
	m_arrow_right.setTextureRect(sf::IntRect(m_arrow.getSize().x, 0, -m_arrow.getSize().x, m_arrow.getSize().y));
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Regular.ttf")))
		return 1;
	if (!m_font2.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	/*
	 * Init heading:
	*/
	m_heading.setFont(m_font2);
	m_heading.setColor(sf::Color::White);
	m_heading.setString(get_wstring(_("newgame_header")));
	return 0;
}
int NewGame::uninit(void)
{
	return 0;
}
int NewGame::calculate_sizes(int w, int h)
{
	m_fire.calculate_sizes(w,h);
	/*
	 * Variable declarations:
	*/
	float scale;
	/*
	 * Set arrow properties:
	*/
	scale = ((h*SIZE_NEWGAME_ARROW_HEIGHT)/100.)/m_arrow.getSize().y;
	m_arrow_left.setScale(scale, scale);
	m_arrow_right.setScale(scale, scale);
	m_arrow_left.setPosition((w*SIZE_NEWGAME_ARROW_XOFFSET)/100., (h*SIZE_NEWGAME_ARROW_YOFFSET)/100.);
	m_arrow_right.setPosition(w-(w*SIZE_NEWGAME_ARROW_XOFFSET)/100.-m_arrow_right.getGlobalBounds().width, (h*SIZE_NEWGAME_ARROW_YOFFSET)/100.);
	/*
	 * Set heading properties:
	*/
	m_heading.setCharacterSize((h*SIZE_NEWGAME_HEADER)/100.);
	m_heading.setPosition((w-m_heading.getGlobalBounds().width)/2., (h*SIZE_NEWGAME_HEADER_YOFFSET)/100.);
	return 0;
}
void NewGame::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
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
UniversalDrawableArray NewGame::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * Init array:
	*/
	arr.init(4);
	/*
	 * Add items:
	*/
	arr.add_sprite(m_fire.get_sprite());
	arr.add_text(m_heading);
	arr.add_sprite(m_arrow_left);
	arr.add_sprite(m_arrow_right);
	return arr;
}
