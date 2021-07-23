#include "Player.h"
#include "IKeyInputNotifier.h"
#include <list>

class KeyInputNotifier : public IKeyInputNotifier
{
    std::list<Player *> m_playerObservers;
public:
    virtual ~KeyInputNotifier() {}
    virtual void attach(Player* player) override;
    virtual void detach(Player* player) override;
    virtual void notifier(int key, int action) override;
};
