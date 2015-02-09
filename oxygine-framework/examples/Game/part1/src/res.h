#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

namespace res {
    
	extern Resources ui;
    
    /**
     * Loads the resources.
     */
	void load();
    
    /**
     * Unloads the resources.
     */
	void free();
}