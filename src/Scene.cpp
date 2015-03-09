#include "Scene.h"


/**
 * Constructor.
 */
Scene::Scene() {
    _view = new Actor;
    _view->setSize(getStage()->getSize());
}


/**
 * Hides the current scene and shows the next scene.
 */
void Scene::changeScene(spScene next) {
    hide();
    next->show();
}


/**
 * Adds the scene view to the root, fades in the scene, and calls _show for all children.
 */
void Scene::show() {
    getStage()->addChild(_view);
    _view->setAlpha(0);
    _view->addTween(Actor::TweenAlpha(255), 300);
    _show();
}


/**
 * Fades out the current scene and detaches it from the view.
 */
void Scene::hide() {
    spTween tween = _view->addTween(Actor::TweenAlpha(0), 300);
    tween->setDetachActor(true);
}


/**
 * Gets the view.
 */
spActor Scene::getView() {
    return _view;
}
