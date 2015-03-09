#pragma once
#include <stdio.h>

#pragma once
#include "oxygine-framework.h"
#include "Game.h"
#include "res.h"

using namespace oxygine;

class Game;
DECLARE_SMART(WeaponCount, spWeaponCount);
class WeaponCount : public Object {
    
public:
    WeaponCount(Game *game);
    
    /**
     * Renders the on screen gold counter on room changes.
     */
    void render();
    
    /**
     * Updates the string count and sets the on screen gold count.
     *
     * @count is the value to add to the count.
     */
    void updateWeaponCount(int value);
    
private:
    Game *_game;
    spTextField _weaponCount;
    spSprite _sword;
    int _count;
};
