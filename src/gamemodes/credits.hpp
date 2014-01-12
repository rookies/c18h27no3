/*
 * credits.hpp
 * 
 * Copyright 2013 Robert Knauer <robert@privatdemail.net>
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
#ifndef CREDITS_HPP
#	define CREDITS_HPP

#	include <libintl.h>
#	include "../gamemode.hpp"
#	include "../universal_drawable.hpp"
#	include "../event_processor_return.hpp"
#	include "../dataloader.hpp"
#	include "../widestring.hpp"
#	include "../fireanimation.hpp"
	
	class Credits : public Gamemode
	{
		public:
			Credits();
			virtual ~Credits();
			
			/*
			 * (Un)init:
			*/
			int init(Config conf, std::string arg); /* Called in Game::init_gamemode() */
			int uninit(void); /* Called in Game::uninit_gamemode() */
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(int w, int h); /* Called in Game::calculate_sizes() */
			/*
			 * Load item:
			*/
			void load_item(int i);
			/*
			 * Process events:
			*/
			void process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret); /* Called in Game::process_events() */
			/*
			 * Get drawable items:
			*/
			UniversalDrawableArray get_drawables(void); /* Called in Game::draw() */
		private:
			sf::Texture m_img_texture;
			sf::Sprite m_img;
			sf::Font m_font1;
			sf::Font m_font2;
			sf::Text m_header;
			sf::Text m_text;
			sf::Texture m_cdev_texture;
			sf::Sprite m_cdev;
			unsigned int m_hover_x1[CREDITS_COUNT] = {499,550,929,998,1592,1097};
			unsigned int m_hover_x2[CREDITS_COUNT] = {557,611,997,1063,1666,1294};
			unsigned int m_hover_y1[CREDITS_COUNT] = {383,285,297,330,89,3};
			unsigned int m_hover_y2[CREDITS_COUNT] = {460,369,391,423,183,377};
			unsigned int m_hovert_x1[CREDITS_COUNT];
			unsigned int m_hovert_x2[CREDITS_COUNT];
			unsigned int m_hovert_y1[CREDITS_COUNT];
			unsigned int m_hovert_y2[CREDITS_COUNT];
			int m_credits_yoffset;
			int m_item_over;
			int m_item_loaded;
			sf::Text m_sign;
			FireAnimation m_fire;
	};
#endif // CREDITS_HPP
