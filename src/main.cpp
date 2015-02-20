#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
#include "Gauntmore.h"

using namespace oxygine;


int main(int argc, char* argv[]) {
    Gauntmore gauntmore = Gauntmore();
    
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

    gauntmore.init();
    
    // Start the main loop.
    while (1) {
        int done = gauntmore.mainLoop();
        if (done) {
            break;
        }
    }
    // If the user wants to leave the game...
    
    // Dump all created objects into log. All created and not freed resources are displayed.
    ObjectBase::dumpCreatedObjects();

    gauntmore.destroy();
    
    // Releases all internal components and Stage
    core::release();
    
    // Dump list should be empty now. Everything has been deleted and there can't be any memory leaks.
    ObjectBase::dumpCreatedObjects();
    
    ObjectBase::__stopTracingLeaks();
    
	return 0;
}

