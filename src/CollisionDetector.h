#include <iostream>
#include "oxygine-framework.h"
#include "Game.h"

using namespace oxygine;

DECLARE_SMART(CollisionDetector, spCollisionDetector)

#ifndef __gauntmore__CollisionDetector__
#define __gauntmore__CollisionDetector__

class CollisionDetector : public Object {
    
public:
    CollisionDetector();
    
    int count = 0;
    
    bool detectWalls(std::vector<SDL_Rect> tiles, int x, int y, int h, int w);
    
//    bool detectWalls(std::vector<SDL_Rect> tiles, SDL_Rect spriteRect);
    bool detectUnits(std::list<spUnit> *units, int x, int y, int h, int w);
    
//    bool detectUnits(list<SDL_Rect> units, int x, int y, int h, int w);
    
private:
};

#endif