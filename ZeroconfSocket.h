//
//  ZeroconfSocket.h
//  CUGL
//
//  Created by David Ma on 4/1/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef ZeroconfSocket_h
#define ZeroconfSocket_h


#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include <thread>

/**
    This class is meant to represent the socket where we begin listening for other connections. This is meant to hold things related to the standard TCP socket server.
 **/
class ZeroconfSocket {
    
    int socketType;     //SOCK_STREAM or SOCK_DATAGRAM (TCP/UDP)
    int socketfd;       //Socketfd
    struct sockaddr_in addr;
    std::vector<int> allConnections;   //List of all sockets that have connected to use
    
    void beginListening();      //Starts listening on the socket
    void beginAccepting();      //Starts accepting clients
    std::thread *acceptingThread;
    int shutdown = 0;
    
public:
    int portNum;        //For passing to Bonjour, so they know which port this thing lives on.
    void createSocket();                    //Creates a socket, and binds it
    void beginListeningAndAccepting();      //Starts listening on the socket, accepting all
    
    ZeroconfSocket();
    ZeroconfSocket(int type);
    ~ZeroconfSocket();
    
} ;


#endif /* ZeroconfSocket_h */
