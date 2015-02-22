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
    void render();
    void updateGoldCount(string count);
    
private:
    Game *_game;
    spTextField _goldCount;
    spSprite _coin;
    
};