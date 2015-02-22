#include "GoldCount.h"
#include "res.h"

GoldCount::GoldCount(Game *game):_game(game) {
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
    _goldCount->setText("0000");
}


void GoldCount::render() {
    _coin->attachTo(_game);
    _goldCount->attachTo(_game);
}


void GoldCount::updateGoldCount(string count) {
    _goldCount->setText(count);
}