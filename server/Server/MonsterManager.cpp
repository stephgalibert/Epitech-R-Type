#include "MonsterManager.hpp"
#include "DLManager.hpp"

MonsterManager::MonsterManager(ConnectionManager const& cm) : _cm(cm)
{
	_dlManager = NULL;
}

MonsterManager::~MonsterManager(void)
{
	if (_dlManager) {
		delete (_dlManager);
	}
}

void MonsterManager::init(void)
{
	try {
		_dlManager = new DLManager<IMonster>();
		_dlManager->parseDirectory("monsters/");
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void MonsterManager::update(float delta)
{

}
