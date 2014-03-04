/*
 * minigames.hpp
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
#ifndef MINIGAMES_HPP
#	define MINIGAMES_HPP

#	define PLAYER_RUNNING_LEFT 1
#	define PLAYER_RUNNING_RIGHT 2

#	include "../gamemode.hpp"
#	include "../universal_drawable.hpp"
#	include "../event_processor_return.hpp"
#	include "../dataloader.hpp"
	
	class Minigames : public Gamemode
	{
		public:
			Minigames();
			virtual ~Minigames();
			
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
			void place_player(void);
			void toggle_playertexture(void);
			
			sf::Texture m_grass_texture;
			sf::Sprite m_grass;
			sf::Texture m_player_texture;
			sf::Sprite m_player;
			sf::Texture m_door;
			sf::Sprite m_doors[MINIGAMES_DOORNUM];
			sf::Texture m_exit_texture;
			sf::Sprite m_exit;
			int m_key_goleft;
			int m_key_goright;
			long double m_playerx;
			int m_player_xaction;
			double m_blockw;
			double m_blockh;
			bool m_backwards;
			sf::Clock m_actiontimer;
			sf::Clock m_playertimer;
			unsigned int m_player_textures;
			unsigned int m_player_texture_c;
			int m_player_texturecounter;
	};
#endif // MINIGAMES_HPP
