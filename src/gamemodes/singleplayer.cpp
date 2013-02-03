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
	if (!m_testblock_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "test.png")))
		return 1;
	m_testblock.setTexture(m_testblock_texture);
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
	 * Variable declarations:
	*/
	int block_height;
	int block_width;
	/*
	 * Calculate block sizes:
	*/
	block_height = (h/VERTICAL_BLOCK_NUMBER);
	block_width = 2*block_height;
	/*
	 * Set block properties:
	*/
	m_testblock.setPosition(sf::Vector2f(0, h-block_height));
	m_testblock.setScale(block_width/32., block_height/16.);
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
	 * Fill array:
	*/
	arr.init(1);
	arr.add_sprite(m_testblock);
	return arr;
}
