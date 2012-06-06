// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2002-2009, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#ifndef _NET_SERVER_H_
#define _NET_SERVER_H_

#include <vector>
#include <string>

#ifdef WIN32
#include <winsock2.h>
#else // assume UNIX
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#endif 

#include "netclient.h"

namespace net {
	void closeSocket(int *sock);
	int setSocketNonBlocking(int sock);
	int disableSocketNagle(int sock);
	bool socketWouldBlock();

	int netInit(); // must be executed once before using network code on Win32
}

class netServer {
public:
	// can throw -1 on failure!
	netServer(const char *port = "6860"); // 6860 = 0x1acc = Jack
	~netServer();

	int poll();
	inline int getListenPort() {return m_listenPort;}

	void displayNetStatus();

	void sendMessage(const std::string &msg); // sends message to all clients

protected:
	std::vector<netClient> m_clients;

	int m_listenPort; // tcp port we are listening on
	int m_listenSocket; // tcp socket we are listening on

	int acceptClient();
	int pollClient(int idx); // idx points into m_clientSockets / m_clientReadBuffers
	int recvClient(int idx);
	int sendClient(int idx);
	int processClientCommands(int idx);

private:
};


#endif /* _NET_SERVER_H_ */
