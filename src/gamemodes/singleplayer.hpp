/*
 * FILEHEADER
 */
#ifndef SINGLEPLAYER_HPP
#	define SINGLEPLAYER_HPP

#	include "../gamemode.hpp"
#	include "../universal_drawable.hpp"
#	include "../event_processor_return.hpp"
	
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
			
	};
#endif // SINGLEPLAYER_HPP
