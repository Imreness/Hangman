#include <iostream>
#include "Code/Core/Game.h"
#include "Code/Sidesystems/IconLoader.h"
#include "Code/Sidesystems/configloader.h"

/*.....................................................................
 *                        H A N G M A N - 2019
 *.....................................................................
 * Created by: Imre "Imreness" Barta
 *.....................................................................
 */

int main()
{
	GLFWimage* icon = IconLoader::LoadIcon("Textures/icon.png");

	Config config = ConfigLoader::loadConfig();

	Game hangman(config, "Hangman - A game made by Imre Barta" , icon);

	while (!hangman.gameShouldClose())
	{
		hangman.Update();
	}

	hangman.Close();

	return 0;
}