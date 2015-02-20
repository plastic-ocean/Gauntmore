//
//  Collision.cpp
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/19/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//
#include "Game.h"
#include "Collision.h"
#include "Unit.h"


Collision::Collision() {
    
}
Collision::~Collision() {}

 bool Collision::detectCollision(int x, int y, int h, int w) {
    bool isCollision = false;
    SDL_Rect spriteRect;
    spriteRect.x = x + 12;
    spriteRect.y = y + 12;
    spriteRect.h = h - 12;
    spriteRect.w = w - 12;
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
        unitRect.x = unitPosition.x-3 ;
        unitRect.y = unitPosition.y-3 ;
        unitRect.h = 13;
        unitRect.w = 13;
        
        
        const SDL_Rect *constUnitRect = &unitRect;
        // we also make sure that we are not collecting a collision with outself by doing a type check
        if (SDL_HasIntersection(sprite, constUnitRect) && typeid(*unit).name() != "6Player") {
            isCollision = true;
//            std::cout << "collision with unit: " << typeid(*unit).name() << std::endl;
        }
    }
    
    return isCollision;
}
