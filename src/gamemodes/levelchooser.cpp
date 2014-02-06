/*
 * levelchooser.cpp
 * 
 * Copyright 2014 Robert Knauer <robert@privatdemail.net>
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
#include "levelchooser.hpp"

LevelChooser::LevelChooser()
{

}
LevelChooser::~LevelChooser()
{

}
int LevelChooser::init(Config conf, std::string arg)
{
	/*
	 * Variable declaration:
	*/
	unsigned int i;
	char tmp[LEVELCHOOSER_FILENAME_BUFLEN];
	/*
	 * Load fonts:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "Vollkorn-Bold.ttf")))
		return 1;
	/*
	 * Init header:
	*/
	m_header.setFont(m_font1);
	m_header.setColor(sf::Color::White);
	m_header.setString(get_wstring(_("levelchooser_header")));
	m_subheading.setFont(m_font1);
	m_subheading.setColor(sf::Color::White);
	m_subheading.setString(get_wstring(_("levelchooser_subheading")));
	/*
	 * Init back button:
	*/
	m_backtext.setFont(m_font1);
	m_backtext.setColor(sf::Color::Black);
	m_backtext.setString(get_wstring(_("levelchooser_back")));
	m_backbutton.setOutlineColor(COLOR_MENU_ELEMENT_OUTLINE);
	m_backbutton.setFillColor(COLOR_MENU_ELEMENT);
	/*
	 * Search for levels & init thumbnails:
	*/
	for (m_lvlc=0; m_lvlc <= LEVELCHOOSER_NUMITEMS; m_lvlc++)
	{
		sprintf(tmp, "%04d.dat", m_lvlc);
		if (get_data_path(DATALOADER_TYPE_LEVEL, tmp).compare("") == 0)
			break;
		else
		{
			m_levels[m_lvlc].load_from_file(get_data_path(DATALOADER_TYPE_LEVEL, tmp), LEVELLOADER_NOBACKGROUND | LEVELLOADER_NOMUSIC | LEVELLOADER_NOTEXTURES);
			if (m_levels[m_lvlc].has_thumbnail())
			{
				m_level_sprite[m_lvlc].setTexture(m_levels[m_lvlc].get_thumbnail());
			};
		};
	}
	std::cout << "Levelchooser: Showing " << m_lvlc << " levels." << std::endl;
	/*
	 * Init frames:
	*/
	if (!m_frame.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "levelchooser_frame.png")))
		return 1;
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
		m_frame_sprite[i].setTexture(m_frame);
	/*
	 * Init locks:
	*/
	if (!m_lock.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "lock.png")))
		return 1;
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
		m_lock_sprite[i].setTexture(m_lock);
	/*
	 * Init level backgrounds:
	*/
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
	{
		if (i < m_lvlc)
			m_level_bg[i].setFillColor(COLOR_LEVELCHOOSER_LEVEL_BACKGROUND_HOVER);
		else
			m_level_bg[i].setFillColor(COLOR_LEVELCHOOSER_LEVEL_BACKGROUND);
	}
	return 0;
}
int LevelChooser::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int LevelChooser::calculate_sizes(int w, int h)
{
	m_fire.calculate_sizes(w,h);
	/*
	 * Variable declaration:
	*/
	unsigned int i;
	double multip;
	unsigned long pos1, pos2;
	/*
	 * Resize & position header:
	*/
	m_header.setCharacterSize(h/SIZE_LEVELCHOOSER_HEADER_SIZE_DIVIDER);
	m_header.setPosition((w-m_header.getGlobalBounds().width)/2., h*SIZE_LEVELCHOOSER_HEADER_GAP/100.);
	m_subheading.setCharacterSize(h/SIZE_LEVELCHOOSER_SUBHEADING_SIZE_DIVIDER);
	m_subheading.setPosition((w-m_subheading.getGlobalBounds().width)/2., m_header.getGlobalBounds().height+h*SIZE_LEVELCHOOSER_SUBHEADING_GAP/100.);
	/*
	 * Resize & position back button:
	*/
	m_backbutton.setSize(sf::Vector2f(w*SIZE_MENU_ELEMENT_WIDTH/100., h*SIZE_MENU_ELEMENT_HEIGHT/100.));
	m_backbutton.setOutlineThickness(h*SIZE_MENU_ELEMENT_OUTLINE/100.0);
	m_backbutton.setPosition((w-m_backbutton.getGlobalBounds().width)/2., h*SIZE_LEVELCHOOSER_BACKBUTTON_YOFFSET/100.);
	m_backtext.setCharacterSize(h*SIZE_MENU_ELEMENT_HEIGHT/200.);
	m_backtext.setPosition((w-m_backtext.getGlobalBounds().width)/2., h*(SIZE_MENU_ELEMENT_TEXT_GAP+SIZE_LEVELCHOOSER_BACKBUTTON_YOFFSET)/100.);
	/*
	 * Resize & position frames, level images, locks & level backgrounds:
	*/
	multip = w/1920.;
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
	{
		pos1 = (i % 4)*(60+SIZE_LEVELCHOOSER_FRAME_IMGWIDTH*5)+170;
		pos2 = int(i/4)*(60+SIZE_LEVELCHOOSER_FRAME_IMGHEIGHT*5)+120;
		// Frames:
		m_frame_sprite[i].setScale(5*multip, 5*multip);
		m_frame_sprite[i].setPosition(pos1*multip, pos2*multip);
		// Level Images:
		m_level_sprite[i].setScale(0.63*multip, 0.63*multip); // div 8 * 5 + tolerance
		m_level_sprite[i].setPosition((pos1+20)*multip, (pos2+20)*multip);
		// Locks:
		m_lock_sprite[i].setScale(5*multip, 5*multip);
		m_lock_sprite[i].setPosition((pos1+112.5)*multip, (pos2+17.5)*multip); // 22.5*5 ; 3.5*5
		// Level Backgrounds:
		m_level_bg[i].setSize(sf::Vector2f(SIZE_LEVELCHOOSER_LVLIMG_IMGWIDTH*0.63*multip, SIZE_LEVELCHOOSER_LVLIMG_IMGHEIGHT*0.63*multip));
		m_level_bg[i].setPosition((pos1+20)*multip, (pos2+20)*multip);
	}
	return 0;
}
void LevelChooser::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	/*
	 * Variable declarations:
	*/
	unsigned int i;
	char tmp[LEVELCHOOSER_FILENAME_BUFLEN];
	/*
	 * Event handling:
	*/
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(1);
					break;
			}
			break;
		case sf::Event::MouseMoved:
			if (m_backbutton.getGlobalBounds().contains(mouse_x, mouse_y))
				m_backbutton.setFillColor(COLOR_MENU_ELEMENT_HOVER);
			else
				m_backbutton.setFillColor(COLOR_MENU_ELEMENT);
			for (i=0; i < m_lvlc; i++)
			{
				if (m_level_sprite[i].getGlobalBounds().contains(mouse_x, mouse_y))
				{
					m_level_sprite[i].setColor(COLOR_LEVELCHOOSER_LEVEL_MASK_HOVER);
					break;
				}
				else
					m_level_sprite[i].setColor(COLOR_LEVELCHOOSER_LEVEL_MASK);
			}
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
				case sf::Mouse::Left:
					if (m_backbutton.getGlobalBounds().contains(mouse_x, mouse_y))
						ret->set_gamemode(1); // go to main menu
					else
					{
						for (i=0; i < m_lvlc; i++)
						{
							if (m_level_sprite[i].getGlobalBounds().contains(mouse_x, mouse_y))
							{
								ret->set_gamemode(7); // go to singleplayer
								sprintf(tmp, "%04d.dat", i);
								ret->set_gamemode_arg(get_data_path(DATALOADER_TYPE_LEVEL, tmp));
								break;
							};
						}
					};
					break;
			}
			break;
	}
}
UniversalDrawableArray LevelChooser::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	unsigned int i;
	/*
	 * Add elements:
	*/
	arr.init(5+2*LEVELCHOOSER_NUMITEMS+m_lvlc);
	arr.add_sprite(m_fire.get_sprite());
	arr.add_text(m_header);
	arr.add_text(m_subheading);
	arr.add_rectshape(m_backbutton);
	arr.add_text(m_backtext);
	for (i=0; i < LEVELCHOOSER_NUMITEMS; i++)
	{
		arr.add_rectshape(m_level_bg[i]);
		if (i < m_lvlc)
			arr.add_sprite(m_level_sprite[i]);
		arr.add_sprite(m_frame_sprite[i]);
		//if (i > 0 && i < 5)
		//	arr.add_sprite(m_lock_sprite[i]);
	}
	return arr;
}
