#ifndef WORLDGENSCRIPT_H
#define WORLDGENSCRIPT_H

#include "../scene/Script.h"
#include "../scene/TileMapComponent.h"

class WorldGenScript : public Script
{
private:
    TileMapComponent* m_map = nullptr;
public:
    void onCreate() 
    {
        m_map = &getComponent<TileMapComponent>();
    }

    void onUpdate(float deltaTime) {}

    void onDestroy() {}
};

#endif