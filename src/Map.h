#ifndef MAP_H
#define MAP_H

#include <string>
#include "graphics/Shader.h"
#include "Map_Objects.h"
#include "Sprite_RandSet.h"
#include "graphics/Texture.h"

class WorldMap
{
    const int m_mapHeight;
    const int m_mapWidth;
    const unsigned int m_screenWidth;
    const unsigned int m_screenHeight;
    char** m_tilemap;
public:
    WorldMap(const unsigned int screenWidth, const unsigned int screenHeight,
             const int mapHeight, const int mapWidth);

    virtual ~WorldMap();
    
    void initialize(char** array);
    
    void setRandomSprites(const char*** spriteSet, SpriteRandSet& spriteObj);
    
    char getMapKey(const int i, const int j);

    int getRandomNumber(int min, int max);

    const int getMapHeight();
    const int getMapWidth();

    void render(MapObjects** mapObjects, Shader& shader, unsigned int vaoId,
                Texture texture, const int rowOffset, const int columnOffset,
                int randId, int randIdNextLevel);

    void drawMap(float coordX, float coordY, Shader shader, unsigned int vaoId, Texture texture);
};

#endif
