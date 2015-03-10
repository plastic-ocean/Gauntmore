#include "Input.h"
#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_events.h"

#include "PauseMenu.h"
#include "res.h"


spPauseMenu PauseMenu::instance;


/**
 * Constructor.
 */
PauseMenu::PauseMenu():_isReady(false), _selection(selectContinue) {
    _name = new Sprite;
    _name->setResAnim(resources.getResAnim("title_small"));
    _name->setAnchor(Vector2(0.5f, 0.5f));
    _name->setPosition(Vector2(768 / 2, _name->getHeight()));
    _name->attachTo(_view);
    
    _continue = new Sprite;
    _continue->setResAnim(resources.getResAnim("continue_selected"));
    _continue->setAnchor(Vector2(0.5f, 0.5f));
    _continue->setPosition(Vector2(768 / 2, 768 / 2 - 80));
    _continue->attachTo(_view);
    
    _newGame = new Sprite;
    _newGame->setResAnim(resources.getResAnim("new_game"));
    _newGame->setAnchor(Vector2(0.5f, 0.5f));
    _newGame->setPosition(Vector2(768 / 2, 768 / 2));
    _newGame->attachTo(_view);
    
    _quit = new Sprite;
    _quit->setResAnim(resources.getResAnim("quit"));
    _quit->setAnchor(Vector2(0.5f, 0.5f));
    _quit->setPosition(Vector2(768 / 2, 768 / 2 + _quit->getHeight()));
    _quit->attachTo(_view);
    
    // Add keyboard listener
    Input::instance.addEventListener(Input::event_platform, CLOSURE(this, &PauseMenu::_onEvent));
}


/**
 * Changes the new game image between selected and unselected.
 */
void PauseMenu::setNewGame(string newGameImage) {
    _newGame->setResAnim(resources.getResAnim(newGameImage));
}


/**
 * Changes the continue image between selected and unselected.
 */
void PauseMenu::setContinue(string continueImage) {
    _continue->setResAnim(resources.getResAnim(continueImage));
}


/**
 * Changes the quit image between selected and unselected.
 */
void PauseMenu::setQuit(string quitImage) {
    _quit->setResAnim(resources.getResAnim(quitImage));
}


/**
 * Sets the game.
 */
void PauseMenu::setGame(Game *game) {
    _game = game;
}


/**
 * Keyboard event handler.
 *
 * @ev is the SDL event sent by the event listener.
 */
void PauseMenu::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && _isReady) {
        switch (event->key.keysym.sym) {
            case SDLK_RETURN:
                if (_selection == selectContinue) {
                    _isReady = false;
                    changeScene(GameScene::instance);
                } else if (_selection == selectNewGame) {
                    _isReady = false;
                    _game->createNewGame();
                    changeScene(GameScene::instance);
                } else if (_selection == selectQuit) {
                    core::requestQuit();
                }
                break;
            case SDLK_UP:
            case SDLK_w:
                _selectNext("up");
                break;
            case SDLK_DOWN:
            case SDLK_s:
                _selectNext("down");
                break;
            default:
                break;
        }
    }
    
    if (event->type == SDL_KEYUP && event->key.repeat == 0) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                _isReady = true;
                break;
            default:
                break;
        }
    }
}


/**
 * Selects the next item in the menu list.
 */
void PauseMenu::_selectNext(string direction) {
    if (_selection == selectContinue && direction == "down") {
        _selection = selectNewGame;
        setNewGame("new_game_selected");
        setContinue("continue");
    } else if (_selection == selectContinue && direction == "up") {
        _selection = selectQuit;
        setQuit("quit_selected");
        setContinue("continue");
    } else if (_selection == selectNewGame && direction == "down") {
        _selection = selectQuit;
        setNewGame("new_game");
        setQuit("quit_selected");
    } else if (_selection == selectNewGame && direction == "up") {
        _selection = selectContinue;
        setNewGame("new_game");
        setContinue("continue_selected");
    } else if (_selection == selectQuit && direction == "down") {
        _selection = selectContinue;
        setQuit("quit");
        setContinue("continue_selected");
    } else if (_selection == selectQuit && direction == "up") {
        _selection = selectNewGame;
        setNewGame("new_game_selected");
        setQuit("quit");
    }
}
