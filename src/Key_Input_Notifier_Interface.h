#ifndef KEY_INPUT_NOTIFIER_INTERFACE
#define KEY_INPUT_NOTIFIER_INTERFACE

#include "Player_Implementation.h"

class IKeyInputNotifier
{
public:
    virtual ~IKeyInputNotifier() {}
    virtual void attach(PlayerImpl* player) = 0;
    virtual void detach(PlayerImpl* player) = 0;
    virtual void notifier(int key, int action) = 0;
};

#endif
