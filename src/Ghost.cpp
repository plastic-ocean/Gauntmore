#include "res.h"
#include "Ghost.h"


/**
 * Constructor
 */
Ghost::Ghost() {
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
SDL_Rect Ghost::getBounds() {
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
bool Ghost::isPotion() {
    return false;
}

void Ghost::damage() {
    
}

void Ghost::addSprite() {
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(resources.getResAnim("ghost_down"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    move();
}

/**
 * Initializes a creatures position and sprite. Called by Unit's init() method.
 */
void Ghost::_init() {
    addSprite();
    _setContents();
}


/**
 * Plays the move animation.
 */
void Ghost::move() {
    //_checkTween();
    switch (_facing) {
        case up:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("ghost_up")), 500, -1);
            break;
        case right:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("ghost_right")), 500, -1);
            break;
        case down:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("ghost_down")), 500, -1);
            break;
        case left:
            _moveTween = _sprite->addTween(TweenAnim(resources.getResAnim("ghost_left")), 500, -1);
            break;
        default:
            break;
    }
}


void Ghost::_interact() {
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
void Ghost::_update(const UpdateState &us) {
    
    Vector2 direction = moveMe();
    Vector2 position = getPosition();
    Facing prevFacing = _facing;
    
    
    if((direction.x == 1 && direction.y == 0)){
        cout << "creature update east" << endl;
        // if direction is moving east or northeast or southeast
        _facing = right;
        //move();
    }else if ((direction.x == 0 && direction.y == 1)
              || (direction.x == -1 && direction.y == 1)
              || (direction.x == 1 && direction.y == 1)){
        cout << "creature update north" << endl;
        // if direction is moving north
        _facing = up;
        //move();
    } else if((direction.x == -1 && direction.y == 0)){
        cout << "creature update west" << endl;
        // if moving west or north west or south west
        _facing = left;
        //move();
    }else if((direction.x == 0 && direction.y == -1)
             || (direction.x == -1 && direction.y == -1)
             || (direction.x == 1 && direction.y == -1)){
        cout << "creature update south" << endl;
        // if moving south
        _facing = down;
        //move();
    }
    if(_facing != prevFacing){
        move();
    }
    
    position += direction * (us.dt / 1000.0f) * _speed; //CHANGE ME!!!!!!!!!!!
    setPosition(position);
    
}