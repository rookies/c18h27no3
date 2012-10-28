/*
 * main.cpp
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
#include "main.hpp"

using namespace std;

int main(int argc, char **argv)
{
	/*
	 * Variable declarations:
	*/
	Game game;
	/*
	 * Startup:
	*/
	cout << "c18h27no3 v" << VERSION << endl;
	/*
	 * Init game:
	*/
	if (game.init() == 1)
		return EXIT_FAILURE;
	/*
	 * Start event loop:
	*/
	while (game.loop() == 2)
	{
		game.uninit();
		if (game.init() == 1)
		{
			return EXIT_FAILURE;
		};
	}
	/*
	 * Shutdown:
	*/
	game.uninit();
	cout << "Shutting down." << endl;
	return EXIT_SUCCESS;
}
