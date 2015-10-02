/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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

#include <vix_modelmanager.h>
#include <vix_stlutil.h>
#include <vix_tinyxml.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>

namespace Vixen {

    bool ModelManager::Initialize()
    {
        ModelManager& _manager = ModelManager::instance();

        using namespace tinyxml2;

        //need to attempt to open scene list
        File* file = FileManager::OpenFile(PathManager::ModelPath() + VTEXT("models.config"));
        if (file) {

            //File is actually an XML file
            //we should now open for reading
            XMLDOC document;
            XMLError err = document.LoadFile(file->Handle());
            UString errString;
            if (XMLErrCheck(err, errString))
            {
                DebugPrintF(VTEXT("Models Config File failed to load\n"));
                FileManager::CloseFile(file);
                return false;
            }

            const XMLElement* modelsElement = document.FirstChildElement("models");
            const XMLElement* modelElement = modelsElement->FirstChildElement("model");
            while (modelElement != NULL)
            {
                const char* fileID = modelElement->Attribute("file");
                UString id = UStringFromCharArray(fileID);
                IModel* model = ResourceManager::OpenModel(id);
                if (model)
                    _manager.m_models[id] = model;
                else
                    DebugPrintF(VTEXT("ModelManager: %s failed to load"), id.c_str());

                modelElement = modelElement->NextSiblingElement("model");
            }
            FileManager::CloseFile(file);
            return true;
        }

        FileManager::CloseFile(file);
        return false;
    }

    void ModelManager::DeInitialize()
    {
        STLMAP_DELETE(ModelManager::instance().m_models);
    }

    IModel* ModelManager::AccessModel(UString id)
    {
        ModelManager& _manager = ModelManager::instance();

        ModelMap::iterator it = _manager.m_models.find(id);
        if (it != _manager.m_models.end())
            return it->second;
        else
            return NULL;
    }
}
