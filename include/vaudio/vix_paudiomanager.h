/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

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

#ifndef VIX_PAUDIOMANAGER_H
#define VIX_PAUDIOMANAGER_H

#include <vix_platform.h>
#include <vix_manager.h>
#include <vix_portaudio.h>
#include <vix_sndfile.h>

namespace Vixen {

	class VIX_API PAudioStream
	{
	public:
		PAudioStream();

		~PAudioStream();

	private:
		PaStream* m_stream;
	};

	class VIX_API PAudioManager
	{
		typedef std::vector<SNDFILE_DATA*> SoundList;
	public:
		PAudioManager(void);

		~PAudioManager(void);

		void Init();
		void Load(const UString& file);
		void Term();
		void Play(size_t index);
		void Stop();

	private:
		SoundList  m_sounds;
		PaStream*  m_stream;
	};

}

#endif
