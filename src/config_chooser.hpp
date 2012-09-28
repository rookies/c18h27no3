/*
 * config_chooser.hpp
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
#ifndef _config_chooser_hpp_
#	define _config_chooser_hpp_
	
#	include <string>
	
	class ConfigChooserElement
	{
		public:
			ConfigChooserElement();
			~ConfigChooserElement();
			
			std::string get_showable(void);
			int get_int(void);
			bool get_bool(void);
			std::string get_string(void);
			
			void set_showable(std::string value);
			void set_int(int value);
			void set_bool(bool value);
			void set_string(std::string value);
		private:
			std::string m_showable;
			int m_value_int;
			bool m_value_bool;
			std::string m_value_string;
	};
	class ConfigChooser
	{
		public:
			ConfigChooser();
			~ConfigChooser();
			
			/*
			 * Init the ConfigChooser with [number] elements:
			*/
			void init(int type, int number);
			/*
			 * Go to the next element:
			*/
			void next(void);
			/*
			 * Go to the previous element:
			*/
			void prev(void);
			/*
			 * Go to the element at [index]:
			*/
			void _goto(int index);
			/*
			 * Get the actual element in showable format:
			*/
			std::string get_actual_showable(void);
			/*
			 * Get the actual element:
			*/
			int get_actual_int(void);
			bool get_actual_bool(void);
			std::string get_actual_string(void);
			/*
			 * Add an element:
			*/
			void add_int(std::string showable, int value);
			void add_bool(std::string showable, bool value);
			void add_string(std::string showable, std::string value);
			/*
			 * Set the actual element:
			*/
			void set_actual_int(int value);
			void set_actual_bool(bool value);
			void set_actual_string(std::string value);
		private:
			int m_type;
			int m_number;
			int m_addpointer;
			int m_getpointer;
			ConfigChooserElement *m_elements;
			bool m_elements_initialized;
	};
#endif // _config_chooser_hpp_
