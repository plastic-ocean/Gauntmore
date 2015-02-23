#include "HealthBar.h"


/**
 * Constructor.
 */
HealthBar::HealthBar(Game *game) :_game(game), _health(1.0f) {
    _healthBar = new ProgressBar();
    _healthBar->setResAnim(resources.getResAnim("health"));
    _healthBar->setAnchor(Vector2(0.5f, 0.5f));
    _healthBar->setPosition(74, 20);
    _healthBar->setDirection(ProgressBar::dir_0);
    _healthBar->attachTo(_game);
    
    _healthBorder = new Sprite;
    _healthBorder->setResAnim(resources.getResAnim("health_border"));
    _healthBorder->setAnchor(Vector2(0.5f, 0.5f));
    _healthBorder->setPosition(74, 20);
    _healthBorder->attachTo(_game);
}


/**
 * Render the health bar.
 */
void HealthBar::render() {
    _healthBar->attachTo(_game);
    _healthBorder->attachTo(_game);
}


/**
 * Update the health bar to a new position. 
 * 
 * @damage value in range [0.0f, 1.0f]
 */
void HealthBar::updateHealth(float damage) {
    _health += damage;
    _healthBar->setProgress(_health);
//    _health->addTween(ProgressBar::TweenProgress(num), 1000);
}