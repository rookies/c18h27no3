/*
 * FILEHEADER
 */
#include "GAMEMODE.hpp"

CLASSNAME::CLASSNAME()
{

}
CLASSNAME::~CLASSNAME()
{

}
int CLASSNAME::init(Config conf)
{
	/*
	 * ...
	*/
	return 0;
}
int CLASSNAME::uninit(void)
{
	/*
	 * ...
	*/
	return 0;
}
int CLASSNAME::calculate_sizes(int w, int h)
{
	/*
	 * ...
	*/
	return 0;
}
void CLASSNAME::process_event(sf::Event event, int mouse_x, int mouse_y, EventProcessorReturn *ret)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Escape:
					//ret->set_gamemode(1);
					break;
			}
			break;
	}
}
UniversalDrawableArray CLASSNAME::get_drawables(void)
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
