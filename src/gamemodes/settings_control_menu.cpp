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
std::string SettingsControlMenu::keycode2string(sf::Keyboard::Key code)
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
		case sf::Keyboard::Back:
			return _("key_Back");
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
	m_menuitem6.setOutlineColor(sf::Color::Black);
	m_menuitem7.setOutlineColor(sf::Color::Black);
	m_menuitem8.setOutlineColor(sf::Color::Black);
	
	/*
	 * Init menuitem texts:
	*/
	m_menuitem7_txt.setString(get_wstring(_("settings_control_menu_entry_save")));
	m_menuitem8_txt.setString(get_wstring(_("settings_control_menu_entry_abort")));
	m_menuitem7_txt.setColor(sf::Color::Black);
	m_menuitem8_txt.setColor(sf::Color::Black);
	m_menuitem7_txt.setFont(m_font1);
	m_menuitem8_txt.setFont(m_font1);
	reset_menuitem_over();
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
	m_menuitem6.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*5+menuitem_gap);
	m_menuitem7.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*6+menuitem_gap);
	m_menuitem8.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*7+menuitem_gap);
	m_menuitem6.setFillColor(COLOR_MENU_ELEMENT);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem7_txt.setCharacterSize(menuitem_height/2);
	m_menuitem8_txt.setCharacterSize(menuitem_height/2);
	m_menuitem7_txt.setPosition((w-(int)m_menuitem7_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*6+text_gap+menuitem_gap);
	m_menuitem8_txt.setPosition((w-(int)m_menuitem8_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*7+text_gap+menuitem_gap);
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
			std::cout << "KEY: " << event.key.code << " => " << keycode2string(event.key.code) << std::endl;
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret.set_gamemode(2); // back to settings menu
					break;
			}
			break;
		case sf::Event::MouseMoved:
			reset_menuitem_over();
			if (m_menuitem1.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem1_over = true;
			else if (m_menuitem2.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem2_over = true;
			else if (m_menuitem3.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem3_over = true;
			else if (m_menuitem4.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem4_over = true;
			else if (m_menuitem5.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem5_over = true;
			else if (m_menuitem7.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem7_over = true;
			else if (m_menuitem8.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem8_over = true;
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_menuitem7_over)
					{
						/*
						 * Save!
						*/
					}
					else if (m_menuitem8_over)
						ret.set_gamemode(2); // back to settings menu
					break;
			}
			break;
	}
	return ret;
}
void SettingsControlMenu::reset_menuitem_over(void)
{
	m_menuitem1_over = false;
	m_menuitem2_over = false;
	m_menuitem3_over = false;
	m_menuitem4_over = false;
	m_menuitem5_over = false;
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
	 * Init UniversalDrawableArray:
	*/
	arr.init(10);
	/*
	 * Add elements:
	*/
	if (m_menuitem1_over)
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(0, m_menuitem1);
	//
	if (m_menuitem2_over)
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem2.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(1, m_menuitem2);
	//
	if (m_menuitem3_over)
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem3.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(2, m_menuitem3);
	//
	if (m_menuitem4_over)
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(3, m_menuitem4);
	//
	if (m_menuitem5_over)
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(4, m_menuitem5);
	//
	arr.set_rectshape(5, m_menuitem6);
	//
	if (m_menuitem7_over)
		m_menuitem7.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem7.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(6, m_menuitem7);
	//
	if (m_menuitem8_over)
		m_menuitem8.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem8.setFillColor(COLOR_MENU_ELEMENT);
	arr.set_rectshape(7, m_menuitem8);
	//
	arr.set_text(8, m_menuitem7_txt);
	//
	arr.set_text(9, m_menuitem8_txt);
	/*
	 * Return:
	*/
	return arr;
}
