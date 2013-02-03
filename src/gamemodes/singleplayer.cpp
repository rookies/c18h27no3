/*
 * FILEHEADER
 */
#include "singleplayer.hpp"

SinglePlayer::SinglePlayer()
{

}
SinglePlayer::~SinglePlayer()
{

}
int SinglePlayer::init(Config conf)
{
	/*
	 * ...
	*/
	return 0;
}
int SinglePlayer::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int SinglePlayer::calculate_sizes(int w, int h)
{
	/*
	 * ...
	*/
	return 0;
}
void SinglePlayer::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					ret->set_gamemode(1);
					break;
			}
			break;
	}
}
UniversalDrawableArray SinglePlayer::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	UniversalDrawableArray arr;
	/*
	 * ...
	*/
	arr.init(0);
	return arr;
}
