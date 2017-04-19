/*
 * Game.cpp
 * Implements a static class that runs the Orbis game
 * Created by Andrew Davis
 * Created on 4/9/2017
 * All rights reserved
 */

//include header
#include "Game.h"

//init the static variables

//first the SDL variables
SDL_Window* Game::window = nullptr; //initialize the window to nullptr
SDL_Renderer* Game::renderer = nullptr; //initialize the renderer to nullptr

//then the game variables
ImgComponent* Game::title = nullptr; //initialize the title screen to nullptr
ImgComponent* Game::splash = nullptr; //initialize the splash to nullptr

//end of variable initializations

//static method implementations

//start method - starts up the game and sets up the window and renderer
bool Game::start() {
	//set flags
	bool success = true; //init success flag

	//start initialization
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) { //if preliminary initialization fails
		std::cerr << "SDL could not initialize! Error: " << SDL_GetError() << std::endl; //display an error message
		success = false; //and reset the success flag
	} else {
		//set texture filtering to linear
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) { //if the texture filtering setting failed
			std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl; //display a warning
		}
		//create the window
		window = SDL_CreateWindow(WIN_HEADER, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if(window == nullptr) { //if the creation failed
			std::cerr << "Fatal: Window could not be created. SDL Error: " << SDL_GetError() << std::endl; //display an error message
			success = false; //and reset the success flag
		} else { 
			//create the renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == nullptr) { //if the creation failed
				//display an error message
				std::cerr << "Fatal: Renderer could not be created. SDL Error: " << SDL_GetError() << std::endl;
				success = false; //and reset the success flag
			} else {
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff); //init the draw colors
			}
		}
	}
	//Initialize SDL_ttf
	if( TTF_Init() == -1 ) {	
		std::cerr << "Could not initialize SDL_TTF. Error: " << TTF_GetError() << std::endl;			
		success = false;
	}

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {						                  
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}

	//finish initializing SDL_mixer
	int mixflags = MIX_INIT_OGG; //the flags that denote format support
	int result = Mix_Init(mixflags); //call the init function for the mixer and get the result
	if((result & mixflags) != mixflags) { //if the initialization failed
		std::cerr << "Failed to initialize ogg support. Error: " << Mix_GetError() << std::endl; //then show an error msg
		success = false; //and reset the success flag
	}

	return success; //return the success flag

}

//run method - runs the game
void Game::run() {
	splash = new ImgComponent(0, 0, "../assets/images/Splash.png", renderer); //init the splash image
	title = new ImgComponent(0, 0, "../assets/images/title.png", renderer); //init the title image
	displaySplash(); //display the splash image
	//start the loop
	while(true) { //loop forever, or until a quit event is detected by the event regulator
		EventRegulator::getInstance().nextEvent(); //poll the next event
		//draw a blank screen
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff); //set the draw color to white
		SDL_RenderClear(renderer); //fill the screen with white
		displayTitle(); //display the title image
		SDL_RenderPresent(renderer); //update the draw screen
		if(GameDB::getInstance().getInt(OP_KEY) == SHUTDOWN) { //if a shutdown event was detected
			break; //then exit the loop
		}
	}

}

//shutdown method - shuts down the game
void Game::shutdown() {
	delete title; //deallocate the title field
	title = nullptr; //and zero it out
	delete splash; //deallocate the splash field
	splash = nullptr; //and zero it out

	//destroy the renderer
	SDL_DestroyRenderer(renderer); 
	renderer = nullptr;

	//destroy the window
	SDL_DestroyWindow(window);
	window = nullptr;

	//quit TTF
	TTF_Quit();

	//quit IMG
	IMG_Quit();

	//quit Mix
	Mix_Quit();

	//Quit SDL
	SDL_Quit();
}

//getter methods

//getWindow method - returns the window field
SDL_Window* Game::getWindow() {
	return window; //return the window field
}

//getRenderer method - returns the renderer field
SDL_Renderer* Game::getRenderer() {
	return renderer; //return the renderer field
}

//other methods

//displaySplash method - fades in the splash, waits a second, and fades it out
void Game::displaySplash() {
	if(splash == nullptr) { //if the splash is not initialized
		return; //then exit the method
	}

	//create the sound effect
	SoundEffect* intro = new SoundEffect("../assets/sounds/Intro.ogg"); //load the sound effect from a file

	//play the sound effect
	intro->play(); //call SoundEffect::play()

	//draw a black screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff); //set the draw color to black
	SDL_RenderClear(renderer); //fill the screen with black

	//fade in the splash screen
	int alpha = 0; //the alpha value for the splash screen
	splash->setAlpha(alpha); //make the splash image transparent
	while(alpha < 0xff) { //loop while the alpha value isn't maxed out
		//draw a black screen
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff); //set the draw color to black
		SDL_RenderClear(renderer); //fill the screen with black
		splash->render(); //render the splash screen
		SDL_RenderPresent(renderer); //update the draw screen
		alpha += 10; //increment the alpha value
		splash->setAlpha(alpha); //set the new alpha value
		uwait(50); //wait 50/1000 of a second
	}

	//allow the user to view the logo
	uwait(2500); //wait 2.5 seconds

	//fade out the splash screen
	while(alpha > 0x00) { //loop while the alpha value isn't zero
		splash->render(); //render the splash screen
		SDL_RenderPresent(renderer); //update the draw screen
		alpha -= 10; //decrement the alpha value
		splash->setAlpha(alpha); //set the new alpha value
		//draw a black screen
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff); //set the draw color to black
		SDL_RenderClear(renderer); //fill the screen with black
		uwait(50); //wait 50/1000 of a second
	}
	//draw a black screen
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff); //set the draw color to black
	SDL_RenderClear(renderer); //fill the screen with black

	//and deallocate the sound effect
	delete intro; //deallocate the sound effect object
	intro = nullptr; //and zero it out
}
	
//displayTitle method - displays the title screen
void Game::displayTitle() {
	//TODO: Add music code
	title->render(); //render the title screen
}

//end of implementation
