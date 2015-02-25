#include "Gold.h"
#include "res.h"
#include "Game.h"


Gold::Gold():_value(10) {
}

SDL_Rect Gold::getBounds() {
    Vector2 unitPosition = getPosition();
    _bounds.x = unitPosition.x + 20;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 30;
    _bounds.w = 20;
    
    return _bounds;
}

void Gold::addSprite() {
    _sprite = new Sprite;
    _sprite->addTween(TweenAnim(resources.getResAnim("gold")), 500, -1);;
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}

void Gold::_init() {
    addSprite();
}


void Gold::_interact() {
    if (!isDead()) {        
        // add gold to gold count
        _game->updateGoldCount(_value);
        
        // remove sprite
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        _dead = true;
    }
}


void Gold::_update(const UpdateState &us) {
}