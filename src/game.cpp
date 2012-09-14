#include "game.h"

using namespace std;

Game::Game()
{
	
}
Game::~Game()
{
	
}
int Game::init(int w, int h, int fullscreen)
{
	/*
	 * Variable declarations:
	*/
	int i;
	Uint32 flags;
	int w_;
	int h_;
	const SDL_VideoInfo *videoinfo;
	SDL_Rect **modes;
	/*
	 * Initialize SDL:
	*/
	cout << "Trying to initialize SDL... ";
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		return 1;
	}
	else
	{
		cout << "[DONE]" << endl;
	};
	/*
	 * Get video info:
	*/
	cout << "Getting video info..." << endl;
	videoinfo = SDL_GetVideoInfo();
	cout << "  Screen Resolution: " << videoinfo->current_w << "x" << videoinfo->current_h << endl;
	/*
	 * Check forced screen width:
	*/
	if (w == -1)
	{
		m_screen_w = videoinfo->current_w;
	}
	else
	{
		m_screen_w = w;
		cout << "  Forced Screen Width: " << w << endl;
	};
	/*
	 * Check forced screen height:
	*/
	if (h == -1)
	{
		m_screen_h = videoinfo->current_h;
	}
	else
	{
		m_screen_h = h;
		cout << "  Forced Screen Height: " << h << endl;
	};
	/*
	 * Create flag variable:
	*/
	if (fullscreen == 1)
		m_screenflags = SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF;
	else
		m_screenflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	/*
	 * Get modes:
	*/
	cout << "Getting video modes... ";
	modes = SDL_ListModes(NULL, m_screenflags);
	if (modes == (SDL_Rect**)0)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: No modes available!" << endl;
		return 1;
	}
	else if (modes == (SDL_Rect**)-1)
	{
		cout << "[DONE]" << endl;
		cout << "All modes available!" << endl;
	}
	else
	{
		cout << "[DONE]" << endl;
		cout << "Available modes:" << endl;
		for (i=0; modes[i]; i++)
			cout <<  "  " << modes[i]->w << "x" << modes[i]->h << endl;
	};
	/*
	 * Init window:
	*/
	if (init_window() == 1)
		return 1;
	/*
	 * Finish successful:
	*/
	return 0;
}
int Game::uninit(void)
{
	SDL_FreeSurface(m_surface);
	SDL_FreeSurface(m_screen);
	m_cursor.uninit();
	SDL_Quit();
	return 0;
}
int Game::loop(void)
{
	/*
	 * Variable definitons:
	*/
	int done = 0;
	SDL_Rect rect, rect2;
	SDL_Surface *img;
	SDL_Surface *img2;
	/*
	 * Loop:
	*/
	while (done == 0)
	{
		/*
		 * Process events:
		*/
		done = process_events();
		/*
		 * Clean surfaces:
		*/
		SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 156, 156, 156));
		SDL_FillRect(m_screen, NULL, SDL_MapRGB(m_screen->format, 0, 0, 0));
		/*
		 * Blit everything on padded surface:
		*/
		img = IMG_Load("data/grass.png");
		img2 = zoomSurface(img, 10.0, 10.0, 0);
		rect2.x = 5;
		rect2.y = 5;
		rect2.w = m_padding_data_calculator.get_usable_w();
		rect2.h = m_padding_data_calculator.get_usable_h();
		SDL_BlitSurface(img2, NULL, m_surface, &rect2);
		SDL_FreeSurface(img2);
		img2 = zoomSurface(img, 10.0, 10.0, 1);
		rect2.x = 210;
		rect2.y = 5;
		rect2.w = m_padding_data_calculator.get_usable_w();
		rect2.h = m_padding_data_calculator.get_usable_h();
		SDL_BlitSurface(img2, NULL, m_surface, &rect2);
		SDL_FreeSurface(img2);
		SDL_FreeSurface(img);
		m_cursor.draw(m_surface);
		/*
		 * Update padded surface:
		*/
		SDL_UpdateRect(m_surface, 0, 0, 0, 0);
		/*
		 * Blit padded surface on screen, update and flip:
		*/
		rect.x = m_padding_data_calculator.get_padding_x();
		rect.y = m_padding_data_calculator.get_padding_y();
		rect.w = m_padding_data_calculator.get_usable_w();
		rect.h = m_padding_data_calculator.get_usable_h();
		SDL_BlitSurface(m_surface, NULL, m_screen, &rect);
		SDL_UpdateRect(m_screen, 0, 0, 0, 0);
        SDL_Flip(m_screen);
	}
	return done;
}
int Game::process_events(void)
{
	/*
	 * Variable definitons:
	*/
	SDL_Event event;
	int x, y;
	/*
	 * Check for events:
	*/
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_MOUSEMOTION:
				/*
				 * Calculate new mouse position:
				*/
				x = event.motion.x-m_padding_data_calculator.get_padding_x();
				y = event.motion.y-m_padding_data_calculator.get_padding_y();
				if (x < 0)
					x = 0;
				else if (x > m_padding_data_calculator.get_usable_w())
					x = m_padding_data_calculator.get_usable_w();
				if (y < 0)
					y = 0;
				else if (y > m_padding_data_calculator.get_usable_h())
					y = m_padding_data_calculator.get_usable_h();
				/*
				 * Set mouse position:
				*/
				m_cursor.set_mouse_position(x, y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				cout << "MOUSEBUTTONDOWN ";
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						cout << "LEFT";
						m_cursor.activate_action_cursor();
						break;
					case SDL_BUTTON_MIDDLE:
						cout << "MIDDLE";
						break;
					case SDL_BUTTON_RIGHT:
						cout << "RIGHT";
						break;
				}
				x = event.button.x-m_padding_data_calculator.get_padding_x();
				y = event.button.y-m_padding_data_calculator.get_padding_y();
				if (x < 0)
					x = 0;
				else if (x > m_padding_data_calculator.get_usable_w())
					x = m_padding_data_calculator.get_usable_w();
				if (y < 0)
					y = 0;
				else if (y > m_padding_data_calculator.get_usable_h())
					y = m_padding_data_calculator.get_usable_h();
				cout << " @ (" << x << "," << y << ")" << endl;
				break;
			case SDL_MOUSEBUTTONUP:
				cout << "MOUSEBUTTONUP ";
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
						cout << "LEFT";
						m_cursor.deactivate_action_cursor();
						break;
					case SDL_BUTTON_MIDDLE:
						cout << "MIDDLE";
						break;
					case SDL_BUTTON_RIGHT:
						cout << "RIGHT";
						break;
				}
				x = event.button.x-m_padding_data_calculator.get_padding_x();
				y = event.button.y-m_padding_data_calculator.get_padding_y();
				if (x < 0)
					x = 0;
				else if (x > m_padding_data_calculator.get_usable_w())
					x = m_padding_data_calculator.get_usable_w();
				if (y < 0)
					y = 0;
				else if (y > m_padding_data_calculator.get_usable_h())
					y = m_padding_data_calculator.get_usable_h();
				cout << " @ (" << x << "," << y << ")" << endl;
				break;
			case SDL_KEYDOWN:
				cout << "KEYDOWN " << event.key.keysym.sym << endl;
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						cout << "ESCAPE key pressed." << endl;
						return 1;
						break;
					case SDLK_F1:
						cout << "F1 key pressed." << endl;
						return 2;
						break;
				}
				break;
			case SDL_QUIT:
				cout << "QUIT signal received." << endl;
				return 1;
				break;
		}
	}
	/*
	 * Finish successful:
	*/
	return 0;
}
int Game::create_surface(void)
{
	cout << "Creating padded surface... ";
	m_surface = SDL_CreateRGBSurface(
		SDL_HWSURFACE,
		int(m_padding_data_calculator.get_usable_w()),
		int(m_padding_data_calculator.get_usable_h()),
		32,
		0,
		0,
		0,
		0
	);
	if (m_surface == NULL)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	return 0;
}
int Game::calculate_sizes(void)
{
	
}
int Game::init_window(void)
{
	/*
	 * Set video mode:
	*/
	cout << "Setting video mode (" << m_screen_w << "x" << m_screen_h << ")... ";
	m_screen = SDL_SetVideoMode(m_screen_w, m_screen_h, 32, m_screenflags);
	if (m_screen == NULL)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	/*
	 * Set window caption:
	*/
	SDL_WM_SetCaption("Game", NULL);
	/*
	 * Calculate padding data:
	*/
	m_padding_data_calculator.set_screen_w(double(m_screen_w));
	m_padding_data_calculator.set_screen_h(double(m_screen_h));
	m_padding_data_calculator.calculate();
	/*
	 * Create padded surface:
	*/
	if (create_surface() == 1)
		return 1;
	/*
	 * Init cursor:
	*/
	SDL_ShowCursor(0);
	if (m_cursor.init() == 1)
		return 1;
	m_cursor.set_mouse_position(
		int(m_padding_data_calculator.get_usable_w()/2.0),
		int(m_padding_data_calculator.get_usable_h()/2.0)
	);
}
