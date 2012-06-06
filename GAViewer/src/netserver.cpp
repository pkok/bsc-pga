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

#include "netserver.h"
#include "state.h"
#include "object.h"


void state::closeNetServers() {
	for (int i = 0; i < m_nbNetServers; i++)
		if (m_netServers[i]) delete m_netServers[i];
	free(m_netServers);
	m_netServers = NULL;
	m_nbNetServers = 0;
}

void state::openNetServer(const char *port) {
	netServer *N = NULL;
	try {
		N = new netServer(port);
	} catch (int) {
		return;
	}
	m_nbNetServers++;
	m_netServers = (netServer**)realloc(m_netServers, m_nbNetServers * sizeof(netServer*));
	m_netServers[m_nbNetServers-1] = N;
}

void state::pollNetServers() {
	if (m_nbNetServers == -1) {
		m_nbNetServers = 0;
		openNetServer(m_defaultNetPort.c_str());
	}

	// send message to all (contains variable changes in ASCII text):
	if (m_netVarChanges.size()) {
		std::string netMessage = createNetMessage(m_netVarChanges);
		for (int i = 0; i < m_nbNetServers; i++)
			m_netServers[i]->sendMessage(netMessage);
		m_netVarChanges.clear();
	}

	for (int i = 0; i < m_nbNetServers; i++)
		if (m_netServers[i]) 
			m_netServers[i]->poll();
}

void state::closeNetServer(const char *_port) {
	int port = atoi(_port);
	for (int i = 0; i < m_nbNetServers; i++) {
		if (m_netServers[i] && (m_netServers[i]->getListenPort() == port)) {
			delete m_netServers[i];
			m_netServers[i] = m_netServers[m_nbNetServers];
			m_nbNetServers--;
			return;
		}
	}
	cprintf("No server listening on port %s", _port);
}

void state::displayNetStatus() {
	if (m_nbNetServers == 0) {
		cprintf("Network connections disabled; use add_net_port(port#) to start listening on port#. ");
	}
	else {
		for (int i = 0; i < m_nbNetServers; i++) {
			if (m_netServers[i])
				m_netServers[i]->displayNetStatus();
		}
	}
}

std::string state::createNetMessage(const std::set<std::string> &names) {
	std::string msg;
	for (std::set<std::string>::const_iterator I = names.begin();
		I != names.end(); I++) {
		object *ptr = getObjectPtrByName(*I);
		if (ptr) {
			std::string objectStr = ptr->toString("%2.15e");
			if (objectStr.length() > 0) {
				msg.append(objectStr);
				msg.append((ptr->m_drawMode & OD_HIDE) ? ";$" : ",$");
			}
		}
	}
	return msg;
}


