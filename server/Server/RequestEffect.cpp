#include "RequestEffect.hpp"
#include "AConnection.hpp"

RequestEffect::RequestEffect(void)
{
}

RequestEffect::~RequestEffect(void)
{
}

void RequestEffect::execute(std::shared_ptr<AConnection> owner,
	std::shared_ptr<ICommand> received,
	std::shared_ptr<ICommand> &reply)
{
	(void)reply;

	Effect const *effect = reinterpret_cast<Effect const *>(received->getData());

	if (owner->getPlayerData().id == effect->id) {
		if (effect->type == EffectType::AddLife) {
			owner->setLife(owner->getLife() + 1);
		}
		else {
			owner->setEffect(effect->type, effect->to_add);
		}
	}
}