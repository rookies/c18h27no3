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

MainMenu::MainMenu() : m_menuitem_over(-1), m_menuitem_loaded(-1), m_updates(false), m_updatetext_changed(false)
{
	
}
MainMenu::~MainMenu()
{
	
}
int MainMenu::init(Config conf, std::string arg)
{
	/*
	 * Init background:
	*/
	if (!m_bg.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "menu_bg.png")))
		return 1;
	m_bgs.setTexture(m_bg);
	/*
	 * Start update thread:
	*/
	m_update_thread = new sf::Thread(&MainMenu::updater, this);
	m_update_thread->launch();
	/*
	 * Init logo & menu image:
	*/
	if (!m_img1.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "mainmenu.png")))
		return 1;
	m_img1.setSmooth(true);
	m_img1_sprite.setTexture(m_img1);
	/*
	 * Init coloured menu image:
	*/
	if (!m_img2.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "mainmenu_active.png")))
		return 1;
	m_img2.setSmooth(true);
	m_img2_sprite.setTexture(m_img2);
	m_menuitem_over = -1;
	m_menuitem_loaded = -1;
	/*
	 * Load font:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Regular.ttf")))
		return 1;
	/*
	 * Init update text:
	*/
	m_text1.setFont(m_font1);
	m_text1.setColor(sf::Color::Red);
	return 0;
}
int MainMenu::uninit(void)
{
	m_update_thread->terminate();
	delete m_update_thread;
	return 0;
}
int MainMenu::calculate_sizes(int w, int h)
{
	m_w = w;
	m_h = h;
	unsigned int i;
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
	m_logo_yoffset = h*(SIZE_MAINMENU_LOGO_YOFFSET/100.0);
	m_activewidth = w*MAINMENU_ACTIVEWIDTH/1920.;
	/*
	 * Resize background:
	*/
	m_bgs.setScale(w/SIZE_MENU_BG_IMGWIDTH, w/SIZE_MENU_BG_IMGWIDTH);
	/*
	 * Update logo position & size:
	*/
	m_img1_sprite.setScale(logo_height/1080.0, logo_height/1080.0);
	m_logo_xoffset = (w-m_img1_sprite.getGlobalBounds().width)/2;
	m_img1_sprite.setPosition(m_logo_xoffset, m_logo_yoffset);
	/*
	 * Calculate sizes for coloured menu image:
	*/
	for (i=0; i < MAINMENU_COUNT; i++)
	{
		m_menuc_a[i] = (m_menu_a[i]/1920.0)*w;
		m_menuc_x[i] = (m_menu_x[i]/1920.0)*w;
		m_menuc_y[i] = (m_menu_y[i]/1920.0)*w;
		m_menuc_h[i] = (m_menu_h[i]/1920.0)*w;
	}
	/*
	 * Calculate update text properties:
	*/
	m_text1.setCharacterSize(h/SIZE_UPDATER_TEXT_SIZE_DIVIDER);
	m_text1.setPosition(sf::Vector2f(w*SIZE_UPDATER_TEXT_XOFFSET/100., h*SIZE_UPDATER_TEXT_YOFFSET/100.));
	return 0;
}
void MainMenu::load_menuitem(int i)
{
	if (m_menuitem_loaded == i)
		return;
	m_img2_sprite.setTextureRect(sf::IntRect(0, m_menu_a[i], MAINMENU_ACTIVEWIDTH, (m_menu_a[i+1]-m_menu_a[i])));
	m_img2_sprite.setScale(m_w/1920.0, m_w/1920.0);
	m_img2_sprite.setPosition((m_logo_xoffset+m_menuc_x[i]), (m_logo_yoffset+m_menuc_y[i]+m_menuc_a[i]));
	m_menuitem_loaded = i;
}
void MainMenu::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	unsigned int i;
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
			m_menuitem_over = -1;
			for (i=0; i < MAINMENU_COUNT; i++)
			{
				if (mouse_x >= m_logo_xoffset+m_menuc_x[i] &&
					mouse_x <= m_logo_xoffset+m_menuc_x[i]+m_activewidth &&
					mouse_y >= m_logo_yoffset+m_menuc_y[i]+m_menuc_a[i] &&
					mouse_y <= m_logo_yoffset+m_menuc_y[i]+m_menuc_a[i]+m_menuc_h[i])
				{
					if (i != 1 && i != 2) // FIXME: disable loading & highscore
						m_menuitem_over = i;
					break;
				};
			}
			if (m_menuitem_over != m_menuitem_loaded)
				load_menuitem(m_menuitem_over);
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_menuitem_over == 0)
						ret->set_gamemode(7); // go to singleplayer
					else if (m_menuitem_over == 3)
						ret->set_gamemode(2); // go to settings menu
					else if (m_menuitem_over == 4)
						ret->set_gamemode(8); // go to credits
					else if (m_menuitem_over == 5)
						ret->set_exit(true); // exit
					break;
			}
			break;
	}
}
UniversalDrawableArray MainMenu::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * Change update text:
	*/
	if (m_updatetext_changed)
	{
		m_text1.setString(get_wstring(m_updatetext));
		m_updatetext_changed = false;
	};
	/*
	 * Init UniversalDrawableArray:
	*/
	arr.init(2+(m_menuitem_over>-1?1:0)+(m_updates?1:0));
	/*
	 * Add elements:
	*/
	arr.add_sprite(m_bgs);
	arr.add_sprite(m_img1_sprite);
	if (m_menuitem_over > -1)
		arr.add_sprite(m_img2_sprite);
	if (m_updates)
		arr.add_text(m_text1);
	/*
	 * Return:
	*/
	return arr;
}
void MainMenu::updater(void)
{
	/*
	 * Variable declarations:
	*/
	sf::Http http;
	sf::Http::Request req;
	sf::Http::Response res;
	/*
	 * Set host:
	*/
	http.setHost(UPDATESERVER);
	/*
	 * Send request:
	*/
	std::cout << "Updater: Requesting " << UPDATESERVER << UPDATEURI << " ..." << std::endl;
	req.setUri(UPDATEURI);
	req.setField("User-Agent", UPDATEAGENT);
	res = http.sendRequest(req);
	/*
	 * Analyze response:
	*/
	std::cout << "Updater: Got " << res.getStatus() << " response, length: " << res.getBody().length() << std::endl;
	if (res.getStatus() == sf::Http::Response::Ok && res.getBody().length() > 0)
	{
		/*
		 * Got an update.
		*/
		std::cout << "Updater: Got an update:" << std::endl;
		std::cout << "= TEXT START =" << std::endl;
		std::cout << res.getBody();
		std::cout << "= TEXT END =" << std::endl;
		m_updatetext = res.getBody();
		m_updatetext_changed = true;
		m_updates = true;
	};
}
