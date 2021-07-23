#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "Shader.h"

class Camera2D
{
private:
    float m_width;
    float m_height;
    glm::vec2 m_position;
    float m_zn;
    float m_zf;
public:
    Camera2D(glm::vec2 position, float width = 0.0f, float height = 0.0f, float zn = 0.0f, float zf = 100.0f);

    glm::vec2 getPosition() const;
    void setPosition(glm::vec2 position);

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
};

#endif
