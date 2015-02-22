#pragma once
#include "oxygine-framework.h"
#include "Game.h"
#include "res.h"

using namespace oxygine;

class Game;
DECLARE_SMART(GoldCount, spGoldCount);
class GoldCount : public Object {
    
public:
    GoldCount(Game *game);
    
    /**
     * Renders the on screen gold counter on room changes.
     */
    void render();
    
    /**
     * Updates the string count and sets the on screen gold count.
     *
     * @count is the value to add to the count.
     */
    void updateGoldCount(int value);
    
private:
    Game *_game;
    spTextField _goldCount;
    spSprite _coin;
    int _count;
};