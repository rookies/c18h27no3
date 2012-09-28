/*
 * event_processor_return.cpp
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
#include "event_processor_return.hpp"

EventProcessorReturn::EventProcessorReturn()
{
	m_gamemode = 0; // no new gamemode
	m_lang = ""; // no new language
	m_exit = false; // don't exit
	m_reload = false; // no reload
	m_confvars_initialized = false;
}
EventProcessorReturn::~EventProcessorReturn()
{
	
}
void EventProcessorReturn::uninit(void)
{
	if (m_confvars_initialized)
		delete[] m_confvars;
}
void EventProcessorReturn::set_gamemode(int gamemode)
{
	m_gamemode = gamemode;
}
void EventProcessorReturn::init_confvars(int count)
{
	m_confvars = new ConfigVariable[count];
	m_confvar_pointer = 0;
	m_confvars_initialized = true;
}
void EventProcessorReturn::add_confvar(ConfigVariable var)
{
	m_confvars[m_confvar_pointer] = var;
	m_confvar_pointer++;
}
void EventProcessorReturn::set_language(std::string lang)
{
	m_lang = lang;
}
void EventProcessorReturn::set_exit(bool exit)
{
	m_exit = exit;
}
void EventProcessorReturn::set_reload(bool reload)
{
	m_reload = reload;
}
int EventProcessorReturn::get_gamemode(void)
{
	return m_gamemode;
}
bool EventProcessorReturn::are_confvars_initialized(void)
{
	return m_confvars_initialized;
}
int EventProcessorReturn::get_confvars_count(void)
{
	return m_confvar_pointer;
}
ConfigVariable EventProcessorReturn::get_confvar(int index)
{
	return m_confvars[index];
}
std::string EventProcessorReturn::get_language(void)
{
	return m_lang;
}
bool EventProcessorReturn::get_exit(void)
{
	return m_exit;
}
bool EventProcessorReturn::get_reload(void)
{
	return m_reload;
}
