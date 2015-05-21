#ifndef VIX_NSERVER_H
#define VIX_NSERVER_H

#include <vix_platform.h>
#include <vix_raknet.h>

namespace Vixen {

	class VIX_API NServer
	{
	public:
		NServer();

		~NServer();

	private:
		RakNet::RakPeerInterface*  m_server;

	};

}

#endif
