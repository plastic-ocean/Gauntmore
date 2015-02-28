//
//  ArmorCount.cpp
//  gauntmore_macosx
//
//  Created by Steven Warren on 2/27/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#include "ArmorCount.h"

/**
 * Constructor.
 */
ArmorCount::ArmorCount(Game *game):_game(game), _count(0) {
    _shield = new Sprite;
    _shield->setResAnim(resources.getResAnim("armor"));
    _shield->setAnchor(Vector2(0.5f, 0.5f));
    _shield->setPosition(250, 20);
    _shield->attachTo(_game);
    
    _armorCount = new TextField();
    _armorCount->setAnchor(Vector2(0.5f, 0.5f));
    _armorCount->setPosition(290, 16);
    _armorCount->attachTo(_game);
    
    TextStyle style;
    style.font = resFonts.getResFont("main")->getFont();
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    
    _armorCount->setStyle(style);
    _armorCount->setText("0");
}


/**
 * Renders the on screen gold counter on room changes.
 */
void ArmorCount::render() {
    _shield->attachTo(_game);
    _armorCount->attachTo(_game);
}


/**
 * Updates the string count and sets the on screen gold count.
 *
 * @count is the value to add to the count.
 */
void ArmorCount::updateArmorCount(int value) {
    _count += value;
    _armorCount->setText(to_string(_count));
}