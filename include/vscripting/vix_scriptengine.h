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

#ifndef VIX_SCRIPTENGINE_H
#define VIX_SCRIPTENGINE_H

#include <vix_platform.h>
#include <vix_errglobals.h>
#include <vix_stringutil.h>
#include <vix_noncopy.h>

namespace Vixen {

	class VIX_API IScriptEngine : INonCopy
	{
	public:
		virtual ~IScriptEngine() { }

        virtual bool    VInitialize() = 0;
        virtual bool    VDeInitialize() = 0;

		virtual ErrCode VExecuteFile(const UString& path) = 0;
		virtual ErrCode VExecuteExpression(const UString& expression) = 0;
	};

}

#endif
