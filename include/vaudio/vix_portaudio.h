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

#ifndef VIX_PORTAUDIO_H
#define VIX_PORTAUDIO_H

#include <vix_platform.h>
#include <portaudio.h>
#include <stdlib.h>
#include <vix_stringutil.h>

/*PORTAUDIO DEFINES*/
#define PAUDIO_SAMPLERATE   44100
#define PAUDIO_SLEEPSECONDS 2

struct PAUDIO_FILE
{
	PaStream*	stream;
	const char*	name;
};

/*
*
*	PAUDIO_Callback
*
*/
VIX_API
int PAUDIO_Callback(const void* input,
					void* output,
					unsigned long frameCnt,
					const PaStreamCallbackTimeInfo* paTimeInfo,
					PaStreamCallbackFlags statusFlags,
					void* userData);


/*
*	PAUDIO_Error
*	Checks for PortAudio error and outputs
*   error string.
*   returns true if error
*   return false if no error
*/
VIX_API
bool PAUDIO_Error(PaError err);

/*
*	PAUDIO_Init
*	Initializes PortAudio
*
*	Called on application startup
*/
VIX_API
bool PAUDIO_Init();

/*
*	PAUDIO_Term
*	Terminates PortAudio
*
*	Called on application exit
*/
VIX_API
bool PAUDIO_Term();

/*
*	PAUDIO_QueryDevices
*	Queries physical audio devices and outputs
*   information for each device.
*
*/
VIX_API
void PAUDIO_QueryDevices();

VIX_API
void PAUDIO_QueryDevices(USStream& stream);

/*
*   PAUDIO_Sleep
*
*   Sleeps PortAudio caller for PAUDIO_SLEEPSECONDS
*
*/
VIX_API
void PAUDIO_Sleep();

/*
*	PAUDIO_PrintDevice
*	Prints information about specified device
*
*/
VIX_API
void PAUDIO_PrintDevice(const PaDeviceInfo* dInfo, size_t i);

VIX_API
void PAUDIO_PrintDevice(USStream& stream, const PaDeviceInfo* dInof, size_t i);


VIX_API
void PAUDIO_OpenDefaultStream(PaStream** stream,
							  int inChannels,
							  int outChannels,
							  PaSampleFormat format,
							  double sampleRate,
							  unsigned long frameCnt,
							  void* data);



VIX_API
bool PAUDIO_CloseStream(PaStream* stream);

#endif
