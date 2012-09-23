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
	/*
	 * Init grassblock:
	*/
	m_img1.loadFromFile("data/grass.png");
	m_img1_sprite.setTexture(m_img1);
	m_img1_sprite.setColor(sf::Color(255, 255, 255, 255));
	/*
	 * Init menuitem shapes:
	*/
	m_menuitem1.setOutlineColor(sf::Color::Black);
	m_menuitem2.setOutlineColor(sf::Color::Black);
	m_menuitem3.setOutlineColor(sf::Color::Black);
	m_menuitem4.setOutlineColor(sf::Color::Black);
	m_menuitem5.setOutlineColor(sf::Color::Black);
	m_menuitem6.setOutlineColor(sf::Color::Black);
	/*
	 * Init menuitem texts:
	*/
	m_menuitem1_txt.setString("Neues Spiel");
	m_menuitem2_txt.setString("Spiel Laden");
	m_menuitem3_txt.setString("Level-Editor");
	m_menuitem4_txt.setString("Einstellungen");
	m_menuitem5_txt.setString("Credits");
	m_menuitem6_txt.setString("Beenden");
	m_menuitem1_txt.setColor(sf::Color::Black);
	m_menuitem2_txt.setColor(sf::Color::Black);
	m_menuitem3_txt.setColor(sf::Color::Black);
	m_menuitem4_txt.setColor(sf::Color::Black);
	m_menuitem5_txt.setColor(sf::Color::Black);
	m_menuitem6_txt.setColor(sf::Color::Black);
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
	 * Menuitem outline thickness = 1%
	*/
	m_sizes_menuitem_width = w*(30/100.0);
	m_sizes_menuitem_height = h*(5/100.0);
	m_sizes_menuitem_outline = h*(0.5/100.0);
	/*
	 * Menuitem X offset = middle
	 * Menuitem first Y offset = 45%
	 * Menuitem gap = 2%
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2.0;
	m_sizes_menuitem_first_yoffset = h*(45/100.0);
	m_sizes_menuitem_gap = h*(2/100.0);
	/*
	 * Grassblock height = 30%
	 * Grassblock X offset = middle
	 * Grassblock Y offset = 10%
	*/
	m_sizes_grassblock = h*(30/100.0);
	m_sizes_grassblock_xoffset = (w-m_sizes_grassblock)/2.0;
	m_sizes_grassblock_yoffset = h*(10/100.0);
	/*
	 * Menuitem text additional gap = 2%
	*/
	m_sizes_menuitem_text_add_gap = h*(1/100.0);
	/*
	 * Update grassblock position & size:
	*/
	m_img1_sprite.setPosition(m_sizes_grassblock_xoffset, m_sizes_grassblock_yoffset);
	m_img1_sprite.setScale(m_sizes_grassblock/20.0, m_sizes_grassblock/20.0);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem4.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem5.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem6.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem1.setOutlineThickness(m_sizes_menuitem_outline);
	m_menuitem2.setOutlineThickness(m_sizes_menuitem_outline);
	m_menuitem3.setOutlineThickness(m_sizes_menuitem_outline);
	m_menuitem4.setOutlineThickness(m_sizes_menuitem_outline);
	m_menuitem5.setOutlineThickness(m_sizes_menuitem_outline);
	m_menuitem6.setOutlineThickness(m_sizes_menuitem_outline);
	m_menuitem1.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset);
	m_menuitem2.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap);
	m_menuitem3.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*2);
	m_menuitem4.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*3);
	m_menuitem5.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*4);
	m_menuitem6.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*5+m_sizes_menuitem_gap);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem1_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem2_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem3_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem4_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem5_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem6_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem1_txt.setPosition((w-m_menuitem1_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_text_add_gap);
	m_menuitem2_txt.setPosition((w-m_menuitem2_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+m_sizes_menuitem_text_add_gap);
	m_menuitem3_txt.setPosition((w-m_menuitem3_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*2+m_sizes_menuitem_text_add_gap);
	m_menuitem4_txt.setPosition((w-m_menuitem4_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*3+m_sizes_menuitem_text_add_gap);
	m_menuitem5_txt.setPosition((w-m_menuitem5_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*4+m_sizes_menuitem_text_add_gap);
	m_menuitem6_txt.setPosition((w-m_menuitem6_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*5+m_sizes_menuitem_text_add_gap+m_sizes_menuitem_gap);
	return 0;
}
int MainMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					return -1; // exit
					break;
			}
			break;
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
				else if (mouse_y > m_sizes_menuitem_first_yoffset+5*m_sizes_menuitem_height+5*m_sizes_menuitem_gap+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+6*m_sizes_menuitem_height+5*m_sizes_menuitem_gap+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 6
					*/
					reset_menuitem_over();
					m_menuitem6_over = 1;
					//std::cout << "#6" << std::endl;
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
					if (m_menuitem6_over == 1)
						return -1; // exit
					else if (m_menuitem4_over == 1)
						return 2; // go to settings menu
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
	m_menuitem6_over = 0;
}
sf::Sprite MainMenu::get_grassblock(void)
{
	return m_img1_sprite;
}
sf::RectangleShape MainMenu::get_menuitem1(void)
{
	if (m_menuitem1_over == 1)
		m_menuitem1.setFillColor(sf::Color(115, 228, 71));
	else
		m_menuitem1.setFillColor(sf::Color(73, 186, 29));
	return m_menuitem1;
}
sf::RectangleShape MainMenu::get_menuitem2(void)
{
	if (m_menuitem2_over == 1)
		m_menuitem2.setFillColor(sf::Color(115, 228, 71));
	else
		m_menuitem2.setFillColor(sf::Color(73, 186, 29));
	return m_menuitem2;
}
sf::RectangleShape MainMenu::get_menuitem3(void)
{
	if (m_menuitem3_over == 1)
		m_menuitem3.setFillColor(sf::Color(115, 228, 71));
	else
		m_menuitem3.setFillColor(sf::Color(73, 186, 29));
	return m_menuitem3;
}
sf::RectangleShape MainMenu::get_menuitem4(void)
{
	if (m_menuitem4_over == 1)
		m_menuitem4.setFillColor(sf::Color(115, 228, 71));
	else
		m_menuitem4.setFillColor(sf::Color(73, 186, 29));
	return m_menuitem4;
}
sf::RectangleShape MainMenu::get_menuitem5(void)
{
	if (m_menuitem5_over == 1)
		m_menuitem5.setFillColor(sf::Color(115, 228, 71));
	else
		m_menuitem5.setFillColor(sf::Color(73, 186, 29));
	return m_menuitem5;
}
sf::RectangleShape MainMenu::get_menuitem6(void)
{
	if (m_menuitem6_over == 1)
		m_menuitem6.setFillColor(sf::Color(115, 228, 71));
	else
		m_menuitem6.setFillColor(sf::Color(73, 186, 29));
	return m_menuitem6;
}
sf::Text MainMenu::get_menuitem1_txt(void)
{
	return m_menuitem1_txt;
}
sf::Text MainMenu::get_menuitem2_txt(void)
{
	return m_menuitem2_txt;
}
sf::Text MainMenu::get_menuitem3_txt(void)
{
	return m_menuitem3_txt;
}
sf::Text MainMenu::get_menuitem4_txt(void)
{
	return m_menuitem4_txt;
}
sf::Text MainMenu::get_menuitem5_txt(void)
{
	return m_menuitem5_txt;
}
sf::Text MainMenu::get_menuitem6_txt(void)
{
	return m_menuitem6_txt;
}
