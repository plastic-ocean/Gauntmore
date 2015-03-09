#include "Menu.h"

/**
 * Construtor.
 */
Menu::Menu() {}

/**
 * Changes the new game image between selected and unselected.
 */
void Menu::setNewGame(string newGameImage) {
    _newGame->setResAnim(resources.getResAnim(newGameImage));
}


/**
 * Changes the continue image between selected and unselected.
 */
void Menu::setContinue(string continueImage) {
    _continue->setResAnim(resources.getResAnim(continueImage));
}


/**
 * Changes the quit image between selected and unselected.
 */
void Menu::setQuit(string quitImage) {
    _quit->setResAnim(resources.getResAnim(quitImage));
}


/**
 * Sets the game.
 */
void Menu::setGame(Game *game) {
    _game = game;
}