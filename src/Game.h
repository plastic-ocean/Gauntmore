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

DECLARE_SMART(Bat, spBat);
DECLARE_SMART(Snake, spSnake);
DECLARE_SMART(Slime, spSlime);
DECLARE_SMART(Ghost, spGhost);
DECLARE_SMART(Eyeball, spEyeball);
DECLARE_SMART(Worm, spWorm);

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
    void updateHealth(double value);

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
    
    /**
     * Pauses the game when switching to the pause menu.
     */
    void pauseGame();
    
    /**
     * Pauses the game when switching to the start menu.
     */
    void startGame();
    
    /**
     * Pauses the game when switching to the death menu.
     */
    void killPlayer();
    
    /**
     * Creates a new game on player death.
     */
    void createNewGame();

    /* Getters and Setters */
    
    /**
     * Gets the player.
     */
    spPlayer getPlayer();
    
    /**
     * Gets the map.
     */
    spMap getMap();

    /**
     * Gets the list of collision rects.
     */
    vector<SDL_Rect> getTiles();
    
    /**
     * Gets the keyboard input handler.
     */
    spKeyboardInput getMove();

    /**
     * Gets the keyboard input handler.
     */
    spHealthBar getHealthBar();
    
    /**
     * Gets the tile size.
     */
    int getTileSize();
    
    /**
     * Sets the game state to paused.
     */
    void setPaused(bool isPaused);
    
    /**
     * Checks if the game is paused.
     */
    bool isPaused();
    
    /**
     * Sets the games state to first run.
     */
    void setFirstRun(bool isFirstRun);
    
    /**
     * Checks if this is th games first run.
     */
    bool isFirstRun();
    
    /**
     * Gets the list of chest contents.
     */
    list<spThing>* getContentsList();

protected:
    const int tileSize = 64;
    spMap _map;
    Tmx::Map *_tileMap;
    vector<SDL_Rect> _tiles;
    list<SDL_Rect> _units;
    
    list<spThing> _things;
    
    spKeyboardInput _move;
    spPlayer _player;
    
    spBat _bat;
    spSnake _snake;
    spSlime _slime;
    spWorm _worm;
    spEyeball _eyeball;
    spGhost _ghost;
    
    spChest _chest;
    spGold _gold;
    spPotion _potion;
    
    spHealthBar _healthBar;
    spGoldCount _goldCount;
    spArmorCount _armorCount;
    spWeaponCount _weaponCount;
    
    bool _isPaused;
    bool _isFirstRun;
    
    /**
     * Updates the player each frame. A virtual method of Actor it is being called each frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void doUpdate(const UpdateState &us);
    
    /**
     * Creates the map, renders it, and creates the collision list.
     */
    void _createMap();
    
    /**
     * Create the creatures and the player.
     */
    void _createUnits();
    
    /**
     * Create the health, gold, defense, and attack HUD elements.
     */
    void _createHud();
    
    /**
     * Reads the tile map description from the .tmx file and uses it to render the map.
     */
    void _renderMap();
    
    /**
     * Creates a vector of rectangles called tiles that is used to detect collisions.
     */
    void _createCollisionRects();

    /**
     * Gets the maze entrance location.
     */
    Vector2 _getEntrance();
};