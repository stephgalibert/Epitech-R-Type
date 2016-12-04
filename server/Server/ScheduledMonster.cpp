#include "ScheduledMonster.hpp"


ScheduledMonster::ScheduledMonster(void)
{
	loadLevel(1);
}


ScheduledMonster::~ScheduledMonster(void)
{
}

void ScheduledMonster::loadLevel(size_t level)
{
	std::string file = "level_";
	
	file += static_cast<char>(level);
	file += ".lvl";
	try {
		std::ifstream ifs(file, std::ifstream::in);

		while (ifs.eof()) {
			std::string line;
			std::getline(ifs, line);
			std::stringstream ss;
			ss << line;
			std::string name;
			float time;
			ss >> time;
			ss >> name;
			
			_schedule.push_back(std::make_pair(time, name));
		}
	} catch (std::runtime_error const&) {
		throw;
	}

}