#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "IGLObject.h"

class VertexArray final : public IGLObject
{
private:
    unsigned int m_id{};
public:
    VertexArray();

    void bind();
    void unbind();

    void destroy() override;

    unsigned int getId() const override;
};


#endif