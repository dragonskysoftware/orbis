/*
 * EventFuncs.cpp
 * Implements functions that act as event callbacks for the various bits of Orbis code that require them
 * Created by Andrew Davis
 * Created on 4/19/2017
 * All rights reserved
 */

//include header
#include "EventFuncs.h"

//function implementations

//shutdown function - shuts down the game
void shutdown() {
	shutdownGame(); //call the inline function
}

//showGameNotMadeDialog function - displays a warning dialog communicating that a part of the game is not implemented
void showGameNotMadeDialog() {
	SoundEffect* warning = new SoundEffect("../assets/sounds/warning.ogg"); //create the warning sound
	std::string title = "Notice"; //the title of the message box
	std::string message = "This part of Orbis has not been implemented yet."; //the message of the message box
	SimpleMsgBox box(SDL_MESSAGEBOX_WARNING, title, message); //create the warning box object
	GUIGateway::getInstance().playWarningTone(); //play a warning tone
	warning->play(); //play the warning sound
	delete warning; //deallocate the warning
	warning = nullptr; //and zero it out
	box.show(); //and show the warning box
}

//end of implementation
