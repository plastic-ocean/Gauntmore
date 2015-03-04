//
//  WeaponCount.cpp
//  gauntmore_macosx
//
//  Created by Steven Warren on 3/3/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "WeaponCount.h"

/**
 * Constructor.
 */
WeaponCount::WeaponCount(Game *game):_game(game), _count(0) {
    _sword = new Sprite;
    _sword->setResAnim(resources.getResAnim("weapon1"));
    _sword->setAnchor(Vector2(0.5f, 0.5f));
    _sword->setPosition(314, 20);
    _sword->attachTo(_game);
    
    _weaponCount = new TextField();
    _weaponCount->setAnchor(Vector2(0.5f, 0.5f));
    _weaponCount->setPosition(344, 16);
    _weaponCount->attachTo(_game);
    
    TextStyle style;
    style.font = resFonts.getResFont("main")->getFont();
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    
    _weaponCount->setStyle(style);
    _weaponCount->setText("0");
}


/**
 * Renders the on screen gold counter on room changes.
 */
void WeaponCount::render() {
    _sword->attachTo(_game);
    _weaponCount->attachTo(_game);
}


/**
 * Updates the string count and sets the on screen gold count.
 *
 * @count is the value to add to the count.
 */
void WeaponCount::updateWeaponCount(int value) {
    _count = value;
    
    cout << "value: " << value << endl;
    switch (value) {
        case 2:
            _sword->setResAnim(resources.getResAnim("weapon2"));
            break;
        case 3:
            _sword->setResAnim(resources.getResAnim("weapon3"));
            break;
        default:
            break;
    }
    
    _weaponCount->setText(to_string(_count));
}