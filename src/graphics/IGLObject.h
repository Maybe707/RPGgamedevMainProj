#ifndef GLOBJECT_H
#define GLOBJECT_H

class IGLObject
{
public:
    virtual ~IGLObject() = default;

    virtual unsigned int getId() const = 0;
    virtual void destroy() = 0;
};

#endif