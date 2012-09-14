#ifndef _cursor_h_
#	define _cursor_h_
	
#	include <iostream>
#	include <SDL.h>
#	include "globals.h"
	
	class Cursor
	{
		public:
			Cursor();
			~Cursor();
			
			/*
			 * Init cursor:
			*/
			int init(void);
			void uninit(void);
			/*
			 * Set mouse position:
			*/
			void set_mouse_position(int x, int y);
			/*
			 * Get mouse position:
			*/
			int get_mouse_position_x(void);
			int get_mouse_position_y(void);
			/*
			 * Draw cursor:
			*/
			void draw(SDL_Surface *surface);
			/*
			 * (De)Activate action cursor:
			*/
			void activate_action_cursor(void);
			void deactivate_action_cursor(void);
			/*
			 * Action cursor timer callback:
			*/
			static Uint32 actioncursor_timer_callback(Uint32 intervall, void *parameter);
		private:
			/*
			 * Internal variables:
			*/
			SDL_Surface *m_cursor1;
			SDL_Surface *m_cursor2;
			int m_mouse_x;
			int m_mouse_y;
			SDL_TimerID m_actioncursor_timer;
			int m_actioncursor_active;
	};
#endif // _cursor_h_
