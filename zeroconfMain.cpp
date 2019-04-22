//
//  zeroconfMain.cpp
//  HelloWorld (Mac)
//
//  Created by David Ma on 4/7/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#include <stdio.h>
#include <cugl/ZeroconfNetwork.h>
#include <cugl/ZeroconfSocket.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    ZeroconfSocket *socket = new ZeroconfSocket();
    socket->createSocket();
    ZeroconfNetwork *network = new ZeroconfNetwork(socket->portNum);
    network->advertiseNetwork();
    socket->beginListeningAndAccepting();
    
    while(true){
        usleep(1000000);
        printf("hello from the main thread\n");
    }
    
}
