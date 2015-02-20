//
//  Collision.h
//  gauntmore_macosx
//
//  Created by David Wenzel on 2/19/15.
//  Copyright (c) 2015 oxygine. All rights reserved.
//

#ifndef __gauntmore_macosx__Collision__
#define __gauntmore_macosx__Collision__

#include <stdio.h>
typedef list<spUnit> Units;

class Collision {
public:
    Collision();
    ~Collision();
    bool detectCollision(int,int,int,int);
    void setTiles(vector<SDL_Rect> tileset );
    void setUnits( vector<spUnit> );
    
    
    
private:
    vector<SDL_Rect> _tiles;
    Units _units;

    
};

#endif /* defined(__gauntmore_macosx__Collision__) */
