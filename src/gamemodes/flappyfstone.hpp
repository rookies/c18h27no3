/*
 * flappyfstone.hpp
 * 
 * Copyright 2014 Robert Knauer <robert@capsaicin-dev.de>
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
#ifndef FLAPPYFSTONE_HPP
#	define FLAPPYFSTONE_HPP

#	define FLAPPYFSTONE_PIPENUM 12

#	include "../gamemode.hpp"
#	include "../universal_drawable.hpp"
#	include "../event_processor_return.hpp"
#	include "../dataloader.hpp"
	
	class FlappyFStone : public Gamemode
	{
		public:
			FlappyFStone();
			virtual ~FlappyFStone();
			
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
			void update_points(void);
		
			unsigned int m_pipes_visible;
			int m_pipe_overwrite;
			bool m_pipes_wasfull;
			unsigned int m_w, m_h;
			sf::RectangleShape m_pipes[FLAPPYFSTONE_PIPENUM];
			sf::Clock m_creationtimer;
			sf::Clock m_movementtimer;
			int m_lastpos;
			unsigned int m_gapheight;
			sf::Texture m_fstone_texture;
			sf::Sprite m_fstone;
			bool m_rising;
			sf::Clock m_risingtimer;
			bool m_failed;
			unsigned int m_points;
			sf::Font m_font1;
			sf::Text m_pointstext;
			sf::Clock m_exittimer;
	};
#endif // FLAPPYFSTONE_HPP
