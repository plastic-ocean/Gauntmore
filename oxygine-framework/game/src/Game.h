#pragma once
#include "oxygine-framework.h"
#include "KeyboardInput.h"
#include "Tmx.h"

using namespace oxygine;


DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Joystick, spJoystick);
DECLARE_SMART(Game, spGame);
DECLARE_SMART(KeyboardInput, spKeyboardInput)
DECLARE_SMART(Map, spMap);


class Game: public Actor {
    
public:
	Game();
    
    /**
     * Initialzes the game. Creates the map, the player, the monsters, the static objects
     * and puts them in the game world.
     */
	void init();    
    
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

private:
	friend class Player;
    Tmx::Map *map;
    std::vector<SDL_Rect> tiles;
    spKeyboardInput _move;
    spPlayer _player;
    
    /**
     * Updates the player each frame. A virtual method of Actor it is being called each frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void doUpdate(const UpdateState &us);
    
    /**
     * Reads the tile map description from the .tmx file and uses it to render the map.
     */
    void renderMap();
    
    /**
     * Creates a vector of rectangles called tiles that is used to detect collisions.
     */
    void createTiles();
};