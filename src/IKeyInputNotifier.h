#ifndef KEY_INPUT_NOTIFIER_INTERFACE
#define KEY_INPUT_NOTIFIER_INTERFACE

#include "Player.h"

class IKeyInputNotifier
{
public:
    virtual ~IKeyInputNotifier() {}
    virtual void attach(Player *player) = 0;
    virtual void detach(Player *player) = 0;
    virtual void notifier(int key, int action) = 0;
};

#endif
