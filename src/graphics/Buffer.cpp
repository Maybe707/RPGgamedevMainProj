#include "Buffer.h"
#include <glad/gl.h>

Buffer::Buffer(unsigned int target) : m_target(target)
{
    glGenBuffers(1, &m_id);    
}

Buffer::~Buffer()
{
    
}

void Buffer::bind()
{
    glBindBuffer(m_target, m_id);
}

void Buffer::unbind()
{
    glBindBuffer(m_target, 0);
}

void Buffer::destroy()
{
    glDeleteBuffers(1, &m_id);
}

void Buffer::setBufferData(void* data, size_t size, unsigned int usage)
{
    glNamedBufferData(m_id, size, data, usage);
}

unsigned int Buffer::getId() const
{
    return m_id;
}


unsigned int Buffer::getTarget() const
{
    return m_target;
}
