#ifndef __gauntmore__CollisionDetector__
#define __gauntmore__CollisionDetector__

#include <iostream>
#include "oxygine-framework.h"
#include "Game.h"

using namespace oxygine;

DECLARE_SMART(CollisionDetector, spCollisionDetector)
class CollisionDetector : public Object {
    
public:
    CollisionDetector();
    
    int count = 0;

    /**
     * Detects collisions between a sprite and the walls.
     *
     * @tiles is the tiles/Things list.
     * @x is the sprite's x coordinate.
     * @y is the sprite's y coordinate.
     * @h is the sprite's height.
     * @w is the sprite's width.
     * @return: ture if there is a collision. false if not.
     */
    bool detect(std::vector<SDL_Rect> tiles, int x, int y, int h, int w);

    /**
     * Detects collisions between a sprite and potions. Used to pickup potions
     *
     * @tiles is the list of units.
     * @x is the sprite's x coordinate.
     * @y is the sprite's y coordinate.
     * @h is the sprite's height.
     * @w is the sprite's width.
     * @return: ture if there is a collision. false if not.
     */
    bool detectPotions(std::list<spUnit> *units, int x, int y, int h, int w);

private:

};

#endif