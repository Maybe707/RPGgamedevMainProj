#include "VertexArray.h"
#include <glad/gl.h>

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    destroy();
}

void VertexArray::bind()
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}

void VertexArray::destroy()
{
    glDeleteVertexArrays(1, &m_id);
    m_id = 0;
}

unsigned int VertexArray::getId() const
{
    return m_id;
}
