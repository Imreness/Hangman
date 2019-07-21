#include <iostream>
#include "Code/Core/Game.h"
#include "Code/Sidesystems/IconLoader.h"

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
	GLFWimage* icon = IconLoader::LoadIcon("Textures/icon.png");

	Game hangman(896, 504 ,  "Hangman - A game made by Imre Barta" , icon);

	while (!hangman.gameShouldClose())
	{
		hangman.Update();
	}

	hangman.Close();

	return 0;
}