#ifndef _game_h_
	#define _game_h_
	
	#include <iostream>
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_rotozoom.h>
	#include "padding_data_calculator.h"
	#include "video_sequence.h"
	#include "cursor.h"
	
	class Game
	{
		public:
			Game();
			~Game();
			
			/*
			 * Init game:
			*/
			int init(int w, int h, int fullscreen);
			/*
			 * Start main loop:
			*/
			void loop(void);
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
			 * Internal variables:
			*/
			const SDL_VideoInfo *m_videoinfo;
			SDL_Rect **m_modes;
			SDL_Surface *m_screen;
			SDL_Surface *m_surface;
			PaddingDataCalculator m_padding_data_calculator;
			VideoSequence m_video_sequence;
			Cursor m_cursor;
			/*
			 * Game mode:
			 *  0 - undefined
			 *  ...
			*/
			int m_gamemode;
	};
#endif // _game_h_
