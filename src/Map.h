#ifndef MAP_H
#define MAP_H

#include <string>
#include "graphics/Shader.h"
#include "Map_Objects.h"
#include "Sprite_RandSet.h"

class WorldMap
{
	const int map_height;
	const int map_width;
	const unsigned int m_scr_width;
	const unsigned int m_scr_height;
    char** tile_Map;
    
    public:
	WorldMap(const unsigned int scr_width, const unsigned int scr_height,
			 const int map_h, const int map_w);

	~WorldMap();
    
	void Initializing(char** array);
    
    void set_RandomSprites(const char*** Sprite_Set, Sprite_RandSet& sprite_obj);
    
	char getMapKey(const int i, const int j);
    int getRandomNumber(int min, int max);
	const int getMapHeight();
	const int getMapWidth();

	void Render(Map_Objects** Map_Objects_Pointer, Shader& ourShader, unsigned int VAO, unsigned int texture1, const int row_offset, const int col_offset, int rand_id, int rand_id_next_level);

	void MapDraw(float coordX, float coordY, Shader ourShader, unsigned int VAO, unsigned int texture1);
};

#endif
