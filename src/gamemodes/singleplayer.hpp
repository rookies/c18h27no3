/*
 * FILEHEADER
 */
#ifndef SINGLEPLAYER_HPP
#	define SINGLEPLAYER_HPP

#	define PLAYER_RUNNING_LEFT 1
#	define PLAYER_RUNNING_RIGHT 2

#	include <math.h>
#	include "../gamemode.hpp"
#	include "../universal_drawable.hpp"
#	include "../event_processor_return.hpp"
#	include "../dataloader.hpp"
	
	class SinglePlayer : public Gamemode
	{
		public:
			SinglePlayer();
			virtual ~SinglePlayer();
			
			/*
			 * (Un)init:
			*/
			int init(Config conf); /* Called in Game::init_gamemode() */
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
			void toggle_playertexture(void);
			
			sf::Texture m_testblock_texture;
			sf::Sprite *m_testblocks;
			sf::Sprite m_testblock;
			int m_testblock_num;
			sf::Texture m_player_texture1;
			sf::Texture m_player_texture2;
			bool m_player_texture2_en;
			int m_player_texturecounter;
			sf::Sprite m_player;
			int m_startpos_x;
			int m_startpos_y;
			int m_endpos_x;
			int m_player_action;
			int m_key_goleft;
			int m_key_goright;
			float m_stepwidth;
	};
#endif // SINGLEPLAYER_HPP
