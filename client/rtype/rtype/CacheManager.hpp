#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>

template<typename Key, typename Cache>
class CacheManager
{
public:
	CacheManager(void) {}
	~CacheManager(void) {}

	Cache &operator[](Key const& key);

	void insert(Key const& key, Cache const& cache);
	Cache const& at(Key const& key) const;
	bool find(Key const& key) const;

private:
	std::unordered_map<Key, Cache> _cache;
};


/* Template implementation */


template<typename Key, typename Cache>
Cache &CacheManager<Key, Cache>::operator[](Key const& key)
{
	return (_cache[key]);
}

template<typename Key, typename Cache>
void CacheManager<Key, Cache>::insert(Key const& key, Cache const& cache)
{
	_cache.insert(std::make_pair(key, cache));
}

template<typename Key, typename Cache>
Cache const& CacheManager<Key, Cache>::at(Key const& key) const
{
	return (_cache.at(key));
}

template<typename Key, typename Cache>
bool CacheManager<Key, Cache>::find(Key const& key) const
{
	return (_cache.find(key) != _cache.end());
}