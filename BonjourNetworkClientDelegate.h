//
//  ZeroconfNetworkClientDelegate.h
//  CUGL
//
//  Created by David Ma on 4/9/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef ZeroconfNetworkClientDelegate_h
#define ZeroconfNetworkClientDelegate_h
#include <vector>
#include <string>
#include "NetworkData.h"

@interface BonjourNetworkClientDelegate : NSObject <NSNetServiceBrowserDelegate>
{
}

- (void) setDataVector: (std::vector<NetworkData> *) vec;

@property std::vector<NetworkData> *serviceDataVector;

@end


#endif /* ZeroconfNetworkClientDelegate_h */
