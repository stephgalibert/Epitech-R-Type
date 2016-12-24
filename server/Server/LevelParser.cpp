#include "LevelParser.hpp"

LevelParser::LevelParser(void)
{
}

LevelParser::~LevelParser(void)
{
}

void LevelParser::parse(uint8_t level)
{
	std::string str;
	std::ifstream ifs;

	str = "levels/level" + std::to_string(level) + ".txt";
	ifs.open(str);
	if (ifs) {
		retrieveData(ifs);
	}
	else {
		throw (std::runtime_error("LevelParser: can't open " + str));
	}
}

std::vector<std::vector<std::string> > const& LevelParser::getData(void) const
{
	return (_data);
}

void LevelParser::retrieveData(std::ifstream &ifs)
{
	std::string buffer;
	std::vector<std::string> tokens;

	while (std::getline(ifs, buffer))
	{
		if (buffer.size() > 0 && buffer.at(0) != '#') {
			StaticTools::SplitString(buffer, ' ', tokens);
			if (tokens.size() > 3) {
				_data.push_back({ tokens[0], tokens[1], tokens[2], tokens[3] });
			}
			tokens.clear();
		}
	}
}