/*
 * config_windows.cpp
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
#include "config_windows.hpp"

int Config::load(void)
{
	std::cout << "Loading config...";
	/*
	 * Variable declarations:
	*/
	std::ostringstream keyname;
	HKEY hkey;
	int i;
	DWORD type;
	char buf[WINDOWS_CONFIG_BUFLEN];
	DWORD bufsize;
	/*
	 * Open registry key:
	*/
	keyname.str("");
	keyname << "Software\\";
	keyname << CORPORATION;
	keyname << "\\";
	keyname << PROJECTNAME;
	keyname << "\\config";
	if (RegOpenKey(HKEY_CURRENT_USER, keyname.str().c_str(), &hkey) != ERROR_SUCCESS)
	{
		std::cout << "[FAIL]" << std::endl;
		return 1;
	};
	/*
	 * Read values:
	*/
	for (i=0; i < CONFIGVAR_COUNT; i++)
	{
		/*
		 * Try to read from registry:
		*/
		type = REG_SZ;
		bufsize = WINDOWS_CONFIG_BUFLEN;
		if (RegQueryValueEx(hkey, m_vars[i].index.c_str(), 0, &type, (BYTE*)buf, &bufsize) == ERROR_SUCCESS)
		{
			/*
			 * Try to interpret the value:
			*/
			switch (m_vars[i].type)
			{
				case CONFIGVAR_TYPE_INTEGER:
					m_vars[i].value_int = atoi(buf);
					break;
				case CONFIGVAR_TYPE_BOOLEAN:
					if (std::string(buf).compare("true") == 0)
						m_vars[i].value_bool = true;
					else if (std::string(buf).compare("false") == 0)
						m_vars[i].value_bool = false;
					else
						std::cout << "Invalid registry value: " << buf << std::endl;
					break;
				case CONFIGVAR_TYPE_STRING:
					m_vars[i].value_string = buf;
					break;
			}
		}
		else
			std::cout << "Registry value not found: " << m_vars[i].index << std::endl;
	}
	/*
	 * Close registry key:
	*/
	RegCloseKey(hkey);
	/*
	 * Return success:
	*/
	std::cout << "[DONE]" << std::endl;
	return 0;
}
int Config::write(void)
{
	std::cout << "Writing config... ";
	/*
	 * Variable declarations:
	*/
	std::ostringstream keyname;
	HKEY hkey;
	DWORD status;
	int i;
	DWORD type;
	std::ostringstream buf;
	/*
	 * Create or open registry key:
	*/
	keyname.str("");
	keyname << "Software\\";
	keyname << CORPORATION;
	keyname << "\\";
	keyname << PROJECTNAME;
	keyname << "\\config";
	if (RegCreateKeyEx(
		HKEY_CURRENT_USER,
		keyname.str().c_str(),
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hkey,
		&status
	) != ERROR_SUCCESS)
	{
		std::cout << "[FAIL]" << std::endl;
		return 1;
	};
	if (status == REG_CREATED_NEW_KEY)
		std::cout << "Registry key created." << std::endl;
	/*
	 * Write values:
	*/
	type = REG_SZ;
	for (i=0; i < CONFIGVAR_COUNT; i++)
	{
		buf.str("");
		switch (m_vars[i].type)
		{
			case CONFIGVAR_TYPE_INTEGER:
				buf << m_vars[i].value_int;
				break;
			case CONFIGVAR_TYPE_BOOLEAN:
				if (m_vars[i].value_bool)
					buf << "true";
				else
					buf << "false";
				break;
			case CONFIGVAR_TYPE_STRING:
				buf << m_vars[i].value_string;
				break;
		}
		if (RegSetValueEx(
			hkey,
			m_vars[i].index.c_str(),
			0,
			type,
			(BYTE *)buf.str().c_str(),
			buf.str().length()
		) != ERROR_SUCCESS)
		{
			std::cout << "Failed to write " << m_vars[i].index << "!" << std::endl;
			std::cout << "[FAIL]" << std::endl;
			return 1;
		};
	}
	/*
	 * Close registry key:
	*/
	RegCloseKey(hkey);
	/*
	 * Return success:
	*/
	std::cout << "[DONE]" << std::endl;
	return 0;
}
