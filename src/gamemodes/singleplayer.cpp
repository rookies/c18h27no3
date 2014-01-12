/*
 * singleplayer.cpp
 * 
 * Copyright 2013 Robert Knauer <robert@privatdemail.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include "singleplayer.hpp"

SinglePlayer::SinglePlayer() : 	m_player_xaction(0),
								m_player_ystatus(0),
								m_player_texture2_en(false),
								m_player_texturecounter(0),
								m_initialized(false),
								m_player_canjump(false),
								m_offset(0),
								m_blocks_i(false),
								m_hearts_num(3),
								m_health(100.),
								m_playerx(PLAYERPOS_X),
								m_playery(PLAYERPOS_Y),
								m_moving(false),
								m_backwards(false),
								m_itemoffset(0),
								m_itemoffsetd(false),
								m_money(0),
								m_successful(false),
								m_gameover(false),
								m_exit(false)
{

}
SinglePlayer::~SinglePlayer()
{
	if (m_initialized)
		delete[] m_block_textures;
}
int SinglePlayer::init(Config conf, std::string arg)
{
	/*
	 * Variable declarations:
	*/
	int i;
	std::string fname;
	/*
	 * Load player textures:
	*/
	if (!m_player_f0.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_f0.png")))
		return 1;
	if (!m_player_f1.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_f1.png")))
		return 1;
	if (!m_player_rf0.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_rf0.png")))
		return 1;
	if (!m_player_rf1.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "player_rf1.png")))
		return 1;
	/*
	 * Set player properties:
	*/
	m_player.setTexture(m_player_f0);
	/*
	 * Set key values:
	*/
	m_key_goleft = conf.get("CONTROL__KEY_GOLEFT").value_int;
	m_key_goright = conf.get("CONTROL__KEY_GORIGHT").value_int;
	m_key_jump = conf.get("CONTROL__KEY_JUMP").value_int;
	/*
	 * Load level from file:
	*/
	if (arg.compare("") == 0)
	{
		if (!m_level.load_from_file("level1.dat"))
			return 1;
	}
	else
	{
		if (!m_level.load_from_file(arg))
			return 1;
	};
	/*
	 * Load block textures:
	*/
	m_block_textures = new sf::Texture[m_level.get_blockdefs_number()];
	m_initialized = true;
	for (i=0; i < m_level.get_blockdefs_number(); i++)
	{
		if (m_level.get_blockdef(i).get_type() == BLOCKDEF_TYPE_BUILTIN)
		{
			fname = "";
			fname.append("blocks/");
			fname.append(m_level.get_blockdef(i).get_arg());
			fname.append(".png");
			if (!m_block_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, fname)))
			{
				if (!m_block_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "block_not_found.png")))
					return 1;
			};
		}
		else
		{
			if (!m_block_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "block_not_found.png")))
				return 1;
		};
	}
	/*
	 * Load item textures:
	*/
	for (i=0; i < ITEMS_NUMBER; i++)
	{
		fname = "";
		fname.append("items/");
		fname.append(m_itemdefs[i]);
		fname.append(".png");
		if (!m_item_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, fname)))
		{
			if (!m_item_textures[i].loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "item_not_found.png")))
				return 1;
		};
	}
	/*
	 * Load background texture:
	*/
	if (m_level.has_bgimg())
	{
		fname = "";
		fname.append("backgrounds/");
		fname.append(m_level.get_bgimg());
		fname.append(".png");
		if (!m_bg_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, fname)))
			return 1;
		m_bg.setTexture(m_bg_texture);
	};
	/*
	 * Load background music:
	*/
	if (m_level.has_bgmusic())
	{
		fname = "";
		fname.append("backgrounds/");
		fname.append(m_level.get_bgmusic());
		fname.append(".ogg");
		if (!m_bgbuf.loadFromFile(get_data_path(DATALOADER_TYPE_SOUND, fname)))
			return 1;
		m_bgsound.setBuffer(m_bgbuf);
		m_bgsound.setLoop(true);
		m_bgsound.setVolume(conf.get("SOUND__GAME_MUSIC_VOLUME").value_int);
		m_bgsound.play();
	};
	/*
	 * Load status frame texture:
	*/
	if (!m_frame_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "statusframe.png")))
		return 1;
	m_frame.setTexture(m_frame_texture);
	/*
	 * Load heart textures:
	*/
	if (!m_heart.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "heart.png")))
		return 1;
	if (!m_heart_grey.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "heart_grey.png")))
		return 1;
	/*
	 * Load health meter texture:
	*/
	if (!m_healthm_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "healthmeter.png")))
		return 1;
	m_healthm.setTexture(m_healthm_texture);
	/*
	 * Load portable toilet texture:
	*/
	if (!m_ptoilet_texture.loadFromFile(get_data_path(DATALOADER_TYPE_IMG, "blocks/ptoilet_green4.png")))
		return 1;
	m_ptoilet.setTexture(m_ptoilet_texture);
	/*
	 * Init portable toilet base:
	*/
	m_ptoiletbase.setFillColor(sf::Color::Black);
	m_ptoiletbase.setOutlineThickness(0);
	/*
	 * Init health meter helper:
	*/
	m_healthm_helper.setFillColor(sf::Color::Black);
	m_healthm_helper.setOutlineThickness(0);
	/*
	 * Load font:
	*/
	if (!m_font1.loadFromFile(get_data_path(DATALOADER_TYPE_FONT, "PressStart2P.ttf")))
		return 1;
	/*
	 * Load item sounds:
	*/
	if (!m_coinsound_buf.loadFromFile(get_data_path(DATALOADER_TYPE_SOUND, "items/coin.ogg")))
		return 1;
	m_coinsound.setBuffer(m_coinsound_buf);
	m_coinsound.setVolume(conf.get("SOUND__GAME_SOUND_VOLUME").value_int);
	/*
	 * Init texts:
	*/
	m_moneytext.setFont(m_font1);
	m_moneytext.setColor(sf::Color::Black);
	m_heartstext.setFont(m_font1);
	m_heartstext.setColor(sf::Color::Black);
	m_message.setFont(m_font1);
	m_message.setColor(sf::Color::Red);
	/*
	 * Init hearts:
	*/
	update_hearts();
	/*
	 * Init money:
	*/
	update_money();
	/*
	 * Init timers:
	*/
	m_actiontimer.restart();
	m_playertimer.restart();
	return 0;
}
int SinglePlayer::uninit(void)
{
	/*
	 * Stop music:
	*/
	if (m_level.has_bgmusic())
		m_bgsound.stop();
	return 0;
}
int SinglePlayer::calculate_sizes(int w, int h)
{
	m_w = w;
	m_h = h;
	/*
	 * Variable declarations:
	*/
	float scale;
	unsigned int i;
	/*
	 * Calculate block sizes:
	*/
	m_blockh = h/VERTICAL_BLOCK_NUMBER;
	m_blockw = 2*m_blockh;
	/*
	 * Draw level:
	*/
	update_level();
	/*
	 * Set player properties:
	*/
	m_player.setScale((m_blockw)/16, (m_blockh*3)/24);
	place_player();
	/*
	 * Scale background sprite:
	*/
	m_bg.setScale(h/SIZE_GAME_BG_IMGHEIGHT, h/SIZE_GAME_BG_IMGHEIGHT);
	/*
	 * Set statusframe properties:
	*/
	m_sframe_scale = (h*SIZE_STATUSFRAME_HEIGHT/100.)/SIZE_STATUSFRAME_IMGHEIGHT;
	m_frame.setScale(m_sframe_scale, m_sframe_scale);
	m_frame.setPosition(sf::Vector2f(w*SIZE_STATUSFRAME_XOFFSET/100., h*SIZE_STATUSFRAME_YOFFSET/100.));
	/*
	 * Set health meter properties:
	*/
	m_healthm.setScale(m_sframe_scale, m_sframe_scale);
	/*
	 * Init health meter:
	*/
	update_healthm();
	/*
	 * Set health meter helper properties:
	*/
	m_healthm_helper.setSize(sf::Vector2f(m_sframe_scale, 5*m_sframe_scale));
	m_healthm_helper.setPosition(sf::Vector2f(w*SIZE_HEALTHMETER_HELPER_XOFFSET/100., h*SIZE_HEALTHMETER_HELPER_YOFFSET/100.));
	/*
	 * Set heart properties:
	*/
	scale = (h*SIZE_HEARTS/100.)/SIZE_HEARTS_IMGSIZE;
	for (i=0; i < 3; i++)
	{
		m_hearts[i].setScale(scale, scale);
		m_hearts[i].setPosition(sf::Vector2f(w*SIZE_HEARTS_XOFFSET/100., (h*SIZE_HEARTS_YOFFSET0/100.)+(i*h*SIZE_HEARTS/100.)+(i*h*SIZE_HEARTS_YGAP/100.)));
	}
	/*
	 * Set portable toilet properties:
	*/
	m_ptoilet.setScale(m_blockw/32., m_blockh/16.);
	/*
	 * Set text properties:
	*/
	m_moneytext.setCharacterSize(h/SIZE_GAME_MONEYTEXT_SIZE_DIVIDER);
	m_moneytext.setPosition(sf::Vector2f(w*SIZE_GAME_MONEYTEXT_XOFFSET/100., h*SIZE_GAME_MONEYTEXT_YOFFSET/100.));
	m_heartstext.setCharacterSize(h/SIZE_GAME_HEARTSTEXT_SIZE_DIVIDER);
	m_heartstext.setPosition(sf::Vector2f(w*SIZE_GAME_HEARTSTEXT_XOFFSET/100., h*SIZE_GAME_HEARTSTEXT_YOFFSET/100.));
	m_message.setCharacterSize(h/SIZE_GAME_MESSAGE_SIZE_DIVIDER);
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
					ret->set_gamemode(9); // levelchooser
					break;
				default:
					if (event.key.code == m_key_goleft)
						m_player_xaction = PLAYER_RUNNING_LEFT;
					else if (event.key.code == m_key_goright)
						m_player_xaction = PLAYER_RUNNING_RIGHT;
					else if (event.key.code == m_key_jump && m_player_canjump && m_player_ystatus == 0)
					{
						m_player_ystatus = 1;
						m_playerj = 0;
						m_jumptimer.restart();
					};
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == m_key_goleft && m_player_xaction == PLAYER_RUNNING_LEFT)
				m_player_xaction = 0;
			else if (event.key.code == m_key_goright && m_player_xaction == PLAYER_RUNNING_RIGHT)
				m_player_xaction = 0;
			break;
	}
	if (m_exit)
		ret->set_gamemode(9); // levelchooser
}
UniversalDrawableArray SinglePlayer::get_drawables(void)
{
	/*
	 * Variable declarations:
	*/
	int i, j, x, highest, colno;
	UniversalDrawableArray arr;
	LevelColumn *col;
	double incr, lowest, multip, ssize, y, z;
	bool barrier;
	sf::FloatRect rect;
	long el;
	/*
	 * Perform player actions:
	*/
	if (m_moving)
	{
		multip = m_actiontimer.getElapsedTime().asMilliseconds()/12.;
		ssize = PLAYER_XSTEPSIZE*multip;
		/*
		 * Perform X actions (running):
		*/
		switch (m_player_xaction)
		{
			case PLAYER_RUNNING_LEFT:
				if (m_playerx-ssize >= 0)
				{
					/*
					 * Check for barriers:
					*/
					barrier = false;
					col = m_level.get_column(floor(m_playerx)-1);
					rect = m_player.getGlobalBounds();
					rect.left -= ssize*m_blockw;
					for (i=0; i < col->get_blocknumber(); i++)
					{
						if (m_blocks[col->get_block(i)->offset].getGlobalBounds().intersects(rect))
							barrier = true;
					}
					if (!barrier)
					{
						/*
						 * Move:
						*/
						m_playerx -= ssize;
						m_backwards = true;
						toggle_playertexture();
						if (m_playerx-m_offset <= 15 && m_offset-0.1 >= 0)
						{
							m_offset -= ssize;
							update_level();
						};
						place_player();
					};
				}
				else
					m_player_xaction = 0;
				break;
			case PLAYER_RUNNING_RIGHT:
				if (m_playerx <= m_level.get_levelwidth()-2)
				{
					/*
					 * Check for barriers:
					*/
					barrier = false;
					col = m_level.get_column(floor(m_playerx)+1);
					rect = m_player.getGlobalBounds();
					rect.left += ssize*m_blockw;
					for (i=0; i < col->get_blocknumber(); i++)
					{
						if (m_blocks[col->get_block(i)->offset].getGlobalBounds().intersects(rect))
							barrier = true;
					}
					if (!barrier)
					{
						/*
						 * Move:
						*/
						m_playerx += ssize;
						m_backwards = false;
						toggle_playertexture();
						if (m_playerx-m_offset >= 17 && m_offset+0.1 <= m_level.get_levelwidth()-HORIZONTAL_BLOCK_NUMBER)
						{
							m_offset += ssize;
							update_level();
						};
						place_player();
					};
				}
				else
					m_player_xaction = 0;
				break;
		}
		/*
		 * Perform Y actions (jumping, falling):
		*/
		if (m_player_ystatus > 0)
		{
			/*
			 * We're jumping!
			 * Check if it's still possible:
			*/
			lowest = 100;
			for (i=-1; i < 2; i++)
			{
				col = m_level.get_column(floor(m_playerx)+i);
				for (j=0; j < col->get_blocknumber(); j++)
				{
					if (col->get_block(j)->position < lowest && m_playery+6 < col->get_block(j)->position)
						lowest = col->get_block(j)->position;
				}
			}
			lowest += 0.5;
			if (lowest-2 > m_playery+6)
			{
				if (m_jumptimer.getElapsedTime().asMilliseconds() > JUMPTIME_MS)
					m_player_ystatus = 0;
				else
				{
					el = m_jumptimer.getElapsedTime().asMilliseconds();
					m_playery -= m_playerj;
					m_playerj = -(JUMPHEIGHT/(JUMPTIME_MS*JUMPTIME_MS))*el*el + (2*JUMPHEIGHT/JUMPTIME_MS)*el; // s(t) = -(s_max/(t_max^2))*t^2 + (2*s_max/t_max)*t
					m_playery += m_playerj;
					place_player();
				};
			}
			else
				m_player_ystatus = 0;
		}
		/*
		 * Check if we're falling:
		*/
		highest = -1;
		x = floor(m_playerx);
		for (i=(x>0?-1:0); i <= (x<m_level.get_levelwidth()?1:0); i++)
		{
			col = m_level.get_column(x+i);
			for (j=0; j < col->get_blocknumber(); j++)
			{
				if ((highest == -1 || col->get_block(j)->position > m_level.get_column(colno)->get_block(highest)->position) && m_playery >= col->get_block(j)->position)
				{
					colno = x+i;
					highest = j;
				};
			}
		}
		if (highest > -1)
		{
			/*
			 * Too high!
			*/
			if (m_player_ystatus == 0)
			{
				z = m_level.get_column(colno)->get_block(highest)->position+0.5;
				if (m_playery-z < 0.4*multip)
					y = m_playery-z;
				else
					y = 0.4*multip;
				if (y > 0)
				{
					rect = m_player.getGlobalBounds();
					rect.height += y;
					if (!m_blocks[m_level.get_column(colno)->get_block(highest)->offset].getGlobalBounds().intersects(rect))
					{
						m_playery -= y;
						place_player();
					};
					m_player_canjump = false;
				}
				else
					m_player_canjump = true;
			};
		}
		else
		{
			/*
			 * Free fall!
			*/
			if (m_player_ystatus == 0)
			{
				m_playery -= 0.4*multip;
				place_player();
				m_player_canjump = false;
			}
		};
		/*
		 * Check for interaction with items:
		*/
		x = floor(m_playerx);
		for (i=(x>0?-1:0); i <= (x<m_level.get_levelwidth()?1:0); i++)
		{
			col = m_level.get_column(x+i);
			for (j=0; j < col->get_itemnumber(); j++)
			{
				if (!col->get_item(j)->collected && m_items[col->get_item(j)->offset].getGlobalBounds().intersects(m_player.getGlobalBounds()))
				{
					// Got an item!
					col->get_item(j)->collected = true;
					update_level();
					switch (col->get_item(j)->id)
					{
						case 0:
							m_coinsound.setPlayingOffset(sf::Time::Zero);
							m_coinsound.play();
							m_money++;
							update_money();
							break;
						case 1:
							m_hearts_num++;
							update_hearts();
							break;
						default:
							std::cout << "Collected unknown item!" << std::endl;
					}
				};
			}
		}
		/*
		 * Check for level end:
		*/
		if (m_playerx >= m_level.get_levelwidth()-GAME_ENDOFFSET)
		{
			m_moving = false;
			m_successful = true;
			m_message.setString(get_wstring(_("game_successful_message")));
			place_message();
			m_bgsound.stop();
		};
		/*
		 * Check for death by falling:
		*/
		if (m_playery <= 0)
		{
			m_hearts_num--;
			if (m_hearts_num == -1)
			{
				m_moving = false;
				m_gameover = true;
				m_message.setString(get_wstring(_("game_gameover_message")));
				place_message();
				m_bgsound.stop();
			}
			else
			{
				restart_level();
				update_hearts();
			};
		};
		/*
		 * Restart timer:
		*/
		m_actiontimer.restart();
	}
	else
	{
		if (m_successful)
		{
			if (m_actiontimer.getElapsedTime().asMilliseconds() <= 4080)
				m_player.setColor(sf::Color(255, 255, 255, 255-(m_actiontimer.getElapsedTime().asMilliseconds()/16.)));
			if (m_actiontimer.getElapsedTime().asMilliseconds() > 500)
				m_exit = true;
		}
		else if (m_gameover)
		{
			if (m_actiontimer.getElapsedTime().asMilliseconds() <= 4080)
				m_player.setColor(sf::Color(255, 255, 255, 255-(m_actiontimer.getElapsedTime().asMilliseconds()/16.)));
			if (m_actiontimer.getElapsedTime().asMilliseconds() > 500)
				m_exit = true;
		}
		else
		{
			// Not moving, yet.
			if (m_actiontimer.getElapsedTime().asMilliseconds() <= 450)
				m_ptoiletbase.setRotation(m_actiontimer.getElapsedTime().asMilliseconds()/5.);
			else
			{
				m_moving = true;
				m_actiontimer.restart();
			};
		};
	};
	/*
	 * Update item offset:
	*/
	if (m_itemoffsetd)
	{
		/*
		 * Moving downwards.
		*/
		if (m_itemoffset <= 0)
			m_itemoffsetd = false;
		else
			m_itemoffset -= ITEM_STEPOFFSET*multip;
	}
	else
	{
		/*
		 * Moving upwards.
		*/
		if (m_itemoffset >= ITEM_MAXOFFSET)
			m_itemoffsetd = true;
		else
			m_itemoffset += ITEM_STEPOFFSET*multip;
	};
	update_itempos();
	/*
	 * Fill array:
	*/
	arr.init(10+(m_level.has_bgimg()?1:0)+m_visible_block_number+m_visible_item_number+((m_offset < PLAYERPOS_X+2)?2:0)+((m_hearts_num > 3)?1:0)+((m_successful||m_gameover)?1:0));
	if (m_level.has_bgimg())
		arr.add_sprite(m_bg);
	for (i=0; i < m_visible_block_number; i++)
	{
		arr.add_sprite(m_blocks[i]);
	}
	for (i=0; i < m_visible_item_number; i++)
	{
		arr.add_sprite(m_items[i]);
	}
	arr.add_sprite(m_player);
	arr.add_sprite(m_frame);
	arr.add_sprite(m_healthm);
	arr.add_rectshape(m_healthm_helper);
	for (i=0; i < 3; i++)
		arr.add_sprite(m_hearts[i]);
	if (m_offset < PLAYERPOS_X+2)
	{
		arr.add_sprite(m_ptoilet);
		arr.add_rectshape(m_ptoiletbase);
	};
	arr.add_text(m_moneytext);
	if (m_hearts_num > 3)
		arr.add_text(m_heartstext);
	if (m_successful || m_gameover)
		arr.add_text(m_message);
	return arr;
}
void SinglePlayer::toggle_playertexture(void)
{
	if (m_playertimer.getElapsedTime().asMilliseconds() < 100)
		return;
	if (m_player_texturecounter < 5)
	{
		m_player_texturecounter++;
		return;
	};
	if (m_player_texture2_en)
	{
		if (m_backwards)
			m_player.setTexture(m_player_rf0);
		else
			m_player.setTexture(m_player_f0);
		m_player_texture2_en = false;
	}
	else
	{
		if (m_backwards)
			m_player.setTexture(m_player_rf1);
		else
			m_player.setTexture(m_player_f1);
		m_player_texture2_en = true;
	};
	m_player_texturecounter = 0;
	m_playertimer.restart();
}
void SinglePlayer::place_player(void)
{
	m_player.setPosition((m_playerx-m_offset)*m_blockw/2., (VERTICAL_BLOCK_NUMBER-3-(m_playery/2.))*m_blockh);
}
void SinglePlayer::update_level(void)
{
	/*
	 * Variable declarations:
	*/
	unsigned long i, j, k, l;
	/*
	 * Calculate offset:
	*/
	m_offsetf = floor(m_offset);
	if (m_offsetf > 0)
		m_offsetf -= 1;
	m_offsetr = m_offset-m_offsetf;
	/*
	 * Calculate width in blocks:
	*/
	m_width_hblk = HORIZONTAL_BLOCK_NUMBER;
	if (m_width_hblk > m_level.get_levelwidth()-m_offsetf)
		m_width_hblk = m_level.get_levelwidth()-m_offsetf;
	/*
	 * Calculate visible block & item numbers:
	*/
	m_visible_block_number = 0;
	m_visible_item_number = 0;
	for (i=0; i < m_width_hblk; i++)
	{
		m_visible_block_number += m_level.get_column(m_offsetf+i)->get_blocknumber();
		m_visible_item_number += m_level.get_column(m_offsetf+i)->get_itemnumber();
	}
	/*
	 * Create block & item sprites:
	*/
	if (m_blocks_i)
	{
		delete[] m_blocks;
		delete[] m_items;
	};
	m_blocks = new sf::Sprite[m_visible_block_number];
	m_items = new sf::Sprite[m_visible_item_number];
	m_blocks_i = true;
	k = 0;
	l = 0;
	for (i=0; i < m_width_hblk; i++)
	{
		for (j=0; j < m_level.get_column(m_offsetf+i)->get_blocknumber(); j++)
		{
			m_level.get_column(m_offsetf+i)->get_block(j)->offset = k;
			m_blocks[k].setPosition(sf::Vector2f((i-m_offsetr)*m_blockw/2., m_h-(((m_level.get_column(m_offsetf+i)->get_block(j)->position/2.)+0.5)*m_blockh)));
			m_blocks[k].setScale(m_blockw/32., m_blockh/16.);
			m_blocks[k].setTexture(m_block_textures[m_level.get_column(m_offsetf+i)->get_block(j)->blockdef]);
			k++;
		}
		for (j=0; j < m_level.get_column(m_offsetf+i)->get_itemnumber(); j++)
		{
			if (!m_level.get_column(m_offsetf+i)->get_item(j)->collected)
			{
				m_level.get_column(m_offsetf+i)->get_item(j)->offset = l;
				m_items[l].setScale((m_blockw/32.)*.8, (m_blockh/16.)*.8);
				m_items[l].setTexture(m_item_textures[m_level.get_column(m_offsetf+i)->get_item(j)->id]);
				l++;
			};
		}
	}
	update_itempos();
	/*
	 * Place background:
	*/
	m_bg.setTextureRect(sf::IntRect(m_offset*SIZE_GAME_BG_BLOCKWIDTH/2., 0, m_bg.getLocalBounds().width, m_bg.getLocalBounds().height));
	/*
	 * Place portable toilet:
	*/
	if (m_offset < PLAYERPOS_X+2)
	{
		m_ptoilet.setPosition((PLAYERPOS_X-m_offset-0.5)*m_blockw/2., 0);
		m_ptoiletbase.setSize(sf::Vector2f(m_blockw, m_blockh/SIZE_PTOILETBASE_HEIGHT_DIVIDER));
		m_ptoiletbase.setPosition(sf::Vector2f((PLAYERPOS_X-m_offset-0.5)*m_blockw/2., m_blockh));
	};
}
void SinglePlayer::update_itempos(void)
{
	/*
	 * Variable declarations:
	*/
	unsigned long i, j, k;
	
	k = 0;
	for (i=0; i < m_width_hblk; i++)
	{
		for (j=0; j < m_level.get_column(m_offsetf+i)->get_itemnumber(); j++)
		{
			if (!m_level.get_column(m_offsetf+i)->get_item(j)->collected)
			{
				m_items[k].setPosition(sf::Vector2f((i-m_offsetr+.1)*m_blockw/2., m_h-(((m_level.get_column(m_offsetf+i)->get_item(j)->position/2.)+.5+m_itemoffset)*m_blockh)));
				k++;
			};
		}
	}
}
void SinglePlayer::update_hearts(void)
{
	/*
	 * Variable declarations:
	*/
	unsigned int i;
	std::ostringstream ss;
	
	for (i=0; i < 3; i++)
	{
		if (i < m_hearts_num)
			m_hearts[i].setTexture(m_heart);
		else
			m_hearts[i].setTexture(m_heart_grey);
	}
	/*
	 * Update extra hearts view:
	*/
	if (m_hearts_num > 3)
	{
		m_frame.setTextureRect(sf::IntRect(0, 0, SIZE_STATUSFRAME_IMGWIDTH, SIZE_STATUSFRAME_IMGHEIGHT));
		ss.str("");
		ss << m_hearts_num-3;
		m_heartstext.setString(ss.str());
	}
	else
		m_frame.setTextureRect(sf::IntRect(0, 0, SIZE_STATUSFRAME_NOEHEARTS_WIDTH, SIZE_STATUSFRAME_NOEHEARTS_HEIGHT));
}
void SinglePlayer::update_healthm(void)
{
	/*
	 * Variable declarations:
	*/
	float scale;
	
	scale = (100-m_health)/100.;
	m_healthm.setTextureRect(sf::IntRect(0, 0, ceil(SIZE_HEALTHMETER_IMGWIDTH*(1-scale)), SIZE_HEALTHMETER_IMGHEIGHT));
	m_healthm.setPosition(sf::Vector2f((m_w*SIZE_HEALTHMETER_XOFFSET/100.)+(SIZE_HEALTHMETER_IMGWIDTH*m_sframe_scale*scale), m_h*SIZE_HEALTHMETER_YOFFSET/100.));
}
void SinglePlayer::update_money(void)
{
	/*
	 * Variable declarations:
	*/
	std::ostringstream ss;
	
	ss.str("");
	ss << m_money;
	m_moneytext.setString(ss.str());
}
void SinglePlayer::restart_level(void)
{
	m_offset = 0;
	m_playerx = PLAYERPOS_X;
	m_playery = PLAYERPOS_Y;
	m_player_xaction = 0;
	m_player_ystatus = 0;
	m_moving = false;
	m_backwards = false;
	m_player.setTexture(m_player_f0);
	m_ptoiletbase.setRotation(0);
	update_level();
	place_player();
	m_actiontimer.restart();
}
void SinglePlayer::place_message(void)
{
	m_message.setPosition((m_w-m_message.getGlobalBounds().width)/2., (m_h-m_message.getGlobalBounds().height)/2.);
}
