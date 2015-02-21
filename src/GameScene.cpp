#include "GameScene.h"

spGameScene GameScene::instance;

GameScene::GameScene() {
    // Create game actor.
    _game = new Game;
    _game->init();
    _game->attachTo(_view);
    
    _game->setClock(new Clock);
}