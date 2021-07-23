#include "KeyInputNotifier.h"
#include "Player.h"

void KeyInputNotifier::attach(Player *player)
{
    m_playerObservers.push_back(player);
}

void KeyInputNotifier::detach(Player *player)
{
    m_playerObservers.remove(player);
}

void KeyInputNotifier::notifier(int key, int action)
{
    for(Player* iterator: m_playerObservers)
    {
        iterator->receiver(key, action);
    }
}
