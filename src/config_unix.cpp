/*
 * config_unix.cpp
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
#include "config_unix.hpp"

Config::Config()
{
	/*
	 * Init default config values:
	*/
	m_vars[0].index = "GENERAL__LANGUAGE";
	m_vars[0].type = CONFIGVAR_TYPE_STRING;
	m_vars[0].value_string = "en";
	
	m_vars[1].index = "GRAPHICS__RESOLUTION_X";
	m_vars[1].type = CONFIGVAR_TYPE_INTEGER;
	m_vars[1].value_int = 0;
	
	m_vars[2].index = "GRAPHICS__RESOLUTION_Y";
	m_vars[2].type = CONFIGVAR_TYPE_INTEGER;
	m_vars[2].value_int = 0;
	
	m_vars[3].index = "GRAPHICS__FULLSCREEN";
	m_vars[3].type = CONFIGVAR_TYPE_BOOLEAN;
	m_vars[3].value_bool = true;
}
Config::~Config()
{
	
}
int Config::load(void)
{
	std::cout << "Loading config... ";
	/*
	 * Variable declarations:
	*/
	std::ifstream file;
	std::string line;
	size_t found;
	std::string index;
	std::string value_raw;
	int i;
	/*
	 * Open file
	*/
	file.open("config.txt");
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			found = line.find_first_of("#");
			if (found != std::string::npos)
			{
				/*
				 * Line seems valid
				*/
				index = line.substr(0, found);
				value_raw = line.substr(found+1, std::string::npos);
				/*
				 * Search for the index:
				*/
				for (i=0; i < CONFIGVAR_COUNT; i++)
				{
					if (m_vars[i].index.compare(index) == 0)
					{
						/*
						 * We got the right index
						 * Try to interpret the value:
						*/
						switch (m_vars[i].type)
						{
							case CONFIGVAR_TYPE_INTEGER:
								m_vars[i].value_int = atoi(value_raw.c_str());
								break;
							case CONFIGVAR_TYPE_BOOLEAN:
								if (value_raw.compare("true") == 0)
									m_vars[i].value_bool = true;
								else
									m_vars[i].value_bool = false;
								break;
							case CONFIGVAR_TYPE_STRING:
								m_vars[i].value_string = value_raw;
								break;
						}
					};
				}
			}
			else if (!line.compare("\n") && !line.compare(""))
				std::cout << "Invalid config line: " << line << std::endl;
		}
	}
	else
	{
		std::cout << "[FAIL]" << std::endl;
		return 1;
	};
	/*
	 * Return success:
	*/
	std::cout << "[DONE]" << std::endl;
	return 0;
}
int Config::write(void)
{
	/*
	 * Variable declarations:
	*/
	std::ofstream file;
	int i;
	/*
	 * Open file:
	*/
	file.open("config.txt");
	/*
	 * ... write into it:
	*/
	for (i=0; i < CONFIGVAR_COUNT; i++)
	{
		file << m_vars[i].index;
		switch (m_vars[i].type)
		{
			case CONFIGVAR_TYPE_INTEGER:
				file << "#" << m_vars[i].value_int << std::endl;
				break;
			case CONFIGVAR_TYPE_BOOLEAN:
				if (m_vars[i].value_bool)
					file << "#true" << std::endl;
				else
					file << "#false" << std::endl;
				break;
			case CONFIGVAR_TYPE_STRING:
				file << "#" << m_vars[i].value_string << std::endl;
				break;
		}
	}
	/*
	 * ... and close it:
	*/
	file.close();
	return 0;
}
void Config::dump(void)
{
	/*
	 * Variable declarations:
	*/
	int i;
	std::cout << "== CONFIG DUMP ==" << std::endl;
	/*
	 * Run through variables:
	*/
	for (i=0; i < CONFIGVAR_COUNT; i++)
	{
		std::cout << m_vars[i].index;
		switch (m_vars[i].type)
		{
			case CONFIGVAR_TYPE_INTEGER:
				std::cout << ":int = " << m_vars[i].value_int << std::endl;
				break;
			case CONFIGVAR_TYPE_BOOLEAN:
				if (m_vars[i].value_bool)
					std::cout << ":bool = true" << std::endl;
				else
					std::cout << ":bool = false" << std::endl;
				break;
			case CONFIGVAR_TYPE_STRING:
				std::cout << ":string = " << m_vars[i].value_string << std::endl;
				break;
		}
	}
	std::cout << "== CONFIG DUMP ==" << std::endl;
}
ConfigVariable Config::get(std::string index)
{
	/*
	 * Variable declarations:
	*/
	int i;
	/*
	 * Run through variables:
	*/
	for (i=0; i < CONFIGVAR_COUNT; i++)
	{
		if (m_vars[i].index.compare(index) == 0)
			return m_vars[i];
	}
}
void Config::set(std::string index, ConfigVariable value)
{
	
}
