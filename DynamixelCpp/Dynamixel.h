//
//  Dynamixel.h
//  DynamixelCpp
//
//  Created by damien grobet on 12/05/15.
//  Copyright (c) 2015 damien grobet. All rights reserved.
//

#ifndef __DynamixelCpp__Dynamixel__
#define __DynamixelCpp__Dynamixel__

#include <stdio.h>
#include <iostream>
#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <string>
#include <boost/thread.hpp>

class Dynamixel{

public:
    Dynamixel(const char* dev_name,int baudrate);
    ~Dynamixel();
    void writeSome();
    void writeWord(int ID, int Address, int Value);
    void moveToPosition(unsigned char ID, int Pos);
private:
    boost::asio::io_service m_io;
    boost::asio::serial_port m_port;
    unsigned char mReadMsg[512];
    enum INSTRUCTIONS{
        PING = 1,
        READ = 2,
        WRITE = 3,
        REG_WRITE = 4,
        ACTION = 5,
        RESET = 6,
        SYNC_WRITE = 131
    };
    
    void readSome();
    void sendPacket(std::vector<unsigned char>* Packet);
    void handler(const boost::system::error_code& error, size_t bytes_transferred);
    
    std::vector<unsigned char>* constructPacket(unsigned char ID, unsigned char Address,unsigned char Instruction, int value);

};

#endif /* defined(__DynamixelCpp__Dynamixel__) */
