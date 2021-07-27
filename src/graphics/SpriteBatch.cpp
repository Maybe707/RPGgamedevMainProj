#include "SpriteBatch.h"

#include <glad/gl.h>
#include <numeric>

SpriteBatch::SpriteBatch(Shader &shader, int spriteCount)
        : m_shader(shader), m_spriteCount(spriteCount),
          m_vbo(GL_ARRAY_BUFFER), m_ibo(GL_ELEMENT_ARRAY_BUFFER),
          m_textures(&compareTextures)
{
    const int vertexCount = m_spriteCount * 4;
    const int indexCount = m_spriteCount * 6;

    m_vao.bind();
    m_vbo.bind();

    // Небольшой трюк.
    // Вместо того, чтобы сразу закидывать данные в vbo, мы выделим в нем память для дальнейшего использования
    m_vbo.setData(nullptr, sizeof(Vertex) * vertexCount, GL_DYNAMIC_DRAW);

    // Координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
    glEnableVertexAttribArray(0);

    // Атрибуты цвета
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Атрибуты текстурных координат
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Атрибуты индекса текстуры
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (9 * sizeof(float)));
    glEnableVertexAttribArray(3);

    // Паттерн такой:
    // 0, 1, 2, 2, 3, 0
    // 4, 5, 6, 6, 7, 4
    // и т.д.
    auto *indices = new unsigned int[indexCount];
    unsigned int offset = 0;
    for (int i = 0; i < indexCount; i += 6)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    };
    m_ibo.bind();
    m_ibo.setData(indices, indexCount * sizeof(unsigned int), GL_STATIC_DRAW);

    m_vbo.unbind();
    m_vao.unbind();
    delete[] indices;
}

void SpriteBatch::begin()
{
    m_vertices.clear();
    m_textures.clear();
    m_shader.use();
}

void SpriteBatch::end()
{
    // В этом методе происходит отрисовка всех спрайтов разом
    m_vbo.bind();

    // Закидываем наши вершины в заранее выделенную память
    m_vbo.setSubData(m_vertices, 0);

    m_shader.use();

    int *ids = new int[m_textures.size()];
    std::iota(ids, ids + m_textures.size(), 0);
    m_shader.setUniform("textures", ids, m_textures.size());

    m_shader.setUniform("model", glm::mat4(1));

    for (auto &item : m_textures)
    {
        item.first.bind(item.second);
    }

    m_vao.bind();
    glDrawElements(GL_TRIANGLES, m_spriteCount * 6, GL_UNSIGNED_INT, nullptr);

    delete[] ids;
}

void SpriteBatch::draw(const Sprite &sprite)
{
    if (m_vertices.size() / 4 >= m_spriteCount)
    {
        std::cerr << "Cannot draw a sprite! Maximum number of sprites reached!" << std::endl;
        return;
    }

    // Тут мы ничего не рисуем, а просто сохраняем наши спрайты, чтобы потом отрисовать их все вместе
    glm::vec2 quadPos = sprite.getPosition() - sprite.getOrigin();
    IntRect rect = sprite.getTextureRect();

    // Чтобы не сохранять дубликаты текстур, решил складывать их в мапу
    Texture& texture = sprite.getTexture();
    auto result = m_textures.find(texture);
    if (result == m_textures.end())
    {
        if (m_textures.size() >= MaxTextures)
        {
            std::cerr << "Cannot draw a sprite with texture " << texture.getPath()
                      << "! Maximum number of textures reached!" << std::endl;
            return;
        }
        // Если такой текстуры еще нет, то добавляем ее в кэш
        result = m_textures.insert({texture, m_textures.size()}).first;
    }
    auto texId = static_cast<float>(result->second);

    m_vertices.push_back({
                                 glm::vec3(quadPos, 0.f), // низ лево
                                 sprite.getColor(),
                                 glm::vec2(rect.getLeft(), rect.getBottom()), texId
                         });
    m_vertices.push_back({
                                 glm::vec3(quadPos + glm::vec2(sprite.getWidth(), 0.f), 0.f), // низ право
                                 sprite.getColor(),
                                 glm::vec2(rect.getLeft() + rect.getWidth(), rect.getBottom()), texId
                         });
    m_vertices.push_back({
                                 glm::vec3(quadPos + glm::vec2(sprite.getWidth(), sprite.getHeight()),
                                           0.f), // верх право
                                 sprite.getColor(),
                                 glm::vec2(rect.getLeft() + rect.getWidth(), rect.getBottom() + rect.getHeight()), texId
                         });
    m_vertices.push_back({
                                 glm::vec3(quadPos + glm::vec2(0.f, sprite.getHeight()), 0.f), // верх лево
                                 sprite.getColor(),
                                 glm::vec2(rect.getLeft(), rect.getBottom() + rect.getHeight()), texId
                         });
}

void SpriteBatch::setProjectionMatrix(glm::mat4 projMat)
{
    m_shader.use();
    m_shader.setUniform("projection", projMat);
}

void SpriteBatch::setViewMatrix(glm::mat4 viewMat)
{
    m_shader.use();
    m_shader.setUniform("view", viewMat);
}

void SpriteBatch::destroy()
{
    m_vao.destroy();
    m_vbo.destroy();
    m_ibo.destroy();
}
