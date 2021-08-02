#ifndef WORLDGENSCRIPT_H
#define WORLDGENSCRIPT_H

#include "../scene/Script.h"
#include "../scene/components/TileMapComponent.h"
#include "../graphics/Rect.h"
#include <glm/gtc/noise.hpp>

struct LvlRoom
{
    IntRect roomSize;
    glm::ivec2 roomPos;
    glm::ivec2 origin;

    LvlRoom() : roomSize(0, 0, 0, 0), roomPos(0, 0), origin(0, 0) { }
    LvlRoom(IntRect size, glm::ivec2 pos) : roomSize(size), roomPos(pos) { }
};

class WorldGenScript : public Script
{
private:
    TileMap* m_map = nullptr;
public:
    WorldGenScript() { }

    void onCreate() 
    {
        m_map = &getComponent<TileMap>();
        
        for (int x = m_map->globalBounds.getLeft(); x < m_map->globalBounds.getWidth(); x++)
        {
            for (int y = m_map->globalBounds.getBottom(); y < m_map->globalBounds.getHeight(); y++)
            {
                u8 id = glm::perlin(glm::vec3(x * 0.25f, y * 0.05f, 0.0f)) < 0.055f;

                m_map->setTile({x, y}, *TilesData.at(id));
            }
        }
    }

    void onUpdate(float deltaTime) { }

    void onDestroy() { }
};

#endif