#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "graphics/Shader.h"

class Camera2D
{
    float m_width;
    float m_height;
    float m_xAxis;
    float m_yAxis;
    float m_zAxis;
    float m_zn;
    float m_zf;
    float m_transformMatrix[16] = {};
public:
    Camera2D(
        float xAxis = 0.0f, float yAxis = 0.0f, float zAxis = 0.0f,
        float width = 0.0f, float height = 0.0f, float zn = 0.0f, float zf = 100.0f
    );

    void moveLocal(float xAxis, float yAxis, float zAxis, float distance);

    void moveGlobal(float xAxis, float yAxis, float zAxis, float distance);

    void setPosition(float xAxis, float yAxis, float zAxis, float distance);

    void setView(Shader shader);
};

#endif
