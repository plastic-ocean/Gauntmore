#include "oxygine-framework.h"
#include "res.h"
#include "Game.h"
using namespace oxygine;


void gauntmore_preinit() {}


void gauntmore_init() {
	//load resources
	res::load();
	
	//create scene with game
	spGame game = new Game;
	game->init();
	game->attachTo(getStage());
}


void gauntmore_update() {}


void gauntmore_destroy() {
	res::free();
}