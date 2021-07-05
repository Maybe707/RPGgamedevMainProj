#include "Key_Input_Notifier.h"
#include "Player_Implementation.h"
#include <list>

void Key_Input_Notifier::Attach(Player_Implementation *player_hero)
{
	Player_Observers.push_back(player_hero);
}

void Key_Input_Notifier::Detach(Player_Implementation *player_hero)
{
	Player_Observers.remove(player_hero);
}

void Key_Input_Notifier::Notifier(int key, int action)
{
	for(Player_Implementation* iterator: Player_Observers)
		iterator->Receiver(key, action);
}
