#include <iostream>
#include "CollisionDetector.h"
#include "Player.h"
#include "Unit.h"


/**
 * Constructor.
 */
CollisionDetector::CollisionDetector() {}


/**
 * Detects collisions between a sprite and the walls.
 *
 * @tiles is the tiles/Things list.
 * @x is the sprite's x coordinate.
 * @y is the sprite's y coordinate.
 * @h is the sprite's height.
 * @w is the sprite's width.
 * @return true if there is a collision, false if not.
 */
bool CollisionDetector::detectWalls(vector<SDL_Rect> tiles, int x, int y, int h, int w) {
    bool isCollision = false;
    SDL_Rect spriteRect;
    spriteRect.x = x + 10;
    spriteRect.y = y + 12;
    spriteRect.h = h - 14;
    spriteRect.w = w - 24;
    
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
 * Detects collisions between a sprite and potions. Used to pickup potions
 *
 * @tiles is the list of units.
 * @x is the sprite's x coordinate.
 * @y is the sprite's y coordinate.
 * @h is the sprite's height.
 * @w is the sprite's width.
 * @return true if there is a collision, false if not.
 */
bool CollisionDetector::detectUnits(list<spUnit> *units, int x, int y, int h, int w) {
    bool isCollision = false;
    SDL_Rect spriteRect;
    spriteRect.x = x + 10;
    spriteRect.y = y + 12;
    spriteRect.h = h - 14;
    spriteRect.w = w - 24;
    
    // Detect potion collisions for pickup
    const SDL_Rect *sprite = &spriteRect;
    for (spUnit unit : *units) {
        if (unit->isPotion()) {
            SDL_Rect unitRect = unit->getRect();
            const SDL_Rect *constUnitRect = &unitRect;
            if (SDL_HasIntersection(sprite, constUnitRect)) {
                unit->interact();
            }
        }
    }
    return isCollision;
}
