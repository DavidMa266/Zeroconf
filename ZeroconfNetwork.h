//
//  ZeroconfNetwork.h
//  CUGL
//
//  Created by David Ma on 4/1/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef ZeroconfNetwork_h
#define ZeroconfNetwork_h

#include <string>

#define DEFAULT_DOMAIN "local."
#define DEFAULT_TYPE "_YourService._tcp"
#define DEFAULT_NAME "YourName1"

class ZeroconfNetwork {
    
protected:
    int portNum;
    std::string domainName;
    std::string typeName;
    std::string networkName;
    
public:
    void setPortNumber(int newPortNumber) {portNum = newPortNumber;};
    void setDomainName(std::string newDomainName) {domainName = newDomainName;};
    void setTypeName(std::string newTypeName) {typeName = newTypeName;};
    void setNetworkName(std::string name) {networkName = name;};
    
    virtual void advertiseNetwork() = 0;
    virtual void stopAdvertising() = 0;
    
    ZeroconfNetwork(): domainName(DEFAULT_DOMAIN), typeName(DEFAULT_TYPE), networkName(DEFAULT_NAME), portNum(-1){};
    ZeroconfNetwork(int portNum): domainName(DEFAULT_DOMAIN), typeName(DEFAULT_TYPE), networkName(DEFAULT_NAME), portNum(portNum){}
    ZeroconfNetwork(std::string domain, std::string service, std::string name, int portNum) : domainName(domain), typeName(service), networkName(name), portNum(portNum){};
    virtual ~ZeroconfNetwork() {};
};


#endif /* ZeroconfNetwork_h */
