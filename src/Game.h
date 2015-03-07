#pragma once
#include "oxygine-framework.h"
#include "tmx/Tmx.h"
#include "tmx/tinyxml2.h"
#include "Player.h"
#include "HealthBar.h"
#include "KeyboardInput.h"
#include "Map.h"
#include "Thing.h"

using namespace oxygine;
using namespace std;

DECLARE_SMART(Unit, spUnit);
DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Creature, spCreature);
DECLARE_SMART(Skeleton, spSkeleton);
DECLARE_SMART(Slime, spSlime);

DECLARE_SMART(HealthBar, spHealthBar);
DECLARE_SMART(GoldCount, spGoldCount);
DECLARE_SMART(ArmorCount, spArmorCount);
DECLARE_SMART(WeaponCount, spWeaponCount);

DECLARE_SMART(Chest, spChest);
DECLARE_SMART(Gold, spGold);
DECLARE_SMART(Potion, spPotion);

DECLARE_SMART(Room, spRoom)
DECLARE_SMART(Map, spMap);

DECLARE_SMART(CollisionDetector, spCollisionDetector);
DECLARE_SMART(KeyboardInput, spKeyboardInput)

DECLARE_SMART(Game, spGame);
class Game: public Actor {
    
public:
	Game();
    ~Game();

    /**
     * Switches viewable map to the room in the direction of the given edge in the maze.
     *
     * @edge is the edge the player existed on.
     */
    void switchRoom(int edge);

    /**
     * Checks if the given position is an exit. Used to switch rooms.
     *
     * @position is the position to check.
     */
    bool isExit(Vector2 position);

    /**
     * Updates the health bar.
     *
     * @num is the value to update by.
     */
    void updateHealth(float value);

    /**
     * Updates the gold counter.
     *
     * @num is the value to update by.
     */
    void updateGoldCount(int value);
    
    /**
     * Updates the armor counter.
     *
     * @num is the value to update by.
     */
    void updateArmorCount(int value);

    /**
     * Updates the weapon counter.
     *
     * @num is the value to update by.
     */
    void updateWeaponCount(int value);

    /* Getters and Setters */

    spPlayer getPlayer() {
        return _player;
    }

    spMap getMap() {
        return _map;
    }

    vector<SDL_Rect> getTiles() {
        return _tiles;
    }

    spKeyboardInput getMove() {
        return _move;
    }

    spHealthBar getHealthBar() {
        return _healthBar;
    }

    int getTileSize() {
        return tileSize;
    }
    
    list<spThing>* getContentsList(){
        return &_things;
    }

protected:
    const int tileSize = 64;
    spMap _map;
    Tmx::Map *_tileMap;
    vector<SDL_Rect> _tiles;
    list<SDL_Rect> _units;
    
    list<spThing> _things;
    
    spKeyboardInput _move;
    spPlayer _player;
    
    spSkeleton _skeleton;
    spSlime _slime;
    
    spChest _chest;
    spGold _gold;
    spPotion _potion;
    
    spHealthBar _healthBar;
    spGoldCount _goldCount;
    spArmorCount _armorCount;
    spWeaponCount _weaponCount;
    
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

    /**
     * Gets the maze entrance location.
     */
    Vector2 _getEntrance();
};