#include "GameScene.h"
#include "PauseMenu.h"

spGameScene GameScene::instance;

GameScene::GameScene() {
    // Create game actor.
    _game = new Game;
    _game->attachTo(_view);
    
    _game->setClock(new Clock);
    
    // Subscribe to hidden messages from PauseMenu
//    PauseMenu::instance->addEventListener(GameScene::HiddenEvent::EVENT, CLOSURE(this, &GameScene::_onEvent));
}

void GameScene::_show() {
    _game->setPaused(false);
    _game->getClock()->resume();
}