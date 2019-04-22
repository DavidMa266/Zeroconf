//
//  ZeroconfNetworkDelegate.m
//  cugl-mac
//
//  Created by David Ma on 4/7/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BonjourNetworkDelegate.h"

@implementation BonjourNetworkDelegate


//TODO: Actual proper error logging
//TODO: code to handle letting the server gracefully quit
- (void)netService: (NSNetService *) ns didNotPublish:(NSDictionary *)errorDict
{
    printf("Failed to publish the service\n");
}

- (void) netServiceDidPublish:(NSNetService *) ns
{
    printf("Successfully published Service\n");
}

- (void) netServiceWillPublish:(NSNetService *)ns
{
    printf("Ready to publish\n");
}

- (void) netServiceDidResolveAddress:(NSNetService *)sender
{
    NSLog(@"Addresses have been resolved\n");
}

- (void) netService:(NSNetService *) ns didNotResolve:(NSDictionary *) error
{
    printf("Failed to resolve address\n");
}

- (void) netServiceWillResolve:(NSNetService *) ns
{
    NSLog(@"Currently resolving: %@, %@\n", [ns name], [ns hostName]);
}
@end
