/*
 * settings_control_menu.cpp
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
#include "settings_control_menu.hpp"
SettingsControlMenu::SettingsControlMenu()
{
	
}
SettingsControlMenu::~SettingsControlMenu()
{
	
}
int SettingsControlMenu::init(void)
{
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	/*
	 * Init menuitem shapes:
	*/
	m_menuitem1.setOutlineColor(sf::Color::Black);
	m_menuitem2.setOutlineColor(sf::Color::Black);
	m_menuitem3.setOutlineColor(sf::Color::Black);
	m_menuitem4.setOutlineColor(sf::Color::Black);
	m_menuitem5.setOutlineColor(sf::Color::Black);
	m_menuitem7.setOutlineColor(sf::Color::Black);
	m_menuitem8.setOutlineColor(sf::Color::Black);
	
	/*
	 * Init menuitem texts:
	*/
	m_menuitem7_txt.setString(get_wstring(_("settings_control_menu_entry_save")));
	m_menuitem8_txt.setString(get_wstring(_("settings_menu_entry_abort")));
	m_menuitem7_txt.setColor(sf::Color::Black);
	m_menuitem8_txt.setColor(sf::Color::Black);
	m_menuitem7_txt.setFont(m_font1);
	m_menuitem8_txt.setFont(m_font1);
	return 0;
}
int SettingsControlMenu::uninit(void)
{
	return 0;
}
int SettingsControlMenu::calculate_sizes(int w, int h)
{
	/*
	 * Variable definitions:
	*/
	int menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	int menuitem_height = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	int menuitem_first_yoffset = h*(SIZE_SETTINGS_SUBMENUS_FIRST_ELEMENT_YOFFSET/100.0);
	int menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	int menuitem_xoffset = (w-menuitem_width)/2.0;
	int element_outline = h*(SIZE_MENU_ELEMENT_OUTLINE/100.0);
	int text_gap = h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem4.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem5.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem7.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem8.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem1.setOutlineThickness(element_outline);
	m_menuitem2.setOutlineThickness(element_outline);
	m_menuitem3.setOutlineThickness(element_outline);
	m_menuitem4.setOutlineThickness(element_outline);
	m_menuitem5.setOutlineThickness(element_outline);
	m_menuitem7.setOutlineThickness(element_outline);
	m_menuitem8.setOutlineThickness(element_outline);
	m_menuitem1.setPosition(menuitem_xoffset, menuitem_first_yoffset);
	m_menuitem2.setPosition(menuitem_xoffset, menuitem_first_yoffset+menuitem_height+menuitem_gap);
	m_menuitem3.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*2);
	m_menuitem4.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*3);
	m_menuitem5.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*4);
	m_menuitem7.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*5+menuitem_gap);
	m_menuitem8.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*6+menuitem_gap);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem7_txt.setCharacterSize(menuitem_height/2);
	m_menuitem8_txt.setCharacterSize(menuitem_height/2);
	m_menuitem7_txt.setPosition((w-(int)m_menuitem7_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*5+text_gap+menuitem_gap);
	m_menuitem8_txt.setPosition((w-(int)m_menuitem8_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*6+text_gap+menuitem_gap);
	return 0;
}
EventProcessorReturn SettingsControlMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
{
	/*
	 * Variable declarations:
	*/
	EventProcessorReturn ret;
	
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret.set_gamemode(2); // back to settings menu
					break;
			}
			break;
	}
	return ret;
}
UniversalDrawableArray SettingsControlMenu::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * Init UniversalDrawableArray:
	*/
	arr.init(9);
	/*
	 * Add elements:
	*/
	arr.set_rectshape(0, m_menuitem1);
	//
	arr.set_rectshape(1, m_menuitem2);
	//
	arr.set_rectshape(2, m_menuitem3);
	//
	arr.set_rectshape(3, m_menuitem4);
	//
	arr.set_rectshape(4, m_menuitem5);
	//
	arr.set_rectshape(5, m_menuitem7);
	//
	arr.set_text(6, m_menuitem7_txt);
	//
	arr.set_rectshape(7, m_menuitem8);
	//
	arr.set_text(8, m_menuitem8_txt);
	/*
	 * Return:
	*/
	return arr;
}
