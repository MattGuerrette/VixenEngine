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

#ifndef VIX_INIWRITER_H
#define VIX_INIWRITER_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <utility>

namespace Vixen {

    class VIX_API INIWriter
    {
        typedef std::vector<std::pair<std::string, std::string> > ValuePairList;
    public:
        INIWriter();

        void Write(std::string outname);

        template <typename T>
        void SetValue(std::string section, std::string name, T value);

    private:
        std::map<std::string, ValuePairList> _values;

        static std::string  MakeKey(std::string section);
    };

    template <>
    inline void INIWriter::SetValue(std::string section, std::string name, int value)
    {

    }

    template <>
    inline void INIWriter::SetValue(std::string section, std::string name, float value)
    {

    }

    template <>
    inline void INIWriter::SetValue(std::string section, std::string name, double value)
    {

    }

    template <>
    inline void INIWriter::SetValue(std::string section, std::string name, bool value)
    {

    }

}

#endif
