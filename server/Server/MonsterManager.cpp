#include "MonsterManager.hpp"


MonsterManager::MonsterManager(ConnectionManager const& cm) : _cm(cm)
{
}


MonsterManager::~MonsterManager(void)
{
}

void MonsterManager::init(void)
{
	try {

	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void MonsterManager::update(float delta)
{

}
