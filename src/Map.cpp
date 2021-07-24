#include <glad/gl.h>
#include "Map.h"

WorldMap::WorldMap(const unsigned int screenWidth, const unsigned int screenHeight,
                   const int mapHeight, const int mapWidth) :
        m_screenWidth(screenWidth),
        m_screenHeight(screenHeight),
        m_mapHeight(mapHeight),
        m_mapWidth(mapWidth)
{
    m_tileMap = new char *[m_mapHeight];

    for (int count = 0; count < m_mapHeight; ++count)
        m_tileMap[count] = new char[m_mapWidth];

    for (int i = 0; i < m_mapHeight; ++i)
    {
        for (int j = 0; j < m_mapWidth; ++j)
        {
            m_tileMap[i][j] = ' ';
        }
    }
}

WorldMap::~WorldMap()
{
    for (int count = 0; count < m_mapHeight; ++count)
        delete[] m_tileMap[count];
    delete[] m_tileMap;
    m_tileMap = nullptr;
}

void WorldMap::initialize(char **array)
{
    for (int i = 0; i < m_mapHeight; ++i)
        for (int j = 0; j < m_mapWidth; ++j)
        {
            m_tileMap[i][j] = array[i][j];
        }
}

void WorldMap::setRandomSprites(const char ***spriteSet, SpriteRandSet &spriteObj)
{
    for (int posIndex_X = 0; posIndex_X < ((m_mapHeight - 2) / 7); ++posIndex_X)
    {
        for (int posIndex_Y = 0; posIndex_Y < ((m_mapWidth - 2) / 7); ++posIndex_Y)
        {
            // rand call
            spriteObj.setRandSprite(spriteSet, getRandomNumber(0, 2));

            for (int localArrIndex_X = 0; localArrIndex_X < spriteObj.getHeight(); ++localArrIndex_X)
            {
                for (int localArrIndex_Y = 0; localArrIndex_Y < spriteObj.getWidth(); ++localArrIndex_Y)
                {
                    if (spriteObj.getSpriteSetArray()[localArrIndex_X][localArrIndex_Y] == '0')
                    {
                        m_tileMap[posIndex_X * 7 + 1 + localArrIndex_X][posIndex_Y * 7 + 1 + localArrIndex_Y] = '0';
                    }
                }
            }
        }
    }
}

char WorldMap::getMapKey(const int i, const int j)
{
    return m_tileMap[i][j];
}

// Генерируем рандомное число между значениями min и max.
// Предполагается, что функцию srand() уже вызывали
int WorldMap::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

const int WorldMap::getMapHeight()
{
    return m_mapHeight;
}

const int WorldMap::getMapWidth()
{
    return m_mapWidth;
}

void WorldMap::render(MapObject** mapObjects, SpriteBatch& batch, Sprite& sprite, const int rowOffset,
                      const int columnOffset, int randId, int randIdNextLevel)
{
    int flagX = 1;
    int flagY = 1;

    if (randId == 1)
        flagX = -1;

    if (randId == 2)
        flagY = -1;

    if (randIdNextLevel == 3)
        flagX = -1;

    if (randIdNextLevel == 4)
        flagY = -1;

    int height = m_mapHeight;
    int width = m_mapWidth;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (getMapKey(i, j) == '0')
            {
                float tempRow = flagX * (-i - rowOffset) * 64;
                float tempCol = flagY * (j + columnOffset) * 64;

                mapObjects[i][j].setXAxis(tempCol);
                mapObjects[i][j].setYAxis(tempRow);
                mapObjects[i][j].setSize(64.0f);
                mapObjects[i][j].setSymbol('0');
                mapObjects[i][j].setI(i);
                mapObjects[i][j].setJ(j);

                drawMap(tempCol, tempRow, batch, sprite);
            }
        }
    }
}

void WorldMap::drawMap(float coordX, float coordY, SpriteBatch& batch, Sprite& sprite)
{
    sprite.setPosition(glm::vec2(coordX, coordY));
    batch.draw(sprite);
}
