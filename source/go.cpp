#include "go.hpp"

go::go()
{
	debprintf("Go constructor works...\n");
} // go

void go::Start()
{
	debprintf("Go starts...\n");

	while (1) {
		game newGame;
		newGame.Start();
	}
} // Start


