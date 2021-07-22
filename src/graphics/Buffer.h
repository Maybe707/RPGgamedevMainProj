#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>

class Buffer
{
private:
    unsigned int m_id;
    unsigned int m_target;
public:
    Buffer();
    Buffer(unsigned int);
    ~Buffer();

    void bind();
    void unbind();
    void destroy();

    void setBufferData(void* data, size_t size, unsigned int usage);

    unsigned int getId() const;
    unsigned int getTarget() const;
};

#endif