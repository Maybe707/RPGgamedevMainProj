#ifndef WORLDGENSCRIPT_H
#define WORLDGENSCRIPT_H

#include "../scene/Script.h"
#include "../scene/components/TileMapComponent.h"

class WorldGenScript : public Script
{
private:
    TileMap* m_map = nullptr;
public:
    void onCreate() 
    {
        m_map = &getComponent<TileMap>();
        
        for (int x = m_map->bounds.getLeft() * CHUNK_SIZE; x < m_map->bounds.getWidth() * CHUNK_SIZE; x++)
        {
            for (int y = m_map->bounds.getBottom() * CHUNK_SIZE; y < m_map->bounds.getHeight() * CHUNK_SIZE; y++)
            {
                m_map->setTile({x, y}, *map::TilesData.at(1));
            }
        }
    }

    void onUpdate(float deltaTime) { }

    void onDestroy() { }
};

#endif