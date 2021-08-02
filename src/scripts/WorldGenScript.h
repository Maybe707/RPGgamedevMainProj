#ifndef WORLDGENSCRIPT_H
#define WORLDGENSCRIPT_H

#include "../scene/Script.h"
#include "../scene/components/TileMapComponent.h"
#include "../graphics/Rect.h"
#include "../utils/OpenSimplexNoise.h"

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
    OpenSimplexNoise* m_simplexNoise;
public:
    WorldGenScript() : m_simplexNoise(new OpenSimplexNoise()) { }

    void onCreate() 
    {
        m_map = &getComponent<TileMap>();
        
        for (int x = m_map->globalBounds.getLeft(); x < m_map->globalBounds.getWidth(); x++)
        {
            for (int y = m_map->globalBounds.getBottom(); y < m_map->globalBounds.getHeight(); y++)
            {
                double value = m_simplexNoise->getNoise(x, y);
                u8 id = 0;
                if (value > -0.2f)
                {
                    id = 1;
                }
                if (value > 0.f)
                {
                    id = 2;
                }
                if (value > 1.f)
                {
                    id = 3;
                }

                m_map->setTile({x, y}, *TilesData.at(id));
            }
        }
    }

    void onUpdate(float deltaTime) { }

    void onDestroy() 
    {
        delete m_simplexNoise;
    }
};

#endif