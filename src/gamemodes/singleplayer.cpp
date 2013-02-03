/*
 * FILEHEADER
 */
#include "singleplayer.hpp"

SinglePlayer::SinglePlayer() : m_player_action(0), m_player_texture2_en(false), m_player_texturecounter(0)
{

}
SinglePlayer::~SinglePlayer()
{
	delete[] m_testblocks;
}
int SinglePlayer::init(Config conf)
{
	/*
	 * Variable declarations:
	*/
	int i;
	/*
	 * Load grass block texture:
	*/
	if (!m_testblock_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "grass.png")))
		return 1;
	/*
	 * Load player textures:
	*/
	if (!m_player_texture1.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_frame1.png")))
		return 1;
	if (!m_player_texture2.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_frame2.png")))
		return 1;
	/*
	 * Set player properties:
	*/
	m_player.setTexture(m_player_texture1);
	/*
	 * Set key values:
	*/
	m_key_goleft = conf.get("CONTROL__KEY_GOLEFT").value_int;
	m_key_goright = conf.get("CONTROL__KEY_GORIGHT").value_int;
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
	int i;
	int block_height;
	int block_width;
	/*
	 * Calculate block sizes:
	*/
	block_height = h/VERTICAL_BLOCK_NUMBER;
	block_width = 2*block_height;
	/*
	 * Calculate block number:
	*/
	m_testblock_num = ceil(w/float(block_width));
	m_testblocks = new sf::Sprite[m_testblock_num];
	/*
	 * Create grass block sprites (should be in init(), but we need the screen width):
	*/
	for (i=0; i < m_testblock_num; i++)
		m_testblocks[i].setTexture(m_testblock_texture);
	/*
	 * Set block properties:
	*/
	m_startpos_x = block_width/2.;
	m_startpos_y = h-(block_height/2.);
	for (i=0; i < m_testblock_num; i++)
	{
		m_testblocks[i].setPosition(sf::Vector2f(i*block_width, m_startpos_y));
		m_testblocks[i].setScale(block_width/32., block_height/16.);
	}
	/*
	 * Set player properties:
	*/
	m_player.scale((block_width/2.)/16, (block_height*1.5)/24);
	m_player.setPosition(sf::Vector2f(m_startpos_x, m_startpos_y-block_height*1.5));
	m_endpos_x = w-m_startpos_x-m_player.getGlobalBounds().width;
	/*
	 * Calculate stepwidth:
	*/
	m_stepwidth = w/STEPS_PER_SCREENWIDTH;
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
				default:
					if (event.key.code == m_key_goleft && m_player.getGlobalBounds().left >= m_startpos_x)
						m_player_action = PLAYER_RUNNING_LEFT;
					else if (event.key.code == m_key_goright && m_player.getGlobalBounds().left <= m_endpos_x)
						m_player_action = PLAYER_RUNNING_RIGHT;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == m_key_goleft && m_player_action == PLAYER_RUNNING_LEFT)
				m_player_action = 0;
			else if (event.key.code == m_key_goright && m_player_action == PLAYER_RUNNING_RIGHT)
				m_player_action = 0;
			break;
	}
}
UniversalDrawableArray SinglePlayer::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	int i;
	UniversalDrawableArray arr;
	/*
	 * Perform player actions:
	*/
	switch (m_player_action)
	{
		case PLAYER_RUNNING_LEFT:
			if (m_player.getGlobalBounds().left >= m_startpos_x)
			{
				m_player.move(sf::Vector2f(-m_stepwidth, 0));
				toggle_playertexture();
			}
			else
				m_player_action = 0;
			break;
		case PLAYER_RUNNING_RIGHT:
			if (m_player.getGlobalBounds().left <= m_endpos_x)
			{
				m_player.move(sf::Vector2f(m_stepwidth, 0));
				toggle_playertexture();
			}
			else
				m_player_action = 0;
			break;
	}
	/*
	 * Fill array:
	*/
	arr.init(m_testblock_num+1);
	for (i=0; i < m_testblock_num; i++)
		arr.add_sprite(m_testblocks[i]);
	arr.add_sprite(m_player);
	return arr;
}
void SinglePlayer::toggle_playertexture(void)
{
	if (m_player_texturecounter < 5)
	{
		m_player_texturecounter++;
		return;
	};
	if (m_player_texture2_en)
	{
		m_player.setTexture(m_player_texture1);
		m_player_texture2_en = false;
	}
	else
	{
		m_player.setTexture(m_player_texture2);
		m_player_texture2_en = true;
	};
	m_player_texturecounter = 0;
}
