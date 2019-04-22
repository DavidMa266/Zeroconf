//
//  BonjourNetworkClient.m
//  CUGL
//
//  Created by David Ma on 4/16/19.
//  Copyright © 2019 Game Design Initiative at Cornell. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "BonjourNetworkClient.h"
#include "BonjourNetworkClientDelegate.h"



//This is run in a separate thread.
//We create a delegate and let it handle our events
//
void discover(NSString *serviceName, NSString *domainName, void** browser, std::vector<NetworkData> *serviceData){
    
    NSNetServiceBrowser *nsb = [[NSNetServiceBrowser alloc] init];
    BonjourNetworkClientDelegate *z = [[BonjourNetworkClientDelegate alloc] init];
    
    *browser = (void*) CFBridgingRetain(nsb);
    [z setDataVector:serviceData];
    
    [nsb setDelegate:z];
    [nsb searchForServicesOfType:serviceName inDomain:domainName];
    printf("Searching for services\n");
    [[NSRunLoop currentRunLoop] run];
    printf("We have finished the run loop\n");
    
    [serviceName autorelease];
    [domainName autorelease];
    [nsb autorelease];
    [z autorelease];
}





//Function takes the target service name and domain, then starts up a new thread
//Creating a NSNetserviceBrowser object and starting its run loop
//Data is sent to serviceHostnames and updated when the delegate gets a new service
//This is done so we can have a map of existing hostnames we can pick and choose from
void BonjourNetworkClient::discoverNetwork() {
    NSString *serviceName = @(typeName.c_str());
    NSString *domain = @(domainName.c_str());
    discoveryThread = new std::thread(discover, serviceName, domain, &browser, this->serviceData);
}

void BonjourNetworkClient::stopDiscovering(){
    if(browser != NULL){
        NSNetServiceBrowser *nsb = CFBridgingRelease(browser);
        [nsb stop];
        [nsb autorelease];
        discoveryThread->join();
        delete discoveryThread;
        discoveryThread = NULL;
        browser = NULL;
    }
}

NetworkData BonjourNetworkClient::getHostnameAndPort(std::string networkName){
    return NetworkData("hello", "goodbye:", 0);
}

BonjourNetworkClient::~BonjourNetworkClient(){
    printf("Shutting down completely\n");
    if(discoveryThread != NULL){
        discoveryThread->join();
        delete discoveryThread;
    }
    if(browser != NULL){
        NSNetServiceBrowser *nsb = CFBridgingRelease(browser);
        [nsb stop];
        [nsb autorelease];
    }
    
}
