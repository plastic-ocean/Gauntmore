#include "GameScene.h"
#include "PauseMenu.h"

spGameScene GameScene::instance;

/**
 * Constructor.
 */
GameScene::GameScene() {
    // Create game actor.
    _game = new Game;
    _game->attachTo(_view);
    _game->setClock(new Clock);
}


/**
 * Unpauses the game when switching to this scene.
 */
void GameScene::_show() {
    _game->setPaused(false);
    _game->getClock()->resume();
}