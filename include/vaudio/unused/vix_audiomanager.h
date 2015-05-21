/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

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

#ifndef VIX_AUDIOMANAGER_H
#define VIX_AUDIOMANAGER_H

#include <vix_platform.h>
#include <vix_manager.h>
#include <vix_singleton.h>
#include <vix_fmod.h>
#include <vix_soundclip.h>
#include <map>

namespace Vixen {

	class VIX_API AudioManager : public IManager
	{
		//friend class Singleton <AudioManager>;

		typedef std::map<UString, SoundClip*> SoundMap;

		const int MAX_CHANNELS = 100;

	public:
		/*constructor (NOTE: intialization occurs in VStartUp()*/
		AudioManager();

		/*desturctor (NOTE: destruction occurs in VShutDown()*/
		~AudioManager();

		/*retrieve FMOD sound system object*/
		FMOD::System* const System();

		/*Initialize AudioManager*/
		ErrCode VStartUp()  override;

		/*Destruct AudioManager*/
		ErrCode VShutDown() override;

		/*create sound*/
		void CreateSound(const UString& path);

	private:
		FMOD::System* m_system;
		SoundMap      m_sounds;
	};
}

#endif
