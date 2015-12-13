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

#include <vix_debugutil.h>

namespace Vixen {

	std::string DebugTimeStamp()
	{
		using namespace std::chrono;
		std::stringstream ss;

		system_clock::time_point now_point = system_clock::now();
		std::time_t now_time = system_clock::to_time_t(now_point);


#ifdef VIX_SYS_WINDOWS
        tm pTime;
		localtime_s(&pTime, &now_time);
		char buffer[VIX_BUFSIZE];
		asctime_s(buffer, &pTime);
		ss << buffer;
#else
		ss << asctime(localtime(&now_time));
#endif

		return ss.str();
	}
}
