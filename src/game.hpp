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
			sf::RenderWindow m_window;
			sf::RenderTexture m_texture;
			PaddingDataCalculator m_padding_data_calculator;
			Cursor m_cursor;
			//VideoSequence m_video_sequence;
			//Config m_config;
			int m_frames;
			/*
			 * Game mode:
			 *  0 - undefined
			 *  ...
			*/
			int m_gamemode;
	};
#endif // _game_h_
