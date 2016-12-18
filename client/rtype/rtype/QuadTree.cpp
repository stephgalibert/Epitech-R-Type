#include "QuadTree.hpp"

QuadTree::QuadTree(int const level, sf::FloatRect const& region)
{
	_region = region;
	_level = level;
	_nodes[0] = NULL;
	_nodes[1] = NULL;
	_nodes[2] = NULL;
	_nodes[3] = NULL;

	_center.x = _region.left + (_region.width / 2.f);
	_center.y = _region.top + (_region.height / 2.f);
}

QuadTree::~QuadTree(void)
{
	clear();
}

int QuadTree::getQuarter(sf::FloatRect const& rect)
{
	int quarter = -1;

	if (rect.left < _center.y && rect.left + rect.width < _center.y) {
		if (rect.top < _center.x && rect.top + rect.height < _center.x) {
			quarter = 1;
		}
		else if (rect.top > _center.x) {
			quarter = 2;
		}
	}
	else if (rect.left > _center.y) {
		if (rect.top < _center.x && rect.top + rect.height < _center.x) {
			quarter = 0;
		}
		else if (rect.top > _center.x) {
			quarter = 3;
		}
    }

  return quarter;
}

bool QuadTree::insert(AEntity *collidable)
{
	if (_nodes[0] != NULL) {
		int quarter = getQuarter(collidable->getBoundingBox());
		if (quarter != -1) {
			_nodes[quarter]->insert(collidable);
			return true;
		}
    }

	_elements.push_back(collidable);
  
	if (_elements.size() > QuadTree::Capacity && _level < QuadTree::MaxLevel) {
		if (!_nodes[0]) {
			subDivide();
		}
    }
  return true;
}

void QuadTree::retrieve(std::vector<AEntity *> &list, AEntity *collidable)
{
	int quarter = getQuarter(collidable->getBoundingBox());

	if (quarter != -1 && _nodes[quarter]) {
		_nodes[quarter]->retrieve(list, collidable);
	}

	for (auto &it : _elements) {
		if (collidable->isCollidingWith(it) && it->getID() != collidable->getID()) {
			list.push_back(it);
		}
	}
}

void QuadTree::subDivide(void)
{
	float width = _region.width / 2.0f;
	float height = _region.height / 2.0f;
	float x = _region.left;
	float y = _region.top;

	sf::FloatRect boundary;
	boundary = sf::FloatRect(x + width, y, width, height);
	_nodes[0] = new QuadTree(_level + 1, boundary);
	boundary = sf::FloatRect(x, y, width, height);
	_nodes[1] = new QuadTree(_level + 1, boundary);  
	boundary = sf::FloatRect(x, y + height, width, height);
	_nodes[2] = new QuadTree(_level + 1, boundary);
	boundary = sf::FloatRect(x + width, y + height, width, height);
	_nodes[3] = new QuadTree(_level + 1, boundary);
}

void QuadTree::clear(void)
{
	_elements.clear();

	for (int i = 0 ; i < 4 ; i++) {
		if (_nodes[i]) {
			_nodes[i]->clear();
			delete _nodes[i];
			_nodes[i] = NULL;
		}
    }
}
