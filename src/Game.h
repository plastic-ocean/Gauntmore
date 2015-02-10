#pragma once
#include "tinyxml2.h"
#include "oxygine-framework.h"
#include "Tmx.h"

using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Creature, spCreature);
DECLARE_SMART(KeyboardInput, spKeyboardInput)
DECLARE_SMART(Unit, spUnit);
DECLARE_SMART(Map, spMap);
DECLARE_SMART(Game, spGame);

class Game: public Actor {
    
public:
	Game();
    ~Game();
    
    /**
     * Initialzes the game. Creates the map, the player, the monsters, the static objects
     * and puts them in the game world.
     */
    void init();
    
    /**
     * Detects collisions between the Units and the walls.
     *
     * @x is the x coordinate to check.
     * @y is the y coordinate to check.
     * @h is the height coordinate to check.
     * @w is the width coordinate to check.
     * @return true is there is a collision and false if there is not
     */
    bool detectCollision(int x, int y, int h, int w);
    
    /**
     * Gets the tile map.
     *
     * @return the tile map.
     */
    Tmx::Map *getMap();
    
    /**
     * Gets tiles.
     *
     * @return the tiles vector<SDL_Rect>.
     */
    std::vector<SDL_Rect> getTiles();
    
    /**
     * Gets the keyboard input handler.
     */
    spKeyboardInput getMove();
    
    /**
     * Adds unit to the back of the units list.
     *
     * @unit is the Unit to be added.
     */
    void pushUnit(spUnit unit);

protected:
    spMap map;
    Tmx::Map *_map;
    std::vector<SDL_Rect> _tiles;
    
    spKeyboardInput _move;
    spPlayer _player;
    
    typedef std::list<spUnit> units;
    units _units;
    
    /**
     * Updates the player each frame. A virtual method of Actor it is being called each frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void doUpdate(const UpdateState &us);
    
    /**
     * Generates a maze in a .tmx file.
     */
    void _generateTmxFile();
    
    /**
     * Reads the tile map description from the .tmx file and uses it to render the map.
     */
    void _renderMap();
    
    /**
     * Creates a vector of rectangles called tiles that is used to detect collisions.
     */
    void _createTiles();
};