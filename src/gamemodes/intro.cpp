/*
 * intro.cpp
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
#include "intro.hpp"

Intro::Intro() : m_stage(0), m_state(0), m_finished(false), m_bumped(false)
{

}
Intro::~Intro()
{

}
int Intro::init(Config conf, std::string arg)
{
	/*
	 * Init logo:
	*/
	if (!m_logo_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "cdev_glowing.png")))
		return 1;
	m_logo_texture.setSmooth(true);
	m_logo.setTexture(m_logo_texture);
	/*
	 * Init menu image:
	*/
	if (!m_menu_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "mainmenu.png")))
		return 1;
	m_menu_texture.setSmooth(true);
	m_menu.setTexture(m_menu_texture);
	/*
	 * Init background:
	*/
	m_bg.setFillColor(sf::Color::Black);
	return 0;
}
int Intro::uninit(void)
{
	return 0;
}
int Intro::calculate_sizes(int w, int h)
{
	m_fire.calculate_sizes(w,h);
	m_w = w;
	m_h = h;
	/*
	 * Variable declarations:
	*/
	float scale;
	/*
	 * Set logo properties:
	*/
	m_logo.setScale(0, 0);
	/*
	 * Set menu properties:
	*/
	scale = h*(SIZE_MAINMENU_LOGO_HEIGHT/100.0)/1080.;
	m_menu.setScale(scale, scale);
	m_menu.setPosition((w-m_menu.getGlobalBounds().width)/2., h);
	/*
	 * Set bg size:
	*/
	m_bg.setSize(sf::Vector2f(w, h));
	return 0;
}
void Intro::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	if (m_finished)
		ret->set_gamemode(1);
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
UniversalDrawableArray Intro::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	float scale, move;
	sf::FloatRect rect;
	/*
	 * Add items:
	*/
	switch (m_stage)
	{
		case 0:
			/*
			 * Capsaicin Dev logo fading in
			*/
			arr.init(2);
			/*
			 * Set logo properties:
			*/
			if (m_clock.getElapsedTime().asMilliseconds() >= 5 && m_state <= 100)
			{
				m_state++;
				scale = ((m_w*SIZE_INTRO_LOGO_WIDTH/100.)/SIZE_CDEV_GLOWING_IMGWIDTH)*m_state/100.;
				m_logo.setScale(scale, scale);
				m_logo.setPosition((m_w-m_logo.getGlobalBounds().width)/2., (m_h-m_logo.getGlobalBounds().height)/2.);
				m_clock.restart();
			}
			else if (m_state > 100)
			{
				m_stage++;
				m_state = 0;
			};
			/*
			 * Add items:
			*/
			arr.add_rectshape(m_bg);
			arr.add_sprite(m_logo);
			break;
		case 1:
			/*
			 * Fist boxing it away
			*/
			arr.init(3);
			/*
			 * Set properties:
			*/
			if (m_clock.getElapsedTime().asMilliseconds() >= 5 && m_menu.getPosition().y >= m_h*(SIZE_MAINMENU_LOGO_YOFFSET/100.0))
			{
				m_state += 3;
				move = m_menu.getPosition().y-m_h*(1-m_state/100.);
				m_menu.setPosition((m_w-m_menu.getGlobalBounds().width)/2., m_h*(1-m_state/100.));
				rect = m_menu.getGlobalBounds();
				rect.top += m_h*SIZE_INTRO_OFFSET/100.;
				if (rect.intersects(m_logo.getGlobalBounds()))
					m_bumped = true;
				if (m_bumped)
					m_logo.setPosition(m_logo.getPosition().x, m_logo.getPosition().y-move*2);
				m_clock.restart();
			}
			else if (m_menu.getPosition().y < m_h*(SIZE_MAINMENU_LOGO_YOFFSET/100.0))
			{
				m_stage++;
				m_menu.setPosition(m_menu.getPosition().x, m_h*(SIZE_MAINMENU_LOGO_YOFFSET/100.0));
			};
			/*
			 * Add items:
			*/
			if (m_bumped)
				arr.add_sprite(m_fire.get_sprite());
			else
				arr.add_rectshape(m_bg);
			arr.add_sprite(m_logo);
			arr.add_sprite(m_menu);
			break;
		case 2:
			/*
			 * Logo moving out of the screen
			*/
			arr.init(3);
			/*
			 * Set properties:
			*/
			if (m_clock.getElapsedTime().asMilliseconds() >= 5 && m_logo.getPosition().y > -m_logo.getGlobalBounds().height)
			{
				m_logo.setPosition(m_logo.getPosition().x, m_logo.getPosition().y-m_h/100.);
				m_clock.restart();
			}
			else if (m_logo.getPosition().y <= -m_logo.getGlobalBounds().height)
				m_finished = true;
			/*
			 * Add items:
			*/
			arr.add_sprite(m_fire.get_sprite());
			arr.add_sprite(m_logo);
			arr.add_sprite(m_menu);
	}
	return arr;
}
