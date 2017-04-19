/*
 * GUIGateway.cpp
 * Implements a singleton class that acts as a gateway between GUI elements and the rest of the program
 * Created by Andrew Davis
 * Created on 4/13/2017
 * All rights reserved
 */

//include header
#include "GUIGateway.h"

//private constructor
GUIGateway::GUIGateway()
{
	//no code needed
}

//getInstance method - returns an instance of the class
GUIGateway& GUIGateway::getInstance() {
	static GUIGateway instance; //only initialized once
	return instance; //return the instance
}

//other methods

//playWarningTone method - plays a short warning tone
void GUIGateway::playWarningTone() const {
	SoundEffect warning("../assets/sounds/warning.ogg"); //create the sound effect
	warning.play(); //and play it
}

//TODO: Add more methods

//end of implementation
