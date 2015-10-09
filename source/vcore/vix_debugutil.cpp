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

#include <vix_debugutil.h>

namespace Vixen {

	UString DebugTimeStamp()
	{
		using namespace std::chrono;
		USStream ss;

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
