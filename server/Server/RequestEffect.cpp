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
		owner->setEffect(effect->type, effect->to_add);
	}
}