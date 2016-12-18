#pragma once

# include <iostream>
# include <vector>
#include <algorithm>

#include "AEntity.hpp"

class QuadTree
{
public:
	static const int Capacity = 16;
	static const int MaxLevel = 40;

public:
	QuadTree(int const level, sf::FloatRect const& region);
	~QuadTree(void);

	bool insert(AEntity *b);
	void retrieve(std::vector<AEntity *> &list, AEntity *collidable);
	void clear(void);
    
private:
	int getQuarter(sf::FloatRect const& rect);
	void subDivide(void);
    
	int _level;
	sf::FloatRect _region;
	std::vector<AEntity *> _elements;
	QuadTree *_nodes[4];

	sf::Vector2f _center;
};