netServer::netServer(const char *listenPortString) {
	int errcode;
	struct sockaddr_in ListenAddress;
#ifndef WIN32
	int reuseaddr = 1;
#endif

	m_listenPort = atoi(listenPortString);
	if ((m_listenPort < 1) || (m_listenPort > 65535)) {
		cprintf("netServer::netServer(): invalid port %s\n", listenPortString);
		throw -1;
	}

	if ( (errcode = net::netInit()) < 0) throw -1;

	/* set up listen socket for connection */
	if ( (m_listenSocket  = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		cprintf("netServer::netServer(): could not create server socket on port %s\n", listenPortString);
		throw -1;
	}
	
	/* set SO_REUSEADDR option */
#ifndef WIN32
	setsockopt(m_listenSocket , SOL_SOCKET, SO_REUSEADDR, (void*)&reuseaddr, sizeof(int));
#endif

	/* set up address and bind socket */
	memset((void*)&ListenAddress, 0, sizeof(ListenAddress));
	ListenAddress.sin_family = AF_INET;
	ListenAddress.sin_addr.s_addr = htonl(INADDR_ANY);	
	ListenAddress.sin_port = htons((short)m_listenPort);
	if (bind(m_listenSocket , (struct sockaddr *)&ListenAddress, sizeof(ListenAddress)) == -1) {
		net::closeSocket(&(m_listenSocket ));
		cprintf("netServer::netServer(): could not bind server socket.\n");
		throw -1;
	}

	/* listen  */
	if (listen(m_listenSocket , SOMAXCONN) == -1) {
		net::closeSocket(&(m_listenSocket ));
		cprintf("Could not listen() server socket %s\n", listenPortString);
		throw -1;
	}

	/* 
	If we arrive here all went well.
	We won't accept() connections on the server socket until poll()
	*/	
	cprintf("Server socket setup correctly at port %d\n", m_listenPort);
}

netServer::~netServer() {
	// close clients . . .
	for (int i = 0; i < (int)m_clients.size(); i++) {
		net::closeSocket(&(m_clients[i].m_socket));
	}
	m_clients.clear();

	// close socket
	if (m_listenSocket >= 0)
		net::closeSocket(&m_listenSocket);

}

void netServer::sendMessage(const std::string &msg) {
	for (int i = 0; i < (int)m_clients.size(); i++) {
		m_clients[i].m_sendBuffer.append(msg);
	}

}


#define U_MAX(x, y) ( ((x) > (y)) ? (x) : (y))

int netServer::poll() {
	int i;
	fd_set readset;
	fd_set writeset;
	struct timeval tv;
	int errcode, maxfd = 0;

	/* sanity check */
	if (m_listenSocket  == -1) {
		cprintf("netServer::poll(): listen socket is invalid\n");
		return -1;
	}

	/* initialize the file descriptor sets */
	FD_ZERO(&readset);
	FD_ZERO(&writeset);

	/* add the listen socket to the read set */
	FD_SET((unsigned int)m_listenSocket , &readset);
	maxfd = U_MAX(maxfd, m_listenSocket );

	/* add all client sockets for read and write (set for write only if required...) */
	for (i = 0; i < (int)m_clients.size(); i++) {
		/* sanity check */
		if (m_clients[i].m_socket == -1) continue;	/* should never happen */

		/* set for reading */
		FD_SET((unsigned int)m_clients[i].m_socket, &readset);
		maxfd = U_MAX(maxfd, m_clients[i].m_socket);

		/* set for writing if required */
		if (m_clients[i].m_sendBuffer.length())
			FD_SET((unsigned int)m_clients[i].m_socket, &writeset);
	}
	
	/* setup the timeout struct */
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	/* do the select call */
	errcode = select(maxfd +1, &readset, &writeset, NULL, &tv);

	if (errcode == 0) return -1; /* nothing is ready for anything.... */
	else if (errcode == -1) {		/* an error occured */
		cprintf("netServer::poll(): select() failed\n");
		return -1;
	}
	else {	/* find all sockets which are ready for reading/writing */
		/* listen port ready for accept()? */
		if (FD_ISSET((unsigned int)m_listenSocket , &readset)) {
			/* keep accepting clients */
			errcode = acceptClient();
			/* what to do? */
		}

		/* check every client for reading & writing */
		for (i = 0; i < (int)m_clients.size(); i++) {
			/* sanity check */
			if (m_clients[i].m_socket == -1) {
				continue;	/* should never happen */
			}

			/* check for reading */
			if (FD_ISSET((unsigned int)m_clients[i].m_socket, &readset) ||
			    FD_ISSET((unsigned int)m_clients[i].m_socket, &writeset)) {
				if (pollClient(i) < 0)
					m_clients[i].m_socket = -1;
			}
		}
	}

	// get rid of invalid clients:
	for (i = 0; i < (int)m_clients.size(); i++) {
		if (m_clients[i].m_socket < 0) {
				m_clients[i] = m_clients[m_clients.size()-1];
				m_clients.resize(m_clients.size()-1);
				i--;
		}
	}
	return 0;
}

int netServer::acceptClient() {
	int errcode, nodelay = 1;
	struct sockaddr clientAddress;
	#ifdef WIN32
	int addressLength = sizeof(clientAddress);
	#else
	socklen_t addressLength = sizeof(clientAddress);
	#endif
	int clientSocket;
	char *clientName;

	/* accept a new client */
	clientSocket = accept(m_listenSocket , &clientAddress, &addressLength);
	if (clientSocket == -1) return -1;

	clientName = inet_ntoa(((struct sockaddr_in*)&clientAddress)->sin_addr);
	cprintf("Accepted network connection from %s\n", clientName);

	/* set socket to non-blocking */
	if ( (errcode = net::setSocketNonBlocking(clientSocket)) < 0) {
		cprintf("netServer::acceptClient(): non-fatal error: could not set client socket to non-blocking (closing connection to client)\n");
		net::closeSocket(&clientSocket);
		return 0;
	}

	/* disable nagle algorithm */
	if ( (errcode = net::disableSocketNagle(clientSocket)) < 0) {
		cprintf("netServer::acceptClient(): non-fatal error: could not disable Nagle algorithm (closing connection to client)\n");
		net::closeSocket(&clientSocket);
		return 0;
	}

	m_clients.push_back(netClient(clientSocket, clientName));

	/* send a message to the client containing all current variables */
	//createNetMessage
	{
		std::set<std::string> objectNames;
		for (state::COI I = g_state->m_objects.begin(); I != g_state->m_objects.end(); I++) {
			objectNames.insert(*(I->first).ptr);
		}
		std::string message = g_state->createNetMessage(objectNames);
		m_clients[m_clients.size()-1].m_sendBuffer.append(message);
	}

	return 0;
}

int netServer::pollClient(int idx) {
	int errCode;
	if ( (errCode = recvClient(idx)) < 0) return errCode;
	if ( (errCode = sendClient(idx)) < 0) return errCode;
	return 0;
}

int netServer::recvClient(int idx) {
	const int bufLen = 1024;
	char buf[bufLen+1];

	int n;
	do {
		n = recv(m_clients[idx].m_socket, buf, bufLen, 0);
		if ((n == 0) || ((n < 0) && !net::socketWouldBlock())) {
			cprintf("socket error during recv() message type (probably just 'connection closed')\n");
			net::closeSocket(&(m_clients[idx].m_socket));
			return -1;
		}
		if (n > 0) {
			buf[n] = 0;
			m_clients[idx].m_readBuffer.append(buf);
		}
	} while ((n == bufLen) && (m_clients[idx].m_readBuffer.length() < 64 * 1024)); // arbitrary anti-overflow threshold

	return processClientCommands(idx);
}

int netServer::processClientCommands(int idx) {
	int i = 0, j = 0;

	while ( (i = m_clients[idx].m_readBuffer.find('$', j)) != std::string::npos) { // todo : '$' -> 0
		std::string cmd = m_clients[idx].m_readBuffer.substr(j, i - j);
		
	
		if (g_state->m_displayNetworkCommands) {
		   char *cmdcstr = strdup(cmd.c_str());
			cprintf("// command from %s:\n", m_clients[idx].m_name.c_str());
			cprintf("// %s\n", cmdcstr);
			free(cmdcstr);
		}

		g_state->consoleCommandCallback(cmd.c_str());

		j = i+1;
	}

	m_clients[idx].m_readBuffer.erase(0, j);
	if (m_clients[idx].m_readBuffer.length() > 64 * 1024) return -1; // overflow

	return 0;
}

int netServer::sendClient(int idx) {
	// todo: buf(Len)
	if (m_clients[idx].m_sendBuffer.length() == 0) return 0;

	int n = send(m_clients[idx].m_socket, m_clients[idx].m_sendBuffer.c_str(), m_clients[idx].m_sendBuffer.length(), 0);

	if (n < 0) {	/* either a block or an error */
		if (!net::socketWouldBlock()) {
			cprintf("error during send(), closing connection to client\n");
			net::closeSocket(&(m_clients[idx].m_socket));
			return -1;
		}
		else return 0;
	}
	else if (n == 0) {	/* connection closed */
		cprintf("connection to client closed\n");
			net::closeSocket(&(m_clients[idx].m_socket));
		return -1;
	}
	else {	/* wrote 'n' bytes */
		// so remove them from send buffer . . .
		m_clients[idx].m_sendBuffer.erase(0, n);
		return 0;
	}
}

void netServer::displayNetStatus() {
	cprintf("Listening on port %d\n", m_listenPort);
	for (int i = 0; i < (int)m_clients.size(); i++) {
		cprintf("Client connected from IP address: %s\n", m_clients[i].m_name.c_str());
	}
}


namespace net {
/* one function to close sockets on both windows and unix */
void closeSocket(int *sock) {
	if (*sock == -1) return;
#ifdef WIN32
	closesocket(*sock);
#else  /* UNIX */
	close(*sock);
#endif
	*sock = -1;
}

/* one function to set sockets to non-blocking on both windows and unix */
/* returns 0 on success, -1 on failure */
int setSocketNonBlocking(int sock) {
#ifdef WIN32
	u_long arg = 1;
	return ((ioctlsocket(sock, FIONBIO, &arg) != -1) ? 0 : -1);
#else  /* UNIX */
	int currentValue;
	if ( (currentValue = fcntl(sock, F_GETFL, 0)) == -1) return -1;
	if (fcntl(sock, F_SETFL, currentValue | O_NONBLOCK) == -1) return -1;
	return 0;
#endif
}

/* this function disables the  nagle algorithm for the given port */
int disableSocketNagle(int sock) {
	int nodelay = 1;
	if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(int))) {
		return -1;
	}
	return 0;
}

namespace {
	int s_netInitDone = 0;
}

int netInit() {
#ifdef WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int WSAerr; 
#endif

	if (s_netInitDone) return 0;
	s_netInitDone = 1;

	/* startup windows sockets */
#ifdef WIN32
	wVersionRequested = MAKEWORD( 2, 0 ); 
	WSAerr = WSAStartup( wVersionRequested, &wsaData );
	if ( WSAerr != 0 ) {
		cprintf("netInit(): an error occured during WSAStartup() (%d).\n", WSAerr);
		return -1;
	}
#endif /* WIN32 */
/* no init for UNIX required... */
	return 0;
}

bool socketWouldBlock() {
#ifdef WIN32
	return ((WSAGetLastError() == WSAEWOULDBLOCK) ? true : false);
#else
	return ((errno == EWOULDBLOCK) ? true : false);
#endif
}
} // end of namespace net
