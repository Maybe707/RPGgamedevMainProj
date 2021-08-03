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

// TODO: Класс пока еще сырой, его стоит дальше дорабатывать и оптимизировать
class SpriteBatch
{
    Shader m_shader;
    int m_spriteCount;

    VertexArray m_vao;
    Buffer m_vbo;
    Buffer m_ibo;

    std::vector<Vertex> m_vertices;

    // Функция сравнения текстур, хз куда ее лучше положить
    inline static bool compareTextures(const Texture &texture1, const Texture &texture2)
    {
        return texture1.getId() < texture2.getId();
    }

    // Мапа с текстурами. Нужна для проверки дубликатов и биндинга
    std::map<Texture, unsigned int, decltype(&compareTextures)> m_textures;

public:
    SpriteBatch() = default;
    SpriteBatch(Shader shader, int spriteCount = 2000);

    void begin();

    void end();

    void draw(const Sprite &sprite);

    void setProjectionMatrix(glm::mat4 projMat);

    void setViewMatrix(glm::mat4 viewMat);

    void destroy();

};

#endif //RPG_SPRITEBATCH_H
