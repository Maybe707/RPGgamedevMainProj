#ifndef MAP_H
#define MAP_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexMath.h"
#include "graphics/Shader.h"
#include "Map_Objects.h"

class WorldMap
{
	const int map_height;
	const int map_width;
	const unsigned int m_scr_width;
	const unsigned int m_scr_height;
    char** tile_Map;
    
    public:
	WorldMap(const unsigned int scr_width, const unsigned int scr_height,
			 const int map_h, const int map_w) :
		m_scr_width(scr_width), m_scr_height(scr_height), map_height(map_h), map_width(map_w)
	{
		tile_Map = new char*[map_height];
		for(int count = 0; count < map_height; ++count)
			tile_Map[count] = new char[map_width];
	}

	~WorldMap()
	{
		for(int count = 0; count < map_height; ++count)
			delete [] tile_Map[count];
		delete [] tile_Map;
	}

	void Initializing(char** array)
	{
		for(int i = 0; i < map_height; ++i)
			for(int j = 0; j < map_width; ++j)
			{
				tile_Map[i][j] = array[i][j];
			}
	}

	char getMapKey(const int i, const int j) { return tile_Map[i][j]; }
	const int getMapHeight() { return map_height; }
	const int getMapWidth() { return map_width; }

	void Render(Map_Objects** Map_Objects_Pointer, Shader& ourShader,
				unsigned int VAO, unsigned int texture1)
	{
		int height = map_height;
		int width = map_width - 1;
		for(int i = 0; i < height; ++i)
			for(int j = 0; j < width; ++j)
			{
				if(getMapKey(i, j) == '0')
					{
						if(i < height/2 && j < width/2)
						{
							float tempRow = 0;
							float tempCol = 0;
							tempRow = (height/2 -1) - i;
							tempCol = (width/2 - 1) - j;
							tempRow *= 64;
							tempCol *= (-64);
							tempRow += 32;
							tempCol -= 32;
							Map_Objects_Pointer[i][j].set_xAxis(tempCol);
							Map_Objects_Pointer[i][j].set_yAxis(tempRow);
							Map_Objects_Pointer[i][j].set_Size(64.0f);
							Map_Objects_Pointer[i][j].set_Symbol('0');
							Map_Objects_Pointer[i][j].setI(i);
							Map_Objects_Pointer[i][j].setJ(j);

							MapDraw(m_scr_width, m_scr_height, tempCol, tempRow, ourShader, VAO, texture1);
							continue;
						}
						if(i < height/2 && j > (width/2 - 1))
						{
							float tempRow = 0;
							float tempCol = 0;
							tempRow = (height/2 - 1) - i;
							tempCol = j - (width/2 -1);
							tempRow *= 64;
							tempCol *= 64;
							tempRow += 32;
							tempCol -= 32;
							Map_Objects_Pointer[i][j].set_xAxis(tempCol);
							Map_Objects_Pointer[i][j].set_yAxis(tempRow);
							Map_Objects_Pointer[i][j].set_Size(64.0f);
							Map_Objects_Pointer[i][j].set_Symbol('0');
							Map_Objects_Pointer[i][j].setI(i);
							Map_Objects_Pointer[i][j].setJ(j);

							MapDraw(m_scr_width, m_scr_height, tempCol, tempRow, ourShader, VAO, texture1);
							continue;
						}
						if(j < width/2 && i > (height/2 -1))
						{
							float tempRow = 0;
							float tempCol = 0;
							tempRow = i - (height/2 - 1);
							tempCol = (width/2 - 1) - j;
							tempRow *= (-64);
							tempCol *= (-64);
							tempRow += 32;
							tempCol -= 32;
							Map_Objects_Pointer[i][j].set_xAxis(tempCol);
							Map_Objects_Pointer[i][j].set_yAxis(tempRow);
							Map_Objects_Pointer[i][j].set_Size(64.0f);
							Map_Objects_Pointer[i][j].set_Symbol('0');
							Map_Objects_Pointer[i][j].setI(i);
							Map_Objects_Pointer[i][j].setJ(j);

							MapDraw(m_scr_width, m_scr_height, tempCol, tempRow, ourShader, VAO, texture1);
							continue;
						}
					    if(i > (height/2 - 1) && j > (width/2 - 1))
						{
							float tempRow = 0;
							float tempCol = 0;
							tempRow = i - (height/2 - 1);
							tempCol = j - (width/2 - 1);
							tempRow *= (-64);
							tempCol *= 64;
							tempRow += 32;
							tempCol -= 32;
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
	}

	void MapDraw(const int SCR_WIDTH, const int SCR_HEIGHT, float coordX, float coordY,
		         Shader ourShader, unsigned int VAO, unsigned int texture1)
	{
		Matrix<float, 4> trans(64.0f);
		//Matrix<float, 4> view(1.0f);

		//view = LookAt(view, Vector<float, 4>(0.0f, 0.0f, 0.0f, -1.0f));

		trans = Translate(trans, Vector<float, 4> (coordX, coordY, 0.0f, 1.0f));

		//Matrix<float, 4> projection;
		//projection = Ortho<float, 4>(SCR_WIDTH, SCR_HEIGHT, 0.0f, 100.0f);


		unsigned int transformtLoc = glGetUniformLocation(ourShader.ID, "model");
		glUniformMatrix4fv(transformtLoc, 1, GL_TRUE, &trans[0][0]);

		//unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		//glUniformMatrix4fv(viewLoc, 1, GL_TRUE, &view[0][0]);

		//unsigned int cameraLoc = glGetUniformLocation(ourShader.ID, "projection");
		//glUniformMatrix4fv(cameraLoc, 1, GL_TRUE, &projection[0][0]);

        // Привязка текстур к соответствующим текстурным юнитам
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

		ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};

#endif
