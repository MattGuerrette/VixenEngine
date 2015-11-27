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

#include <vix_modelmanager.h>
#include <vix_stlutil.h>
#include <vix_tinyxml.h>
#include <vix_filemanager.h>
#include <vix_pathmanager.h>
#include <vix_resourcemanager.h>

namespace Vixen {

    //bool ModelManager::Initialize()
    //{
    //    ModelManager& _manager = ModelManager::instance();

    //    using namespace tinyxml2;

    //    //need to attempt to open scene list
    //    File* file = FileManager::OpenFile(PathManager::ModelPath() + VTEXT("models.config"));
    //    if (file) {

    //        //File is actually an XML file
    //        //we should now open for reading
    //        XMLDOC document;
    //        XMLError err = document.LoadFile(file->Handle());
    //        UString errString;
    //        if (XMLErrCheck(err, errString))
    //        {
    //            DebugPrintF(VTEXT("Models Config File failed to load\n"));
    //            FileManager::CloseFile(file);
    //            return false;
    //        }

    //        const XMLElement* modelsElement = document.FirstChildElement("models");
    //        const XMLElement* modelElement = modelsElement->FirstChildElement("model");
    //        while (modelElement != NULL)
    //        {
    //            const char* fileID = modelElement->Attribute("file");
    //            UString id = UStringFromCharArray(fileID);
    //            IModel* model = ResourceManager::OpenModel(id);
    //            if (model)
    //                _manager.m_models[id] = model;
    //            else
    //                DebugPrintF(VTEXT("ModelManager: %s failed to load"), id.c_str());

    //            modelElement = modelElement->NextSiblingElement("model");
    //        }
    //        FileManager::CloseFile(file);
    //        return true;
    //    }

    //    FileManager::CloseFile(file);
    //    return false;
    //}

    void ModelManager::DeInitialize()
    {
        //STLMAP_DELETE(ModelManager::instance().m_models);
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

	void ModelManager::RegisterModel(UString id, IModel* model)
	{
		ModelManager& _manager = ModelManager::instance();

		_manager.m_models[id] = model;
	}

    std::vector<IModel*> ModelManager::ActiveModels()
    {
        ModelManager& _manager = ModelManager::instance();

        std::vector<IModel*> models;

        ModelMap::iterator it = _manager.m_models.begin();
        for (it; it != _manager.m_models.end(); it++)
            models.push_back(it->second);

        return models;
    }
}
