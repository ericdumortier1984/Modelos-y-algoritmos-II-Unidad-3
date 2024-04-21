#include "Game.h"

// Realice un programa que simule dos pelotas unidas por un resorte. 
// Con el mouse debe poder mover cualquiera de ellas.

int main()
{

	Game* GO;
	GO = new Game(800, 600);
	GO->Loop();

	return EXIT_SUCCESS;
}