#include "cursor.h"

using namespace std;

Cursor::Cursor()
{
	m_actioncursor_active = 0;
}
Cursor::~Cursor()
{
	uninit();
}
int Cursor::init(void)
{
	cout << "Loading cursor1... ";
	m_cursor1 = SDL_LoadBMP("data/cursor1.bmp");
	if (m_cursor1 == NULL)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	cout << "Loading cursor2... ";
	m_cursor2 = SDL_LoadBMP("data/cursor2.bmp");
	if (m_cursor1 == NULL)
	{
		cout << "[FAIL]" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	return 0;
}
void Cursor::uninit(void)
{
	SDL_FreeSurface(m_cursor1);
	SDL_FreeSurface(m_cursor2);
}
void Cursor::set_mouse_position(int x, int y)
{
	m_mouse_x = x;
	m_mouse_y = y;
}
int Cursor::get_mouse_position_x(void)
{
	return m_mouse_x;
}
int Cursor::get_mouse_position_y(void)
{
	return m_mouse_y;
}
void Cursor::draw(SDL_Surface *surface)
{
	SDL_Rect dst_rect;
	
	dst_rect.x = m_mouse_x-CURSOR_WIDTH/2;
	dst_rect.y = m_mouse_y-CURSOR_HEIGHT/2;
	dst_rect.w = surface->w;
	dst_rect.h = surface->h;
	if (m_actioncursor_active == 1)
		SDL_BlitSurface(m_cursor2, NULL, surface, &dst_rect);
	else
		SDL_BlitSurface(m_cursor1, NULL, surface, &dst_rect);
}
void Cursor::activate_action_cursor(void)
{
	if (m_actioncursor_active == 0)
	{
		m_actioncursor_active = 1;
		//m_actioncursor_timer = SDL_AddTimer(100, actioncursor_timer_callback, this);
	};
}
void Cursor::deactivate_action_cursor(void)
{
	if (m_actioncursor_active == 1)
	{
		m_actioncursor_active = 0;
		SDL_RemoveTimer(m_actioncursor_timer);
	};
}
Uint32 Cursor::actioncursor_timer_callback(Uint32 intervall, void *parameter)
{
	Cursor *cursor = reinterpret_cast<Cursor*>(parameter);
	cursor->deactivate_action_cursor();
	return intervall;
}
