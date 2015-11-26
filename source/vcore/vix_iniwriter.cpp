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
                    name += VTEXT("=") + _map[i].second;
                    file->Write((BYTE*)name.c_str(), name.size());
                }
            }
        }
    }

    std::string INIWriter::MakeKey(std::string section)
    {
        std::string key = VTEXT("[") + section + VTEXT("]");

        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        return section;
    }

}
