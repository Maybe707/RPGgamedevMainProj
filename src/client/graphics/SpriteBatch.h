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

// TODO: optimize this
class SpriteBatch
{
    Shader m_shader;
    int m_spriteCount;

    VertexArray m_vao;
    Buffer m_vbo;
    Buffer m_ibo;

    // layer -> vertices
    std::map<int, std::vector<Vertex>> m_vertices;

    // Texture comparator, idk where to place it
    inline static bool compareTextures(const Texture &texture1, const Texture &texture2)
    {
        return texture1.getId() < texture2.getId();
    }

    // Map with textures. We need this to check for duplicates and for texture binding
    std::map<Texture, unsigned int, decltype(&compareTextures)> m_textures;

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
