/*
 * singleplayer.hpp
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
#ifndef SINGLEPLAYER_HPP
#	define SINGLEPLAYER_HPP

#	define PLAYER_RUNNING_LEFT 1
#	define PLAYER_RUNNING_RIGHT 2

#	include <math.h>
#	include <sstream>
#	include <SFML/Audio.hpp>
#	include <libintl.h>
#	include "../gamemode.hpp"
#	include "../universal_drawable.hpp"
#	include "../event_processor_return.hpp"
#	include "../dataloader.hpp"
#	include "../level.hpp"
#	include "../widestring.hpp"
	
	class SinglePlayer : public Gamemode
	{
		public:
			SinglePlayer();
			virtual ~SinglePlayer();
			
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
			/*
			 * Place player:
			*/
			void place_player(void);
			/*
			 * Update level:
			*/
			void update_level(void);
			/*
			 * Update item position:
			*/
			void update_itempos(void);
			/*
			 * Update hearts:
			*/
			void update_hearts(void);
			/*
			 * Update health meter:
			*/
			void update_healthm(void);
			/*
			 * Update money:
			*/
			void update_money(void);
			/*
			 * Restart level:
			*/
			void restart_level(void);
			/*
			 * Place message:
			*/
			void place_message(void);
			/*
			 * Play itemsound:
			*/
			void play_itemsound(unsigned int id);
		private:
			void toggle_playertexture(void);

			int m_h, m_w;
			bool m_initialized;
			sf::Texture *m_block_textures;
			sf::Sprite *m_blocks;
			bool m_blocks_i;
			int m_visible_block_number;
			int m_width_hblk;
			sf::Texture m_player_texture;
			unsigned int m_player_textures;
			unsigned int m_player_texture_c;
			int m_player_texturecounter;
			sf::Sprite m_player;
			int m_player_xaction;
			int m_player_ystatus;
			bool m_player_canjump;
			int m_key_goleft;
			int m_key_goright;
			int m_key_jump;
			long double m_playerx;
			long double m_playery;
			long double m_offset;
			unsigned long m_offsetf;
			double m_offsetr;
			double m_playerj;
			double m_blockw;
			double m_blockh;
			Level m_level;
			sf::Clock m_actiontimer;
			sf::Clock m_playertimer;
			sf::Clock m_jumptimer;
			sf::Image m_bg_image;
			sf::Texture m_bg_texture;
			sf::Sprite m_bg;
			bool m_hasbg;
			sf::Texture m_frame_texture;
			sf::Sprite m_frame;
			float m_sframe_scale;
			sf::Texture m_heart;
			sf::Sprite m_hearts[3];
			unsigned int m_hearts_num;
			sf::Texture m_healthm_texture;
			sf::Sprite m_healthm;
			unsigned char m_health;
			unsigned long m_money;
			sf::RectangleShape m_healthm_helper;
			sf::Texture m_ptoilet_texture;
			sf::Sprite m_ptoilet;
			sf::RectangleShape m_ptoiletbase;
			bool m_moving;
			bool m_backwards;
			std::string m_itemdefs[ITEMS_NUMBER] = {
				"coin",
				"bottle"
			};
			sf::Texture m_item_textures[ITEMS_NUMBER];
			int m_visible_item_number;
			sf::Sprite *m_items;
			float m_itemoffset;
			bool m_itemoffsetd;
			sf::Font m_font1;
			sf::Text m_moneytext;
			sf::Text m_heartstext;
			bool m_successful;
			bool m_gameover;
			sf::Text m_message;
			bool m_exit;
			sf::SoundBuffer m_bgbuf;
			sf::Sound m_bgsound;
			sf::SoundBuffer m_itemsounds[ITEMS_NUMBER];
			sf::Sound m_itemsound;
			sf::Texture m_weapon;
			sf::Sprite m_weaponsprite;
			sf::Clock m_blinktimer;
			bool m_blink;
	};
#endif // SINGLEPLAYER_HPP
