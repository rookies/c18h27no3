/*
 * flappyfstone.cpp
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

#include "flappyfstone.hpp"

FlappyFStone::FlappyFStone() : m_pipes_visible(0), m_pipes_wasfull(false), m_pipe_overwrite(-1), m_rising(false), m_failed(false), m_points(0)
{

}
FlappyFStone::~FlappyFStone()
{

}
int FlappyFStone::init(Config conf, std::string arg)
{
	/*
	 * Variable declarations:
	*/
	unsigned int i;
	/*
	 * Load font:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "PressStart2P.ttf")))
		return 1;
	/*
	 * Init points text:
	*/
	m_pointstext.setFont(m_font1);
	m_pointstext.setString("0");
	m_pointstext.setColor(sf::Color::Black);
	/*
	 * Init pipes:
	*/
	for (i=0; i < FLAPPYFSTONE_PIPENUM; i++)
		m_pipes[i].setFillColor(sf::Color(0,255,0));
	/*
	 * Load fstone:
	*/
	if (!m_fstone_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "fstone.png")))
		return 1;
	m_fstone_texture.setSmooth(true);
	m_fstone.setTexture(m_fstone_texture);
	return 0;
}
int FlappyFStone::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int FlappyFStone::calculate_sizes(int w, int h)
{
	m_w = w;
	m_h = h;
	/*
	 * Variable declarations:
	*/
	unsigned int i;
	/*
	 * Set points text properties:
	*/
	m_pointstext.setCharacterSize(h/10.);
	update_points();
	/*
	 * Set pipe size:
	*/
	for (i=0; i < FLAPPYFSTONE_PIPENUM; i++)
		m_pipes[i].setSize(sf::Vector2f(w/20., h));
	/*
	 * Set fstone position & size:
	*/
	m_fstone.setScale(0.001*h, 0.001*h);
	m_fstone.setPosition(w*0.05, (h-m_fstone.getGlobalBounds().height)/2.);
	/*
	 * Set middle position:
	*/
	m_lastpos = h/2;
	/*
	 * Set gap height:
	*/
	m_gapheight = h/3;
	return 0;
}
void FlappyFStone::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	if (m_failed && m_exittimer.getElapsedTime().asSeconds() >= 1)
		ret->set_gamemode(1);
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(1);
					break;
				case sf::Keyboard::Space:
					if (!m_rising)
					{
						m_rising = true;
						m_risingtimer.restart();
					};
					break;
			}
			break;
	}
}
UniversalDrawableArray FlappyFStone::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	unsigned int i;
	unsigned int t;
	int pos;
	bool collision;
	sf::FloatRect rect;
	/*
	 * Check for gameover:
	*/
	if (!m_failed)
	{
		/*
		 * Read movement timer:
		*/
		t = m_movementtimer.getElapsedTime().asMilliseconds();
		/*
		 * Move fstone:
		*/
		if (m_rising)
		{
			if (m_risingtimer.getElapsedTime().asMilliseconds() >= 100)
				m_rising = false;
			else
			{
				m_fstone.setPosition(m_fstone.getPosition().x, m_fstone.getPosition().y-((t/2.)*m_w/1280.));
			};
		}
		else
			m_fstone.setPosition(m_fstone.getPosition().x, m_fstone.getPosition().y+((t/5.)*m_w/1280.));
		/*
		 * Move pipes & check for completion:
		*/
		for (i=0; i < m_pipes_visible; i++)
		{
			rect = m_pipes[i].getGlobalBounds();
			if (i % 2 == 0 && rect.left+rect.width > m_fstone.getPosition().x && rect.left+rect.width-((t/4.)*m_w/1280.) <= m_fstone.getPosition().x)
			{
				m_points++;
				update_points();
			};
			m_pipes[i].setPosition(rect.left-((t/4.)*m_w/1280.), rect.top);
		}
		m_movementtimer.restart();
		/*
		 * Remove old pipes:
		*/
		for (i=0; i < m_pipes_visible; i += 2)
		{
			if (m_pipes[i].getPosition().x <= -m_pipes[i].getGlobalBounds().width)
			{
				m_pipe_overwrite = i;
				break;
			};
		}
		/*
		 * Add new pipes:
		*/
		if ((m_creationtimer.getElapsedTime().asMilliseconds() >= m_w/1.5 && rand() % 20 == 0) || m_pipes_visible == 0)
		{
			if (!m_pipes_wasfull || m_pipe_overwrite > -1)
			{
				/*
				 * Get a free array index:
				*/
				if (m_pipes_wasfull)
				{
					i = m_pipe_overwrite;
					m_pipe_overwrite = -1;
				}
				else
				{
					i = m_pipes_visible;
					m_pipes_visible += 2;
				};
				/*
				 * Calculate a position:
				*/
				pos = ((rand() % (m_h/2))-(m_h/4));
				if (m_lastpos+pos-(int(m_gapheight)/2) < 0 || m_lastpos+pos+(int(m_gapheight)/2) > m_h)
					pos = -pos;
				pos += m_lastpos;
				m_lastpos = pos;
				/*
				 * Add the pipe:
				*/
				m_pipes[i].setPosition(m_w-1, pos-(int(m_gapheight)/2)-int(m_h));
				m_pipes[i+1].setPosition(m_w-1, pos+(m_gapheight/2));
				if (m_pipes_visible == FLAPPYFSTONE_PIPENUM)
					m_pipes_wasfull = true;
				m_creationtimer.restart();
				std::cout << "Added pipe at " << i << std::endl;
			};
		};
		/*
		 * Check for collisions:
		*/
		collision = false;
		for (i=0; i < m_pipes_visible; i++)
		{
			if (m_pipes[i].getGlobalBounds().intersects(m_fstone.getGlobalBounds()))
				collision = true;
		}
		if (m_fstone.getPosition().y >= m_h-m_fstone.getGlobalBounds().height || collision)
		{
			m_failed = true;
			update_points();
			m_exittimer.restart();
		};
	};
	/*
	 * Add elements:
	*/
	arr.init(m_pipes_visible+2);
	for (i=0; i < m_pipes_visible; i++)
		arr.add_rectshape(m_pipes[i]);
	arr.add_sprite(m_fstone);
	arr.add_text(m_pointstext);
	return arr;
}
void FlappyFStone::update_points(void)
{
	/*
	 * Variable declarations:
	*/
	std::ostringstream ss;
	/*
	 * Set properties:
	*/
	ss.str("");
	if (m_failed)
		ss << "Score: ";
	ss << m_points;
	m_pointstext.setString(ss.str());
	m_pointstext.setPosition((m_w-m_pointstext.getGlobalBounds().width)/2, (m_h-m_pointstext.getGlobalBounds().height)/2);
}
