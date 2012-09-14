#ifndef _game_h_
#	define _game_h_
	
#	include <iostream>
#	include <SDL.h>
#	include <SDL_image.h>
#	include <SDL_rotozoom.h>
#	include "padding_data_calculator.h"
#	include "video_sequence.h"
#	include "cursor.h"
#	include "config.h"
	
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
			 * Create surface:
			*/
			int create_surface(void);
			/*
			 * Calculate sizes:
			*/
			int calculate_sizes(void);
			/*
			 * Init window:
			*/
			int init_window(void);
			
			/*
			 * Internal variables:
			*/
			SDL_Surface *m_screen;
			SDL_Surface *m_surface;
			Uint32 m_screenflags;
			int m_screen_w;
			int m_screen_h;
			PaddingDataCalculator m_padding_data_calculator;
			VideoSequence m_video_sequence;
			Cursor m_cursor;
			Config m_config;
			/*
			 * Game mode:
			 *  0 - undefined
			 *  ...
			*/
			int m_gamemode;
	};
#endif // _game_h_
