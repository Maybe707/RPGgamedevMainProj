#ifndef RPG_WORLDMAPSCRIPT_H
#define RPG_WORLDMAPSCRIPT_H

#include "../scene/Script.h"
#include "../scene/components/WorldMapComponent.h"
#include "../client/graphics/Rect.h"
#include "../utils/OpenSimplexNoise.h"

#define DEBUG_SEED INT_MAX

class WorldMapGenerator : public IWorldMapGenerator
{
    OpenSimplexNoise m_simplexNoise;

public:
    WorldMapGenerator()
            : m_simplexNoise(DEBUG_SEED) {}

    int generate(int x, int y) override
    {
        double value = m_simplexNoise.getNoise(x, y);
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
        return id;
    }
};

class WorldMapScript : public Script
{
private:
    WorldMapComponent *m_map;
    WorldMapGenerator m_worldMapGenerator;
public:
    void onCreate() override
    {
        m_map = &getComponent<WorldMapComponent>();
        m_map->generator = &m_worldMapGenerator;
    }
};

#endif //RPG_WORLDMAPSCRIPT_H
