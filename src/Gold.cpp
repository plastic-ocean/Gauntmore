//
//  Gold.cpp
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/16/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "Gold.h"
#include "Game.h"
#include "KeyboardInput.h"
#include "res.h"
#include "Tmx.h"
#include "SDL.h"


Gold::Gold(){
    
       spGold _gold;
    
}

void Gold::interact(){
        _view->addTween(Actor::TweenAlpha(0), 300)->setDetachActor(true);
    
}

void Gold::_init(){
    // Initialize the stats.
    
    // Add sprite to the game scene view.
    _sprite = new Sprite;
    _sprite->setResAnim(res::ui.getResAnim("gold"));
    _sprite->attachTo(_view);
    _sprite->setAnchor(Vector2(0.5f, 0.5f));
    
}

void Gold::_update(const UpdateState &us){
    
}