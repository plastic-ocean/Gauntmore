cmake_minimum_required (VERSION 2.6)
project (gauntmore)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_subdirectory(oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

add_executable(gauntmore
src/Game.cpp src/Game.h src/GameScene.cpp src/GameScene.h src/Map.cpp src/Map.h src/Map.cpp src/Map.h
src/Room.cpp src/Room.h src/Scene.cpp src/Scene.h src/KeyboardInput.cpp src/KeyboardInput.h src/Player.cpp src/Player.h
src/Creature.cpp src/Creature.h src/Unit.cpp src/Unit.h  src/gauntmore.cpp  src/res.cpp src/res.h
src/tmx/base64.cpp src/tmx/TmxEllipse.h src/tmx/TmxMapTile.h src/tmx/TmxPropertySet.cpp src/tmx/base64.h
src/tmx/TmxObject.cpp src/tmx/TmxPropertySet.h src/tmx/TmxImage.cpp src/tmx/TmxObjectGroup.cpp src/tmx/TmxTile.cpp
src/tmx/TmxImage.h src/tmx/TmxObjectGroup.h src/tmx/TmxTile.h src/tmx/TmxImageLayer.cpp src/tmx/TmxObject.h
src/tmx/TmxTileset.cpp src/tmx/TmxImageLayer.h src/tmx/TmxPoint.h src/tmx/TmxTileset.h src/tmx/TmxLayer.cpp
src/tmx/TmxPolygon.cpp src/tmx/TmxUtil.cpp src/tmx/tinyxml2.cpp src/tmx/TmxLayer.h src/tmx/TmxPolygon.h
src/tmx/TmxUtil.h src/tmx/tinyxml2.h src/tmx/TmxMap.cpp src/tmx/TmxPolyline.cpp src/tmx/TmxEllipse.cpp src/tmx/TmxMap.h
src/tmx/TmxPolyline.h src/tmx/Tmx.h
)

target_link_libraries(gauntmore ${OXYGINE_CORE_LIBS})
