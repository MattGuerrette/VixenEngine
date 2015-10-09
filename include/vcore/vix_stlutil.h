/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
