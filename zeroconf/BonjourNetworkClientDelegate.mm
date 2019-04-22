//
//  ZeroconfNetworkClientDelegate.m
//  CUGL
//
//  Created by David Ma on 4/9/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BonjourNetworkClientDelegate.h"
#import "ResolvingAddressDelegate.h"

#include <vector>
@implementation BonjourNetworkClientDelegate

-(id) init {
    self = [super init];
    return self;
}

-(void) setDataVector:(std::vector<NetworkData> *)vec
{
    self.serviceDataVector = vec;
}


//A service has been found. We should save the information that lets us connect to
- (void) netServiceBrowser:(NSNetServiceBrowser *)browser didFindService:(NSNetService *)service moreComing:(BOOL)moreComing {
    
    ResolvingAddressDelegate *rad = [[ResolvingAddressDelegate alloc] init];
    [rad setDataVector:self.serviceDataVector];
    
    NSString * name = [service name];
    NSString *type = [service type];
    NSString * domain = [service domain];
    int port = (int) [service port];
    NSNetService *ns = [[NSNetService alloc] initWithDomain:domain type:type name:name port:port];
    
    [ns setDelegate:rad];
    [ns resolveWithTimeout:5.0];
    
    [name autorelease];
    [type autorelease];
    [domain autorelease];
    
    NSLog(@"We have found the service: %@, %@\n", [service name], [service hostName]);
}




- (void) netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveService:(nonnull NSNetService *)service moreComing:(BOOL)moreComing{
    //No need to go find the hostname, since we have the service name. We can just remove it here I guess
    std::string name = std::string([[service name] UTF8String]);
    
    std::vector<NetworkData>::iterator it = self.serviceDataVector->begin();
    
    while( it != self.serviceDataVector->end()){
        if ((*it).name.compare(name) == 0){
            it = self.serviceDataVector->erase(it);
        }
        else{
            ++it;
        }
    }
    
    printf("Current size of our vector thing: %d\n", self.serviceDataVector->size());
    //Iterate through the serviceVector and find the thing that matches the hostname then delete it
    NSLog(@"We have removed the service: %@, %@\n", [service name], [service hostName]);
}







- (void) netServiceBrowser:(NSNetServiceBrowser *)browser didFindDomain:(NSString *)domainString moreComing:(BOOL)moreComing {
    NSLog(@"Found the domain: %@\n", domainString);
}


- (void) netServiceBrowser:(NSNetServiceBrowser *)browser didRemoveDomain:(nonnull NSString *)domainString moreComing:(BOOL)moreComing{
    NSLog(@"Removed the domain: %@\n", domainString);
}

- (void) netServiceBrowser:(NSNetServiceBrowser *)browser didNotSearch:(NSDictionary<NSString *,NSNumber *> *)errorDict {
    NSLog(@"A failure has occurred\n");
}

- (void) netServiceBrowserWillSearch:(NSNetServiceBrowser *)browser {
    NSLog(@"We are beginning to search\n");
}

- (void) netServiceBrowserDidStopSearch:(NSNetServiceBrowser *)browser{
    NSLog(@"We have stopped the search\n");
}


@end
