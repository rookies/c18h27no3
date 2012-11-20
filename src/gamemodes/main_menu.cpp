/*
 * main_menu.cpp
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
#include "main_menu.hpp"

MainMenu::MainMenu()
{
	
}
MainMenu::~MainMenu()
{
	
}
int MainMenu::init(Config conf)
{
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	/*
	 * Init grassblock:
	*/
	if (!m_img1.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "c18h27no3.png")))
		return 1;
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
	m_menuitem6.setOutlineColor(sf::Color::Black);
	/*
	 * Init menuitem texts:
	*/
	m_menuitem1_txt.setString(get_wstring(_("main_menu_entry_newgame")));
	m_menuitem2_txt.setString(get_wstring(_("main_menu_entry_loadgame")));
	m_menuitem3_txt.setString(get_wstring(_("main_menu_entry_highscore")));
	m_menuitem4_txt.setString(get_wstring(_("main_menu_entry_settings")));
	m_menuitem5_txt.setString(get_wstring(_("main_menu_entry_credits")));
	m_menuitem6_txt.setString(get_wstring(_("main_menu_entry_exit")));
	m_menuitem1_txt.setColor(sf::Color::Black);
	m_menuitem2_txt.setColor(sf::Color::Black);
	m_menuitem3_txt.setColor(sf::Color::Black);
	m_menuitem4_txt.setColor(sf::Color::Black);
	m_menuitem5_txt.setColor(sf::Color::Black);
	m_menuitem6_txt.setColor(sf::Color::Black);
	m_menuitem1_txt.setFont(m_font1);
	m_menuitem2_txt.setFont(m_font1);
	m_menuitem3_txt.setFont(m_font1);
	m_menuitem4_txt.setFont(m_font1);
	m_menuitem5_txt.setFont(m_font1);
	m_menuitem6_txt.setFont(m_font1);
	reset_menuitem_over();
	return 0;
}
int MainMenu::uninit(void)
{
	return 0;
}
int MainMenu::calculate_sizes(int w, int h)
{
	/*
	 * Variable definitions:
	*/
	int menuitem_width = w*(SIZE_MENU_ELEMENT_WIDTH/100.0);
	int menuitem_height = h*(SIZE_MENU_ELEMENT_HEIGHT/100.0);
	int menuitem_first_yoffset = h*(SIZE_MENU_FIRST_ELEMENT_YOFFSET/100.0);
	int menuitem_gap = h*(SIZE_MENU_ELEMENT_GAP/100.0);
	int logo_height = h*(SIZE_MAINMENU_LOGO_HEIGHT/100.0);
	int menuitem_xoffset = (w-menuitem_width)/2.0;
	int text_gap = h*(SIZE_MENU_ELEMENT_TEXT_GAP/100.0);
	int element_outline = h*(SIZE_MENU_ELEMENT_OUTLINE/100.0);
	int logo_yoffset = h*(SIZE_MAINMENU_LOGO_YOFFSET/100.0);
	/*
	 * Update logo position & size:
	*/
	m_img1_sprite.setScale(logo_height/47, logo_height/47);
	m_img1_sprite.setPosition((w-m_img1_sprite.getGlobalBounds().width)/2, logo_yoffset);
	/*
	 * Update menuitem positions & sizes:
	*/
	m_menuitem1.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem2.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem3.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem4.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem5.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem6.setSize(sf::Vector2f(menuitem_width, menuitem_height));
	m_menuitem1.setOutlineThickness(element_outline);
	m_menuitem2.setOutlineThickness(element_outline);
	m_menuitem3.setOutlineThickness(element_outline);
	m_menuitem4.setOutlineThickness(element_outline);
	m_menuitem5.setOutlineThickness(element_outline);
	m_menuitem6.setOutlineThickness(element_outline);
	m_menuitem1.setPosition(menuitem_xoffset, menuitem_first_yoffset);
	m_menuitem2.setPosition(menuitem_xoffset, menuitem_first_yoffset+menuitem_height+menuitem_gap);
	m_menuitem3.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*2);
	m_menuitem4.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*3);
	m_menuitem5.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*4);
	m_menuitem6.setPosition(menuitem_xoffset, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*5+menuitem_gap);
	/*
	 * Update menuitem text size & positions:
	*/
	m_menuitem1_txt.setCharacterSize(menuitem_height/2);
	m_menuitem2_txt.setCharacterSize(menuitem_height/2);
	m_menuitem3_txt.setCharacterSize(menuitem_height/2);
	m_menuitem4_txt.setCharacterSize(menuitem_height/2);
	m_menuitem5_txt.setCharacterSize(menuitem_height/2);
	m_menuitem6_txt.setCharacterSize(menuitem_height/2);
	m_menuitem1_txt.setPosition((w-(int)m_menuitem1_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+text_gap);
	m_menuitem2_txt.setPosition((w-(int)m_menuitem2_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+menuitem_height+menuitem_gap+text_gap);
	m_menuitem3_txt.setPosition((w-(int)m_menuitem3_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*2+text_gap);
	m_menuitem4_txt.setPosition((w-(int)m_menuitem4_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*3+text_gap);
	m_menuitem5_txt.setPosition((w-(int)m_menuitem5_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*4+text_gap);
	m_menuitem6_txt.setPosition((w-(int)m_menuitem6_txt.getGlobalBounds().width)/2, menuitem_first_yoffset+(menuitem_height+menuitem_gap)*5+text_gap+menuitem_gap);
	return 0;
}
void MainMenu::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_exit(1); // exit
					break;
			}
			break;
		case sf::Event::MouseMoved:
			reset_menuitem_over();
			if (m_menuitem1.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem1_over = 1;
			else if (m_menuitem2.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem2_over = 1;
			else if (m_menuitem3.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem3_over = 1;
			else if (m_menuitem4.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem4_over = 1;
			else if (m_menuitem5.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem5_over = 1;
			else if (m_menuitem6.getGlobalBounds().contains(mouse_x, mouse_y))
				m_menuitem6_over = 1;
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_menuitem6_over == 1)
						ret->set_exit(true); // exit
					else if (m_menuitem4_over == 1)
						ret->set_gamemode(2); // go to settings menu
					break;
			}
			break;
	}
}
void MainMenu::reset_menuitem_over(void)
{
	m_menuitem1_over = 0;
	m_menuitem2_over = 0;
	m_menuitem3_over = 0;
	m_menuitem4_over = 0;
	m_menuitem5_over = 0;
	m_menuitem6_over = 0;
}
UniversalDrawableArray MainMenu::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * Init UniversalDrawableArray:
	*/
	arr.init(13);
	/*
	 * Add elements:
	*/
	arr.add_sprite(m_img1_sprite);
	//
	if (m_menuitem1_over == 1)
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem1.setFillColor(COLOR_MENU_ELEMENT);
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
	if (m_menuitem4_over == 1)
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem4.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem4);
	//
	if (m_menuitem5_over == 1)
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem5.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem5);
	//
	if (m_menuitem6_over == 1)
		m_menuitem6.setFillColor(COLOR_MENU_ELEMENT_HOVER);
	else
		m_menuitem6.setFillColor(COLOR_MENU_ELEMENT);
	arr.add_rectshape(m_menuitem6);
	//
	arr.add_text(m_menuitem1_txt);
	//
	arr.add_text(m_menuitem2_txt);
	//
	arr.add_text(m_menuitem3_txt);
	//
	arr.add_text(m_menuitem4_txt);
	//
	arr.add_text(m_menuitem5_txt);
	//
	arr.add_text(m_menuitem6_txt);
	/*
	 * Return:
	*/
	return arr;
}
