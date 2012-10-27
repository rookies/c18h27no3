/*
 * dataloader.cpp
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
#include "dataloader.hpp"

std::string get_data_path(int type, std::string fname, bool append_fname)
{
	/*
	 * Variable declarations:
	*/
	int datasource_c;
	std::string *datasources;
	int i;
	std::string ret_nofname, ret;
	std::ifstream testfile;
	/*
	 * Get array of possible source directories:
	 * (depends on the type of the file)
	*/
	switch (type)
	{
		case DATALOADER_TYPE_IMG:
			datasource_c = 2;
			datasources = new std::string[datasource_c];
			/*
			 * Source #1:
			 * UNIX: /usr/share/@PROJECTNAME@/data/img/
			 * WINDOWS: FIXME: add windows-specific default path
			*/
#if defined(__unix__)
			datasources[0] = "/usr/share/";
			datasources[0].append(PROJECTNAME);
			datasources[0].append("/data/img/");
#elif defined(_WIN32)
			datasources[0] = "/"; // FIXME: add windows-specific default path
#endif
			/*
			 * Source #2:
			 * ./data/img/
			*/
			datasources[1] = "./data/img/";
			break;
		case DATALOADER_TYPE_FONT:
			datasource_c = 2;
			datasources = new std::string[datasource_c];
			/*
			 * Source #1:
			 * UNIX: /usr/share/fonts/TTF/
			 * WINDOWS: C:/WINDOWS/Fonts/
			*/
#if defined(__unix__)
			datasources[0] = "/usr/share/fonts/TTF/";
#elif defined(_WIN32)
			datasources[0] = "C:/WINDOWS/Fonts/";
#endif
			/*
			 * Source #2:
			 * ./data/fonts/
			*/
			datasources[1] = "./data/fonts/";
			break;
		case DATALOADER_TYPE_LOCALE:
			datasource_c = 2;
			datasources = new std::string[datasource_c];
			/*
			 * Source #1:
			 * UNIX: /usr/share/locale/
			 * WINDOWS: FIXME: add windows-specific locale path
			*/
#if defined(__unix)
			datasources[0] = "/usr/share/locale/";
#elif defined(_WIN32)
			datasources[0] = "/"; // FIXME: add windows-specific locale path
#endif
			/*
			 * Source #2:
			 * ./locale/
			*/
			datasources[1] = "./locale/";
			break;
		default:
			datasource_c = 0;
	}
	/*
	 * Run through the datasources:
	*/
	ret_nofname = "";
	ret = "";
	for (i=0; i < datasource_c; i++)
	{
		/*
		 * Put the full filename together:
		*/
		ret_nofname = datasources[i];
		ret = datasources[i];
		ret.append(fname);
		/*
		 * Check if the file is readable:
		*/
		testfile.open(ret.c_str());
		if (testfile.is_open())
		{
			/*
			 * It is readable, so take this directory:
			*/
#ifdef DATALOADER_DEBUG
			std::cout << "Dataloader: '" << fname << "' found in '" << datasources[i] << "', returning." << std::endl;
#endif // DATALOADER_DEBUG
			testfile.close();
			break;
		}
		else
		{
#ifdef DATALOADER_VERBOSE
			std::cout << "Dataloader: '" << fname << "' not found in '" << datasources[i] << "'." << std::endl;
#endif // DATALOADER_VERBOSE
		};
	}
#ifdef DATALOADER_DEBUG
	if (ret.length() == 0)
		std::cout << "Dataloader: '" << fname << "' not found." << std::endl;
#endif // DATALOADER_DEBUG
	/*
	 * IMPORTANT: Call delete[] to prevent memory leaks:
	*/
	delete[] datasources;
	/*
	 * Return:
	*/
	if (append_fname)
		return ret;
	else
		return ret_nofname;
}
