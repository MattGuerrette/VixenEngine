
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string>

#include <vix_filemanager.h>
#include <vix_inireader.h>
#include <vix_iniwriter.h>
#include <vix_debugutil.h>

using namespace Vixen;

int main(int argc, char* argv[])
{
    FileManager::Initialize();
    INIReader* _reader = new INIReader;
    INIWriter* _writer = new INIWriter;

    File* file = FileManager::OpenFile("test.ini", FileMode::ReadBinary);
    if(file)
    {
        _reader->Load(file->Handle());

    }
    FileManager::CloseFile(file);


    _writer->Write("test2.ini");

    //DebugPrintF("Width: %d", _reader->GetValue<int>("TEST_SECTION", "iWidth", 50));

    _reader->PrintValues();

    FileManager::DeInitialize();

    return 0;
}
