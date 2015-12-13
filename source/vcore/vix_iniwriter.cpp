
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

#include <vix_iniwriter.h>
#include <vix_filemanager.h>

namespace Vixen {

    INIWriter::INIWriter()
    {

    }

    void INIWriter::Write(std::string outname)
    {

        File* file = FileManager::OpenFile(outname.c_str(), Vixen::FileMode::WriteBinary);
        if(file)
        {
            for(auto& key : _values)
            {
                //Write section
                std::string section = "[" + key.first + "]\n";

                file->Write((BYTE*)section.c_str(), section.size());

                ValuePairList _map = key.second;
                for(uint32_t i = 0; i < _map.size(); i++)
                {
                    std::string name = _map[i].first;
                    name += "=" + _map[i].second;

                    file->Write((BYTE*)name.c_str(), name.size());
                }
            }
        }
    }


    std::string INIWriter::MakeKey(std::string section)
    {
        std::string key = "[" + section + "]";

        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        return section;
    }
}
