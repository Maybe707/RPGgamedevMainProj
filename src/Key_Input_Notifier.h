#include "Player_Implementation.h"
#include "Key_Input_Notifier_Interface.h"
#include <list>

class Key_Input_Notifier : public Key_Input_Notifier_Interface
{
	std::list<Player_Implementation *> Player_Observers;
	public:
	virtual ~Key_Input_Notifier() {}
	virtual void Attach(Player_Implementation* player_hero) override;
	virtual void Detach(Player_Implementation* player_hero) override;
	virtual void Notifier(int key, int action) override;
};
