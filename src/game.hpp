#ifndef _game_h_
#	define _game_h_
	
#	include <iostream>
#	include <SFML/Window.hpp>
#	include "padding_data_calculator.hpp"
#	include "cursor.hpp"
#	include "video_sequence.hpp"
#	include "config.hpp"
	
	class Game
	{
		public:
			Game();
			~Game();
			
			/*
			 * (Un)Init game:
			*/
			int init(int w, int h, int fullscreen);
			int uninit(void);
			/*
			 * Start main loop:
			*/
			int loop(void);
		private:
			/*
			 * Wait for focus:
			*/
			int wait_for_focus(void);
			/*
			 * Process events:
			*/
			int process_events(void);
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(void);
			
			/*
			 * Internal variables:
			*/
			int m_screen_w;
			int m_screen_h;
			int m_screen_bits;
			int m_framerate_frames;
			sf::RenderWindow m_window;
			sf::RenderTexture m_texture;
			sf::Clock m_framerate_clock;
			PaddingDataCalculator m_padding_data_calculator;
			Cursor m_cursor;
			//VideoSequence m_video_sequence;
			//Config m_config;
			int m_frames;
			int m_window_has_focus;
			/*
			 * Game mode:
			 *  0 - undefined
			 *  ...
			*/
			int m_gamemode;
	};
#endif // _game_h_
