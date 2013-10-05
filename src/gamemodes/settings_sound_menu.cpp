/*
 * settings_sound_menu.cpp
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
#include "settings_sound_menu.hpp"
SettingsSoundMenu::SettingsSoundMenu()
{
	
}
SettingsSoundMenu::~SettingsSoundMenu()
{
	
}
int SettingsSoundMenu::init(Config conf, std::string arg)
{
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	if (!m_font2.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Regular.ttf")))
		return 1;
	/*
	 * Init ConfigChooser instance for menu music volume:
	*/
	m_config_chooser1.init(CONFIGVAR_TYPE_INTEGER, 11);
	m_config_chooser1.add_int("  0 %", 0);
	m_config_chooser1.add_int(" 10 %", 10);
	m_config_chooser1.add_int(" 20 %", 20);
	m_config_chooser1.add_int(" 30 %", 30);
	m_config_chooser1.add_int(" 40 %", 40);
	m_config_chooser1.add_int(" 50 %", 50);
	m_config_chooser1.add_int(" 60 %", 60);
	m_config_chooser1.add_int(" 70 %", 70);
	m_config_chooser1.add_int(" 80 %", 80);
	m_config_chooser1.add_int(" 90 %", 90);
	m_config_chooser1.add_int("100 %", 100);
	m_config_chooser1.set_actual_int(conf.get("SOUND__MENU_MUSIC_VOLUME").value_int);
	/*
	 * Init arrows:
	*/
	if (!m_arrow_left.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "arrow_left.png")))
		return 1;
	if (!m_arrow_right.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "arrow_right.png")))
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
	m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	/*
	 * Init menuitem headers:
	*/
	m_menuitem1_header.setString(get_wstring(_("settings_sound_menu_entry_header_menu_music_volume")));
	m_menuitem1_header.setColor(sf::Color::Black);
	m_menuitem1_header.setFont(m_font1);
	/*
	 * Init menuitem values:
	*/
	m_menuitem1_value.setString(get_wstring(m_config_chooser1.get_actual_showable()));
	m_menuitem1_value.setColor(sf::Color::Black);
	m_menuitem1_value.setFont(m_font2);
	/*
	 * Init menuitem texts:
	*/
	m_menuitem2_txt.setString(get_wstring(_("settings_sound_menu_entry_save")));
	m_menuitem3_txt.setString(get_wstring(_("settings_sound_menu_entry_abort")));
	m_menuitem2_txt.setColor(sf::Color::Black);
	m_menuitem3_txt.setColor(sf::Color::Black);
	m_menuitem2_txt.setFont(m_font1);
	m_menuitem3_txt.setFont(m_font1);
	reset_menuitem_over();
	return 0;
}
int SettingsSoundMenu::uninit(void)
{
	return 0;
}
int SettingsSoundMenu::calculate_sizes(int w, int h)
{
	/*
	 * Save screen sizes:
	*/
	m_w = w;
	m_h = h;
	
	int menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	int menuitem_height = h*(SIZE_MENU_CONFIG_ELEMENT_HEIGHT/100.0);
	int menuitem_height2 = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	int menuitem_first_yoffset = h*(SIZE_SETTINGS_SUBMENUS_FIRST_ELEMENT_YOFFSET/100.0);
	int menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	int arrow_height = h*(SIZE_MENU_CONFIG_ARROW_HEIGHT/100.0);
	int arrow_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_ARROW_XGAP)/100.0;
	int arrow_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_ARROW_YGAP)/100.0;
	int menuitem_xoffset = (w-menuitem_width)/2.0;
	int element_outline = h*(SIZE_MENU_ELEMENT_OUTLINE/100.0);
	int header_size = menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_HEADER_SIZE_DIVIDER;
	int text_gap = h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0);
	int value_size = menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_VALUE_SIZE_DIVIDER;
	int value_gap = h*(SIZE_MENU_CONFIG_ELEMENT_VALUE_GAP/100.0);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(menuitem_width, menuitem_height2));
	m_menuitem3.setSize(sf::Vector2f(menuitem_width, menuitem_height2));
	m_menuitem1.setOutlineThickness(element_outline);
	m_menuitem2.setOutlineThickness(element_outline);
	m_menuitem3.setOutlineThickness(element_outline);
	m_menuitem1.setPosition(menuitem_xoffset, menuitem_first_yoffset);
	m_menuitem2.setPosition(menuitem_xoffset, menuitem_first_yoffset+2*menuitem_gap+menuitem_height);
	m_menuitem3.setPosition(menuitem_xoffset, menuitem_first_yoffset+2*menuitem_gap+menuitem_height+menuitem_gap+menuitem_height2);
	/*
	 * Update menuitem header size & positions:
	*/
	m_menuitem1_header.setCharacterSize(header_size);
	m_menuitem1_header.setPosition((w-(int)m_menuitem1_header.getGlobalBounds().width)/2, menuitem_first_yoffset+text_gap);
	/*
	 * Update menuitem value size & positions:
	*/
	m_menuitem1_value.setCharacterSize(value_size);
	m_menuitem1_value.setPosition((w-(int)m_menuitem1_value.getGlobalBounds().width)/2, menuitem_first_yoffset+text_gap+value_gap);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem2_txt.setCharacterSize(menuitem_height2/SIZE_MENU_ELEMENT_TEXT_SIZE_DIVIDER);
	m_menuitem3_txt.setCharacterSize(menuitem_height2/SIZE_MENU_ELEMENT_TEXT_SIZE_DIVIDER);
	m_menuitem2_txt.setPosition((w-(int)m_menuitem2_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+2*menuitem_gap+menuitem_height+text_gap);
	m_menuitem3_txt.setPosition((w-(int)m_menuitem3_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+2*menuitem_gap+menuitem_height+menuitem_gap+menuitem_height2+text_gap);
	/*
	 * Update arrow positions & sizes:
	*/
	m_arrow_left1_sprite.setPosition(menuitem_xoffset+arrow_xgap, menuitem_first_yoffset+arrow_ygap);
	m_arrow_right1_sprite.setPosition(menuitem_xoffset+menuitem_width-arrow_xgap-arrow_height, menuitem_first_yoffset+arrow_ygap);
	m_arrow_left1_sprite.setScale(arrow_height/7, arrow_height/7);
	m_arrow_right1_sprite.setScale(arrow_height/7, arrow_height/7);
	return 0;
}
void SettingsSoundMenu::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(2); // back to settings menu
					break;
			}
			break;
		case sf::Event::MouseMoved:
			reset_menuitem_over();
			if (m_menuitem2.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem2_over = 1;
			else if (m_menuitem3.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem3_over = 1;
			else if (m_arrow_left1_sprite.getGlobalBounds().contains(mouse_x, mouse_y))
				m_arrow_left1_over = 1;
			else if (m_arrow_right1_sprite.getGlobalBounds().contains(mouse_x, mouse_y))
				m_arrow_right1_over = 1;
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_arrow_left1_over == 1)
					{
						/*
						 * Left Menu Music Volume Arrow
						*/
						m_config_chooser1.prev();
						m_menuitem1_value.setString(get_wstring(m_config_chooser1.get_actual_showable()));
						calculate_sizes(m_w, m_h);
					}
					else if (m_arrow_right1_over == 1)
					{
						/*
						 * Right Menu Music Volume Arrow
						*/
						m_config_chooser1.next();
						m_menuitem1_value.setString(get_wstring(m_config_chooser1.get_actual_showable()));
						calculate_sizes(m_w, m_h);
					}
					else if (m_menuitem2_over == 1)
					{
						/*
						 * Save!
						*/
						ConfigVariable var1;
						ret->init_confvars(1);
						/*
						 * Menu Music Volume:
						*/
						var1.type = CONFIGVAR_TYPE_INTEGER;
						var1.index = "SOUND__MENU_MUSIC_VOLUME";
						var1.value_int = m_config_chooser1.get_actual_int();
						ret->add_confvar(var1);
						/*
						 * Back to settings menu:
						*/
						ret->set_gamemode(2);
					}
					else if (m_menuitem3_over == 1)
						ret->set_gamemode(2); // back to settings menu
					break;
			}
			break;
	}
}
void SettingsSoundMenu::reset_menuitem_over(void)
{
	m_menuitem2_over = 0;
	m_menuitem3_over = 0;
	m_arrow_left1_over = 0;
	m_arrow_right1_over = 0;
}
UniversalDrawableArray SettingsSoundMenu::get_drawables(void)
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
	arr.add_rectshape(m_menuitem1);
	//
	if (m_menuitem2_over == 1)
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem2);
	//
	if (m_menuitem3_over == 1)
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem3);
	//
	arr.add_text(m_menuitem1_header);
	//
	arr.add_text(m_menuitem1_value);
	//
	arr.add_text(m_menuitem2_txt);
	//
	arr.add_text(m_menuitem3_txt);
	//
	arr.add_sprite(m_arrow_left1_sprite);
	//
	arr.add_sprite(m_arrow_right1_sprite);
	/*
	 * Return:
	*/
	return arr;
}
