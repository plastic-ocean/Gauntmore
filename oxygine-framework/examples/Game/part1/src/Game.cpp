#include <iostream>

#include "Game.h"
#include "Player.h"
#include "res.h"
#include "Tmx.h"
#include "KeyboardInput.h"


/**
 * Constructor.
 */
Game::Game() {}


/**
 * Initialzes the game. Creates the map, the player, the monsters, the static objects 
 * and puts them in the game world.
 */
void Game::init() {
	// scene layer would have size of display
	setSize(getStage()->getSize());

	// create map
    renderMap();
    createTiles();
    
	// create player
	_player = new Player;
	_player->init(this);

	// handle input
    _move = new KeyboardInput;
    _move->attachTo(this);
}


/**
 * Updates the player each frame. A virtual method of Actor it is being called each frame.
 *
 * @us is the UpdateStatus sent by the global update method.
 */
void Game::doUpdate(const UpdateState &us) {
	_player->update(us);
}


/**
 * Reads the tile map description from the .tmx file and uses it to render the map.
 */
void Game::renderMap() {
    map = new Tmx::Map();
    
    map->ParseFile("../data/tmx/room01.tmx");
    
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
//    delete map;
}


/**
 * Creates a vector of rectangles called tiles that is used to detect collisions.
 */
void Game::createTiles() {
    // Build a vector of rectangles to represent the collidable tiles.
    for (int i = 0; i < map->GetNumLayers(); ++i) {
        // Get a layer.
        const Tmx::Layer *layer = map->GetLayer(i);
        for (int x = 0; x < layer->GetWidth(); ++x) {
            for (int y = 0; y < layer->GetHeight(); ++y) {
                
                int tilesetIndex = layer->GetTileTilesetIndex(x, y);
                const Tmx::Tileset *tileset = map->GetTileset(tilesetIndex);
                int tileSize = tileset->GetImage()->GetWidth();
                std::string name = tileset->GetName();
                
                if (name == "wall") {
                    int posX = x * tileSize;
                    int posY = y * tileSize;
                    SDL_Rect tile;
                    tile.x = posX;
                    tile.y = posY;
                    tile.h = tileSize;
                    tile.w = tileSize;
                    tiles.push_back(tile);
                }
            }
        }
    }
}


/**
 * Detects collisions between the player and the walls.
 *
 * @x is the x coordinate to check.
 * @y is the y coordinate to check.
 * @h is the height coordinate to check.
 * @w is the width coordinate to check.
 * @return true if there is a collision and false if there is not
 */
bool Game::detectCollision(int x, int y, int h, int w) {
    bool isCollision = false;
    SDL_Rect spriteRect;
    spriteRect.x = x;
    spriteRect.y = y;
    spriteRect.h = h;
    spriteRect.w = w;
    
    // Iterate through the tiles vector to see if the spriteRect collides with the tile.
    const SDL_Rect *sprite = &spriteRect;
    for (SDL_Rect tileRect : tiles) {
        const SDL_Rect *tile = &tileRect;
        if (SDL_HasIntersection(sprite, tile)) {
            isCollision = true;
        }
    }
    
    return isCollision;
}


/**
 * Gets the tile map.
 *
 * @return the tile map.
 */
Tmx::Map *Game::getMap() {
    return map;
}


/**
 * Gets tiles.
 *
 * @return the tiles vector<SDL_Rect>.
 */
std::vector<SDL_Rect> Game::getTiles() {
    return tiles;
}