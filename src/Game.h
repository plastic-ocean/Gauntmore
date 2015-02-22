#pragma once
#include "oxygine-framework.h"
#include "tmx/Tmx.h"
#include "tmx/tinyxml2.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Creature, spCreature);
DECLARE_SMART(Skeleton, spSkeleton);
DECLARE_SMART(HealthBar, spHealthBar);
DECLARE_SMART(GoldCount, spGoldCount);
DECLARE_SMART(Unit, spUnit);
DECLARE_SMART(Chest, spChest);
DECLARE_SMART(Gold, spGold);
DECLARE_SMART(CollisionDetector, spCollisionDetector);
DECLARE_SMART(Potion, spPotion);
DECLARE_SMART(KeyboardInput, spKeyboardInput)
DECLARE_SMART(Unit, spUnit);
DECLARE_SMART(Room, spRoom)
DECLARE_SMART(Map, spMap);
DECLARE_SMART(Game, spGame);

class Game: public Actor {
    
public:
	Game();
    ~Game();
    
    typedef list<spUnit> Units;
    
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
    //bool detectCollision(int x, int y, int h, int w);
    
    /**
     * Gets the tile map.
     *
     * @return the tile map.
     */
    Tmx::Map *getTileMap();
    
    /**
     * Gets tiles.
     *
     * @return the tiles vector<SDL_Rect>.
     */
    vector<SDL_Rect> getTiles();
    
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
    
    void switchRoom(int edge);
    
    spPlayer getPlayer();
    
    std::list<spUnit> getUnits();

    spMap getMap();
    
    void updateHealth(float num);
    
    void updateGoldCount(string count);

protected:
    const int tileSize = 64;
    spMap _map;
    Tmx::Map *_tileMap;
    vector<SDL_Rect> _tiles;
    
    spKeyboardInput _move;
    spPlayer _player;

    Units _units;
    
    spSkeleton _skeleton;
    
    spChest _chest;
    spGold _gold;
    spPotion _potion;
    spUnit _unit;
    
    spHealthBar _healthBar;
    spGoldCount _goldCount;
    
    /**
     * Updates the player each frame. A virtual method of Actor it is being called each frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void doUpdate(const UpdateState &us);
    
    /**
     * Reads the tile map description from the .tmx file and uses it to render the map.
     */
    void _renderMap();
    
    /**
     * Creates a vector of rectangles called tiles that is used to detect collisions.
     */
    void _createTiles();

    void _setUnits();
    
    Vector2 _getEntrance();
};