//
//  BonjourNetworkClient.h
//  CUGL
//
//  Created by David Ma on 4/16/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef BonjourNetworkClient_h
#define BonjourNetworkClient_h

#include "ZeroconfNetworkClient.h"
#include <thread>
#include <vector>
#include "NetworkData.h"

class BonjourNetworkClient : public ZeroconfNetworkClient {
    
private:
    std::thread *discoveryThread = NULL;
    std::vector<NetworkData> *serviceData = NULL;
    void *browser = NULL;
    
public:
    void discoverNetwork();
    void stopDiscovering();
    NetworkData getHostnameAndPort(std::string networkName);
    
    BonjourNetworkClient(): ZeroconfNetworkClient(){
        this->serviceData = new std::vector<NetworkData>();
    };
    BonjourNetworkClient(std::string domainName, std::string service): ZeroconfNetworkClient(domainName, service){
        this->serviceData = new std::vector<NetworkData>();
    };
    
    ~BonjourNetworkClient();
};


#endif /* BonjourNetworkClient_h */
