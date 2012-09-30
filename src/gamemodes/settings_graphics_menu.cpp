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
int SettingsGraphicsMenu::init(bool fullscreen, int screenw, int screenh)
{
	/*
	 * Init NumericalTextfieldBuffer instances for resolution:
	*/
	m_textfield1_1_buffer.init(4);
	m_textfield1_1_buffer.set(screenw);
	m_textfield1_2_buffer.init(4);
	m_textfield1_2_buffer.set(screenh);
	/*
	 * Init ConfigChooser instance for fullscreen:
	*/
	m_config_chooser2.init(CONFIGVAR_TYPE_BOOLEAN, CONFIGVAR_FULLSCREEN_COUNT);
	m_config_chooser2.add_bool("settings_graphics_menu_entry_value_fullscreen_enabled", true);
	m_config_chooser2.add_bool("settings_graphics_menu_entry_value_fullscreen_disabled", false);
	m_config_chooser2.set_actual_bool(fullscreen);
	/*
	 * Init textfields:
	*/
	m_textfield1_1.setOutlineColor(sf::Color::Black);
	m_textfield1_2.setOutlineColor(sf::Color::Black);
	/*
	 * Init textfield texts:
	*/
	m_textfield1_1_txt.setString(m_textfield1_1_buffer.get_string());
	m_textfield1_2_txt.setString(m_textfield1_2_buffer.get_string());
	m_textfield1_1_txt.setColor(sf::Color::Black);
	m_textfield1_2_txt.setColor(sf::Color::Black);
	/*
	 * Init arrows:
	*/
	if (!m_arrow_left.loadFromFile("data/arrow_left.png")) /* TODO: add function to get data path */
		return 1;
	if (!m_arrow_right.loadFromFile("data/arrow_right.png")) /* TODO: add function to get data path */
		return 1;
	m_arrow_left2_sprite.setTexture(m_arrow_left);
	m_arrow_right2_sprite.setTexture(m_arrow_right);
	m_arrow_left2_sprite.setColor(sf::Color(255, 255, 255, 255));
	m_arrow_right2_sprite.setColor(sf::Color(255, 255, 255, 255));
	/*
	 * Init menuitem shapes:
	*/
	m_menuitem1.setOutlineColor(sf::Color::Black);
	m_menuitem2.setOutlineColor(sf::Color::Black);
	m_menuitem3.setOutlineColor(sf::Color::Black);
	m_menuitem4.setOutlineColor(sf::Color::Black);
	m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
	m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	/*
	 * Init menuitem headers:
	*/
	m_menuitem1_header.setString(get_wstring(_("settings_graphics_menu_entry_header_resolution")));
	m_menuitem1_header.setColor(sf::Color::Black);
	m_menuitem2_header.setString(get_wstring(_("settings_graphics_menu_entry_header_fullscreen")));
	m_menuitem2_header.setColor(sf::Color::Black);
	/*
	 * Init menuitem values:
	*/
	m_menuitem1_value.setString("x");
	m_menuitem2_value.setString(get_wstring(_(m_config_chooser2.get_actual_showable().c_str())));
	m_menuitem1_value.setColor(sf::Color::Black);
	m_menuitem2_value.setColor(sf::Color::Black);
	/*
	 * Init menuitem texts:
	*/
	m_menuitem3_txt.setString(get_wstring(_("settings_graphics_menu_entry_save")));
	m_menuitem4_txt.setString(get_wstring(_("settings_graphics_menu_entry_abort")));
	m_menuitem3_txt.setColor(sf::Color::Black);
	m_menuitem4_txt.setColor(sf::Color::Black);
	reset_menuitem_over();
	return 0;
}
int SettingsGraphicsMenu::uninit(void)
{
	return 0;
}
int SettingsGraphicsMenu::calculate_sizes(int w, int h)
{
	/*
	 * Save screen size:
	*/
	m_w = w;
	m_h = h;
	
	m_sizes_menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	m_sizes_menuitem_height = h*(SIZE_MENU_CONFIG_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_height2 = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	m_sizes_menuitem_first_yoffset = h*(SIZE_SETTINGS_SUBMENUS_FIRST_ELEMENT_YOFFSET/100.0);
	m_sizes_menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	m_sizes_textfield_width = w*(SIZE_MENU_SETTINGS_GRAPHICS_RESOLUTION_TEXTFIELD_WIDTH/100.0);
	m_sizes_textfield_height = h*(SIZE_MENU_SETTINGS_GRAPHICS_RESOLUTION_TEXTFIELD_HEIGHT/100.0);
	m_sizes_textfield_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_XGAP/100.0);
	m_sizes_textfield_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_YGAP/100.0);
	m_sizes_arrow_height = h*(SIZE_MENU_CONFIG_ARROW_HEIGHT/100.0);
	m_sizes_arrow_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_ARROW_XGAP/100.0);
	m_sizes_arrow_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_ARROW_YGAP/100.0);
	/*
	 * Menuitem X offset = middle
	*/
	m_sizes_menuitem_xoffset = (w-m_sizes_menuitem_width)/2.0;
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height2));
	m_menuitem4.setSize(sf::Vector2f(m_sizes_menuitem_width, m_sizes_menuitem_height2));
	m_menuitem1.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem2.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem3.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem4.setOutlineThickness(h*(SIZE_MENU_ELEMENT_OUTLINE/100.0));
	m_menuitem1.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset);
	m_menuitem2.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_gap+m_sizes_menuitem_height);
	m_menuitem3.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_gap+2*m_sizes_menuitem_height+m_sizes_menuitem_gap);
	m_menuitem4.setPosition(m_sizes_menuitem_xoffset, m_sizes_menuitem_first_yoffset+3*m_sizes_menuitem_gap+2*m_sizes_menuitem_height+m_sizes_menuitem_height2+m_sizes_menuitem_gap);
	/*
	 * Update menuitem header size & positions:
	*/
	m_menuitem1_header.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_HEADER_SIZE_DIVIDER);
	m_menuitem2_header.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_HEADER_SIZE_DIVIDER);
	m_menuitem1_header.setPosition((w-m_menuitem1_header.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	m_menuitem2_header.setPosition((w-m_menuitem2_header.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_gap+m_sizes_menuitem_height+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0));
	/*
	 * Update menuitem value size & positions:
	*/
	m_menuitem1_value.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_VALUE_SIZE_DIVIDER);
	m_menuitem2_value.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_VALUE_SIZE_DIVIDER);
	m_menuitem1_value.setPosition((w-m_menuitem1_value.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+h*(SIZE_MENU_CONFIG_ELEMENT_VALUE_GAP/100.0));
	m_menuitem2_value.setPosition((w-m_menuitem2_value.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+h*(SIZE_MENU_CONFIG_ELEMENT_VALUE_GAP/100.0));
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem3_txt.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_ELEMENT_TEXT_SIZE_DIVIDER);
	m_menuitem4_txt.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_ELEMENT_TEXT_SIZE_DIVIDER);
	m_menuitem3_txt.setPosition((w-m_menuitem3_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_gap+2*m_sizes_menuitem_height+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+m_sizes_menuitem_gap);
	m_menuitem4_txt.setPosition((w-m_menuitem4_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+3*m_sizes_menuitem_gap+2*m_sizes_menuitem_height+m_sizes_menuitem_height2+h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0)+m_sizes_menuitem_gap);
	/*
	 * Update textfield positions & sizes:
	*/
	m_textfield1_1.setSize(sf::Vector2f(m_sizes_textfield_width, m_sizes_textfield_height));
	m_textfield1_2.setSize(sf::Vector2f(m_sizes_textfield_width, m_sizes_textfield_height));
	m_textfield1_1.setOutlineThickness(h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_OUTLINE/100.0));
	m_textfield1_2.setOutlineThickness(h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_OUTLINE/100.0));
	m_textfield1_1.setPosition(m_sizes_menuitem_xoffset+m_sizes_textfield_xgap, m_sizes_menuitem_first_yoffset+m_sizes_textfield_ygap);
	m_textfield1_2.setPosition(m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_textfield_width-m_sizes_textfield_xgap, m_sizes_menuitem_first_yoffset+m_sizes_textfield_ygap);
	/*
	 * Update textfield text size & positions:
	*/
	m_textfield1_1_txt.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_VALUE_SIZE_DIVIDER);
	m_textfield1_2_txt.setCharacterSize(m_sizes_menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_VALUE_SIZE_DIVIDER);
	m_textfield1_1_txt.setPosition(m_sizes_menuitem_xoffset+m_sizes_textfield_xgap+(m_sizes_textfield_width-m_textfield1_1_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_TEXT_YGAP/100.0));
	m_textfield1_2_txt.setPosition(m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_textfield_width-m_sizes_textfield_xgap+(m_sizes_textfield_width-m_textfield1_2_txt.getGlobalBounds().width)/2.0, m_sizes_menuitem_first_yoffset+h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_TEXT_YGAP/100.0));
	/*
	 * Update arrow positions & sizes:
	*/
	m_arrow_left2_sprite.setPosition(m_sizes_menuitem_xoffset+m_sizes_arrow_xgap, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+m_sizes_arrow_ygap);
	m_arrow_right2_sprite.setPosition(m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_arrow_xgap-m_sizes_arrow_height, m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+m_sizes_arrow_ygap);
	m_arrow_left2_sprite.setScale(m_sizes_arrow_height/7.0, m_sizes_arrow_height/7.0);
	m_arrow_right2_sprite.setScale(m_sizes_arrow_height/7.0, m_sizes_arrow_height/7.0);
	return 0;
}
EventProcessorReturn SettingsGraphicsMenu::process_event(sf::Event event, int mouse_x, int mouse_y)
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
			if (m_textfield1_1_over)
			{
				m_textfield1_1_buffer.handle_keypress(event);
				m_textfield1_1_txt.setString(m_textfield1_1_buffer.get_string());
				calculate_sizes(m_w, m_h);
			}
			else if (m_textfield1_2_over)
			{
				m_textfield1_2_buffer.handle_keypress(event);
				m_textfield1_2_txt.setString(m_textfield1_2_buffer.get_string());
				calculate_sizes(m_w, m_h);
			};
			break;
		case sf::Event::MouseMoved:
			reset_menuitem_over();
			if (mouse_x > m_sizes_menuitem_xoffset && mouse_x < m_sizes_menuitem_xoffset+m_sizes_menuitem_width)
			{
				/*
				 * Cursor is in X range of the menu items
				*/
				if (mouse_y > m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+2*m_sizes_menuitem_gap+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+m_sizes_menuitem_height2+2*m_sizes_menuitem_gap+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 3
					*/
					m_menuitem3_over = 1;
				}
				else if (mouse_y > m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+m_sizes_menuitem_height2+3*m_sizes_menuitem_gap+m_sizes_menuitem_gap && mouse_y < m_sizes_menuitem_first_yoffset+2*m_sizes_menuitem_height+2*m_sizes_menuitem_height2+3*m_sizes_menuitem_gap+m_sizes_menuitem_gap)
				{
					/*
					 * Menuitem 4
					*/
					m_menuitem4_over = 1;
				};
				if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_textfield_ygap && mouse_y < m_sizes_menuitem_first_yoffset+m_sizes_textfield_ygap+m_sizes_textfield_height)
				{
					/*
					 * Cursor is in Y range of the resolution textfields
					*/
					if (mouse_x > m_sizes_menuitem_xoffset+m_sizes_textfield_xgap && mouse_x < m_sizes_menuitem_xoffset+m_sizes_textfield_xgap+m_sizes_textfield_width)
					{
						/*
						 * Textfield 1_1
						*/
						m_textfield1_1_over = 1;
					}
					else if (mouse_x > m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_textfield_width-m_sizes_textfield_xgap && mouse_x < m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_textfield_xgap)
					{
						/*
						 * Textfield 1_2
						*/
						m_textfield1_2_over = 1;
					};
				};
				if (mouse_y > m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+m_sizes_arrow_ygap && mouse_y < m_sizes_menuitem_first_yoffset+m_sizes_menuitem_height+m_sizes_menuitem_gap+m_sizes_arrow_ygap+m_sizes_arrow_height)
				{
					/*
					 * Cursor is in Y range of the fullscreen arrows
					*/
					if (mouse_x > m_sizes_menuitem_xoffset+m_sizes_arrow_xgap &&  mouse_x < m_sizes_menuitem_xoffset+m_sizes_arrow_height+m_sizes_arrow_xgap)
					{
						/*
						 * Arrow Left 2
						*/
						m_arrow_left2_over = 1;
					}
					else if (mouse_x > m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_arrow_xgap-m_sizes_arrow_height && mouse_x < m_sizes_menuitem_xoffset+m_sizes_menuitem_width-m_sizes_arrow_xgap)
					{
						/*
						 * Arrow Right 2
						*/
						m_arrow_right2_over = 1;
					};
				};
			};
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_arrow_left2_over == 1)
					{
						/*
						 * Left Fullscreen Arrow
						*/
						m_config_chooser2.prev();
						m_menuitem2_value.setString(get_wstring(_(m_config_chooser2.get_actual_showable().c_str())));
						calculate_sizes(m_w, m_h);
					}
					else if (m_arrow_right2_over == 1)
					{
						/*
						 * Right Fullscreen Arrow
						*/
						m_config_chooser2.next();
						m_menuitem2_value.setString(get_wstring(_(m_config_chooser2.get_actual_showable().c_str())));
						calculate_sizes(m_w, m_h);
					}
					else if (m_menuitem3_over == 1)
					{
						/*
						 * Save!
						*/
						ConfigVariable var1, var2, var3;
						ret.init_confvars(3);
						/*
						 * Resolution:
						*/
						var1.type = CONFIGVAR_TYPE_INTEGER;
						var1.index = "GRAPHICS__RESOLUTION_X";
						var1.value_int = m_textfield1_1_buffer.get_int();
						ret.add_confvar(var1);
						var2.type = CONFIGVAR_TYPE_INTEGER;
						var2.index = "GRAPHICS__RESOLUTION_Y";
						var2.value_int = m_textfield1_2_buffer.get_int();
						ret.add_confvar(var2);
						/*
						 * Fullscreen:
						*/
						var3.type = CONFIGVAR_TYPE_BOOLEAN;
						var3.index = "GRAPHICS__FULLSCREEN";
						var3.value_bool = m_config_chooser2.get_actual_bool();
						ret.add_confvar(var3);
						/*
						 * Reload:
						*/
						ret.set_reload(true); // reload
					}
					else if (m_menuitem4_over == 1)
						ret.set_gamemode(2); // back to settings menu
					break;
			}
			break;
	}
	return ret;
}
void SettingsGraphicsMenu::reset_menuitem_over(void)
{
	m_textfield1_1_over = 0;
	m_textfield1_2_over = 0;
	m_arrow_left2_over = 0;
	m_arrow_right2_over = 0;
	m_menuitem3_over = 0;
	m_menuitem4_over = 0;
}
UniversalDrawableArray SettingsGraphicsMenu::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * Init UniversalDrawableArray:
	*/
	arr.init(16);
	/*
	 * Add elements:
	*/
	arr.set_rectshape(0, m_menuitem1);
	//
	arr.set_rectshape(1, m_menuitem2);
	//
	if (m_menuitem3_over == 1)
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(2, m_menuitem3);
	//
	if (m_menuitem4_over == 1)
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(3, m_menuitem4);
	//
	arr.set_text(4, m_menuitem1_header);
	//
	arr.set_text(5, m_menuitem2_header);
	//
	arr.set_text(6, m_menuitem1_value);
	//
	arr.set_text(7, m_menuitem2_value);
	//
	arr.set_text(8, m_menuitem3_txt);
	//
	arr.set_text(9, m_menuitem4_txt);
	//
	if (m_textfield1_1_over == 1)
		m_textfield1_1.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD_HOVER);
	else
		m_textfield1_1.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD);
	arr.set_rectshape(10, m_textfield1_1);
	//
	if (m_textfield1_2_over == 1)
		m_textfield1_2.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD_HOVER);
	else
		m_textfield1_2.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD);
	arr.set_rectshape(11, m_textfield1_2);
	//
	arr.set_text(12, m_textfield1_1_txt);
	//
	arr.set_text(13, m_textfield1_2_txt);
	//
	arr.set_sprite(14, m_arrow_left2_sprite);
	//
	arr.set_sprite(15, m_arrow_right2_sprite);
	/*
	 * Return:
	*/
	return arr;
}
