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

#ifndef _NET_CLIENT_
#define _NET_CLIENT_

#include <string.h>
class netClient {
public:
	netClient();
	netClient(int socket);
	netClient(int socket, std::string name);
	netClient(const netClient&);
	~netClient();

	netClient &operator=(const netClient&);

	int m_socket;
	std::string m_readBuffer;
	std::string m_sendBuffer;
	std::string m_name;

};

#endif /* _NET_CLIENT_ */
