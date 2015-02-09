cmake_minimum_required (VERSION 2.6)
project (gauntmore)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_subdirectory(oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

add_executable(gauntmore ../src/Game.cpp ../src/Game.h ../src/KeyboardInput.cpp ../src/KeyboardInput.h ../src/Player.cpp ../src/Player.h ../src/Creature.cpp ../src/Creature.h ../src/Unit.cpp ../src/Unit.h ../src/entry_point.cpp ../src/gauntmore.cpp ../src/gauntmore.h ../src/res.cpp ../src/res.h ../src/base64.cpp ../src/TmxEllipse.h ../src/TmxMapTile.h ../src/TmxPropertySet.cpp ../src/base64.h ../src/TmxObject.cpp ../src/TmxPropertySet.h ../src/TmxImage.cpp ../src/TmxObjectGroup.cpp ../src/TmxTile.cpp ../src/TmxImage.h ../src/TmxObjectGroup.h ../src/TmxTile.h ../src/TmxImageLayer.cpp ../src/TmxObject.h ../src/TmxTileset.cpp ../src/TmxImageLayer.h ../src/TmxPoint.h ../src/TmxTileset.h ../src/TmxLayer.cpp ../src/TmxPolygon.cpp ../src/TmxUtil.cpp ../src/tinyxml2.cpp ../src/TmxLayer.h ../src/TmxPolygon.h ../src/TmxUtil.h ../src/tinyxml2.h ../src/TmxMap.cpp ../src/TmxPolyline.cpp ../src/TmxEllipse.cpp ../src/TmxMap.h ../src/TmxPolyline.h )

target_link_libraries(gauntmore ${OXYGINE_CORE_LIBS})
