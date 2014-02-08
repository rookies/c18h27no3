/*
 * fireanimation.hpp
 * 
 * Copyright 2014 Robert Knauer <robert@privatdemail.net>
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
#ifndef FIREANIMATION_HPP
#	define FIREANIMATION_HPP

#	include <SFML/Graphics.hpp>
#	include "dataloader.hpp"

	class FireAnimation
	{
		public:
			FireAnimation();
			virtual ~FireAnimation();
			void calculate_sizes(int w, int h);
			sf::Sprite get_sprite(void);
		private:
			sf::Texture m_fire;
			sf::Sprite m_fire_sprite;
			sf::Clock m_fireclock;
			unsigned int m_fireframe;
			bool m_backwards;
	};
#endif // FIREANIMATION_HPP
