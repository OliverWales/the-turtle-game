#pragma once

#define TITLE "The Turtle Game" // window title
#define PIXEL_SIZE 4 // screen pixels per game pixel
#define TICK_TIME 20 // animation frame length in ms

#define BACKGROUND_COLOUR sf::Color(80, 120, 180)
#define TILE_SET "TileSet.png"
#define TILE_SIZE 32

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 50

#define SPLASH_SCREEN "SplashScreen.png"
#define SPLASH_SCREEN_TIME 1000

#define MAIN_MENU_BUTTONS "MainMenuButtons.png"
#define TITLE_BANNER "Title.png"

static int MAIN_MENU_MAP[160] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
};

#define SETUP_BUTTONS "SetupButtons.png"
#define SETUP_TITLES "SetupTitles.png"
#define TURTLE_SELECTOR "TurtleSelector.png"
#define KEYBOARD_BUTTONS "KeyboardButtons.png"