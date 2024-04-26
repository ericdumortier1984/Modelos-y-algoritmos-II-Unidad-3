#include "Game.h"

// Debe crear un ragdoll

int main()
{

	Game* GO;
	GO = new Game(800, 600);
	GO->Loop();

	return EXIT_SUCCESS;
}