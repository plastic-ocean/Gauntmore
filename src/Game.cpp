#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Creature.h"
#include "Chest.h"
#include "Gold.h"
#include "Potion.h"
#include "res.h"
#include "KeyboardInput.h"
#include "Map.h"
#include "MazeGen.h"
#include "Skeleton.h"
#include "HealthBar.h"

typedef list<spUnit> Units;


/**
 * Constructor.
 */
Game::Game() {}


/**
 * Destructor.
 */
Game::~Game() {}


/**
 * Initializes the game. Creates the map, the player, the monsters, the static objects
 * and puts them in the game world.
 */
void Game::init() {
	// Set the size of the scene to the size of the display.
	setSize(getStage()->getSize());
    
    // Size is the number of tiles (with 32 px tiles; 15 tiles = 480 px; 20 tiles = 640 px)
    int size = 13;

	// Create map
    _map = new Map(size);
    _renderMap();
    _createTiles();
    
	// Create player
	_player = new Player(20, 1, 1);
    _player->init(_getEntrance(), this);

    _setUnits();
    

    // TODO Create enemy creatures (with random loot!)
//    for (int i = 0; i < **large number**; ++i) {
//        spCreature creature = new Creature;
//        creature->init(Vector2(**calculate starting position**, this);
//    }

    // Create chest
    Vector2 chestLocation = Vector2((64 * 6), (64 * 6));

    _chest = new Chest;

    _chest->init(chestLocation, this);
   
    //location for skeleton
    
    // TODO Create enemy creatures (with random loot!)

    // TODO Create chests (with even more random loot!)

	// Handle input
    _move = new KeyboardInput(this);
    
    // Health bar
    _healthBar = new HealthBar(this);
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
    spriteRect.y = y + 12;
    spriteRect.h = h - 14;
    spriteRect.w = w - 24;
    const SDL_Rect *sprite = &spriteRect;
    
    // Check for collision between the sprite and each tile

    for (SDL_Rect tileRect : _tiles) {
        const SDL_Rect *tile = &tileRect;
        if (SDL_HasIntersection(sprite, tile)) {
            isCollision = true;
        }
    }
    
    for (spUnit unit : _units){
        Vector2 unitPosition = unit->getPosition();
        SDL_Rect unitRect;
        // these are adjusted for a skeleton sprite, we will need to make different ones for
        // different sprites
        unitRect.x = unitPosition.x - 32;
        unitRect.y = unitPosition.y - 32;
        cout << "Unit Pos.x: " << unitPosition.x << endl;
        cout << "Unit Pos.y: " << unitPosition.y << endl;
        unitRect.h = 1;
        unitRect.w = 1;

        const SDL_Rect *constUnitRect = &unitRect;
        // we also make sure that we are not collecting a collision with outself by doing a type check
        if (SDL_HasIntersection(sprite, constUnitRect) && typeid(*unit).name() != "6Player") {
            isCollision = true;
            std::cout << "collision with unit: " << typeid(*unit).name() << std::endl;
        }
    }
    
    return isCollision;
}


/**
* Switches viewable map to the room in the direction of the given edge in the maze.
*/
void Game::switchRoom(int edge) {
    // Change to a new room in the maze.
    _map->changeRoom(edge);
    _renderMap();
    _createTiles();
//    _setUnits();

    // Get player entrance position
    int playerCol = 1;
    int playerRow = 1;

    switch (edge) {
        case 0: // top
            playerCol = _map->getRoom()->getBottom() * tileSize;
            playerRow = (_map->getRoom()->getSize() - 2) * tileSize;
            break;
        case 1: // right
            playerCol = tileSize;
            playerRow = _map->getRoom()->getLeft() * tileSize;
            break;
        case 2: // bottom
            playerCol = _map->getRoom()->getTop() * tileSize;
            playerRow = tileSize;
            break;
        case 3: // left
            playerCol = (_map->getRoom()->getSize() - 2) * tileSize;
            playerRow = _map->getRoom()->getRight() * tileSize;
            break;
        default:
            break;
    }

//    cout << "switch position: " << playerCol << ", " << playerRow << endl;

    // Setup player
    _player->detachUnit();
    _player->attachUnit();
    _player->addSprite();
    _player->setPosition(Vector2(playerCol, playerRow));
    
    // Update health bar
    _healthBar->render();
}


