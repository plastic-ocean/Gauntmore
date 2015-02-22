

#include <iostream>
#include "CollisionDetector.h"
#include "Player.h"
#include "Unit.h"

CollisionDetector::CollisionDetector(Game *game):_game(game) {}


bool CollisionDetector::detectWalls(std::vector<SDL_Rect> tiles, SDL_Rect spriteRect) {
    bool isCollision = false;
    const SDL_Rect *sprite = &spriteRect;
    
    // Check for collision between the sprite and each tile
    
    // pass in the sdl rect below
    for (SDL_Rect tileRect : tiles) {
        const SDL_Rect *tile = &tileRect;
        if (SDL_HasIntersection(sprite, tile)) {
            isCollision = true;
        }
    }
    
    return isCollision;
}

bool CollisionDetector::detectUnits(list<spUnit> units, SDL_Rect spriteRect) {
    bool isCollision = false;
    const SDL_Rect *sprite = &spriteRect;
    
    for (spUnit unit : units) {
        if (unit->getType() != "player") {
            
            SDL_Rect unitRect = unit->getBounds();
            // these are adjusted for a skeleton sprite, we will need to make different ones for
            // different sprites
            
            const SDL_Rect *constUnitRect = &unitRect;
            // we also make sure that we are not collecting a collision with outself by doing a type check
            if (SDL_HasIntersection(sprite, constUnitRect)) {
                isCollision = true;
                std::cout << "collision with unit: " << unit->getType() << std::endl;
            }
            //std::cout << "no collision with unit: " << typeid(*unit).name() << std::endl;
        }
        
    }
    
    return isCollision;
}
