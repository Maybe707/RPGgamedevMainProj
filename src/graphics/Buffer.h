#ifndef BUFFER_H
#define BUFFER_H

#include <cstddef>
#include <vector>
#include "IGLObject.h"

class Buffer : public IGLObject
{
private:
    unsigned int m_id{};
    unsigned int m_target{};
public:
    Buffer() = default;
    Buffer(unsigned int);

    void bind() const;
    void unbind() const;
    void destroy() override;

    template<typename T>
    void setBufferData(const std::vector<T>& data, unsigned int usage);

    void setBufferData(const void* data, size_t size, unsigned int usage) const;

    unsigned int getId() const override;
    unsigned int getTarget() const;
};

#endif