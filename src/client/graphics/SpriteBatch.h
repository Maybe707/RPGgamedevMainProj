#ifndef RPG_SPRITEBATCH_H
#define RPG_SPRITEBATCH_H

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "VertexArray.h"
#include "Buffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Sprite.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoord;
    float texId;
};

static const size_t MaxTextures = 16;

class SpriteBatch
{
    Shader m_shader;
    int m_spriteCount;

    VertexArray m_vao;
    Buffer m_vbo;
    Buffer m_ibo;

    // layer -> vertices
    std::map<int, std::vector<Vertex>> m_vertices;

    Texture m_textures[MaxTextures];
    int m_texturesSize{0};

public:
    SpriteBatch() = default;

    SpriteBatch(Shader shader, int spriteCount = 2000);

    void begin();

    void end();

    void draw(const Sprite &sprite, int layer = 0);

    void setProjectionMatrix(glm::mat4 projMat);

    void setViewMatrix(glm::mat4 viewMat);

    void destroy();

};

#endif //RPG_SPRITEBATCH_H
