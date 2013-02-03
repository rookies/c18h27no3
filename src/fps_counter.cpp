/*
 * fps_counter.cpp
 * 
 * Copyright 2012 Robert Knauer <robert@privatdemail.net>
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
#include "fps_counter.hpp"

FPScounter::FPScounter()
{
	
}
FPScounter::~FPScounter()
{
	
}
int FPScounter::init(void)
{
	/*
	 * Load text:
	*/
	m_txt.setColor(sf::Color::Black);
	m_txt.setString("0 fps");
	/*
	 * Set bg properties:
	*/
	m_bg.setFillColor(COLOR_MENU_BACKGROUND);
	m_bg.setOutlineThickness(0);
	/*
	 * Reset clock:
	*/
	m_clock.restart();
	m_frames = 0;
}
int FPScounter::calculate_sizes(int w, int h)
{
	m_txt.setCharacterSize((int)(h*(SIZE_FPS_COUNTER_TEXT/100.0)));
	m_txt.setPosition((int)(w*(SIZE_FPS_COUNTER_XGAP/100.0)), (int)(h-h*(SIZE_FPS_COUNTER_YGAP/100.0)-m_txt.getGlobalBounds().height));
	m_bg.setSize(sf::Vector2f(m_txt.getGlobalBounds().width+2, m_txt.getGlobalBounds().height+2));
	m_bg.setPosition(sf::Vector2f(m_txt.getGlobalBounds().left-1, m_txt.getGlobalBounds().top-1));
}
sf::Text FPScounter::get_drawable(void)
{
	if (m_frames == 100)
	{
		/*
		 * Build the string for showing:
		*/
		m_txt_float.str("");
		m_txt_float << floor(m_frames/m_clock.getElapsedTime().asSeconds() + 0.5); // round
		m_txt_str = m_txt_float.str();
		m_txt_str += " fps";
		/*
		 * Print to console:
		*/
		//std::cout << m_txt_float.str() << " fps" << std::endl;
		/*
		 * Show on display:
		*/
		m_txt.setString(m_txt_str);
		/*
		 * Reset framerate clock:
		*/
		m_clock.restart();
		m_frames = 0;
	}
	else
		m_frames++;
	return m_txt;
}
sf::RectangleShape FPScounter::get_drawable_bg(void)
{
	return m_bg;
}
void FPScounter::restart(void)
{
	m_clock.restart();
	m_frames = 0;
}
