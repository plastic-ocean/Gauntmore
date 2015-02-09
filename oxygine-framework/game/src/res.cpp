#include "res.h"

namespace res {
	Resources ui;
    
    /**
     * Loads the resources.
     */
	void load() {
		ui.loadXML("xmls/ui.xml");
	}
    
    /**
     * Unloads the resources.
     */
	void free() {
		ui.free();
	}
}