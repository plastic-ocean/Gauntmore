#include <iostream>

#include "Game.h"
#include "Joystick.h"
#include "Player.h"
#include "res.h"
#include "Tmx.h"
//#include "Map.h"

Game::Game() {}


void Game::init() {
	// scene layer would have size of display
	setSize(getStage()->getSize());

	// create map
//    _map = new Map();
//    _map->render(this);
    renderMap();
    
	// create player
	_player = new Player;
	_player->init(this);

	// create virtual joystick
	_move = new Joystick;
	_move->attachTo(this);
	_move->setY(getHeight() - _move->getHeight());
}


void Game::doUpdate(const UpdateState &us) {
	// doUpdate is virtual method of Actor
	// it is being called each frame

	// update player each frame
	_player->update(us);
}


void Game::renderMap() {
    Tmx::Map *map = new Tmx::Map();
    
    map->ParseFile("room01.tmx");
    
    for (int i = 0; i < map->GetNumLayers(); ++i) {
        // Get a layer.
        const Tmx::Layer *layer = map->GetLayer(i);
        
        for (int x = 0; x < layer->GetWidth(); ++x) {
            for (int y = 0; y < layer->GetHeight(); ++y) {
                int tilesetIndex = layer->GetTileTilesetIndex(x, y);
                const Tmx::Tileset *tileset = map->GetTileset(tilesetIndex);
                std::string name = tileset->GetName();
                int tileSize = tileset->GetImage()->GetWidth();
                int drawX = x * tileSize;
                int drawY = y * tileSize;
                // Draw the tile.
                spSprite sprite = new Sprite;
                sprite->setResAnim(res::ui.getResAnim(name));
                sprite->setX(drawX);
                sprite->setY(drawY);
                sprite->attachTo(this);
            }
        }
    }
    delete map;
}