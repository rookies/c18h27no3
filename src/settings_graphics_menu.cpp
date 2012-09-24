/*
 * settings_graphics_menu.cpp
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
#include "settings_graphics_menu.hpp"
SettingsGraphicsMenu::SettingsGraphicsMenu()
{
	
}
SettingsGraphicsMenu::~SettingsGraphicsMenu()
{
	
}
int SettingsGraphicsMenu::init(void)
{
	/*
	 * Init menuitem shapes:
	*/
	m_menuitem1.setOutlineColor(sf::Color::Black);
	m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
	m_menuitem2.setOutlineColor(sf::Color::Black);
	m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	/*
	 * Init menuitem headers:
	*/
	m_menuitem1_header.setString(get_wstring(_("settings_graphics_menu_entry_header_resolution")));
	m_menuitem1_header.setColor(sf::Color::Black);
	m_menuitem2_header.setString(get_wstring(_("settings_graphics_menu_entry_header_fullscreen")));
	m_menuitem2_header.setColor(sf::Color::Black);
	return 0;
}
int SettingsGraphicsMenu::uninit(void)
{
	return 0;
}
int SettingsGraphicsMenu::calculate_sizes(int w, int h)
{
	m_sizes_menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	m_sizes_menuitem_height = h*(SIZE_MENU_CONFIG_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_first_yoffset = h*(SIZE_MENU_FIRST_ELEMENT_YOFFSET/100.0);
	m_sizes_menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	/*
	 * Menuitem X offset = middle
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2.0;
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem1.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem2.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem1.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset);
	m_menuitem2.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_gap+m_sizes_menuitem_height);
	/*
	 * Update menuitem header size & positions:
	*/
	m_menuitem1_header.setCharacterSize(h*(SIZE_MENU_ELEMENT_HEIGHT/100.0)/2.0);
	m_menuitem2_header.setCharacterSize(h*(SIZE_MENU_ELEMENT_HEIGHT/100.0)/2.0);
	m_menuitem1_header.setPosition((w-m_menuitem1_header.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem2_header.setPosition((w-m_menuitem2_header.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_gap+m_sizes_menuitem_height+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	return 0;
}
int SettingsGraphicsMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					return 2; // back to settings menu
					break;
			}
			break;
	}
	return 0;
}
sf::RectangleShape SettingsGraphicsMenu::get_menuitem1(void)
{
	return m_menuitem1;
}
sf::Text SettingsGraphicsMenu::get_menuitem1_header(void)
{
	return m_menuitem1_header;
}
sf::RectangleShape SettingsGraphicsMenu::get_menuitem2(void)
{
	return m_menuitem2;
}
sf::Text SettingsGraphicsMenu::get_menuitem2_header(void)
{
	return m_menuitem2_header;
}
