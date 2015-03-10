cmake_minimum_required (VERSION 2.6)
project (gauntmore)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_subdirectory(oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

add_executable(gauntmore
src/main.cpp
src/Gauntmore.cpp src/Gauntmore.h
src/res.cpp src/res.h
src/Game.cpp src/Game.h
src/KeyboardInput.cpp src/KeyboardInput.h
src/CollisionDetector.cpp src/CollisionDetector.h

src/Map.cpp src/Map.h
src/MazeGen.cpp src/MazeGen.h
src/Room.cpp src/Room.h

src/PathFinder.cpp src/PathFinder.h
src/PathNode.cpp src/PathNode.h
src/NodeArray.cpp src/NodeArray.h
src/NodeMinHeap.cpp src/NodeMinHeap.h

src/Scene.cpp src/Scene.h
src/GameScene.cpp src/GameScene.h
src/Menu.cpp src/Menu.h
src/DeathMenu.cpp src/DeathMenu.h
src/PauseMenu.cpp src/PauseMenu.h
src/StartMenu.cpp src/StartMenu.h

src/Unit.cpp src/Unit.h
src/Player.cpp src/Player.h
src/Thing.cpp src/Thing.h
src/Chest.cpp src/Chest.h
src/Gold.cpp src/Gold.h
src/Potion.cpp src/Potion.h
src/Armor.cpp src/Armor.h
src/Weapon.cpp src/Weapon.h
src/Creature.cpp src/Creature.h
src/Slime.cpp src/Slime.h
src/Eyeball.cpp src/Eyeball.h
src/Ghost.cpp src/Ghost.h
src/Bat.cpp src/Bat.h
src/Snake.cpp src/Snake.h
src/Worm.cpp src/Worm.h

src/GoldCount.cpp src/GoldCount.h
src/HealthBar.cpp src/HealthBar.h
src/ArmorCount.cpp src/ArmorCount.h
src/WeaponCount.cpp src/WeaponCount.h

src/tmx/base64.cpp src/tmx/base64.h
src/tmx/TmxEllipse.cpp src/tmx/TmxEllipse.h
src/tmx/TmxPropertySet.cpp src/tmx/TmxPropertySet.h
src/tmx/TmxObject.cpp src/tmx/TmxObject.h
src/tmx/TmxImage.cpp src/tmx/TmxImage.h
src/tmx/TmxObjectGroup.cpp src/tmx/TmxObjectGroup.h
src/tmx/TmxTile.cpp src/tmx/TmxTile.h
src/tmx/TmxImageLayer.cpp src/tmx/TmxImageLayer.h
src/tmx/TmxTileset.cpp src/tmx/TmxTileset.h
src/tmx/TmxLayer.cpp src/tmx/TmxLayer.h
src/tmx/TmxPolygon.cpp src/tmx/TmxPolygon.h
src/tmx/TmxUtil.cpp src/tmx/TmxUtil.h
src/tmx/tinyxml2.cpp src/tmx/tinyxml2.h
src/tmx/TmxMap.cpp src/tmx/TmxMap.h
src/tmx/TmxPolyline.cpp src/tmx/TmxPolyline.h
src/tmx/TmxPoint.h
src/tmx/TmxMapTile.h
src/tmx/Tmx.h
)

target_link_libraries(gauntmore ${OXYGINE_CORE_LIBS})
