/*
 * EventFuncs.h
 * Declares functions that act as event callbacks for the various bits of Orbis code that require them
 * Created by Andrew Davis
 * Created on 4/19/2017
 * All rights reserved
 */

//disallow reinclusion
#ifndef EVENT_FUNCS_H_INC
#define EVENT_FUNCS_H_INC

//includes
#include "../gui/SimpleMsgBox.h"
#include "../gui/GUIGateway.h"
#include "../util/functions.h"

//function prototypes
void shutdown(); //shuts down the game
void showGameNotMadeDialog(); //displays a warning dialog communicating that the game is not implemented

#endif
