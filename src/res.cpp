#include "res.h"

Resources resources;
Resources resSounds;
Resources resFonts;

/**
* Loads the resources.
*/
void loadResources() {
	resources.loadXML("xmls/sprites.xml");
    resSounds.loadXML("xmls/sounds.xml");
    resFonts.loadXML("xmls/fonts.xml");
}

/**
* Unloads the resources.
*/
void freeResources() {
	resources.free();
    resSounds.free();
    resFonts.free();
}