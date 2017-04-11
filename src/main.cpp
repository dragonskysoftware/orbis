/*
 * main.cpp
 * Runs main code for Orbis
 * Created by Andrew Davis
 * Created on 4/9/2017
 * All rights reserved
 */

//includes
#include "core/Game.h"
#include <iostream>
#include <cstdlib>

//main function - main entry point for program
int main(int argc, char* argv[]) {
	//start by calling init()
	if(!Game::start()) { //if the game failed to start
		std::cerr << "Fatal: Failed to start game." << std::endl; //display an error message
		return EXIT_FAILURE; //and exit with an error
	} else { //if the init succeeded
		Game::run(); //run the game
	}
	Game::shutdown(); //shut the game down
	return EXIT_SUCCESS; //and exit with no errors
}

//end of program
