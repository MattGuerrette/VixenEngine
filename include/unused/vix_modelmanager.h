/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIX_MODELMANAGER_H
#define VIX_MODELMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_containers.h>
#include <vix_model.h>

namespace Vixen {

    class VIX_API ModelManager : public Singleton<ModelManager>
    {
        typedef std::map<UString, IModel*> ModelMap;
    public:
<<<<<<< HEAD:include/vgame/vix_modelmanager.h


        static bool    Initialize();
=======
       
        
        //static bool    Initialize();
>>>>>>> 7e4502b797e001a298b2a224c9fc4b4dcc75a61d:include/unused/vix_modelmanager.h
        static void    DeInitialize();
		static void	   RegisterModel(UString id, IModel* model);
        static IModel* AccessModel(UString id);
        static std::vector<IModel*> ActiveModels();

    private:
        ModelMap m_models;
    };

}

#endif
