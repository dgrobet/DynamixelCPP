//
//  main.cpp
//  DynamixelCpp
//
//  Created by damien grobet on 12/05/15.
//  Copyright (c) 2015 damien grobet. All rights reserved.
//

#include <iostream>
#include "Dynamixel.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    char a;
    int count =0;
    int Positions[2]={0,1023};
    
    Dynamixel* sdyn = new Dynamixel("/dev/cu.usbserial-A4012ABX", 9600);
    while(a!='q')
    {
        sdyn->moveToPosition(3, Positions[count%2]);
        count ++;
        std::cin>>a;
    }
    
    delete sdyn;
    return 0;
}
