/*
    The MIT License(MIT)

    Copyright(c) 2015 Matt Guerrette

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files(the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions :
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
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
