// 301CR.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "GameManager.h"
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	std::cout << "Use the mouse click and space to jump!\n";
	std::cout << "Use the up arrow key to change the flappy!\n";
	std::cout << "Remember to have the texture files named textureFlappy\n";
	std::cout << "and to put them in the 301CR file with the solution not in textures!\n";
	std::cout << "and make sure to provide the abosolute path in the textureChanger.cpp i couldent make it work otherwise\n";
	std::cout << "sorry to announce texture changer currently not working!\n";
	srand(time(nullptr));

	GameManager gameManager;
	gameManager.Start();

	return 0;
}

