#include <iostream>

#include "tmx/Tmx.h"

#include "Game.h"
#include "res.h"
#include "KeyboardInput.h"

#include "Player.h"

#include "Creature.h"
#include "Skeleton.h"
#include "Slime.h"

#include "Chest.h"
#include "Gold.h"
#include "Potion.h"

#include "Map.h"

#include "HealthBar.h"
#include "GoldCount.h"

typedef list<spUnit> Units;


/**
 * Constructor.
 */
Game::Game() {
    // Set the size of the scene to the size of the display.
    setSize(getStage()->getSize());
    
    // Size is the number of tiles
    int size = 13;
    
    // Create map
    _map = new Map(size);
    _renderMap();
    _createTiles();
    
    list<spUnit> *units = _map->getRoom()->getUnits();
    for (Units::iterator i = units->begin(); i != units->end(); ++i) {
        spUnit unit = *i;
        if (unit->getType() != "player") {
            unit->init(unit->getLocation(), this);
//            unit->attachUnit();
//            unit->setPosition(unit->getLocation());
//            unit->addSprite();
//            cout << unit->getType() << " x: " << unit->getPosition().x << " y: " <<  unit->getPosition().y << endl;
        }
    }
 
    // Create player
    _player = new Player(10, 1, 1);
    _player->init(_getEntrance(), this);
    _map->getRoom()->getUnits()->push_back(_player);
    
    // Handle input
    _move = new KeyboardInput(this);
    
    // Health bar
    _healthBar = new HealthBar(this);
    
    // Gold count
    _goldCount = new GoldCount(this);
}


/**
 * Destructor.
 */
Game::~Game() {}


void Game::movePlayer(int facing) {
    getPlayer()->move(facing);
}

void Game::stopPlayer() {
    getPlayer()->removeTween();
}


/**
* Switches viewable map to the room in the direction of the given edge in the maze.
*/
void Game::switchRoom(int edge) {
    // Change to a new room in the maze.
    _map->changeRoom(edge);
    _renderMap();
    _createTiles();

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

    // Setup units
    list<spUnit> *units = _map->getRoom()->getUnits();
    for (Units::iterator i = units->begin(); i != units->end(); ) {
        spUnit unit = *i;
        if (unit->getType() == "player") {
            i = units->erase(i);
        } else {
            unit->init(unit->getLocation(), this);
//            unit->attachUnit();
//            unit->setPosition(unit->getLocation());
//            unit->addSprite();
            ++i;
        }
    }
    
    // Setup player
//    _player->detachUnit();
    _player->attachUnit();
    _player->addSprite();
    _player->setPosition(Vector2(playerCol, playerRow));
    _map->getRoom()->getUnits()->push_back(_player);
    
    // Update UI
    _healthBar->render();
    _goldCount->render();
}


void Game::pushUnit(spUnit unit) {
    _map->getRoom()->pushUnit(unit);
}


spPlayer Game::getPlayer() {
    return _player;
}


spMap Game::getMap() {
    return _map;
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

/**
 * Gets the keyboard input handler.
 */
spKeyboardInput Game::getMove() {
    return _move;
}


void Game::updateHealth(float num) {
    _healthBar->updateHealth(num);
}


void Game::updateGoldCount(int value) {
    _goldCount->updateGoldCount(value);
}


bool Game::isExit(Vector2 position) {
    bool isExit = false;
    int size = getMap()->getRoom()->getSize() * tileSize;
    
    if (!(position.x > 0 && position.x < size - tileSize && position.y > 0 && position.y < size - tileSize)) {
        isExit = true;
        int edge = 0;
        
        if (position.y <= 0) {
            // top
            edge = 0;
        } else if (position.x >= size - tileSize) {
            // right
            edge = 1;
        } else if (position.y >= size - tileSize) {
            // bottom
            edge = 2;
        } else if (position.x <= 0) {
            // left
            edge = 3;
        }
        
        switchRoom(edge);
    }
    
    return isExit;
}

int Game::getTileSize() {
    return tileSize;
}


/**
 * Updates the Units each frame. A virtual method of Actor it is being called each frame.
 *
 * @us is the UpdateStatus sent by the global update method.
 */
void Game::doUpdate(const UpdateState &us) {
    list<spUnit> *units = _map->getRoom()->getUnits();
    // Iterate through the unit list and call their update method. Then check for death.
    for (Units::iterator i = units->begin(); i != units->end(); ) {
        spUnit unit = *i;
        unit->update(us);
//        cout << "update " << unit->getType() << endl;
        if (unit->isDead()) {
//            cout << "erase " << unit->getType() << endl;
            // If it is dead remove it from list.
            i = units->erase(i);
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
