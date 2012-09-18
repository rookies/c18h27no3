#ifndef _cursor_h_
#	define _cursor_h_
	
#	include <iostream>
#	include <SFML/Graphics.hpp>
#	include "globals.hpp"
	
	class Cursor
	{
		public:
			Cursor();
			~Cursor();
			
			/*
			 * Init cursor:
			*/
			int init(void);
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
			sf::Sprite get_drawable(void);
			/*
			 * (De)Activate action cursor:
			*/
			void activate_action_cursor(void);
			void deactivate_action_cursor(void);
		private:
			/*
			 * Internal variables:
			*/
			int m_mouse_x;
			int m_mouse_y;
			int m_actioncursor_active;
			sf::Texture m_cursor1_texture;
			sf::Texture m_cursor2_texture;
	};
#endif // _cursor_h_
