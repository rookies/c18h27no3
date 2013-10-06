/*
 * event_processor_return.hpp
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
#ifndef EVENT_PROCESSOR_RETURN_HPP
#	define EVENT_PROCESSOR_RETURN_HPP
	
#	include "config_common.hpp"
	
	class EventProcessorReturn
	{
		public:
			EventProcessorReturn();
			virtual ~EventProcessorReturn();
			
			void uninit(void);
			void set_gamemode(int gamemode);
			void init_confvars(int count);
			void add_confvar(ConfigVariable var);
			void set_language(std::string lang);
			void set_exit(bool exit);
			void set_reload(bool reload);
			void set_menumusic_vol(int vol);
			
			int get_gamemode(void);
			bool are_confvars_initialized(void);
			int get_confvars_count(void);
			ConfigVariable get_confvar(int index);
			std::string get_language(void);
			bool get_exit(void);
			bool get_reload(void);
			int get_menumusic_vol(void);
		private:
			int m_gamemode;
			ConfigVariable *m_confvars;
			int m_confvar_pointer;
			bool m_confvars_initialized;
			std::string m_lang;
			int m_menumusic_vol;
			bool m_exit;
			bool m_reload;
	};
#endif // EVENT_PROCESSOR_RETURN_HPP
