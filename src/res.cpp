#include "res.h"

Resources resources;

/**
* Loads the resources.
*/
void loadResources() {
	resources.loadXML("xmls/ui.xml");
}

/**
* Unloads the resources.
*/
void freeResources() {
	resources.free();
}