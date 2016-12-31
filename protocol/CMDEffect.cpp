#include "CMDEffect.hpp"

CMDEffect::CMDEffect(EffectType type, uint16_t id, bool toAdd)
{
	_data = new Effect;
	_data->cmdType = getCommandType();
	_data->type = type;
	_data->id = id;
	_data->to_add = toAdd;
}

CMDEffect::CMDEffect(void)
{
	_data = new Effect;
}

CMDEffect::~CMDEffect(void)
{
	delete (_data);
}

void CMDEffect::loadFromMemory(char const *data)
{
	Effect const *effect = reinterpret_cast<Effect const *>(data);

	_data->cmdType = getCommandType();
	_data->type = effect->type;
	_data->id = effect->id;
	_data->to_add = effect->to_add;
}

size_t CMDEffect::getSize(void) const
{
	return (sizeof(Effect));
}

CommandType CMDEffect::getCommandType(void) const
{
	return (CommandType::Effect);
}

char *CMDEffect::getData(void) const
{
	return (reinterpret_cast<char *>(_data));
}