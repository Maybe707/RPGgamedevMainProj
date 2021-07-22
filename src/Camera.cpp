#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera_2D::Camera_2D(float xAxis, float yAxis, float zAxis,
					 float width, float height, float zn, float zf) :
	m_width(width), m_height(height), m_zn(zn), m_zf(zf)
{
	for(int i = 0; i < 16; ++i)
        Matrix_Transform[i] = 0.0f;

	Matrix_Transform[0] = 1.0f;
	Matrix_Transform[5] = 1.0f;
	Matrix_Transform[10] = 1.0f;
	Matrix_Transform[15] = 1.0f;

	Matrix_Transform[12] = xAxis;
	Matrix_Transform[13] = yAxis;
	Matrix_Transform[14] = zAxis;
}

void Camera_2D::Move_Local(float xAxis, float yAxis, float zAxis, float distance)
{
	float deltaX = xAxis * Matrix_Transform[0] + yAxis * Matrix_Transform[4]
		+ zAxis * Matrix_Transform[8];
	float deltaY = xAxis * Matrix_Transform[1] + yAxis * Matrix_Transform[5]
		+ zAxis * Matrix_Transform[9];
	float deltaZ = xAxis * Matrix_Transform[2] + yAxis * Matrix_Transform[6]
		+ zAxis * Matrix_Transform[10];

	Matrix_Transform[12]  += deltaX * distance;
	Matrix_Transform[13]  += deltaY * distance;
	Matrix_Transform[14]  += deltaZ * distance;
}

void Camera_2D::Move_Global(float xAxis, float yAxis, float zAxis, float distance)
{
	Matrix_Transform[12]  += xAxis * distance;
	Matrix_Transform[13]  += yAxis * distance;
	Matrix_Transform[14]  += zAxis * distance;
}

void Camera_2D::Set_Position(float xAxis, float yAxis, float zAxis, float distance)
{
	Matrix_Transform[12]  = xAxis * distance;
	Matrix_Transform[13]  = yAxis * distance;
	Matrix_Transform[14]  = zAxis * distance;
}

void Camera_2D::Set_View(Shader ourShader)
{
    glm::mat4 projMat = glm::ortho(-m_width / 2, m_width / 2, -m_height / 2, m_height / 2, 0.0f, 100.0f);
	ourShader.setUniform("projection", projMat);

	float viewArray[16] =
		{Matrix_Transform[0], Matrix_Transform[4], Matrix_Transform[8],  0.0f,
		 Matrix_Transform[1], Matrix_Transform[5], Matrix_Transform[9],  0.0f,
		 Matrix_Transform[2], Matrix_Transform[6], Matrix_Transform[10], 0.0f,

		 (Matrix_Transform[0]*Matrix_Transform[12] +
		  Matrix_Transform[1]*Matrix_Transform[13] +
		  Matrix_Transform[2]*Matrix_Transform[14]),

		 (Matrix_Transform[4]*Matrix_Transform[12] +
		  Matrix_Transform[5]*Matrix_Transform[13] +
		  Matrix_Transform[6]*Matrix_Transform[14]),

		 (Matrix_Transform[8]*Matrix_Transform[12] +
		  Matrix_Transform[9]*Matrix_Transform[13] +
		  Matrix_Transform[10]*Matrix_Transform[14]), 1.0f};
    glm::mat4 viewMat = glm::make_mat4(viewArray);
	ourShader.setUniform("view", viewMat);
}
