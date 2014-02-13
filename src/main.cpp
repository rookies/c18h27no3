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
	int gamemode;
	string arg;
	/*
	 * Startup:
	*/
	cout << "route94 v" << VERSION << endl;
	/*
	 * Init game:
	*/
	gamemode = 13;
	arg = "";
	if (argc >= 2)
	{
		if (argc >= 3 && string(argv[1]).compare("load") == 0)
		{
			gamemode = 7;
			arg = argv[2];
		}
		else if (argc >= 3 && string(argv[1]).compare("mode") == 0)
		{
			gamemode = atoi(argv[2]);
			if (argc >= 4)
				arg = argv[3];
			else
				arg = "";
		}
		else if (string(argv[1]).compare("help") == 0)
		{
			std::cout << "== Help Overview ==" << std::endl;
			std::cout << " -> Showing this help screen:" << std::endl;
			std::cout << "   " << argv[0] << " help" << std::endl;
			std::cout << " -> Loading a level file:" << std::endl;
			std::cout << "   " << argv[0] << " load <filename>" << std::endl;
			std::cout << " -> Loading a custom gamemode:" << std::endl;
			std::cout << "   " << argv[0] << " mode <id> [argument]" << std::endl;
			return EXIT_SUCCESS;
		};
	};
	if (game.init(gamemode, arg) == 1)
		return EXIT_FAILURE;
	/*
	 * Start event loop:
	*/
	while (game.loop() == 2)
	{
		game.uninit();
		if (game.init() == 1)
			return EXIT_FAILURE;
	}
	/*
	 * Shutdown:
	*/
	game.uninit();
	cout << "Shutting down." << endl;
	return EXIT_SUCCESS;
}
