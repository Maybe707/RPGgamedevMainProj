#ifndef UNIT_INTERFACE_H
#define UNIT_INTERFACE_H

#include "graphics/Shader.h"
#include "graphics/Texture.h"

class Unit_Interface
{
public:
	virtual ~Unit_Interface() {}
	virtual void Draw(const int SCR_WIDTH, const int SCR_HEIGHT, Shader ourShader,
					  unsigned int VAO, Texture texture) = 0;
	virtual void Receiver(int key, int action) = 0;
};

#endif
