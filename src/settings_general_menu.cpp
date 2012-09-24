/*
 * settings_general_menu.cpp
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
#include "settings_general_menu.hpp"
SettingsGeneralMenu::SettingsGeneralMenu()
{
	
}
SettingsGeneralMenu::~SettingsGeneralMenu()
{
	
}
int SettingsGeneralMenu::init(void)
{
	/*
	 * Init menuitem shapes:
	*/
	m_menuitem1.setOutlineColor(sf::Color::Black);
	m_menuitem2.setOutlineColor(sf::Color::Black);
	m_menuitem3.setOutlineColor(sf::Color::Black);
	m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
	/*
	 * Init menuitem headers:
	*/
	m_menuitem1_header.setString(get_wstring(_("settings_general_menu_entry_header_language")));
	m_menuitem1_header.setColor(sf::Color::Black);
	/*
	 * Init menuitem values:
	*/
	m_menuitem1_value.setString(L"<test>Deutsch</test>");
	m_menuitem1_value.setColor(sf::Color::Black);
	/*
	 * Init menuitem texts:
	*/
	m_menuitem2_txt.setString(get_wstring(_("settings_general_menu_entry_save")));
	m_menuitem3_txt.setString(get_wstring(_("settings_general_menu_entry_abort")));
	m_menuitem2_txt.setColor(sf::Color::Black);
	m_menuitem3_txt.setColor(sf::Color::Black);
	reset_menuitem_over();
	return 0;
}
int SettingsGeneralMenu::uninit(void)
{
	return 0;
}
int SettingsGeneralMenu::calculate_sizes(int w, int h)
{
	m_sizes_menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	m_sizes_menuitem_height = h*(SIZE_MENU_CONFIG_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_height2 = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_first_yoffset = h*(SIZE_SETTINGS_SUBMENUS_FIRST_ELEMENT_YOFFSET/100.0);
	m_sizes_menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	/*
	 * Menuitem X offset = middle
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2.0;
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height2));
	m_menuitem3.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height2));
	m_menuitem1.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem2.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem3.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem1.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset);
	m_menuitem2.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_gap+m_sizes_menuitem_height+m_sizes_menuitem_gap);
	m_menuitem3.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_gap+m_sizes_menuitem_height+m_sizes_menuitem_height2+m_sizes_menuitem_gap);
	/*
	 * Update menuitem header size & positions:
	*/
	m_menuitem1_header.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_HEADER_SIZE_DIVIDER);
	m_menuitem1_header.setPosition((w-m_menuitem1_header.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	/*
	 * Update menuitem value size & positions:
	*/
	m_menuitem1_value.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_VALUE_SIZE_DIVIDER);
	m_menuitem1_value.setPosition((w-m_menuitem1_value.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+h*(SIZE_MENU_CONFIG_ELEMENT_VALUE_GAP/100.0));
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem2_txt.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_ELEMENT_TEXT_SIZE_DIVIDER);
	m_menuitem3_txt.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_ELEMENT_TEXT_SIZE_DIVIDER);
	m_menuitem2_txt.setPosition((w-m_menuitem2_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_gap+m_sizes_menuitem_height+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+m_sizes_menuitem_gap);
	m_menuitem3_txt.setPosition((w-m_menuitem3_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_gap+m_sizes_menuitem_height+m_sizes_menuitem_height2+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+m_sizes_menuitem_gap);
	return 0;
}
int SettingsGeneralMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
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
		case sf::Event::MouseMoved:
			if (mouse_x > m_sizes_menuitem_xoffset && mouse_x < m_sizes_menuitem_xoffset+m_sizes_menuitem_width)
			{
				/*
				 * Cursor is in X range of the menu items
				*/
				if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_height2+m_sizes_menuitem_gap+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 2
					*/
					reset_menuitem_over();
					m_menuitem2_over = 1;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_height2+2*m_sizes_menuitem_gap+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+2*m_sizes_menuitem_height2+2*m_sizes_menuitem_gap+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 3
					*/
					reset_menuitem_over();
					m_menuitem3_over = 1;
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
					if (m_menuitem3_over == 1)
						return 2; // back to settings menu
					break;
			}
			break;
	}
	return 0;
}
void SettingsGeneralMenu::reset_menuitem_over(void)
{
	m_menuitem2_over = 0;
	m_menuitem3_over = 0;
}
sf::RectangleShape SettingsGeneralMenu::get_menuitem1(void)
{
	return m_menuitem1;
}
sf::RectangleShape SettingsGeneralMenu::get_menuitem2(void)
{
	if (m_menuitem2_over == 1)
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem2;
}
sf::RectangleShape SettingsGeneralMenu::get_menuitem3(void)
{
	if (m_menuitem3_over == 1)
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
	return m_menuitem3;
}
sf::Text SettingsGeneralMenu::get_menuitem1_header(void)
{
	return m_menuitem1_header;
}
sf::Text SettingsGeneralMenu::get_menuitem1_value(void)
{
	return m_menuitem1_value;
}
sf::Text SettingsGeneralMenu::get_menuitem2_txt(void)
{
	return m_menuitem2_txt;
}
sf::Text SettingsGeneralMenu::get_menuitem3_txt(void)
{
	return m_menuitem3_txt;
}
