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
}

#endif // VIX_STLUTIL_H
