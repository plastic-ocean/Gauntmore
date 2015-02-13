#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Creature.h"
#include "res.h"
#include "Tmx.h"
#include "KeyboardInput.h"
#include "Map.h"

/**
 * Constructor.
 */
Game::Game() {}


/**
 * Destructor.
 */
Game::~Game() {}


/**
 * Initialzes the game. Creates the map, the player, the monsters, the static objects 
 * and puts them in the game world.
 */
void Game::init() {
	// Set the size of the scene to the size of the display.
	setSize(getStage()->getSize());

	// Create map
    map = new Map(15);
//    map->createMaze();
    map->createRoom();
    
    _renderMap();
    _createTiles();
    
	// Create player
    Vector2 location = map->getEntrance();
    location.x *= 32;
    location.y *= 32;
    
    std::cout << "location: " << location.x << ", " << location.y << std::endl;
    
	_player = new Player;
	_player->init(location, this);
    
    // TODO Create enemy creatures (with random loot!)
//    for (int i = 0; i < **large number**; ++i) {
//        spCreature creature = new Creature;
//        creature->init(Vector2(**calulate starting postion**, this);
//    }
    
    // TODO Create chests (with even more random loot!)

	// Handle input
    _move = new KeyboardInput;
    _move->attachTo(this);
}


/**
 * Detects collisions between a sprite and the walls.
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
    spriteRect.x = x + 10;
    spriteRect.y = y + 10;
    spriteRect.h = h - 10;
    spriteRect.w = w - 10;
    
    // Iterate through the tiles vector to see if the spriteRect collides with the tile.
    const SDL_Rect *sprite = &spriteRect;
    for (SDL_Rect tileRect : _tiles) {
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
    return _map;
}


/**
 * Gets tiles.
 *
 * @return the tiles vector<SDL_Rect>.
 */
std::vector<SDL_Rect> Game::getTiles() {
    return _tiles;
}


/**
 * Gets the keyboard input handler.
 */
spKeyboardInput Game::getMove() {
    return _move;
}


/**
 * Adds unit to the back of the units list.
 *
 * @unit is the Unit to be added.
 */
void Game::pushUnit(spUnit unit) {
    _units.push_back(unit);
}


/**
 * Updates the Units each frame. A virtual method of Actor it is being called each frame.
 *
 * @us is the UpdateStatus sent by the global update method.
 */
void Game::doUpdate(const UpdateState &us) {
    // Iterate through the unit list and call their update method. Then check for death.
    for (units::iterator i = _units.begin(); i != _units.end(); ) {
        spUnit unit = *i;
        unit->update(us);
        
        if (unit->isDead()) {
            // If it is dead remove it from list.
            i = _units.erase(i);
        } else {
            ++i;
        }
    }
}


/**
 * Generates a maze in a .tmx file.
 */
void _generateTmxFile() {
    
}


/**
 * Reads the tile map description from the .tmx file and uses it to render the map.
 */
void Game::_renderMap() {
    _map = new Tmx::Map();
    
    _map->ParseFile("data/tmx/room.tmx");
    
    for (int i = 0; i < _map->GetNumLayers(); ++i) {
        // Get a layer.
        const Tmx::Layer *layer = _map->GetLayer(i);
        
        for (int x = 0; x < layer->GetWidth(); ++x) {
            for (int y = 0; y < layer->GetHeight(); ++y) {
                int tilesetIndex = layer->GetTileTilesetIndex(x, y);
                const Tmx::Tileset *tileset = _map->GetTileset(tilesetIndex);
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
void Game::_createTiles() {
    // Build a vector of rectangles to represent the collidable tiles.
    for (int i = 0; i < _map->GetNumLayers(); ++i) {
        // Get a layer.
        const Tmx::Layer *layer = _map->GetLayer(i);
        for (int x = 0; x < layer->GetWidth(); ++x) {
            for (int y = 0; y < layer->GetHeight(); ++y) {
                
                int tilesetIndex = layer->GetTileTilesetIndex(x, y);
                const Tmx::Tileset *tileset = _map->GetTileset(tilesetIndex);
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
                    _tiles.push_back(tile);
                }
            }
        }
    }
}

