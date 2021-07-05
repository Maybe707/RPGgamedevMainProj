#ifndef KEY_INPUT_NOTIFIER_INTERFACE
#define KEY_INPUT_NOTIFIER_INTERFACE

#include "Player_Implementation.h"

class Key_Input_Notifier_Interface
{
	public:
	virtual ~Key_Input_Notifier_Interface() {}
	virtual void Attach(Player_Implementation* player_hero) = 0;
	virtual void Detach(Player_Implementation* player_hero) = 0;
	virtual void Notifier(int key, int action) = 0;
};

#endif
