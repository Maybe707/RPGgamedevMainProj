#include "Buffer.h"
#include <glad/gl.h>

Buffer::Buffer(unsigned int target) : m_target(target)
{
    glGenBuffers(1, &m_id);    
}

void Buffer::bind() const
{
    glBindBuffer(m_target, m_id);
}

void Buffer::unbind() const
{
    glBindBuffer(m_target, 0);
}

void Buffer::destroy()
{
    glDeleteBuffers(1, &m_id);
    m_id = 0;
    m_target = 0;
}

template<typename T>
void Buffer::setBufferData(const std::vector<T>& data, unsigned int usage)
{
    glNamedBufferData(m_id, data.size() * sizeof(T), data.data(), usage);
}

void Buffer::setBufferData(const void* data, size_t size, unsigned int usage) const
{
    glNamedBufferData(m_id, static_cast<GLsizeiptr>(size), data, usage);
}

unsigned int Buffer::getId() const
{
    return m_id;
}

unsigned int Buffer::getTarget() const
{
    return m_target;
}
