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
