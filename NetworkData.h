//
//  NetworkData.h
//  CUGL
//
//  Created by David Ma on 4/18/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef NetworkData_h
#define NetworkData_h

#include <string>

//Class to hold the hostname and port.
//Take it and use it to connect to things.


class NetworkData {
public:
    std::string hostname;
    std::string name;
    int portNum;

    NetworkData(std::string hostname, std::string name, int portNum) : hostname(hostname), name(name), portNum(portNum){};
};

#endif /* NetworkData_h */
