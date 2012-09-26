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
	if (!m_img1.loadFromFile("data/grass.png"))
		return 1;
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
	m_menuitem1_txt.setString(get_wstring(_("main_menu_entry_newgame")));
	m_menuitem2_txt.setString(get_wstring(_("main_menu_entry_loadgame")));
	m_menuitem3_txt.setString(get_wstring(_("main_menu_entry_leveleditor")));
	m_menuitem4_txt.setString(get_wstring(_("main_menu_entry_settings")));
	m_menuitem5_txt.setString(get_wstring(_("main_menu_entry_credits")));
	m_menuitem6_txt.setString(get_wstring(_("main_menu_entry_exit")));
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
	 * Variable declarations:
	*/
	int grassblock_height;
	
	m_sizes_menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	m_sizes_menuitem_height = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	std::cout << m_sizes_menuitem_height << std::endl;
	m_sizes_menuitem_first_yoffset = h*(SIZE_MENU_FIRST_ELEMENT_YOFFSET/100.0);
	m_sizes_menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	grassblock_height = h*(SIZE_MAINMENU_GRASSBLOCK_HEIGHT/100.0);
	/*
	 * Menuitem X offset = middle
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2.0;
	/*
	 * Update grassblock position & size:
	*/
	m_img1_sprite.setPosition((w-grassblock_height)/2.0, h*(SIZE_MAINMENU_GRASSBLOCK_YOFFSET/100.0));
	m_img1_sprite.setScale(grassblock_height/20.0, grassblock_height/20.0);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem4.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem5.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem6.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem1.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem2.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem3.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem4.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem5.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem6.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
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
	m_menuitem1_txt.setPosition((w-m_menuitem1_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem2_txt.setPosition((w-m_menuitem2_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem3_txt.setPosition((w-m_menuitem3_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*2+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem4_txt.setPosition((w-m_menuitem4_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*3+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem5_txt.setPosition((w-m_menuitem5_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*4+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem6_txt.setPosition((w-m_menuitem6_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*5+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+m_sizes_menuitem_gap);
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
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 2
					*/
					reset_menuitem_over();
					m_menuitem2_over = 1;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+2*m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+3*m_sizes_menuitem_height+2*m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 3
					*/
					reset_menuitem_over();
					m_menuitem3_over = 1;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+3*m_sizes_menuitem_height+3*m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+4*m_sizes_menuitem_height+3*m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 4
					*/
					reset_menuitem_over();
					m_menuitem4_over = 1;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+4*m_sizes_menuitem_height+4*m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+5*m_sizes_menuitem_height+4*m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 5
					*/
					reset_menuitem_over();
					m_menuitem5_over = 1;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+5*m_sizes_menuitem_height+5*m_sizes_menuitem_gap+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+6*m_sizes_menuitem_height+5*m_sizes_menuitem_gap+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 6
					*/
					reset_menuitem_over();
					m_menuitem6_over = 1;
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
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem1;
}
sf::RectangleShape MainMenu::get_menuitem2(void)
{
	if (m_menuitem2_over == 1)
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem2;
}
sf::RectangleShape MainMenu::get_menuitem3(void)
{
	if (m_menuitem3_over == 1)
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem3;
}
sf::RectangleShape MainMenu::get_menuitem4(void)
{
	if (m_menuitem4_over == 1)
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem4;
}
sf::RectangleShape MainMenu::get_menuitem5(void)
{
	if (m_menuitem5_over == 1)
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem5;
}
sf::RectangleShape MainMenu::get_menuitem6(void)
{
	if (m_menuitem6_over == 1)
		m_menuitem6.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem6.setFillColor(COLOR_MENU_ELEMENT);
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
