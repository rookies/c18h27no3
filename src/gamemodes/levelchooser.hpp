/*
 * levelchooser.hpp
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
#ifndef LEVELCHOOSER_HPP
#	define LEVELCHOOSER_HPP

#	include "../gamemode.hpp"
#	include "../universal_drawable.hpp"
#	include "../event_processor_return.hpp"
#	include "../dataloader.hpp"
#	include "../fireanimation.hpp"
#	include "../widestring.hpp"
#	include "../level.hpp"
	
	class LevelChooser : public Gamemode
	{
		public:
			LevelChooser();
			virtual ~LevelChooser();
			
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
			 * Process events:
			*/
			void process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret); /* Called in Game::process_events() */
			/*
			 * Get drawable items:
			*/
			UniversalDrawableArray get_drawables(void); /* Called in Game::draw() */
		private:
			sf::Texture m_frame;
			sf::Sprite m_frame_sprite[LEVELCHOOSER_NUMITEMS];
			sf::Sprite m_level_sprite[LEVELCHOOSER_NUMITEMS];
			sf::Texture m_lock;
			sf::Sprite m_lock_sprite[LEVELCHOOSER_NUMITEMS];
			sf::RectangleShape m_level_bg[LEVELCHOOSER_NUMITEMS];
			FireAnimation m_fire;
			sf::Font m_font1;
			sf::Text m_header;
			sf::Text m_subheading;
			sf::RectangleShape m_backbutton;
			sf::Text m_backtext;
			unsigned int m_lvlc;
			Level m_levels[LEVELCHOOSER_NUMITEMS];
	};
#endif // LEVELCHOOSER_HPP
