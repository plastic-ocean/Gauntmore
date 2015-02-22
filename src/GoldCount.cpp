#include "GoldCount.h"

/**
 * Constructor.
 */
GoldCount::GoldCount(Game *game):_game(game), _count(0) {
    _coin = new Sprite;
    _coin->setResAnim(resources.getResAnim("coin"));
    _coin->setAnchor(Vector2(0.5f, 0.5f));
    _coin->setPosition(156, 26);
    _coin->attachTo(_game);
    
    _goldCount = new TextField();
    _goldCount->setPosition(196, 22);
    _goldCount->attachTo(_game);
    
    TextStyle style;
    style.font = resFonts.getResFont("main")->getFont();
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    
    _goldCount->setStyle(style);
    _goldCount->setText("0");
}


/**
 * Renders the on screen gold counter on room changes.
 */
void GoldCount::render() {
    _coin->attachTo(_game);
    _goldCount->attachTo(_game);
}


/**
 * Updates the string count and sets the on screen gold count.
 *
 * @count is the value to add to the count.
 */
void GoldCount::updateGoldCount(int value) {
    _count += value;
    _goldCount->setText(to_string(_count));
}