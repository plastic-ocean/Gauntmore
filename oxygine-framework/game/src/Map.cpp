//#include "Map.h"
//#include "Game.h"
//#include "res.h"
//#include "Tmx.h"
//
//void Map::render(Game *game) {
//    Tmx::Map *map = new Tmx::Map();
//    map->ParseFile("/Users/Keith/Desktop/cis330/Gauntmore/oxygine-framework/examples/Game/part1/data/images/room01.tmx");
//    
//    for (int i = 0; i < map->GetNumLayers(); ++i) {
//        // Get a layer.
//        const Tmx::Layer *layer = map->GetLayer(i);
//        
//        for (int x = 0; x < layer->GetWidth(); ++x) {
//            for (int y = 0; y < layer->GetHeight(); ++y) {
//                int tilesetIndex = layer->GetTileTilesetIndex(x, y);
//                const Tmx::Tileset *tileset = map->GetTileset(tilesetIndex);
//                std::string name = tileset->GetName();
//                int tileSize = tileset->GetImage()->GetWidth();
//                int drawX = x * tileSize;
//                int drawY = y * tileSize;
//                
//                // Draw the tile.
//                spSprite sprite = new Sprite;
//                sprite->setResAnim(res::ui.getResAnim(name));
//                sprite->setX(drawX);
//                sprite->setY(drawY);
//                sprite->attachTo(game);
//            }
//        }
//    }
//    delete map;
//}