#pragma once
#include "oxygine-framework.h"
#include "KeyboardInput.h"
//#include "Map.h"

using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Joystick, spJoystick);
DECLARE_SMART(Game, spGame);
DECLARE_SMART(KeyboardInput, spKeyboardInput)
//DECLARE_SMART(Map, spMap);
class Game: public Actor
{
public:
	Game();

	void init();

private:
	friend class Player;
	void doUpdate(const UpdateState &us);
    void renderMap();
    
//    spMap _map;
    
    spKeyboardInput _move;
    
//	spJoystick _move;

	spPlayer _player;
};