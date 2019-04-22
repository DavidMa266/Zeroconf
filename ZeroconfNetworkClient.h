//
//  ZeroconfNetworkClient.h
//  CUGL
//
//  Created by David Ma on 4/7/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef ZeroconfNetworkClient_h
#define ZeroconfNetworkClient_h

#define DOMAIN_NAME "local."
#define SERVICE_TYPE_NAME "_YourService._tcp."

#include <string>
#include <vector>

#include "NetworkData.h"

class ZeroconfNetworkClient{
    
protected:
    std::string domainName;
    std::string typeName;
    int portNum;
    
public:
    void setDomain(std::string name) {domainName = name;};
    void setType(std::string type) {typeName = type;};
    
    virtual void discoverNetwork() = 0;
    virtual void stopDiscovering() = 0;
    virtual NetworkData getHostnameAndPort(std::string name) = 0;
    
    ZeroconfNetworkClient(): domainName(DOMAIN_NAME), typeName(SERVICE_TYPE_NAME) {};
    ZeroconfNetworkClient(std::string domain, std::string service): domainName(domain), typeName(service){};
    virtual ~ZeroconfNetworkClient() {};
};
#endif /* ZeroconfNetworkClient_h */
