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
	Cache const& operator[](Key const& key) const;

	void insert(Key const& key, Cache const& cache);
	bool find(Key const& key);

private:
	std::unordered_map<Key, Cache> _cache;
};


/* Template implementation */


template<typename Key, typename Cache>
Cache &CacheManager<Key, Cache>::operator[](Key const& key)
{
	if (_cache.find(key) != _cache.end()) {
		return (_cache[key]);
	}
	throw (std::runtime_error("CacheManager: key not found"));
}

template<typename Key, typename Cache>
Cache const& CacheManager<Key, Cache>::operator[](Key const& key) const
{
	if (_cache.find(key) != _cache.end()) {
		return (_cache.at(key));
	}
	throw (std::runtime_error("CacheManager: key not found"));
}

template<typename Key, typename Cache>
void CacheManager<Key, Cache>::insert(Key const& key, Cache const& cache)
{
	_cache.insert(std::make_pair(key, cache));
}

template<typename Key, typename Cache>
bool CacheManager<Key, Cache>::find(Key const& key)
{
	return (_cache.find(key) != _cache.end());
}