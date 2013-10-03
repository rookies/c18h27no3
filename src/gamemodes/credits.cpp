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

Credits::Credits() : m_item_over(-1), m_item_loaded(-2)
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
	/*
	 * Init text:
	*/
	m_text.setFont(m_font2);
	m_text.setColor(sf::Color::Black);
	/*
	 * Load standard text:
	*/
	load_item(-1);
	/*
	 * Load capsaicin dev logo texture:
	*/
	if (!m_cdev_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "cdev.png")))
		return 1;
	m_cdev_texture.setSmooth(true);
	m_cdev.setTexture(m_cdev_texture);
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
	 * Variable declarations:
	*/
	float scale;
	int i;
	/*
	 * Set image properties:
	*/
	scale = w/1920.;
	m_img.setScale(scale, scale);
	m_credits_yoffset = h-m_img.getGlobalBounds().height;
	m_img.setPosition(sf::Vector2f(0, m_credits_yoffset));
	/*
	 * Set header properties:
	*/
	m_header.setCharacterSize(h/SIZE_CREDITS_HEADER_TEXT_SIZE_DIVIDER);
	m_header.setPosition(w*SIZE_CREDITS_TEXT_XOFFSET/100., 0);
	/*
	 * Set text properties:
	*/
	m_text.setCharacterSize(h/SIZE_CREDITS_TEXT_SIZE_DIVIDER);
	m_text.setPosition(sf::Vector2f(w*SIZE_CREDITS_TEXT_XOFFSET/100., h/SIZE_CREDITS_HEADER_TEXT_SIZE_DIVIDER*2));
	/*
	 * Set capsaicin dev logo properties:
	*/
	scale = w*SIZE_CREDITS_IMG_WIDTH/100./SIZE_CDEV_IMGWIDTH;
	m_cdev.setScale(scale, scale);
	m_cdev.setPosition(w*SIZE_CREDITS_IMG_XOFFSET/100., h*SIZE_CREDITS_IMG_YOFFSET/100.);
	/*
	 * Translate image positions:
	*/
	for (i=0; i < CREDITS_COUNT; i++)
	{
		m_hovert_x1[i] = (m_hover_x1[i]/1920.0)*w;
		m_hovert_x2[i] = (m_hover_x2[i]/1920.0)*w;
		m_hovert_y1[i] = (m_hover_y1[i]/1920.0)*w;
		m_hovert_y2[i] = (m_hover_y2[i]/1920.0)*w;
	}
	return 0;
}
void Credits::load_item(int i)
{
	if (m_item_loaded == i)
		return;
	switch (i)
	{
		case 0:
			m_header.setString(get_wstring("Max „Die DVU“ Bäz-Dölle"));
			m_text.setString(get_wstring(_("credits_text0")));
			break;
		case 1:
			m_header.setString(get_wstring("Robert „Knauer“ Knauer"));
			m_text.setString(get_wstring(_("credits_text1")));
			break;
		case 2:
			m_header.setString(get_wstring("Robert „F.“ Falkenstein"));
			m_text.setString(get_wstring(_("credits_text2")));
			break;
		case 3:
			m_header.setString(get_wstring("Vasco „Der Pfandjude“ Lehmann"));
			m_text.setString(get_wstring(_("credits_text3")));
			break;
		case 4:
			m_header.setString(get_wstring("Robert „Roert“ Worm"));
			m_text.setString(get_wstring(_("credits_text4")));
			break;
		case 5:
			m_header.setString(get_wstring("Grünlers Tür"));
			m_text.setString(get_wstring(_("credits_text5")));
			break;
		default:
			m_header.setString(get_wstring(_("credits_header")));
			m_text.setString(get_wstring(_("credits_stdtext")));
	}
	m_item_loaded = i;
}
void Credits::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	/*
	 * Variable declarations:
	*/
	int i;
	
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
			m_item_over = -1;
			for (i=0; i < CREDITS_COUNT; i++)
			{
				if (mouse_x >= m_hovert_x1[i] &&
					mouse_x <= m_hovert_x2[i] &&
					mouse_y >= m_credits_yoffset+m_hovert_y1[i] &&
					mouse_y <= m_credits_yoffset+m_hovert_y2[i])
				{
					m_item_over = i;
				};
			}
			if (m_item_over != m_item_loaded)
				load_item(m_item_over);
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_item_loaded == 5)
						ret->set_gamemode(1); // go to main menu
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
	arr.init(4);
	arr.add_sprite(m_img);
	arr.add_text(m_header);
	arr.add_text(m_text);
	arr.add_sprite(m_cdev);
	return arr;
}
