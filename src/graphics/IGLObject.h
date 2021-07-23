#ifndef RPG_IGLOBJECT_H
#define RPG_IGLOBJECT_H

class IGLObject
{
public:
    virtual ~IGLObject() = default;

    virtual unsigned int getId() const = 0;
    virtual void destroy() = 0;
};

#endif //RPG_IGLOBJECT_H
