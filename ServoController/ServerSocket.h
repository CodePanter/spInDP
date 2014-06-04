/* 
 * File:   ServerSocket.h
 * Author: wessel
 *
 * Created on May 12, 2014, 10:02 AM
 */

#ifndef SERVERSOCKET_H
#define	SERVERSOCKET_H

#include "Socket.h"

class ServerSocket : private Socket {
public:

    ServerSocket(int port);

    ServerSocket() {
    };
    virtual ~ServerSocket();

    const ServerSocket& operator <<(const std::string&) const;
    const ServerSocket& operator >>(std::string&) const;

    void accept(ServerSocket&);

};

#endif	/* SERVERSOCKET_H */

