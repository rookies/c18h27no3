/*
 * universal_drawable.cpp
 * 
 * Copyright 2012 Robert Knauer <robert@privatdemail.net>
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
#include "universal_drawable.hpp"

UniversalDrawable::UniversalDrawable()
{
	
}
UniversalDrawable::~UniversalDrawable()
{
	
}
UniversalDrawableArray::UniversalDrawableArray()
{
	m_count = 0;
	m_values_initialized = false;
}
UniversalDrawableArray::~UniversalDrawableArray()
{
	
}
void UniversalDrawableArray::init(int count)
{
	m_count = count;
	m_values = new UniversalDrawable[count];
	m_values_initialized = true;
}
UniversalDrawable UniversalDrawableArray::get(int index)
{
	return m_values[index];
}
int UniversalDrawableArray::get_count(void)
{
	return m_count;
}
void UniversalDrawableArray::set(int index, UniversalDrawable value)
{
	m_values[index] = value;
}
void UniversalDrawableArray::set_text(int index, sf::Text value)
{
	UniversalDrawable el;
	el.type = UNIVERSAL_DRAWABLE_TYPE_TEXT;
	el.value_text = value;
	set(index, el);
}
void UniversalDrawableArray::set_rectshape(int index, sf::RectangleShape value)
{
	UniversalDrawable el;
	el.type = UNIVERSAL_DRAWABLE_TYPE_RECTSHAPE;
	el.value_rectshape = value;
	set(index, el);
}
void UniversalDrawableArray::set_sprite(int index, sf::Sprite value)
{
	UniversalDrawable el;
	el.type = UNIVERSAL_DRAWABLE_TYPE_SPRITE;
	el.value_sprite = value;
	set(index, el);
}
