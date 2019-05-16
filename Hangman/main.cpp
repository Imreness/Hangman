#include <iostream>
#include "Code/Core/Game.h"

int main()
{
	Game hangman(1280, 720, "Hangman");

	while (!hangman.gameShouldClose())
	{
		hangman.Update();
	}

	hangman.Close();

	return 0;
}