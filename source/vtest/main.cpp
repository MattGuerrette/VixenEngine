
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string>

#include <vix_filemanager.h>
#include <vix_inireader.h>
#include <vix_debugutil.h>

using namespace Vixen;

int main(int argc, char* argv[])
{
    FileManager::Initialize();
    INIReader* _reader = new INIReader;

    File* file = FileManager::OpenFile("test.ini");
    if(file)
    {
        _reader->Load(file->Handle());

    }
    FileManager::CloseFile(file);

    //DebugPrintF("Width: %d", _reader->GetValue<int>("TEST_SECTION", "iWidth", 50));

    _reader->PrintValues();

    FileManager::DeInitialize();

    return 0;
}
