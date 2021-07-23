#include "Key_Input_Notifier.h"
#include "Player_Implementation.h"

void KeyInputNotifier::attach(PlayerImpl *player)
{
    m_playerObservers.push_back(player);
}

void KeyInputNotifier::detach(PlayerImpl *player)
{
    m_playerObservers.remove(player);
}

void KeyInputNotifier::notifier(int key, int action)
{
    for(PlayerImpl* iterator: m_playerObservers)
    {
        iterator->receiver(key, action);
    }
}
