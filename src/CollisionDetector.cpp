#include <iostream>
#include "CollisionDetector.h"
#include "Player.h"
#include "Unit.h"

CollisionDetector::CollisionDetector() {}


bool CollisionDetector::detectWalls(std::vector<SDL_Rect> tiles, int x, int y, int h, int w) {
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


//bool CollisionDetector::detectWalls(std::vector<SDL_Rect> tiles, SDL_Rect spriteRect) {
//    bool isCollision = false;
//    const SDL_Rect *sprite = &spriteRect;
//    
//    for (SDL_Rect tileRect : tiles) {
//        const SDL_Rect *tile = &tileRect;
//        if (SDL_HasIntersection(sprite, tile)) {
//            isCollision = true;
//        }
//    }
//    
//    return isCollision;
//}


bool CollisionDetector::detectUnits(list<spUnit> *units, int x, int y, int h, int w) {
    bool isCollision = false;
    SDL_Rect spriteRect;
    spriteRect.x = x + 10;
    spriteRect.y = y + 12;
    spriteRect.h = h - 14;
    spriteRect.w = w - 24;
    
    const SDL_Rect *sprite = &spriteRect;
    
    for (spUnit unit : *units) {
        if (unit->getType() != "player") {
            SDL_Rect unitRect = unit->getBounds();
            const SDL_Rect *constUnitRect = &unitRect;
            if (SDL_HasIntersection(sprite, constUnitRect)) {
                isCollision = true;
            }
        }
        
    }
    
    return isCollision;
}
