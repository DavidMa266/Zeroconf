//
//  BonjourNetwork.h
//  CUGL
//
//  Created by David Ma on 4/16/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef BonjourNetwork_h
#define BonjourNetwork_h

#include "ZeroconfNetwork.h"
#include <thread>

class BonjourNetwork : public ZeroconfNetwork {
    
private:
    void *network;
    std::thread *advertisingThread = NULL;
    
public:
    void advertiseNetwork();
    void stopAdvertising();
    
    BonjourNetwork(): ZeroconfNetwork() {};
    BonjourNetwork(int port): ZeroconfNetwork(port) {} ;
    BonjourNetwork(std::string newDomainName, std::string newTypeName, std::string newNetworkName, int port): ZeroconfNetwork(newDomainName, newTypeName, newNetworkName, port) {};
    
    ~BonjourNetwork();
    
};
#endif /* BonjourNetwork_h */
