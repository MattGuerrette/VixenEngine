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

#ifndef VIX_RAKNET_H
#define VIX_RAKNET_H

#include <RakNetTypes.h>
#include <RakPeerInterface.h>
#include <RakSleep.h>
#include <RakAssert.h>
#include <RakNetStatistics.h>
#include <BitStream.h>
#include <Gets.h>
#include <MessageIdentifiers.h>


/*CREDIT:
*
* Following code was found as part of the RakNet samples
* included with source. [ChatClient/ChatServer sample]
*/
inline unsigned char
RAKNET_GetPacketIdentifier(RakNet::Packet* packet)
{
	if (!packet)
		return 255;
	if ((unsigned char)packet->data[0] == ID_TIMESTAMP)
	{
		RakAssert(packet->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char)packet->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else {
		return (unsigned char)packet->data[0];
	}
}

#endif
