#include "res.h"
#include "Slime.h"


/**
 * Constructor
 */
Slime::Slime() {
    // Initialize the stats.
    _hp = 3;
    _attack = 1;
    _defense = 0;
    _speed = 100;
    
}

/**
 *
 *
 */
SDL_Rect Slime::getBounds() {
    Vector2 unitPosition = getPosition();
    _bounds.x = unitPosition.x + 20;
    _bounds.y = unitPosition.y + 15;
    _bounds.h = 30;
    _bounds.w = 20;
    
    return _bounds;
}


/**
 *
 *
 */
bool Slime::isPotion() {
    return false;
}
    
void Slime::damage() {

}

void Slime::addSprite() {
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("slime_down"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
}

/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Slime::_init() {
    addSprite();
    _setContents();
}


/**
 * Plays the attack animation.
 */
//void Slime::attack() {
//    switch (_facing) {
//        case up:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_up")), 500);
//            break;
//        case right:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_right")), 500);
//            break;
//        case down:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_down")), 500);
//            break;
//        case left:
//            _attackTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_left")), 500);
//            break;
//        default:
//            break;
//    }
//}



/**
 * Plays the move animation.
 */
//void Slime::move() {
//    _checkTween();
//    switch (_facing) {
//        case up:
//            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_up")), 500, -1);
//            break;
//        case right:
//            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_right")), 500, -1);
//            break;
//        case down:
//            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_down")), 500, -1);
//            break;
//        case left:
//            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("slime_left")), 500, -1);
//            break;
//        default:
//            break;
//    }
//}


void Slime::_interact() {
    _hp--;
    if (_hp == 0) {
        // The creature is dead, hide it with an alpha tween.
        _dead = true;
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
        _dropContents();
    }
}


/**
 * Updates the creature every frame. Called by Unit::update.
 *
 * @us is the UpdateStatus sent by Unit's update method.
 */
void Slime::_update(const UpdateState &us) {
//    cout << "creature update" << endl;
    Vector2 direction = moveMe();
    Vector2 position = getPosition();
    position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
    setPosition(position);
    
}