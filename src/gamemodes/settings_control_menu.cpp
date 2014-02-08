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
ControlKeySetting::ControlKeySetting()
{

}
ControlKeySetting::~ControlKeySetting()
{

}
std::string ControlKeySetting::get_config_key(void)
{
	return m_config_key;
}
void ControlKeySetting::set_config_key(std::string key)
{
	m_config_key = key;
}
int ControlKeySetting::get_value(void)
{
	return m_value;
}
void ControlKeySetting::set_value(int value)
{
	m_value = value;
}
std::string ControlKeySetting::get_caption(void)
{
	return m_caption;
}
void ControlKeySetting::set_caption(std::string caption)
{
	m_caption = caption;
}
SettingsControlMenu::SettingsControlMenu()
{
	m_warning_keyused = false;
}
SettingsControlMenu::~SettingsControlMenu()
{
	
}
std::string SettingsControlMenu::keycode2string(int code)
{
	switch (code)
	{
		case sf::Keyboard::A:
			return "A";
		case sf::Keyboard::B:
			return "B";
		case sf::Keyboard::C:
			return "C";
		case sf::Keyboard::D:
			return "D";
		case sf::Keyboard::E:
			return "E";
		case sf::Keyboard::F:
			return "F";
		case sf::Keyboard::G:
			return "G";
		case sf::Keyboard::H:
			return "H";
		case sf::Keyboard::I:
			return "I";
		case sf::Keyboard::J:
			return "J";
		case sf::Keyboard::K:
			return "K";
		case sf::Keyboard::L:
			return "L";
		case sf::Keyboard::M:
			return "M";
		case sf::Keyboard::N:
			return "N";
		case sf::Keyboard::O:
			return "O";
		case sf::Keyboard::P:
			return "P";
		case sf::Keyboard::Q:
			return "Q";
		case sf::Keyboard::R:
			return "R";
		case sf::Keyboard::S:
			return "S";
		case sf::Keyboard::T:
			return "T";
		case sf::Keyboard::U:
			return "U";
		case sf::Keyboard::V:
			return "V";
		case sf::Keyboard::W:
			return "W";
		case sf::Keyboard::X:
			return "X";
		case sf::Keyboard::Y:
			return "Y";
		case sf::Keyboard::Z:
			return "Z";
		case sf::Keyboard::Num0:
			return "0";
		case sf::Keyboard::Num1:
			return "1";
		case sf::Keyboard::Num2:
			return "2";
		case sf::Keyboard::Num3:
			return "3";
		case sf::Keyboard::Num4:
			return "4";
		case sf::Keyboard::Num5:
			return "5";
		case sf::Keyboard::Num6:
			return "6";
		case sf::Keyboard::Num7:
			return "7";
		case sf::Keyboard::Num8:
			return "8";
		case sf::Keyboard::Num9:
			return "9";
		case sf::Keyboard::Numpad0:
			return "Num:0";
		case sf::Keyboard::Numpad1:
			return "Num:1";
		case sf::Keyboard::Numpad2:
			return "Num:2";
		case sf::Keyboard::Numpad3:
			return "Num:3";
		case sf::Keyboard::Numpad4:
			return "Num:4";
		case sf::Keyboard::Numpad5:
			return "Num:5";
		case sf::Keyboard::Numpad6:
			return "Num:6";
		case sf::Keyboard::Numpad7:
			return "Num:7";
		case sf::Keyboard::Numpad8:
			return "Num:8";
		case sf::Keyboard::Numpad9:
			return "Num:9";
		case sf::Keyboard::LControl:
			return _("key_LControl");
		case sf::Keyboard::LShift:
			return _("key_LShift");
		case sf::Keyboard::LAlt:
			return _("key_LAlt");
		case sf::Keyboard::LSystem:
			return _("key_LSystem");
		case sf::Keyboard::RControl:
			return _("key_RControl");
		case sf::Keyboard::RShift:
			return _("key_RShift");
		case sf::Keyboard::RAlt:
			return _("key_RAlt");
		case sf::Keyboard::RSystem:
			return _("key_RSystem");
		case sf::Keyboard::Menu:
			return _("key_Menu");
		case sf::Keyboard::Space:
			return _("key_Space");
		case sf::Keyboard::Return:
			return _("key_Return");
		case sf::Keyboard::BackSpace:
			return _("key_BackSpace");
		case sf::Keyboard::Tab:
			return _("key_Tab");
		case sf::Keyboard::PageUp:
			return _("key_PageUp");
		case sf::Keyboard::PageDown:
			return _("key_PageDown");
		case sf::Keyboard::End:
			return _("key_End");
		case sf::Keyboard::Home:
			return _("key_Home");
		case sf::Keyboard::Insert:
			return _("key_Insert");
		case sf::Keyboard::Delete:
			return _("key_Delete");
		case sf::Keyboard::Left:
			return _("key_Left");
		case sf::Keyboard::Right:
			return _("key_Right");
		case sf::Keyboard::Up:
			return _("key_Up");
		case sf::Keyboard::Down:
			return _("key_Down");
		case sf::Keyboard::Pause:
			return _("key_Pause");
		case sf::Keyboard::F1:
			return "F1";
		case sf::Keyboard::F2:
			return "F2";
		case sf::Keyboard::F3:
			return "F3";
		case sf::Keyboard::F4:
			return "F4";
		case sf::Keyboard::F5:
			return "F5";
		case sf::Keyboard::F6:
			return "F6";
		case sf::Keyboard::F7:
			return "F7";
		case sf::Keyboard::F8:
			return "F8";
		case sf::Keyboard::F9:
			return "F9";
		case sf::Keyboard::F10:
			return "F10";
		case sf::Keyboard::F11:
			return "F11";
		case sf::Keyboard::F12:
			return "F12";
		case sf::Keyboard::LBracket:
			return "[";
		case sf::Keyboard::RBracket:
			return "]";
		case sf::Keyboard::SemiColon:
			return ";";
		case sf::Keyboard::Comma:
			return ",";
		case sf::Keyboard::Period:
			return ".";
		case sf::Keyboard::Quote:
			return "'";
		case sf::Keyboard::Slash:
			return "/";
		case sf::Keyboard::BackSlash:
			return "\\";
		case sf::Keyboard::Tilde:
			return "~";
		case sf::Keyboard::Equal:
			return "=";
		case sf::Keyboard::Dash:
			return "-";
		default:
			return "";
	}
}
void SettingsControlMenu::init_controlkey_settings(void)
{
	/*
	 * Variable declarations:
	*/
	int i;
	char tmp_pagecount[255];
	/*
	 * Exit edit mode:
	*/
	m_controlkeys_editable = -1;
	/*
	 * Calculate how many items we have to show:
	*/
	m_controlkeys_showc = ((CONFIGVAR_CONTROL_KEY_COUNT-m_controlkeys_offset)>=5)?5:(CONFIGVAR_CONTROL_KEY_COUNT-m_controlkeys_offset);
	for (i=0; i < m_controlkeys_showc; i++)
	{
		switch (i)
		{
			case 0:
				m_menuitem1_caption.setString(get_wstring(m_controlkeys[m_controlkeys_offset+i].get_caption()));
				m_menuitem1_value.setString(get_wstring(keycode2string(m_controlkeys[m_controlkeys_offset+i].get_value())));
				break;
			case 1:
				m_menuitem2_caption.setString(get_wstring(m_controlkeys[m_controlkeys_offset+i].get_caption()));
				m_menuitem2_value.setString(get_wstring(keycode2string(m_controlkeys[m_controlkeys_offset+i].get_value())));
				break;
			case 2:
				m_menuitem3_caption.setString(get_wstring(m_controlkeys[m_controlkeys_offset+i].get_caption()));
				m_menuitem3_value.setString(get_wstring(keycode2string(m_controlkeys[m_controlkeys_offset+i].get_value())));
				break;
			case 3:
				m_menuitem4_caption.setString(get_wstring(m_controlkeys[m_controlkeys_offset+i].get_caption()));
				m_menuitem4_value.setString(get_wstring(keycode2string(m_controlkeys[m_controlkeys_offset+i].get_value())));
				break;
			case 4:
				m_menuitem5_caption.setString(get_wstring(m_controlkeys[m_controlkeys_offset+i].get_caption()));
				m_menuitem5_value.setString(get_wstring(keycode2string(m_controlkeys[m_controlkeys_offset+i].get_value())));
				break;
		}
	}
	sprintf(tmp_pagecount, _("settings_control_menu_entry_pagecount %d %d"), (m_controlkeys_offset/5)+1, int((CONFIGVAR_CONTROL_KEY_COUNT/5.0)+1.0));
	m_menuitem6_txt.setString(get_wstring(tmp_pagecount));
}
int SettingsControlMenu::init(Config conf, std::string arg)
{
	/*
	 * Variable declarations:
	*/
	int i;
	std::string confkey;
	std::string caption;
	/*
	 * Init control key settings array:
	*/
	m_controlkeys_offset = 0;
	m_controlkeys_editable = -1;
	m_controlkeys = new ControlKeySetting[CONFIGVAR_CONTROL_KEY_COUNT];
	for (i=0; i < CONFIGVAR_CONTROL_KEY_COUNT; i++)
	{
		switch (i)
		{
			case 0:
				confkey = "CONTROL__KEY_GOLEFT";
				caption = _("settings_control_menu_entry_caption_goleft");
				break;
			case 1:
				confkey = "CONTROL__KEY_GORIGHT";
				caption = _("settings_control_menu_entry_caption_goright");
				break;
			case 2:
				confkey = "CONTROL__KEY_JUMP";
				caption = _("settings_control_menu_entry_caption_jump");
				break;
		}
		m_controlkeys[i].set_value(conf.get(confkey).value_int);
		m_controlkeys[i].set_config_key(confkey);
		m_controlkeys[i].set_caption(caption);
	}
	init_controlkey_settings();
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	if (!m_font2.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Regular.ttf")))
		return 1;
	/*
	 * Init arrows:
	*/
	if (!m_arrow.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "arrow.png")))
		return 1;
	m_arrow_left6_sprite.setTexture(m_arrow);
	m_arrow_right6_sprite.setTexture(m_arrow);
	m_arrow_right6_sprite.setTextureRect(sf::IntRect(m_arrow.getSize().x, 0, -m_arrow.getSize().x, m_arrow.getSize().y));
	/*
	 * Init menuitem shapes:
	*/
	m_menuitem1.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_menuitem2.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_menuitem3.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_menuitem4.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_menuitem5.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_menuitem6.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_menuitem7.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_menuitem8.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	
	/*
	 * Init menuitem texts:
	*/
	m_menuitem6_txt_alt.setString(get_wstring(_("settings_control_menu_warning_keyused")));
	m_menuitem7_txt.setString(get_wstring(_("settings_control_menu_entry_save")));
	m_menuitem8_txt.setString(get_wstring(_("settings_control_menu_entry_abort")));
	m_menuitem6_txt.setColor(sf::Color::Black);
	m_menuitem6_txt_alt.setColor(sf::Color::Red);
	m_menuitem7_txt.setColor(sf::Color::Black);
	m_menuitem8_txt.setColor(sf::Color::Black);
	m_menuitem6_txt.setFont(m_font2);
	m_menuitem6_txt_alt.setFont(m_font2);
	m_menuitem7_txt.setFont(m_font1);
	m_menuitem8_txt.setFont(m_font1);
	/*
	 * Init menuitem captions:
	*/
	m_menuitem1_caption.setColor(sf::Color::Black);
	m_menuitem2_caption.setColor(sf::Color::Black);
	m_menuitem3_caption.setColor(sf::Color::Black);
	m_menuitem4_caption.setColor(sf::Color::Black);
	m_menuitem5_caption.setColor(sf::Color::Black);
	m_menuitem1_caption.setFont(m_font1);
	m_menuitem2_caption.setFont(m_font1);
	m_menuitem3_caption.setFont(m_font1);
	m_menuitem4_caption.setFont(m_font1);
	m_menuitem5_caption.setFont(m_font1);
	/*
	 * Init menuitem values:
	*/
	m_menuitem1_value.setColor(sf::Color::Black);
	m_menuitem2_value.setColor(sf::Color::Black);
	m_menuitem3_value.setColor(sf::Color::Black);
	m_menuitem4_value.setColor(sf::Color::Black);
	m_menuitem5_value.setColor(sf::Color::Black);
	m_menuitem1_value.setFont(m_font2);
	m_menuitem2_value.setFont(m_font2);
	m_menuitem3_value.setFont(m_font2);
	m_menuitem4_value.setFont(m_font2);
	m_menuitem5_value.setFont(m_font2);
	reset_menuitem_over();
	return 0;
}
int SettingsControlMenu::uninit(void)
{
	/*
	 * Uninit control key settings array:
	*/
	delete[] m_controlkeys;
	return 0;
}
int SettingsControlMenu::calculate_sizes(int w, int h)
{
	m_fire.calculate_sizes(w,h);
	m_w = w;
	m_h = h;
	/*
	 * Variable definitions:
	*/
	int menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	int menuitem_height = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	int menuitem_first_yoffset = h*(SIZE_SETTINGS_SUBMENUS_FIRST_ELEMENT_YOFFSET/100.0);
	int menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	int arrow_height = h*(SIZE_MENU_CONFIG_ARROW_HEIGHT/100.0);
	int arrow_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_ARROW_XGAP)/100.0;
	int arrow_ygap = h*(SIZE_MENU_CONFIG_ELEMENT_ARROW_YGAP_CONTROL)/100.0;
	int menuitem_xoffset = (w-menuitem_width)/2.0;
	int element_outline = h*(SIZE_MENU_ELEMENT_OUTLINE/100.0);
	int text_gap = h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0);
	int text_xgap = w*(SIZE_MENU_CONFIG_ELEMENT_TEXT_XGAP/100.0);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem4.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem5.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem6.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem7.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem8.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem1.setOutlineThickness(element_outline);
	m_menuitem2.setOutlineThickness(element_outline);
	m_menuitem3.setOutlineThickness(element_outline);
	m_menuitem4.setOutlineThickness(element_outline);
	m_menuitem5.setOutlineThickness(element_outline);
	m_menuitem6.setOutlineThickness(element_outline);
	m_menuitem7.setOutlineThickness(element_outline);
	m_menuitem8.setOutlineThickness(element_outline);
	m_menuitem1.setPosition(menuitem_xoffset, menuitem_first_yoffset);
	m_menuitem2.setPosition(menuitem_xoffset, menuitem_first_yoffset+menuitem_height+menuitem_gap);
	m_menuitem3.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*2);
	m_menuitem4.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*3);
	m_menuitem5.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*4);
	m_menuitem6.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*m_controlkeys_showc+menuitem_gap);
	m_menuitem7.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*(m_controlkeys_showc+1)+menuitem_gap);
	m_menuitem8.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*(m_controlkeys_showc+2)+menuitem_gap);
	m_menuitem6.setFillColor(COLOR_MENU_ELEMENT);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem6_txt.setCharacterSize(menuitem_height/2);
	m_menuitem6_txt_alt.setCharacterSize(menuitem_height/2);
	m_menuitem7_txt.setCharacterSize(menuitem_height/2);
	m_menuitem8_txt.setCharacterSize(menuitem_height/2);
	m_menuitem6_txt.setPosition((w-(int)m_menuitem6_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*m_controlkeys_showc+text_gap+menuitem_gap);
	m_menuitem6_txt_alt.setPosition((w-(int)m_menuitem6_txt_alt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*m_controlkeys_showc+text_gap+menuitem_gap);
	m_menuitem7_txt.setPosition((w-(int)m_menuitem7_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*(m_controlkeys_showc+1)+text_gap+menuitem_gap);
	m_menuitem8_txt.setPosition((w-(int)m_menuitem8_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*(m_controlkeys_showc+2)+text_gap+menuitem_gap);
	/*
	 * Update menuitem caption size & positions:
	*/
	m_menuitem1_caption.setCharacterSize(menuitem_height/2);
	m_menuitem2_caption.setCharacterSize(menuitem_height/2);
	m_menuitem3_caption.setCharacterSize(menuitem_height/2);
	m_menuitem4_caption.setCharacterSize(menuitem_height/2);
	m_menuitem5_caption.setCharacterSize(menuitem_height/2);
	m_menuitem1_caption.setPosition(menuitem_xoffset+text_xgap, menuitem_first_yoffset+text_gap);
	m_menuitem2_caption.setPosition(menuitem_xoffset+text_xgap, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap));
	m_menuitem3_caption.setPosition(menuitem_xoffset+text_xgap, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap)*2);
	m_menuitem4_caption.setPosition(menuitem_xoffset+text_xgap, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap)*3);
	m_menuitem5_caption.setPosition(menuitem_xoffset+text_xgap, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap)*4);
	/*
	 * Update menuitem value size & positions:
	*/
	m_menuitem1_value.setCharacterSize(menuitem_height/2);
	m_menuitem2_value.setCharacterSize(menuitem_height/2);
	m_menuitem3_value.setCharacterSize(menuitem_height/2);
	m_menuitem4_value.setCharacterSize(menuitem_height/2);
	m_menuitem5_value.setCharacterSize(menuitem_height/2);
	m_menuitem1_value.setPosition(menuitem_xoffset+menuitem_width-text_xgap-m_menuitem1_value.getGlobalBounds().width, menuitem_first_yoffset+text_gap);
	m_menuitem2_value.setPosition(menuitem_xoffset+menuitem_width-text_xgap-m_menuitem2_value.getGlobalBounds().width, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap));
	m_menuitem3_value.setPosition(menuitem_xoffset+menuitem_width-text_xgap-m_menuitem3_value.getGlobalBounds().width, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap)*2);
	m_menuitem4_value.setPosition(menuitem_xoffset+menuitem_width-text_xgap-m_menuitem4_value.getGlobalBounds().width, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap)*3);
	m_menuitem5_value.setPosition(menuitem_xoffset+menuitem_width-text_xgap-m_menuitem5_value.getGlobalBounds().width, menuitem_first_yoffset+text_gap+(menuitem_height+menuitem_gap)*4);
	/*
	 * Update arrow positions & sizes:
	*/
	m_arrow_left6_sprite.setPosition(menuitem_xoffset+arrow_xgap, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*m_controlkeys_showc+arrow_ygap+menuitem_gap);
	m_arrow_right6_sprite.setPosition(menuitem_xoffset+menuitem_width-arrow_xgap-arrow_height, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*m_controlkeys_showc+arrow_ygap+menuitem_gap);
	m_arrow_left6_sprite.setScale(arrow_height/7, arrow_height/7);
	m_arrow_right6_sprite.setScale(arrow_height/7, arrow_height/7);
	return 0;
}
void SettingsControlMenu::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	/*
	 * Variable declarations:
	*/
	bool already_used;
	int i;
	
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					if (m_controlkeys_editable > -1)
					{
						/*
						 * Exit edit mode!
						*/
						m_controlkeys_editable = -1;
						init_controlkey_settings();
						calculate_sizes(m_w, m_h);
					}
					else
						ret->set_gamemode(2); // back to settings menu
					break;
			}
			if (m_controlkeys_editable > -1 && keycode2string(event.key.code).length() > 0)
			{
				/*
				 * The user has typed a new key, so check if it is already used:
				*/
				already_used = false;
				for (i=0; i < CONFIGVAR_CONTROL_KEY_COUNT; i++)
				{
					if (m_controlkeys[i].get_value() == event.key.code && i != m_controlkeys_editable)
					{
						already_used = true;
						break;
					};
				}
				if (already_used)
				{
					/*
					 * And show an error message:
					*/
					m_warning_keyused = true;
					m_warning_keyused_clock.restart();
				}
				else
				{
					/*
					 * ... or save it temporarily:
					*/
					m_controlkeys[m_controlkeys_editable].set_value(event.key.code);
					m_controlkeys_editable = -1;
					init_controlkey_settings();
					calculate_sizes(m_w, m_h);
				};
			};
			break;
		case sf::Event::MouseMoved:
			reset_menuitem_over();
			if (m_menuitem1.getGlobalBounds().contains(mouse_x, mouse_y) && m_controlkeys_showc >= 1)
				m_menuitem1_over = true;
			else if (m_menuitem2.getGlobalBounds().contains(mouse_x, mouse_y) && m_controlkeys_showc >= 2)
				m_menuitem2_over = true;
			else if (m_menuitem3.getGlobalBounds().contains(mouse_x, mouse_y) && m_controlkeys_showc >= 3)
				m_menuitem3_over = true;
			else if (m_menuitem4.getGlobalBounds().contains(mouse_x, mouse_y) && m_controlkeys_showc >= 4)
				m_menuitem4_over = true;
			else if (m_menuitem5.getGlobalBounds().contains(mouse_x, mouse_y) && m_controlkeys_showc >= 5)
				m_menuitem5_over = true;
			else if (m_arrow_left6_sprite.getGlobalBounds().contains(mouse_x, mouse_y) && m_controlkeys_offset > 0)
				m_arrow_left6_over = true;
			else if (m_arrow_right6_sprite.getGlobalBounds().contains(mouse_x, mouse_y) && CONFIGVAR_CONTROL_KEY_COUNT > m_controlkeys_offset+5)
				m_arrow_right6_over = true;
			else if (m_menuitem7.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem7_over = true;
			else if (m_menuitem8.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem8_over = true;
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_menuitem1_over && m_controlkeys_editable == -1)
					{
						m_controlkeys_editable = 0+m_controlkeys_offset;
						m_menuitem1_value.setString(get_wstring(_("settings_control_menu_entry_value_wait")));
						calculate_sizes(m_w, m_h);
					}
					else if (m_menuitem2_over && m_controlkeys_editable == -1)
					{
						m_controlkeys_editable = 1+m_controlkeys_offset;
						m_menuitem2_value.setString(get_wstring(_("settings_control_menu_entry_value_wait")));
						calculate_sizes(m_w, m_h);
					}
					else if (m_menuitem3_over && m_controlkeys_editable == -1)
					{
						m_controlkeys_editable = 2+m_controlkeys_offset;
						m_menuitem3_value.setString(get_wstring(_("settings_control_menu_entry_value_wait")));
						calculate_sizes(m_w, m_h);
					}
					else if (m_menuitem4_over && m_controlkeys_editable == -1)
					{
						m_controlkeys_editable = 3+m_controlkeys_offset;
						m_menuitem4_value.setString(get_wstring(_("settings_control_menu_entry_value_wait")));
						calculate_sizes(m_w, m_h);
					}
					else if (m_menuitem5_over && m_controlkeys_editable == -1)
					{
						m_controlkeys_editable = 4+m_controlkeys_offset;
						m_menuitem5_value.setString(get_wstring(_("settings_control_menu_entry_value_wait")));
						calculate_sizes(m_w, m_h);
					}
					else if (m_arrow_left6_over)
					{
						m_controlkeys_offset -= 5;
						init_controlkey_settings();
						calculate_sizes(m_w, m_h);
					}
					else if (m_arrow_right6_over)
					{
						m_controlkeys_offset += 5;
						init_controlkey_settings();
						calculate_sizes(m_w, m_h);
					}
					else if (m_menuitem7_over)
					{
						ConfigVariable var[CONFIGVAR_CONTROL_KEY_COUNT];
						int i;
						/*
						 * Save!
						*/
						ret->init_confvars(CONFIGVAR_CONTROL_KEY_COUNT);
						for (i=0; i < CONFIGVAR_CONTROL_KEY_COUNT; i++)
						{
							var[i].type = CONFIGVAR_TYPE_INTEGER;
							var[i].index = m_controlkeys[i].get_config_key();
							var[i].value_int = m_controlkeys[i].get_value();
							ret->add_confvar(var[i]);
						}
						/*
						 * Back to settings menu:
						*/
						ret->set_gamemode(2);
					}
					else if (m_menuitem8_over)
						ret->set_gamemode(2); // back to settings menu
					break;
			}
			break;
	}
}
void SettingsControlMenu::reset_menuitem_over(void)
{
	m_menuitem1_over = false;
	m_menuitem2_over = false;
	m_menuitem3_over = false;
	m_menuitem4_over = false;
	m_menuitem5_over = false;
	m_arrow_left6_over = false;
	m_arrow_right6_over = false;
	m_menuitem7_over = false;
	m_menuitem8_over = false;
}
UniversalDrawableArray SettingsControlMenu::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * Check if we should hide the warning message:
	*/
	if (m_warning_keyused && m_warning_keyused_clock.getElapsedTime().asSeconds() >= 2)
		m_warning_keyused = false;
	/*
	 * Init UniversalDrawableArray:
	*/
	arr.init(7+(m_controlkeys_showc*3)+((m_controlkeys_offset > 0)?1:0)+((CONFIGVAR_CONTROL_KEY_COUNT > m_controlkeys_offset+5)?1:0));
	/*
	 * Add elements:
	*/
	arr.add_sprite(m_fire.get_sprite());
	if (m_controlkeys_showc >= 1)
	{
		if (m_menuitem1_over)
			m_menuitem1.setFillColor(COLOR_MENU_ELEMENT_HOVER);
		else
			m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
		arr.add_rectshape(m_menuitem1);
		arr.add_text(m_menuitem1_caption);
		arr.add_text(m_menuitem1_value);
	};
	//
	if (m_controlkeys_showc >= 2)
	{
		if (m_menuitem2_over)
			m_menuitem2.setFillColor(COLOR_MENU_ELEMENT_HOVER);
		else
			m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
		arr.add_rectshape(m_menuitem2);
		arr.add_text(m_menuitem2_caption);
		arr.add_text(m_menuitem2_value);
	};
	//
	if (m_controlkeys_showc >= 3)
	{
		if (m_menuitem3_over)
			m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
		else
			m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
		arr.add_rectshape(m_menuitem3);
		arr.add_text(m_menuitem3_caption);
		arr.add_text(m_menuitem3_value);
	};
	//
	if (m_controlkeys_showc >= 4)
	{
		if (m_menuitem4_over)
			m_menuitem4.setFillColor(COLOR_MENU_ELEMENT_HOVER);
		else
			m_menuitem4.setFillColor(COLOR_MENU_ELEMENT);
		arr.add_rectshape(m_menuitem4);
		arr.add_text(m_menuitem4_caption);
		arr.add_text(m_menuitem4_value);
	};
	//
	if (m_controlkeys_showc >= 5)
	{
		if (m_menuitem5_over)
			m_menuitem5.setFillColor(COLOR_MENU_ELEMENT_HOVER);
		else
			m_menuitem5.setFillColor(COLOR_MENU_ELEMENT);
		arr.add_rectshape(m_menuitem5);
		arr.add_text(m_menuitem5_caption);
		arr.add_text(m_menuitem5_value);
	};
	//
	arr.add_rectshape(m_menuitem6);
	//
	if (m_controlkeys_offset > 0)
		arr.add_sprite(m_arrow_left6_sprite);
	//
	if (CONFIGVAR_CONTROL_KEY_COUNT > m_controlkeys_offset+5)
		arr.add_sprite(m_arrow_right6_sprite);
	//
	if (m_warning_keyused)
		arr.add_text(m_menuitem6_txt_alt);
	else
		arr.add_text(m_menuitem6_txt);
	//
	if (m_menuitem7_over)
		m_menuitem7.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem7.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem7);
	//
	arr.add_text(m_menuitem7_txt);
	//
	if (m_menuitem8_over)
		m_menuitem8.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem8.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem8);
	//
	arr.add_text(m_menuitem8_txt);
	/*
	 * Return:
	*/
	return arr;
}
