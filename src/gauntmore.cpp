#include "oxygine-framework.h"
#include "res.h"
#include "Game.h"
using namespace oxygine;


void gauntmore_preinit() {}


void gauntmore_init() {
	// Load resources.
	res::load();
	
	// Create game scene.
	spGame game = new Game;
	game->init();
	game->attachTo(getStage());
}


void gauntmore_update() {}


void gauntmore_destroy() {
	res::free();
}