void Game::pushUnit(spUnit unit) {
    _map->getRoom()->pushUnit(unit);
    _units.push_back(unit);
}


spPlayer Game::getPlayer() {
    return _player;
}


spMap Game::getMap() {
    return _map;
}


list<spUnit> Game::getUnits() {
    return _units;
}


/**
 * Gets the tile map.
 *
 * @return the tile map.
 */
Tmx::Map *Game::getTileMap() {
    return _tileMap;
}


/**
 * Gets tiles.
 *
 * @return the tiles vector<SDL_Rect>.
 */
std::vector<SDL_Rect> Game::getTiles() {
    return _tiles;
}

//std::list<spUnit> Game::getUnits(){
//    return _units;
//}

/**
 * Gets the keyboard input handler.
 */
spKeyboardInput Game::getMove() {
    return _move;
}

void Game::updateHealth(float num) {
    _healthBar->updateHealth(num);
}


/**
 * Updates the Units each frame. A virtual method of Actor it is being called each frame.
 *
 * @us is the UpdateStatus sent by the global update method.
 */
void Game::doUpdate(const UpdateState &us) {
    // Iterate through the unit list and call their update method. Then check for death.
    for (Units::iterator i = _units.begin(); i != _units.end(); ) {
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
 * Reads the tile map description from the .tmx file and uses it to render the map.
 */
void Game::_renderMap() {
    _tileMap = new Tmx::Map();
    
    _tileMap->ParseFile("tmx/room.tmx");

    _map->getRoom()->setTileMap(_tileMap);
    
    for (int i = 0; i < _tileMap->GetNumLayers(); ++i) {
        // Get a layer.
        const Tmx::Layer *layer = _tileMap->GetLayer(i);
        
        for (int x = 0; x < layer->GetWidth(); ++x) {
            for (int y = 0; y < layer->GetHeight(); ++y) {
                int tilesetIndex = layer->GetTileTilesetIndex(x, y);
                const Tmx::Tileset *tileset = _tileMap->GetTileset(tilesetIndex);
                std::string name = tileset->GetName();
                int tileSize = tileset->GetImage()->GetWidth();
                int drawX = x * tileSize;
                int drawY = y * tileSize;
                // Draw the tile.
                spSprite sprite = new Sprite;
                sprite->setResAnim(resources.getResAnim(name));
//                sprite->setScale(1.25f);
                sprite->setX(drawX);
                sprite->setY(drawY);
                sprite->attachTo(this);
                sprite->setAnchor(Vector2(0.5f, 0.5f));
            }
        }
    }
//    delete map;
}


/**
 * Creates a vector of rectangles called tiles that is used to detect collisions.
 */
void Game::_createTiles() {
    _tiles.clear();
    // Build a vector of rectangles to represent the collidable tiles.
    for (int i = 0; i < _tileMap->GetNumLayers(); ++i) {
        // Get a layer.
        const Tmx::Layer *layer = _tileMap->GetLayer(i);
        for (int x = 0; x < layer->GetWidth(); ++x) {
            for (int y = 0; y < layer->GetHeight(); ++y) {
                
                int tilesetIndex = layer->GetTileTilesetIndex(x, y);
                const Tmx::Tileset *tileset = _tileMap->GetTileset(tilesetIndex);
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



Vector2 Game::_getEntrance() {
    Vector2 location = _map->getRoom()->getEntrance();
    location.x *= tileSize;
    location.y *= tileSize;
    
    return location;
}

void Game::_setUnits() {
    _units = static_cast<Units>(_map->getRoom()->getUnits());
}