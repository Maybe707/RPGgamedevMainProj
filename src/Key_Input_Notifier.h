#include "Player_Implementation.h"
#include "Key_Input_Notifier_Interface.h"
#include <list>

class KeyInputNotifier : public IKeyInputNotifier
{
    std::list<PlayerImpl *> m_playerObservers;
public:
    virtual ~KeyInputNotifier() {}
    virtual void attach(PlayerImpl* player) override;
    virtual void detach(PlayerImpl* player) override;
    virtual void notifier(int key, int action) override;
};
