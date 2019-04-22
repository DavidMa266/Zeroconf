//
//  ZeroconfSocket.cpp
//  cugl-mac
//
//  Created by David Ma on 4/1/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include "ZeroconfSocket.h"

#define BACKLOG_SIZE 10


//Initialization of Main Socket
void ZeroconfSocket::createSocket() {
    socketfd = socket(PF_INET, socketType, 0);
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(0);
    
    if (bind(socketfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error in attempting to bind the socket");
        exit(1);
    }
    
    socklen_t len = sizeof(addr);
    if (getsockname(socketfd, (struct sockaddr *)&addr, &len) < 0) {
        perror("Error in creating socket");
        exit(1);
    }
    portNum = ntohs(addr.sin_port);
    printf("Listening on portnum %d\n", portNum);
}


void ZeroconfSocket::beginListening() {
    if(listen(socketfd, BACKLOG_SIZE) == -1) {
        perror("Error in listening");
        exit(2);
    }
}


//This is supposed to run in a separate thread. Loops forever until a flag is flipped.
void ZeroconfSocket::beginAccepting() {
    fd_set readFDs;
    fd_set master;
    FD_ZERO(&readFDs);
    FD_ZERO(&master);
    FD_SET(socketfd, &master);
    
    int fdmax = socketfd+1;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 500000;
    int nbytes;
    char buf[256];
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;
    
    for(;;){
        readFDs = master;
        
        if (select(fdmax+1, &readFDs, NULL, NULL, &tv) == -1) {
            perror("select");
            exit(3);
        }
        
        for (int i = 0; i <= socketfd; i++){
            if (FD_ISSET(i, &readFDs)){
                printf("Something is ready\n");
                if(i == socketfd){
                    int newfd = accept(socketfd, (struct sockaddr *) &remoteaddr, &addrlen);
                    if (newfd != -1){
                        FD_SET(newfd, &master);
                        if(newfd > fdmax){
                            fdmax = newfd;
                        }
                        allConnections.push_back(newfd);
                        printf("We have a new connection\n");
                        printf("We currently have %d connections.\n", allConnections.size());
                    } else {
                        perror("Failure on accept");
                    }
                }
                else{
                    if((nbytes = recv(i, buf, sizeof(buf), 0) <= 0)){
                        if (nbytes == 0){
                            printf("Server hung up.\n");
                        }
                        close(i);
                        FD_CLR(i, &master);
                    }
                    else{
                        for (int j = 0; j <= fdmax; j++){
                            if(FD_ISSET(j, &master)){
                                if(j != socketfd && j != i){
                                    send(j, buf, nbytes, 0);
                                }
                            }
                        }
                    }
                }
            }
        }
        
        if(shutdown == -1){
            break;
        }
    }
}

void ZeroconfSocket::beginListeningAndAccepting(){
    beginListening();
    acceptingThread = new std::thread(&ZeroconfSocket::beginAccepting, this);
}

ZeroconfSocket::~ZeroconfSocket(){
    shutdown = -1;
    acceptingThread->join();
    delete acceptingThread;
}


ZeroconfSocket::ZeroconfSocket(int type) {
    if(type != SOCK_STREAM || type != SOCK_DGRAM) {
        perror("Incorrect Type. Defaulting to TCP");
        type = SOCK_STREAM;
    }
    socketType = type;
    shutdown = 0;
}

ZeroconfSocket::ZeroconfSocket() {
    socketType = SOCK_STREAM;
    shutdown = 0;
}
