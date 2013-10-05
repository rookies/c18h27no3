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
int SettingsGraphicsMenu::init(Config conf, std::string arg)
{
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	if (!m_font2.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Regular.ttf")))
		return 1;
	/*
	 * Init NumericalTextfieldBuffer instances for resolution:
	*/
	m_textfield1_1_buffer.init(4);
	m_textfield1_1_buffer.set(conf.get("GRAPHICS__RESOLUTION_X").value_int);
	m_textfield1_2_buffer.init(4);
	m_textfield1_2_buffer.set(conf.get("GRAPHICS__RESOLUTION_Y").value_int);
	/*
	 * Init ConfigChooser instance for fullscreen:
	*/
	m_config_chooser2.init(CONFIGVAR_TYPE_BOOLEAN, 2);
	m_config_chooser2.add_bool(__("settings_graphics_menu_entry_value_fullscreen_enabled"), true);
	m_config_chooser2.add_bool(__("settings_graphics_menu_entry_value_fullscreen_disabled"), false);
	m_config_chooser2.set_actual_bool(conf.get("GRAPHICS__FULLSCREEN").value_bool);
	/*
	 * Init textfields:
	*/
	m_textfield1_1.setOutlineColor(sf::Color::Black);
	m_textfield1_2.setOutlineColor(sf::Color::Black);
	/*
	 * Init textfield texts:
	*/
	m_textfield1_1_txt.setString((m_textfield1_1_buffer.get_int()==0)?"auto":m_textfield1_1_buffer.get_string());
	m_textfield1_2_txt.setString((m_textfield1_2_buffer.get_int()==0)?"auto":m_textfield1_2_buffer.get_string());
	m_textfield1_1_txt.setColor(sf::Color::Black);
	m_textfield1_2_txt.setColor(sf::Color::Black);
	m_textfield1_1_txt.setFont(m_font2);
	m_textfield1_2_txt.setFont(m_font2);
	/*
	 * Init arrows:
	*/
	if (!m_arrow_left.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "arrow_left.png")))
		return 1;
	if (!m_arrow_right.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "arrow_right.png")))
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
	m_menuitem2_header.setString(get_wstring(_("settings_graphics_menu_entry_header_fullscreen")));
	m_menuitem1_header.setColor(sf::Color::Black);
	m_menuitem2_header.setColor(sf::Color::Black);
	m_menuitem1_header.setFont(m_font1);
	m_menuitem2_header.setFont(m_font1);
	/*
	 * Init menuitem values:
	*/
	m_menuitem1_value.setString("x");
	m_menuitem2_value.setString(get_wstring(_(m_config_chooser2.get_actual_showable().c_str())));
	m_menuitem1_value.setColor(sf::Color::Black);
	m_menuitem2_value.setColor(sf::Color::Black);
	m_menuitem1_value.setFont(m_font2);
	m_menuitem2_value.setFont(m_font2);
	/*
	 * Init menuitem texts:
	*/
	m_menuitem3_txt.setString(get_wstring(_("settings_graphics_menu_entry_save")));
	m_menuitem4_txt.setString(get_wstring(_("settings_graphics_menu_entry_abort")));
	m_menuitem3_txt.setColor(sf::Color::Black);
	m_menuitem4_txt.setColor(sf::Color::Black);
	m_menuitem3_txt.setFont(m_font1);
	m_menuitem4_txt.setFont(m_font1);
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
	
	int menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	int menuitem_height = h*(SIZE_MENU_CONFIG_ELEMENT_HEIGHT/100.0);
	int menuitem_height2 = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	int menuitem_first_yoffset = h*(SIZE_SETTINGS_SUBMENUS_FIRST_ELEMENT_YOFFSET/100.0);
	int menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	int textfield_width = w*(SIZE_MENU_SETTINGS_GRAPHICS_RESOLUTION_TEXTFIELD_WIDTH/100.0);
	int textfield_height = h*(SIZE_MENU_SETTINGS_GRAPHICS_RESOLUTION_TEXTFIELD_HEIGHT/100.0);
	int textfield_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_XGAP/100.0);
	int textfield_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_YGAP/100.0);
	int arrow_height = h*(SIZE_MENU_CONFIG_ARROW_HEIGHT/100.0);
	int arrow_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_ARROW_XGAP/100.0);
	int arrow_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_ARROW_YGAP/100.0);
	int menuitem_xoffset = (w-menuitem_width)/2.0;
	int element_outline = h*(SIZE_MENU_ELEMENT_OUTLINE/100.0);
	int header_size = menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_HEADER_SIZE_DIVIDER;
	int value_size = menuitem_height2/SIZE_MENU_CONFIG_ELEMENT_VALUE_SIZE_DIVIDER;
	int text_size = menuitem_height2/SIZE_MENU_ELEMENT_TEXT_SIZE_DIVIDER;
	int textfield_outline = h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_OUTLINE/100.0);
	int textfield_text_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_TEXTFIELD_TEXT_YGAP/100.0);
	int text_gap = h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0);
	int value_gap = h*(SIZE_MENU_CONFIG_ELEMENT_VALUE_GAP/100.0);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(menuitem_width, menuitem_height2));
	m_menuitem4.setSize(sf::Vector2f(menuitem_width, menuitem_height2));
	m_menuitem1.setOutlineThickness(element_outline);
	m_menuitem2.setOutlineThickness(element_outline);
	m_menuitem3.setOutlineThickness(element_outline);
	m_menuitem4.setOutlineThickness(element_outline);
	m_menuitem1.setPosition(menuitem_xoffset, menuitem_first_yoffset);
	m_menuitem2.setPosition(menuitem_xoffset, menuitem_first_yoffset+menuitem_gap+menuitem_height);
	m_menuitem3.setPosition(menuitem_xoffset, menuitem_first_yoffset+2*menuitem_gap+2*menuitem_height+menuitem_gap);
	m_menuitem4.setPosition(menuitem_xoffset, menuitem_first_yoffset+3*menuitem_gap+2*menuitem_height+menuitem_height2+menuitem_gap);
	/*
	 * Update menuitem header size & positions:
	*/
	m_menuitem1_header.setCharacterSize(header_size);
	m_menuitem2_header.setCharacterSize(header_size);
	m_menuitem1_header.setPosition((w-(int)m_menuitem1_header.getGlobalBounds().width)/2, menuitem_first_yoffset+text_gap);
	m_menuitem2_header.setPosition((w-(int)m_menuitem2_header.getGlobalBounds().width)/2, menuitem_first_yoffset+menuitem_gap+menuitem_height+text_gap);
	/*
	 * Update menuitem value size & positions:
	*/
	m_menuitem1_value.setCharacterSize(value_size);
	m_menuitem2_value.setCharacterSize(value_size);
	m_menuitem1_value.setPosition((w-(int)m_menuitem1_value.getGlobalBounds().width)/2, menuitem_first_yoffset+text_gap+value_gap);
	m_menuitem2_value.setPosition((w-(int)m_menuitem2_value.getGlobalBounds().width)/2, menuitem_first_yoffset+menuitem_height+menuitem_gap+text_gap+value_gap);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem3_txt.setCharacterSize(text_size);
	m_menuitem4_txt.setCharacterSize(text_size);
	m_menuitem3_txt.setPosition((w-(int)m_menuitem3_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+2*menuitem_gap+2*menuitem_height+text_gap+menuitem_gap);
	m_menuitem4_txt.setPosition((w-(int)m_menuitem4_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+3*menuitem_gap+2*menuitem_height+menuitem_height2+text_gap+menuitem_gap);
	/*
	 * Update textfield positions & sizes:
	*/
	m_textfield1_1.setSize(sf::Vector2f(textfield_width, textfield_height));
	m_textfield1_2.setSize(sf::Vector2f(textfield_width, textfield_height));
	m_textfield1_1.setOutlineThickness(textfield_outline);
	m_textfield1_2.setOutlineThickness(textfield_outline);
	m_textfield1_1.setPosition(menuitem_xoffset+textfield_xgap, menuitem_first_yoffset+textfield_ygap);
	m_textfield1_2.setPosition(menuitem_xoffset+menuitem_width-textfield_width-textfield_xgap, menuitem_first_yoffset+textfield_ygap);
	/*
	 * Update textfield text size & positions:
	*/
	m_textfield1_1_txt.setCharacterSize(value_size);
	m_textfield1_2_txt.setCharacterSize(value_size);
	m_textfield1_1_txt.setPosition(menuitem_xoffset+textfield_xgap+(textfield_width-(int)m_textfield1_1_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+textfield_text_ygap);
	m_textfield1_2_txt.setPosition(menuitem_xoffset+menuitem_width-textfield_width-textfield_xgap+(textfield_width-(int)m_textfield1_2_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+textfield_text_ygap);
	/*
	 * Update arrow positions & sizes:
	*/
	m_arrow_left2_sprite.setPosition(menuitem_xoffset+arrow_xgap, menuitem_first_yoffset+menuitem_height+menuitem_gap+arrow_ygap);
	m_arrow_right2_sprite.setPosition(menuitem_xoffset+menuitem_width-arrow_xgap-arrow_height, menuitem_first_yoffset+menuitem_height+menuitem_gap+arrow_ygap);
	m_arrow_left2_sprite.setScale(arrow_height/7, arrow_height/7);
	m_arrow_right2_sprite.setScale(arrow_height/7, arrow_height/7);
	return 0;
}
void SettingsGraphicsMenu::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
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
			if (m_textfield1_1_over)
			{
				m_textfield1_1_buffer.handle_keypress(event);
				m_textfield1_1_txt.setString((m_textfield1_1_buffer.get_int()==0)?"auto":m_textfield1_1_buffer.get_string());
				calculate_sizes(m_w, m_h);
			}
			else if (m_textfield1_2_over)
			{
				m_textfield1_2_buffer.handle_keypress(event);
				m_textfield1_2_txt.setString((m_textfield1_2_buffer.get_int()==0)?"auto":m_textfield1_2_buffer.get_string());
				calculate_sizes(m_w, m_h);
			};
			break;
		case sf::Event::MouseMoved:
			reset_menuitem_over();
			if (m_menuitem3.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem3_over = 1;
			else if (m_menuitem4.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem4_over = 1;
			else if (m_textfield1_1.getGlobalBounds().contains(mouse_x, mouse_y))
				m_textfield1_1_over = 1;
			else if (m_textfield1_2.getGlobalBounds().contains(mouse_x, mouse_y))
				m_textfield1_2_over = 1;
			else if (m_arrow_left2_sprite.getGlobalBounds().contains(mouse_x, mouse_y))
				m_arrow_left2_over = 1;
			else if (m_arrow_right2_sprite.getGlobalBounds().contains(mouse_x, mouse_y))
				m_arrow_right2_over = 1;
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
						ret->init_confvars(3);
						/*
						 * Resolution:
						*/
						var1.type = CONFIGVAR_TYPE_INTEGER;
						var1.index = "GRAPHICS__RESOLUTION_X";
						var1.value_int = (m_textfield1_1_buffer.get_int() < SCREENWIDTH_MIN)?SCREENWIDTH_MIN:((m_textfield1_1_buffer.get_int() > SCREENWIDTH_MAX)?SCREENWIDTH_MAX:m_textfield1_1_buffer.get_int());
						ret->add_confvar(var1);
						var2.type = CONFIGVAR_TYPE_INTEGER;
						var2.index = "GRAPHICS__RESOLUTION_Y";
						var2.value_int = (m_textfield1_2_buffer.get_int() < SCREENHEIGHT_MIN)?SCREENHEIGHT_MIN:((m_textfield1_2_buffer.get_int() > SCREENHEIGHT_MAX)?SCREENHEIGHT_MAX:m_textfield1_2_buffer.get_int());
						ret->add_confvar(var2);
						/*
						 * Fullscreen:
						*/
						var3.type = CONFIGVAR_TYPE_BOOLEAN;
						var3.index = "GRAPHICS__FULLSCREEN";
						var3.value_bool = m_config_chooser2.get_actual_bool();
						ret->add_confvar(var3);
						/*
						 * Reload:
						*/
						ret->set_reload(true); // reload
					}
					else if (m_menuitem4_over == 1)
						ret->set_gamemode(2); // back to settings menu
					break;
			}
			break;
	}
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
	arr.add_rectshape(m_menuitem1);
	//
	arr.add_rectshape(m_menuitem2);
	//
	if (m_menuitem3_over == 1)
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem3);
	//
	if (m_menuitem4_over == 1)
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem4);
	//
	arr.add_text(m_menuitem1_header);
	//
	arr.add_text(m_menuitem2_header);
	//
	arr.add_text(m_menuitem1_value);
	//
	arr.add_text(m_menuitem2_value);
	//
	arr.add_text(m_menuitem3_txt);
	//
	arr.add_text(m_menuitem4_txt);
	//
	if (m_textfield1_1_over == 1)
		m_textfield1_1.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD_HOVER);
	else
		m_textfield1_1.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD);
	arr.add_rectshape(m_textfield1_1);
	//
	if (m_textfield1_2_over == 1)
		m_textfield1_2.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD_HOVER);
	else
		m_textfield1_2.setFillColor(COLOR_MENU_CONFIG_ELEMENT_TEXTFIELD);
	arr.add_rectshape(m_textfield1_2);
	//
	arr.add_text(m_textfield1_1_txt);
	//
	arr.add_text(m_textfield1_2_txt);
	//
	arr.add_sprite(m_arrow_left2_sprite);
	//
	arr.add_sprite(m_arrow_right2_sprite);
	/*
	 * Return:
	*/
	return arr;
}
