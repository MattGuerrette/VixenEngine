
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

#include <vix_inireader.h>
#include <cctype>
#include <algorithm>
#include <vix_debugutil.h>

namespace Vixen {

    INIReader::INIReader()
    {

    }

    bool INIReader::Load(FILE* handle)
    {
        _error = ini_parse_file(handle, ValueHandler, this);

        return true;
    }

    int INIReader::Error()
    {
        return _error;
    }

    void INIReader::PrintValues()
    {
        for(auto& value : _values)
            DebugPrintF(VTEXT("Key: %s \tValue: %s\n"), UStringFromCharArray(value.first.c_str()).c_str(), UStringFromCharArray(value.second.c_str()).c_str());
    }

    std::string INIReader::Get(std::string section, std::string name)
    {
        std::string key = MakeKey(section, name);

        return _values.count(key) ? _values[key] : "";
    }

    std::string INIReader::MakeKey(std::string section, std::string name)
    {
        std::string key = section + "=" + name;

        //convert to lower case for case-insensitivity
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        return key;
    }

    int INIReader::ValueHandler(void* user, const char* section, const char* name, const char* value)
    {
        INIReader* reader = (INIReader*)user;
        std::string key = MakeKey(section, name);
        if(reader->_values[key].size() > 0)
            reader->_values[key] += "\n";
        reader->_values[key] += value;

        return 1;
    }

}
