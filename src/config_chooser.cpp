/*
 * config_chooser.cpp
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
#include "config_chooser.hpp"
ConfigChooserElement::ConfigChooserElement()
{
	
}
ConfigChooserElement::~ConfigChooserElement()
{
	
}
std::string ConfigChooserElement::get_showable(void)
{
	return m_showable;
}
int ConfigChooserElement::get_int(void)
{
	return m_value_int;
}
bool ConfigChooserElement::get_bool(void)
{
	return m_value_bool;
}
std::string ConfigChooserElement::get_string(void)
{
	return m_value_string;
}
void ConfigChooserElement::set_showable(std::string value)
{
	m_showable = value;
}
void ConfigChooserElement::set_int(int value)
{
	m_value_int = value;
}
void ConfigChooserElement::set_bool(bool value)
{
	m_value_bool = value;
}
void ConfigChooserElement::set_string(std::string value)
{
	m_value_string = value;
}
ConfigChooser::ConfigChooser()
{
	
}
ConfigChooser::~ConfigChooser()
{
	
}
void ConfigChooser::init(int type, int number)
{
	/*
	 * Set type:
	*/
	m_type = type;
	m_number = number;
	/*
	 * Init elements array:
	*/
	m_elements = new ConfigChooserElement[number];
	m_getpointer = 0;
	m_addpointer = 0;
}
void ConfigChooser::next(void)
{
	if (m_getpointer == m_number-1)
		m_getpointer = 0;
	else
		m_getpointer++;
}
void ConfigChooser::prev(void)
{
	if (m_getpointer == 0)
		m_getpointer = m_number-1;
	else
		m_getpointer--;
}
void ConfigChooser::_goto(int index)
{
	m_getpointer = index;
}
std::string ConfigChooser::get_actual_showable(void)
{
	return m_elements[m_getpointer].get_showable();
}
int ConfigChooser::get_actual_int(void)
{
	return m_elements[m_getpointer].get_int();
}
bool ConfigChooser::get_actual_bool(void)
{
	return m_elements[m_getpointer].get_bool();
}
std::string ConfigChooser::get_actual_string(void)
{
	return m_elements[m_getpointer].get_string();
}
void ConfigChooser::add_int(std::string showable, int value)
{
	m_elements[m_addpointer].set_showable(showable);
	m_elements[m_addpointer].set_int(value);
	m_addpointer++;
}
void ConfigChooser::add_bool(std::string showable, bool value)
{
	m_elements[m_addpointer].set_showable(showable);
	m_elements[m_addpointer].set_bool(value);
	m_addpointer++;
}
void ConfigChooser::add_string(std::string showable, std::string value)
{
	m_elements[m_addpointer].set_showable(showable);
	m_elements[m_addpointer].set_string(value);
	m_addpointer++;
}
void ConfigChooser::set_actual_int(int value)
{
	int i;
	for (i=0; i < m_number; i++)
	{
		if (m_elements[i].get_int() == value)
		{
			m_getpointer = i;
			break;
		};
	}
}
void ConfigChooser::set_actual_bool(bool value)
{
	int i;
	for (i=0; i < m_number; i++)
	{
		if (m_elements[i].get_bool() == value)
		{
			m_getpointer = i;
			break;
		};
	}
}
void ConfigChooser::set_actual_string(std::string value)
{
	int i;
	for (i=0; i < m_number; i++)
	{
		if (m_elements[i].get_string().compare(value) == 0)
		{
			m_getpointer = i;
			break;
		};
	}
}
