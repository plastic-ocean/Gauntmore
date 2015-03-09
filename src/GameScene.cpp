#include "GameScene.h"
#include "PauseMenu.h"

spGameScene GameScene::instance;

GameScene::GameScene() {
    // Create game actor.
    _game = new Game;
    _game->attachTo(_view);
    
    _game->setClock(new Clock);
}

void GameScene::_show() {
    _game->setPaused(false);
    _game->getClock()->resume();
}