#include <vix_iniwriter.h>
#include <vix_filemanager.h>

namespace Vixen {

    INIWriter::INIWriter()
    {
        _values["TEST_SECTION"].push_back("bFixed");
        _values["TEST_SECTION"].push_back("iWidth");
        _values["TEST_SECTION"].push_back("iHeight");
        _values["TEST_SECTION"].push_back("fScale");
        _values["TEST_SECTION"].push_back("fDepth");
    }

    void INIWriter::Write(std::string outname)
    {
        File* file = FileManager::OpenFile(UStringFromCharArray(outname.c_str()), Vixen::FileMode::WriteBinary);
        if(file)
        {
            for(auto& key : _values)
            {
                //Write section
                std::string section = "[" + key.first + "]\n";

                file->Write((BYTE*)section.c_str(), section.size());

                std::vector<std::string> _map = key.second;
                for(int i = 0; i < _map.size(); i++)
                {
                    std::string name = _map[i];
                    name += "\n";
                    file->Write((BYTE*)name.c_str(), name.size());
                }
            }
        }
    }

}
