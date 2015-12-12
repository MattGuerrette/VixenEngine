
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

#ifndef VIX_INIREADER_H
#define VIX_INIREADER_H

#include <vix_platform.h>
#include <ini.h>
#include <map>
#include <cstdlib>
#include <algorithm>

namespace Vixen {

    class VIX_API INIReader
    {
    public:
        INIReader();

        bool Load(FILE* handle);

        int  Error();

        std::string Get(std::string section, std::string name);

        template <typename T>
        T GetValue(std::string section, std::string name, T default_value);

        void PrintValues();

    private:
        int                                _error;
        std::map<std::string, std::string> _values;

        static std::string  MakeKey(std::string section, std::string name);
        static int          ValueHandler(void* user, const char* section, const char* name, const char* value);
    };

    template <>
    inline int INIReader::GetValue(std::string section, std::string name, int default_value)
    {
        std::string valueStr = Get(section, name);

        const char* value = valueStr.c_str();

        int _value = std::atoi(value);

        return _value > 0 ? _value : default_value;
    }

    template <>
    inline bool INIReader::GetValue(std::string section, std::string name, bool default_value)
    {
        std::string valueStr = Get(section, name);

        std::transform(valueStr.begin(), valueStr.end(), valueStr.begin(), ::tolower);
        if (valueStr == "true" || valueStr == "yes" || valueStr == "on" || valueStr == "1")
            return true;
        else if (valueStr == "false" || valueStr == "no" || valueStr == "off" || valueStr == "0")
            return false;
        else
            return default_value;
    }

    template <>
    inline double INIReader::GetValue(std::string section, std::string name, double default_value)
    {
        std::string valueStr = Get(section, name);

        const char* value = valueStr.c_str();

        double _value = std::atof(value);

        return _value > 0.0 ? _value : default_value;
    }

    template <>
    inline float INIReader::GetValue(std::string section, std::string name, float default_value)
    {
        return static_cast<float>(INIReader::GetValue<double>(section, name, static_cast<float>(default_value)));
    }

}

#endif
