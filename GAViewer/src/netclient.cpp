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
#include "netclient.h"

netClient::netClient() {
	m_socket = -1;
	m_name = "unknown ip";
}

netClient::netClient(int socket) {
	m_socket = socket;
	m_name = "unknown ip";
}

netClient::netClient(int socket, std::string name) {
	m_socket = socket;
	m_name = name;
}

netClient::~netClient() {
}

netClient::netClient(const netClient& C) {
	m_socket = C.m_socket;
	m_readBuffer = C.m_readBuffer;
	m_sendBuffer = C.m_sendBuffer;
	m_name = C.m_name;
}

netClient &netClient::operator=(const netClient&C) {
	if (this != &C) {
		m_socket = C.m_socket;
		m_readBuffer = C.m_readBuffer;
		m_sendBuffer = C.m_sendBuffer;
		m_name = C.m_name;
	}
	return *this;
}
