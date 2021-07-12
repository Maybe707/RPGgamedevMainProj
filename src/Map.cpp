#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Map.h"
#include "VertexMath.h"
#include <iostream>

WorldMap::WorldMap(const unsigned int scr_width, const unsigned int scr_height, const int map_h, const int map_w) : m_scr_width(scr_width), m_scr_height(scr_height), map_height(map_h), map_width(map_w)
{
	tile_Map = new char*[map_height];
	for(int count = 0; count < map_height; ++count)
		tile_Map[count] = new char[map_width];

    for(int i = 0; i < map_height; ++i)
        for(int j = 0; j < map_width; ++j)
            tile_Map[i][j] = ' ';
}

WorldMap::~WorldMap()
{
	for(int count = 0; count < map_height; ++count)
		delete [] tile_Map[count];
	delete [] tile_Map;
    tile_Map = nullptr;
}

void WorldMap::Initializing(char** array)
{
	for(int i = 0; i < map_height; ++i)
		for(int j = 0; j < map_width; ++j)
		{
			tile_Map[i][j] = array[i][j];
		}
}

void WorldMap::set_RandomSprites(const char*** Sprite_Set, Sprite_RandSet& sprite_obj)
{
    for(int posIndex_X = 0; posIndex_X < ((map_height - 2) / 7); ++posIndex_X)
        for(int posIndex_Y = 0; posIndex_Y < ((map_width - 2) / 7); ++posIndex_Y)
        {
            // rand call
            sprite_obj.setRandSprite(Sprite_Set, getRandomNumber(0, 2));
            for(int localArrIndex_X = 0; localArrIndex_X < sprite_obj.getHeight(); ++localArrIndex_X)
                for(int localArrIndex_Y = 0; localArrIndex_Y < sprite_obj.getWidth(); ++localArrIndex_Y)
                {
                    if(sprite_obj.getSprite_SetArray()[localArrIndex_X][localArrIndex_Y] == '0')
                        tile_Map[posIndex_X*7 + 1 + localArrIndex_X][posIndex_Y*7 + 1 + localArrIndex_Y] = '0';
                }
        }
}

char WorldMap::getMapKey(const int i, const int j) { return tile_Map[i][j]; }

// Генерируем рандомное число между значениями min и max.
// Предполагается, что функцию srand() уже вызывали
int WorldMap::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

const int WorldMap::getMapHeight() { return map_height; }
const int WorldMap::getMapWidth() { return map_width; }

void WorldMap::Render(Map_Objects** Map_Objects_Pointer, Shader& ourShader, unsigned int VAO, unsigned int texture1, const int row_offset, const int col_offset, int rand_id, int rand_id_next_level)
{
    int flag_x = 1;
    int flag_y = 1;
    if(rand_id == 1)
        flag_x = -1;
    if(rand_id == 2)
        flag_y = -1;

    if(rand_id_next_level == 3)
        flag_x = -1;
    if(rand_id_next_level == 4)
        flag_y = -1;

    int height = map_height;
	int width = map_width;
	for(int i = 0; i < height; ++i)
		for(int j = 0; j < width; ++j)
		{
			if(getMapKey(i, j) == '0')
			{
				float tempRow = flag_x*(-i-row_offset)*64;
				float tempCol = flag_y*(j+col_offset)*64;
				Map_Objects_Pointer[i][j].set_xAxis(tempCol);
				Map_Objects_Pointer[i][j].set_yAxis(tempRow);
				Map_Objects_Pointer[i][j].set_Size(64.0f);
				Map_Objects_Pointer[i][j].set_Symbol('0');
				Map_Objects_Pointer[i][j].setI(i);
				Map_Objects_Pointer[i][j].setJ(j);
				MapDraw(m_scr_width, m_scr_height, tempCol, tempRow, ourShader, VAO, texture1);
			}
		}
}

void WorldMap::MapDraw(const int SCR_WIDTH, const int SCR_HEIGHT, float coordX, float coordY, Shader ourShader, unsigned int VAO, unsigned int texture1)
{
	Matrix<float, 4> trans(64.0f);

	trans = Translate(trans, Vector<float, 4> (coordX, coordY, 0.0f, 1.0f));

	unsigned int transformtLoc = glGetUniformLocation(ourShader.ID, "model");
	glUniformMatrix4fv(transformtLoc, 1, GL_TRUE, &trans[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	ourShader.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
