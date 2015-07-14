#ifndef VIX_STLUTIL_H
#define VIX_STLUTIL_H

#include <vector>
#include <list>
#include <map>

template <typename K, typename T>
void STLMAP_DELETE(std::map<K, T>& _map)
{
    typename std::map<K, T>::iterator it = _map.begin();
    for(; it != _map.end(); it++) {
        delete it->second;
        it->second = NULL;
    }
    _map.clear();
}

template <typename K, typename T>
void STLMAP_DELETE(std::map<K, T>& _map, K& key)
{
    typename std::map<K, T>::iterator it = _map.find(key);
    delete it->second;
    _map.erase(key);
}

template <typename T>
void STLVEC_DELETE(std::vector<T>& _vec)
{
    typename std::vector<T>::iterator it = _vec.begin();
    for(; it != _vec.end(); it++) {
        delete *it;
    }
    _vec.clear();
}

#endif // VIX_STLUTIL_H
