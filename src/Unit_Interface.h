#ifndef UNIT_INTERFACE_H
#define UNIT_INTERFACE_H

#include "shader.h"

class Unit_Interface
{
public:
	virtual ~Unit_Interface() {}
	virtual void Draw(const int SCR_WIDTH, const int SCR_HEIGHT, Shader ourShader,
					  unsigned int VAO, unsigned int texture2) = 0;
	virtual void Receiver(int key, int action) = 0;
};

#endif
