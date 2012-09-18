#include "cursor.h"

using namespace std;

Cursor::Cursor()
{
	m_actioncursor_active = 0;
}
Cursor::~Cursor()
{
	
}
int Cursor::init(void)
{
	/*
	 * Load cursor1:
	*/
	cout << "Loading cursor1... ";
	if (!m_cursor1_texture.loadFromFile("data/cursor1.png"))
	{
		cout << "[FAIL]" << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	/*
	 * Load cursor2:
	*/
	cout << "Loading cursor2... ";
	if (!m_cursor2_texture.loadFromFile("data/cursor2.png"))
	{
		cout << "[FAIL]" << endl;
		return 1;
	};
	cout << "[DONE]" << endl;
	return 0;
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
sf::Sprite Cursor::get_drawable(void)
{
	/*
	 * Variable declarations:
	*/
	sf::Sprite sprite;
	/*
	 * Check if actioncursor is active:
	*/
	if (m_actioncursor_active == 1)
		sprite.setTexture(m_cursor2_texture);
	else
		sprite.setTexture(m_cursor1_texture);
	/*
	 * Set position:
	*/
	sprite.setPosition(m_mouse_x-CURSOR_WIDTH/2, m_mouse_y-CURSOR_HEIGHT/2);
	/*
	 * Set color:
	*/
	sprite.setColor(sf::Color(255, 255, 255, 255));
	return sprite;
}
void Cursor::activate_action_cursor(void)
{
	if (m_actioncursor_active == 0)
	{
		m_actioncursor_active = 1;
	};
}
void Cursor::deactivate_action_cursor(void)
{
	if (m_actioncursor_active == 1)
	{
		m_actioncursor_active = 0;
	};
}
