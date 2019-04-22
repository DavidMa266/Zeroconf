//
//  ResolvingAddressDelegate.h
//  CUGL
//
//  Created by David Ma on 4/18/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#ifndef ResolvingAddressDelegate_h
#define ResolvingAddressDelegate_h


#include <string>
#include <vector>
#include "NetworkData.h"

@interface ResolvingAddressDelegate : NSObject <NSNetServiceDelegate>
{
}
- (void) setDataVector: (std::vector<NetworkData> *) vec;

@property std::vector<NetworkData> *serviceDataVector;

@end


#endif /* ResolvingAddressDelegate_h */
