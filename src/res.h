#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

extern Resources resources;
extern Resources resSounds;
extern Resources resFonts;

/**
* Loads the resources.
*/
void loadResources();

/**
* Unloads the resources.
*/
void freeResources();