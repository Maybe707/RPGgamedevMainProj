#ifndef CAMERA_H
#define CAMERA_H

#include "graphics/Shader.h"
class Camera_2D
{
	float m_width;
	float m_height;
	float m_xAxis;
	float m_yAxis;
	float m_zAxis;
	float m_zn;
	float m_zf;
	float Matrix_Transform[16] = {};
public:
    Camera_2D(float xAxis = 0.0f, float yAxis = 0.0f, float zAxis = 0.0f,
			  float width = 0.0f, float height = 0.0f, float zn = 0.0f, float zf = 100.0f);

	void Move_Local(float xAxis, float yAxis, float zAxis, float distance);
	void Move_Global(float xAxis, float yAxis, float zAxis, float distance);
	void Set_Position(float xAxis, float yAxis, float zAxis, float distance);
	void Set_View(Shader ourShader);
};

#endif
