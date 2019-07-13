#include <iostream>
#include "Code/Core/Game.h"

/*.....................................................................
 *                        H A N G M A N - 2019
 *.....................................................................
 * Created by: Imre "Imreness" Barta
 * 
 * Feel free to use this code however you like; for educational,
 * personal and Commercial purposes
 *.....................................................................
 */

int main()
{
	Game hangman(600, 400 ,  "Hangman");

	while (!hangman.gameShouldClose())
	{
		hangman.Update();
	}

	hangman.Close();

	return 0;
}