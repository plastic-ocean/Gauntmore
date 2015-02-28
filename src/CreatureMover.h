#ifndef __gauntmore_macosx__CreatureMover__
#define __gauntmore_macosx__CreatureMover__

#include <stdio.h>
#include "Game.h"


class CreatureMover {
public:
    CreatureMover();
    ~CreatureMover();
    bool updatePath(vector<Vector2>);
    Vector2 popNext();
    Vector2 peekNext();
    bool isEmpty();
    
private:
    std::vector<Vector2> thePath;
    
    
};




#endif /* defined(__gauntmore_macosx__CreatureMover__) */

