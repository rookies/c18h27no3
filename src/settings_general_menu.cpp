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
	 * Init ConfigChooser instance for language:
	*/
	m_config_chooser1.init(CONFIGVAR_TYPE_STRING, CONFIGVAR_LANGUAGE_COUNT);
	m_config_chooser1.add_string("English", "en");
	m_config_chooser1.add_string("Deutsch", "de");
	m_config_chooser1.set_actual_string(getenv("LANGUAGE"));
	/*
	 * Init arrows:
	*/
	if (!m_arrow_left.loadFromFile("data/arrow_left.png"))
		return 1;
	if (!m_arrow_right.loadFromFile("data/arrow_right.png"))
		return 1;
	m_arrow_left1_sprite.setTexture(m_arrow_left);
	m_arrow_right1_sprite.setTexture(m_arrow_right);
	m_arrow_left1_sprite.setColor(sf::Color(255, 255, 255, 255));
	m_arrow_right1_sprite.setColor(sf::Color(255, 255, 255, 255));
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
	m_menuitem1_value.setString(get_wstring(m_config_chooser1.get_actual_showable()));
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
	/*
	 * Save screen sizes:
	*/
	m_w = w;
	m_h = h;
	
	m_sizes_menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	m_sizes_menuitem_height = h*(SIZE_MENU_CONFIG_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_height2 = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_first_yoffset = h*(SIZE_SETTINGS_SUBMENUS_FIRST_ELEMENT_YOFFSET/100.0);
	m_sizes_menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	m_sizes_arrow_height = h*(SIZE_MENU_CONFIG_ARROW_HEIGHT/100.0);
	m_sizes_arrow_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_ARROW_XGAP)/100.0;
	m_sizes_arrow_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_ARROW_YGAP)/100.0;
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
	/*
	 * Update arrow positions & sizes:
	*/
	m_arrow_left1_sprite.setPosition(m_sizes_menuitem_xoffset+m_sizes_arrow_xgap, m_sizes_menuitem_first_yoffset+m_sizes_arrow_ygap);
	m_arrow_right1_sprite.setPosition(m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_arrow_xgap-m_sizes_arrow_height, m_sizes_menuitem_first_yoffset+m_sizes_arrow_ygap);
	m_arrow_left1_sprite.setScale(m_sizes_arrow_height/7.0, m_sizes_arrow_height/7.0);
	m_arrow_right1_sprite.setScale(m_sizes_arrow_height/7.0, m_sizes_arrow_height/7.0);
	return 0;
}
EventProcessorReturn SettingsGeneralMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
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
				if (mouse_x > m_sizes_menuitem_xoffset+m_sizes_arrow_xgap &&  mouse_x < m_sizes_menuitem_xoffset+m_sizes_arrow_height+m_sizes_arrow_xgap)
				{
					/*
					 * Cursor is in X range of the left arrows
					*/
					if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_arrow_ygap && mouse_y < m_sizes_menuitem_first_yoffset+m_sizes_arrow_ygap+m_sizes_arrow_height)
					{
						/*
						 * Arrow Left 1
						*/
						reset_menuitem_over();
						m_arrow_left1_over = 1;
					}
					else
						reset_menuitem_over();
				}
				else if (mouse_x > m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_arrow_xgap-m_sizes_arrow_height && mouse_x < m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_arrow_xgap)
				{
					/*
					 * Cursor is in X range of the right arrows
					*/
					if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_arrow_ygap && mouse_y < m_sizes_menuitem_first_yoffset+m_sizes_arrow_ygap+m_sizes_arrow_height)
					{
						/*
						 * Arrow Right 1
						*/
						reset_menuitem_over();
						m_arrow_right1_over = 1;
					}
					else
						reset_menuitem_over();
				};
			}
			else
				reset_menuitem_over();
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_menuitem2_over == 1)
					{
						/*
						 * Save!
						 * Language:
						*/
						ConfigVariable var;
						ret.set_language(m_config_chooser1.get_actual_string());
						ret.init_confvars(1); // confvar count = 1
						var.type = CONFIGVAR_TYPE_STRING;
						var.index = "GENERAL__LANGUAGE";
						var.value_string = m_config_chooser1.get_actual_string();
						ret.add_confvar(var);
						ret.set_gamemode(2); // back to settings menu
					}
					else if (m_menuitem3_over == 1)
						ret.set_gamemode(2); // back to settings menu
					else if (m_arrow_left1_over == 1)
					{
						/*
						 * Left Language Arrow
						*/
						m_config_chooser1.prev();
						m_menuitem1_value.setString(get_wstring(m_config_chooser1.get_actual_showable()));
						calculate_sizes(m_w, m_h);
					}
					else if (m_arrow_right1_over == 1)
					{
						/*
						 * Right Language Arrow
						*/
						m_config_chooser1.next();
						m_menuitem1_value.setString(get_wstring(m_config_chooser1.get_actual_showable()));
						calculate_sizes(m_w, m_h);
					}
					break;
			}
			break;
	}
	return ret;
}
void SettingsGeneralMenu::reset_menuitem_over(void)
{
	m_menuitem2_over = 0;
	m_menuitem3_over = 0;
	m_arrow_left1_over = 0;
	m_arrow_right1_over = 0;
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
sf::Sprite SettingsGeneralMenu::get_arrow_left1(void)
{
	return m_arrow_left1_sprite;
}
sf::Sprite SettingsGeneralMenu::get_arrow_right1(void)
{
	return m_arrow_right1_sprite;
}
