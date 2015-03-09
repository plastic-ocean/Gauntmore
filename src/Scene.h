#pragma once
#include "oxygine-framework.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(Scene, spScene);
class Scene: public EventDispatcher {
    
public:
    Scene();
    
    /**
     * Hides the current scene and shows the next scene.
     */
    void changeScene(spScene next);
    
    /**
     * Adds the scene view to the root, fades in the scene, and calls _show for all children.
     */
    void show();
    
    /**
     * Fades out the current scene and detaches it from the view.
     */
    void hide();
    
    /**
     * Gets the view.
     */
    spActor getView();
    
protected:
    spActor _view;
    
    /**
     * Virtual method called by show for all children.
     */
    virtual void _show() {}
    
    /**
     * Virtual method called by hide for all children.
     */
    virtual void _hide() {}
};
