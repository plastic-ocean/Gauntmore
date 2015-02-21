#pragma once
#include "oxygine-framework.h"
#include "Game.h"
#include "ProgressBar.h"
#include "res.h"

using namespace oxygine;

class Game;
DECLARE_SMART(HealthBar, spHealthBar);
class HealthBar : public Object {
    
public:
    HealthBar(Game *game);
    void render();
    void updateHealth(float num);
    
private:
    Game *_game;
    spProgressBar _healthBar;
    spSprite _healthBorder;
    float _health;
};