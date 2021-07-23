#include "Texture.h"

#include <iostream>
#include <glad/gl.h>
#include <stb_image.h>

Texture::Texture(const std::string &path)
        : m_path(path)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

    // Установка параметров наложения текстуры
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Установка параметров фильтрации текстуры
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(1);

    int channels;
    unsigned char *data = stbi_load(path.c_str(), &m_width, &m_height, &channels, 0);
    if (data)
    {
        glTextureStorage2D(m_id, 1, GL_RGBA8, m_width, m_height);
        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateTextureMipmap(m_id);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(unsigned int slot) const
{
    glBindTextureUnit(slot, m_id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getId() const noexcept
{
    return m_id;
}

void Texture::destroy()
{
    glDeleteTextures(1, &m_id);
    m_id = 0;
}

std::string Texture::getPath() const
{
    return m_path;
}

int Texture::getWidth() const
{
    return m_width;
}

int Texture::getHeight() const
{
    return m_height;
}
