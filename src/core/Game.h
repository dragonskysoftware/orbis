/*
 * Game.h
 * Declares a static class that runs the Orbis game
 * Created by Andrew Davis
 * Created on 4/9/2017
 * All rights reserved
 */

//disallow reinclusion
#ifndef GAME_H_INC
#define GAME_H_INC

//includes
#include "../data/GameDB.h"
#include "../event/EventRegulator.h"
#include "../component/ImgComponent.h"
#include "../component/TextComponent.h"
#include "../util/constants.h"
#include "../util/functions.h"
#include "../audio/SoundEffect.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <iostream>

//static class declaration
class Game final {
	//public fields and methods
	public:
		//delete the constructor
		Game() = delete;

		//delete the destructor
		~Game() = delete;

		//delete the copy constructor and other such methods
		Game(const Game& g) = delete;
		Game(Game&& g) = delete;
		Game& operator=(const Game& src) = delete;
		Game& operator=(Game&& src) = delete;

		//other methods
		static bool start(); //starts the game
		static void run(); //runs the game
		static void shutdown(); //shuts down the game

	//private fields and methods
	private:
		//methods
		static void displaySplash(); //displays the splash image

		//SDL fields
		static SDL_Window* window; //the window the game runs in
		static SDL_Renderer* renderer; //the graphics renderer for the game

		//game object fields
		static TextComponent* message; //a temporary message displayed while the game is being developed
		static ImgComponent* image; //an image used to test graphics rendering
		static ImgComponent* splash; //the splash image for the game

};


#endif
