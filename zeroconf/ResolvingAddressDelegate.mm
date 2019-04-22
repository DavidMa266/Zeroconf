//
//  ResolvingAddressDelegate.m
//  CUGL
//
//  Created by David Ma on 4/18/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ResolvingAddressDelegate.h"


@implementation ResolvingAddressDelegate


-(void) setDataVector:(std::vector<NetworkData> *)vec
{
    self.serviceDataVector = vec;
}


- (void) netServiceDidResolveAddress:(NSNetService *)sender
{
    NSLog(@"Addresses have been resolved\n");
    std::string name = std::string([[sender name] UTF8String]);
    std::string hostname = std::string([[sender hostName] UTF8String]);
    int port = (int) [sender port];
    NetworkData data(hostname, name, port);
    
    //We need to lock this
    self.serviceDataVector->push_back(data);
    
    printf("Current size of our vector thing: %d\n", self.serviceDataVector->size());
    NSLog(@"Hello from ResolvingAddressDelegate: %@, %@\n", [sender name], [sender hostName]);
}

- (void) netService:(NSNetService *) ns didNotResolve:(NSDictionary *) error
{
    printf("Failed to resolve address\n");
    //Does nothing, I guess?
}
@end
