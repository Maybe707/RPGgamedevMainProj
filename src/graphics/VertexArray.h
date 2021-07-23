#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "IGLObject.h"

class VertexArray final : public IGLObject
{
private:
    unsigned int m_id{};
public:
    VertexArray();
    ~VertexArray() override;

    void bind();
    void unbind();

    void destroy();

    unsigned int getId() const override;
};


#endif