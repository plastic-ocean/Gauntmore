#include <iostream>
#include "CollisionDetector.h"
#include "Player.h"
#include "Unit.h"

CollisionDetector::CollisionDetector(Game *game):_game(game) {}


bool CollisionDetector::detectWalls(std::vector<SDL_Rect> tiles, SDL_Rect spriteRect) {
    bool isCollision = false;
    const SDL_Rect *sprite = &spriteRect;
    
    for (SDL_Rect tileRect : tiles) {
        const SDL_Rect *tile = &tileRect;
        if (SDL_HasIntersection(sprite, tile)) {
            isCollision = true;
        }
    }
    
    return isCollision;
}


bool CollisionDetector::detectUnits(list<spUnit> *units, SDL_Rect spriteRect) {
    bool isCollision = false;
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
