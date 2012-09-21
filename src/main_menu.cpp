/*
 * main_menu.cpp
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
#include "main_menu.hpp"

MainMenu::MainMenu()
{
	
}
MainMenu::~MainMenu()
{
	
}
int MainMenu::init(void)
{
	reset_menuitem_over();
	return 0;
}
int MainMenu::uninit(void)
{
	return 0;
}
int MainMenu::calculate_sizes(int w, int h)
{
	/*
	 * Menuitem width = 30%
	 * Menuitem height = 5%
	*/
	m_sizes_menuitem_width = w*(30/100.0);
	m_sizes_menuitem_height = h*(5/100.0);
	/*
	 * Menuitem X offset = middle
	 * Menuitem first Y offset = 45%
	 * Menuitem gap = 2%
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2;
	m_sizes_menuitem_first_yoffset = h*(45/100.0);
	m_sizes_menuitem_gap = h*(2/100.0);
	return 0;
}
int MainMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
{
	switch (event.type)
	{
		case sf::Event::MouseMoved:
			if (mouse_x > m_sizes_menuitem_xoffset && mouse_x < m_sizes_menuitem_xoffset+m_sizes_menuitem_width)
			{
				/*
				 * Cursor is in X range of the menu items
				*/
				if (mouse_y > m_sizes_menuitem_first_yoffset && mouse_y < m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height)
				{
					/*
					 * Menuitem 1
					*/
					reset_menuitem_over();
					m_menuitem1_over = 1;
					//std::cout << "#1" << std::endl;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 2
					*/
					reset_menuitem_over();
					m_menuitem2_over = 1;
					//std::cout << "#2" << std::endl;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+2*m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+3*m_sizes_menuitem_height+2*m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 3
					*/
					reset_menuitem_over();
					m_menuitem3_over = 1;
					//std::cout << "#3" << std::endl;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+3*m_sizes_menuitem_height+3*m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+4*m_sizes_menuitem_height+3*m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 4
					*/
					reset_menuitem_over();
					m_menuitem4_over = 1;
					//std::cout << "#4" << std::endl;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+4*m_sizes_menuitem_height+4*m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+5*m_sizes_menuitem_height+4*m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 5
					*/
					reset_menuitem_over();
					m_menuitem5_over = 1;
					//std::cout << "#5" << std::endl;
				}
				else
					reset_menuitem_over();
			}
			else
				reset_menuitem_over();
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_menuitem5_over == 1)
						return 1;
					break;
			}
			break;
	}
	return 0;
}
void MainMenu::reset_menuitem_over(void)
{
	m_menuitem1_over = 0;
	m_menuitem2_over = 0;
	m_menuitem3_over = 0;
	m_menuitem4_over = 0;
	m_menuitem5_over = 0;
}
sf::RectangleShape MainMenu::get_menuitem1(void)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	shape.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset);
	if (m_menuitem1_over == 1)
		shape.setFillColor(sf::Color::Red);
	else
		shape.setFillColor(sf::Color::Blue);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5);
	return shape;
}
sf::RectangleShape MainMenu::get_menuitem2(void)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	shape.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap);
	if (m_menuitem2_over == 1)
		shape.setFillColor(sf::Color::Red);
	else
		shape.setFillColor(sf::Color::Blue);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5);
	return shape;
}
sf::RectangleShape MainMenu::get_menuitem3(void)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	shape.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*2);
	if (m_menuitem3_over == 1)
		shape.setFillColor(sf::Color::Red);
	else
		shape.setFillColor(sf::Color::Blue);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5);
	return shape;
}
sf::RectangleShape MainMenu::get_menuitem4(void)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	shape.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*3);
	if (m_menuitem4_over == 1)
		shape.setFillColor(sf::Color::Red);
	else
		shape.setFillColor(sf::Color::Blue);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5);
	return shape;
}
sf::RectangleShape MainMenu::get_menuitem5(void)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	shape.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*4);
	if (m_menuitem5_over == 1)
		shape.setFillColor(sf::Color::Red);
	else
		shape.setFillColor(sf::Color::Blue);
	shape.setOutlineColor(sf::Color::Black);
	shape.setOutlineThickness(5);
	return shape;
}
