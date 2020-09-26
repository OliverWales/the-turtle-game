#pragma once

#define TITLE "The Turtle Game" // window title
#define PIXEL_SIZE 4 // screen pixels per game pixel
#define TICK_TIME 200 // animation frame length in ms

#define BACKGROUND_COLOUR sf::Color(70, 110, 175)
#define TILE_SET "TileSet.png"
#define TILE_SIZE 32

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 60

#define SPLASH_SCREEN "SplashScreen.png"
#define SPLASH_SCREEN_TIME 1500

// Main menu screen
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
 
// Credits screen
#define CREDITS_BUTTONS "SetupButtons.png"
#define CREDITS "Credits.png"
static int CREDITS_MAP[160] = {
	0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
	0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
	1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

// Setup screen
#define SETUP_BUTTONS "SetupButtons.png"
#define SETUP_TITLES "SetupTitles.png"
#define TURTLE_SELECTOR "TurtleSelector.png"
#define KEYBOARD_BUTTONS "KeyboardButtons.png"

static int SETUP_MAP[160] = {
	1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

// Game Screen
#define COIN_COUNT 100
#define GAME_BUTTONS "GameButtons.png"
#define COIN "Coin.png"

#include <SFML/Graphics.hpp>

static sf::Color* PLAYER_COLOURS[4] = {
	new sf::Color(132, 255, 12),
	new sf::Color(255, 89, 194),
	new sf::Color(255, 0, 0),
	new sf::Color(137, 201, 238)
};