#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
#include "res.h"
#include "GameScene.h"
using namespace oxygine;


/**
 * The main loop method. Called each frame.
 */
int mainloop() {
	// Update our stage and all actors. Actor::update is called for all children.
	getStage()->update();
	
	if (core::beginRendering()) {
		Color clearColor(32, 32, 32, 255);
		Rect viewport(Point(0, 0), core::getDisplaySize());
		// Render all actors. Actor::render is called for all children.
		getStage()->render(clearColor, viewport);

		core::swapDisplayBuffers();
	}

	// Update internal components. All input events are passed to Stage::instance.handleEvent.
	// If done is true then User requests quit from app.
	bool done = core::update();

	return done ? 1 : 0;
}


/**
 * Load resources, initialize the game, and attach it to the stage.
 */
void initGauntmore() {
    // Load resources.
    loadResources();
    
    // Create game scene.
    GameScene::instance = new GameScene;
}


/**
 * Free all allocated resources and delete all created actors.
 */
void destroyGauntmore() {
    GameScene::instance = 0;
    freeResources();
}


int main(int argc, char* argv[]) {
    ObjectBase::__startTracingLeaks();
    
    // Initialize Oxygine's internal stuff.
    core::init_desc desc;
    
    // Setup the window.
    desc.w = 768;
    desc.h = 768;
//    desc.fullscreen = true;
    desc.title = "Gauntmore";
    desc.appName = "Gauntmore";
    desc.companyName = "plastic-ocean";
    
    core::init(&desc);
    
    // Create the Stage. Stage is a root node.
    Stage::instance = new Stage(true);
    Point size = core::getDisplaySize();
    getStage()->setSize(size);
    
    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff.
    //DebugActor::show();

    initGauntmore();
    
    // Start the main loop.
    while (1) {
        int done = mainloop();
        if (done) {
            break;
        }
    }
    // If the user wants to leave application...
    
    // Dump all created objects into log. All created and not freed resources are displayed.
    ObjectBase::dumpCreatedObjects();

    destroyGauntmore();
    
    // Releases all internal components and Stage
    core::release();
    
    // Dump list should be empty now. Everything has been deleted and there can't be any memory leaks.
    ObjectBase::dumpCreatedObjects();
    
    ObjectBase::__stopTracingLeaks();
    
	return 0;
}

