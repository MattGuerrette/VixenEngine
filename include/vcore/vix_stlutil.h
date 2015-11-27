/**
**	Vixen Engine
**	Copyright(c) 2015 Matt Guerrette
**
**	GNU Lesser General Public License
**	This file may be used under the terms of the GNU Lesser
**  General Public License version 3 as published by the Free
**  Software Foundation and appearing in the file LICENSE.LGPLv3 included
**  in the packaging of this file. Please review the following information
**  to ensure the GNU Lesser General Public License requirements
**  will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

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

        if(it->second)
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
