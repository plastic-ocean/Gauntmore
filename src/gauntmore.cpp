#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
#include "res.h"
#include "Game.h"
using namespace oxygine;


/**
 * The main loop. Called each frame.
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

	// Update internal components
	// All input events are passed to Stage::instance.handleEvent
	// If done is true then User requests quit from app.
	bool done = core::update();

	return done ? 1 : 0;
}


/**
 * Initializes Oxygine, sets the window size, and creates the Stage.
 */
void initialize(int width, int height) {
    ObjectBase::__startTracingLeaks();
    
    // Initialize Oxygine's internal stuff.
    core::init_desc desc;
    
    // Setup initial window size.
    desc.w = width;
    desc.h = height;
    
    core::init(&desc);
    
    // Create the Stage. Stage is a root node.
    Stage::instance = new Stage(true);
    Point size = core::getDisplaySize();
    getStage()->setSize(size);
    
    // DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff.
    //DebugActor::show();
    
    // Load resources.
    res::load();
}


/**
 * Cleans up, frees, releases, and dumps all allocated resources.
 */
void destroy() {
    // Dump all created objects into log. All created and not freed resources are displayed.
    ObjectBase::dumpCreatedObjects();
    
    // Frees all resources.
    res::free();
    
    // Releases all internal components and the Stage.
    core::release();
    
    // Dump list should be empty now. Everything has been deleted and there can't be any memory leaks.
    ObjectBase::dumpCreatedObjects();
    
    ObjectBase::__stopTracingLeaks();
}


int main(int argc, char* argv[]) {
    // Initializes Oxygine, the game window, and the Stage.
    initialize(480, 480);
    
    // Initialize the game and attach to the stage.
    spGame game = new Game;
    game->init();
    game->attachTo(getStage());
    
    // Start the main loop.
    while (1) {
        int done = mainloop();
        if (done) {
            break;
        }
    }
    
    // If the user wants to leave application:
    destroy();
    
	return 0;
}

