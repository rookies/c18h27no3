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

bool Config::load(void)
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
	std::string fname;
	/*
	 * Open file:
	*/
	fname = getenv("HOME");
	if (fname.substr(fname.length()-1, 1).compare("/") != 0)
		fname.append("/");
	fname.append(".");
	fname.append(PROJECTNAME);
	fname.append("/config.txt");
	file.open(fname.c_str());
	if (!file.is_open())
	{
		std::cout << "[FAIL]" << std::endl;
		return false;
	};
	/*
	 * ... read it:
	*/
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
							else if (value_raw.compare("false") == 0)
								m_vars[i].value_bool = false;
							else
								std::cout << "Invalid config line: " << line << std::endl;
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
	/*
	 * ... and close it:
	*/
	file.close();
	/*
	 * Return success:
	*/
	std::cout << "[DONE]" << std::endl;
	return true;
}
bool Config::write(void)
{
	std::cout << "Writing config... ";
	/*
	 * Variable declarations:
	*/
	std::ofstream file;
	int i;
	int res;
	std::string fname;
	struct stat statbuf;
	/*
	 * Construct $HOME/.sf-game/ into a variable:
	*/
	fname = getenv("HOME");
	if (fname.substr(fname.length()-1, 1).compare("/") != 0)
		fname.append("/");
	fname.append(".");
	fname.append(PROJECTNAME);
	fname.append("/");
	/*
	 * Check if it is a directory:
	*/
	if (stat(fname.c_str(), &statbuf) == -1)
	{
		if (!S_ISDIR(statbuf.st_mode))
		{
			/*
			 * It's not a file and it doesn't exist
			 * => CREATE
			*/
			res = mkdir(fname.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP);
			if (res != 0)
			{
				std::cout << "[FAIL]" << std::endl;
				return false;
			};
		};
	};
	if (S_ISREG(statbuf.st_mode) || S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode) || S_ISFIFO(statbuf.st_mode) || S_ISSOCK(statbuf.st_mode))
	{
		/*
		 * It's not a directory, but it exists
		*/
		std::cout << "[FAIL]" << std::endl;
		return false;
	};
	/*
	 * At this point, the directory should exist, so we can write:
	*/
	fname.append("config.txt");
	file.open(fname.c_str());
	if (!file.is_open())
	{
		std::cout << "[FAIL]" << std::endl;
		return false;
	};
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
	/*
	 * Return success:
	*/
	std::cout << "[DONE]" << std::endl;
	return true;
}
