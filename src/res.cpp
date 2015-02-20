#include "res.h"

Resources resources;
Resources resSounds;

/**
* Loads the resources.
*/
void loadResources() {
	resources.loadXML("xmls/ui.xml");
    resSounds.loadXML("sounds.xml");
}

/**
* Unloads the resources.
*/
void freeResources() {
	resources.free();
    resSounds.free();
}