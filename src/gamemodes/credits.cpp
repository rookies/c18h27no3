/*
 * credits.cpp
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
#include "credits.hpp"

Credits::Credits()
{

}
Credits::~Credits()
{

}
int Credits::init(Config conf, std::string arg)
{
	/*
	 * Load image texture:
	*/
	if (!m_img_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "credits.png")))
		return 1;
	m_img_texture.setSmooth(true);
	m_img.setTexture(m_img_texture);
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	if (!m_font2.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Regular.ttf")))
		return 1;
	/*
	 * Init header:
	*/
	m_header.setFont(m_font1);
	m_header.setColor(sf::Color::Black);
	m_header.setString(_("credits_header"));
	/*
	 * Init text:
	*/
	m_text.setFont(m_font2);
	m_text.setColor(sf::Color::Black);
	m_text.setString(get_wstring(_("credits_stdtext")));
	return 0;
}
int Credits::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int Credits::calculate_sizes(int w, int h)
{
	/*
	 * Set image properties:
	*/
	m_img.setScale(w/1920., w/1920.);
	m_img.setPosition(sf::Vector2f(0, h-m_img.getGlobalBounds().height));
	/*
	 * Set header properties:
	*/
	m_header.setCharacterSize(h/SIZE_CREDITS_HEADER_TEXT_SIZE_DIVIDER);
	/*
	 * Set text properties:
	*/
	m_text.setCharacterSize(h/SIZE_CREDITS_TEXT_SIZE_DIVIDER);
	m_text.setPosition(sf::Vector2f(0, h/SIZE_CREDITS_HEADER_TEXT_SIZE_DIVIDER*2));
	return 0;
}
void Credits::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
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
UniversalDrawableArray Credits::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	arr.init(3);
	arr.add_sprite(m_img);
	arr.add_text(m_header);
	arr.add_text(m_text);
	return arr;
}
