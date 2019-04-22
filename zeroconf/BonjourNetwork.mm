//
//  BonjourNetwork.mm
//  CUGL
//
//  Created by David Ma on 4/16/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "BonjourNetwork.h"
#include "BonjourNetworkDelegate.h"


void advertise(NSString* domainName, NSString* typeName, NSString* networkName, int portNum, void** network){
    printf("Beginning the advertisement\n");
    
    if(portNum <= -1) {
        perror("Invalid port number.");
        exit(1);
    }
    
    NSNetService *netService;
    BonjourNetworkDelegate *netDelegate = nil;
    
    netService = [[NSNetService alloc] initWithDomain:domainName type:typeName name:networkName port:portNum];
    netDelegate = [[BonjourNetworkDelegate alloc] init];
    *network = (void*) CFBridgingRetain(netService);
    [netService setDelegate:netDelegate];
    [netService publish];
}

void BonjourNetwork::advertiseNetwork() {
    NSString *domain = @(domainName.c_str());
    NSString *type = @(typeName.c_str());
    NSString *name = @(networkName.c_str());
    advertisingThread = new std::thread(advertise, domain, type, name, portNum, &network);
}

void BonjourNetwork::stopAdvertising() {
    NSNetService *ns = CFBridgingRelease(network);
    [ns stop];
    advertisingThread->join();
}

BonjourNetwork::~BonjourNetwork(){
    if (advertisingThread != NULL){
        delete advertisingThread;
    }
}
