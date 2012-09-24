/*
 * settings_menu.cpp
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
#include "settings_menu.hpp"

SettingsMenu::SettingsMenu()
{
	
}
SettingsMenu::~SettingsMenu()
{
	
}
int SettingsMenu::init(void)
{
	/*
	 * Init creeper:
	*/
	m_img1.loadFromFile("data/creeper.png");
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
	/*
	 * Init menuitem texts:
	*/
	m_menuitem1_txt.setString(get_wstring(_("settings_menu_entry_general")));
	m_menuitem2_txt.setString(get_wstring(_("settings_menu_entry_graphics")));
	m_menuitem3_txt.setString(get_wstring(_("settings_menu_entry_control")));
	m_menuitem4_txt.setString(get_wstring(_("settings_menu_entry_sound")));
	m_menuitem5_txt.setString(get_wstring(_("settings_menu_entry_back")));
	m_menuitem1_txt.setColor(sf::Color::Black);
	m_menuitem2_txt.setColor(sf::Color::Black);
	m_menuitem3_txt.setColor(sf::Color::Black);
	m_menuitem4_txt.setColor(sf::Color::Black);
	m_menuitem5_txt.setColor(sf::Color::Black);
	reset_menuitem_over();
	return 0;
}
int SettingsMenu::uninit(void)
{
	return 0;
}
int SettingsMenu::calculate_sizes(int w, int h)
{
	/*
	 * Variable declarations:
	*/
	int creeper_height;
	
	m_sizes_menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	m_sizes_menuitem_height = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_first_yoffset = h*(SIZE_MENU_FIRST_ELEMENT_YOFFSET/100.0);
	m_sizes_menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	creeper_height = h*(SIZE_SETTINGSMENU_CREEPER_HEIGHT/100.0);
	/*
	 * Menuitem X offset = middle
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2.0;
	/*
	 * Update creeper position & size:
	*/
	m_img1_sprite.setPosition((w-creeper_height)/2.0, h*(SIZE_SETTINGSMENU_CREEPER_YOFFSET/100.0));
	m_img1_sprite.setScale(creeper_height/98.0, creeper_height/98.0);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem4.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem5.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem1.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem2.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem3.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem4.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem5.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem1.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset);
	m_menuitem2.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap);
	m_menuitem3.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*2);
	m_menuitem4.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*3);
	m_menuitem5.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*4+m_sizes_menuitem_gap);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem1_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem2_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem3_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem4_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem5_txt.setCharacterSize(m_sizes_menuitem_height/2.0);
	m_menuitem1_txt.setPosition((w-m_menuitem1_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem2_txt.setPosition((w-m_menuitem2_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem3_txt.setPosition((w-m_menuitem3_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*2+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem4_txt.setPosition((w-m_menuitem4_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*3+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem5_txt.setPosition((w-m_menuitem5_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+(m_sizes_menuitem_height+m_sizes_menuitem_gap)*4+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+m_sizes_menuitem_gap);
	return 0;
}
int SettingsMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					return 1; // back to gamemode 1 (main menu)
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
				else if (mouse_y > m_sizes_menuitem_first_yoffset+4*m_sizes_menuitem_height+4*m_sizes_menuitem_gap+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+5*m_sizes_menuitem_height+4*m_sizes_menuitem_gap+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 5
					*/
					reset_menuitem_over();
					m_menuitem5_over = 1;
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
					if (m_menuitem1_over == 1)
						return 3; // go to settings general menu
					else if (m_menuitem2_over == 1)
						return 4; // go to settings graphics menu
					else if (m_menuitem3_over == 1)
						return 5; // go to settings control menu
					else if (m_menuitem4_over == 1)
						return 6; // go to settings sound menu
					else if (m_menuitem5_over == 1)
						return 1; // back to main menu
					break;
			}
			break;
	}
	return 0;
}
void SettingsMenu::reset_menuitem_over(void)
{
	m_menuitem1_over = 0;
	m_menuitem2_over = 0;
	m_menuitem3_over = 0;
	m_menuitem4_over = 0;
	m_menuitem5_over = 0;
}
sf::Sprite SettingsMenu::get_creeper(void)
{
	return m_img1_sprite;
}
sf::RectangleShape SettingsMenu::get_menuitem1(void)
{
	if (m_menuitem1_over == 1)
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem1;
}
sf::RectangleShape SettingsMenu::get_menuitem2(void)
{
	if (m_menuitem2_over == 1)
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem2;
}
sf::RectangleShape SettingsMenu::get_menuitem3(void)
{
	if (m_menuitem3_over == 1)
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem3;
}
sf::RectangleShape SettingsMenu::get_menuitem4(void)
{
	if (m_menuitem4_over == 1)
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem4;
}
sf::RectangleShape SettingsMenu::get_menuitem5(void)
{
	if (m_menuitem5_over == 1)
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem5;
}
sf::Text SettingsMenu::get_menuitem1_txt(void)
{
	return m_menuitem1_txt;
}
sf::Text SettingsMenu::get_menuitem2_txt(void)
{
	return m_menuitem2_txt;
}
sf::Text SettingsMenu::get_menuitem3_txt(void)
{
	return m_menuitem3_txt;
}
sf::Text SettingsMenu::get_menuitem4_txt(void)
{
	return m_menuitem4_txt;
}
sf::Text SettingsMenu::get_menuitem5_txt(void)
{
	return m_menuitem5_txt;
}
