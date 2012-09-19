#include "main.hpp"

using namespace std;

int main(int argc, char **argv)
{
	/*
	 * Variable declarations:
	*/
	Game game;
	int w, h, fullscreen;
	/*
	 * Variable definitions:
	*/
	//w = -1; // auto resolution
	w = 1580;
	//h = -1; // auto resolution
	h = 1000;
	//fullscreen = 1; // fullscreen
	//fullscreen = 0;
	/*
	 * Startup:
	*/
	cout << "Game v" << VERSION << endl;
	/*
	 * Init game:
	*/
	if (game.init(w, h, fullscreen) == 1)
	{
		return 1;
	};
	/*
	 * Start event loop:
	*/
	while (game.loop() == 2)
	{
		game.uninit();
		if (game.init(w, h, fullscreen) == 1)
		{
			return 1;
		};
	}
	/*
	 * Shutdown:
	*/
	cout << "Shutting down." << endl;
	return 0;
}
