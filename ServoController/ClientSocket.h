/* 
 * File:   ClientSocket.h
 * Author: wessel
 *
 * Created on May 12, 2014, 10:10 AM
 */

#ifndef CLIENTSOCKET_H
#define	CLIENTSOCKET_H

#include "Socket.h"

class ClientSocket : private Socket {
public:

    ClientSocket(std::string host, int port);

    virtual ~ClientSocket() {
    };

    const ClientSocket& operator <<(const std::string&) const;
    const ClientSocket& operator >>(std::string&) const;

};

#endif	/* CLIENTSOCKET_H */

