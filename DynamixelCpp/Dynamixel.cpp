//
//  Dynamixel.cpp
//  DynamixelCpp
//
//  Created by damien grobet on 12/05/15.
//  Copyright (c) 2015 damien grobet. All rights reserved.
//

#include "Dynamixel.h"

Dynamixel::Dynamixel(const char* dev_name,int baudrate):m_io(),m_port(m_io, dev_name){
    
    boost::asio::serial_port_base::baud_rate baud_option(baudrate);
    
    std::cout<< m_port.is_open() <<std::endl;
    m_port.set_option(baud_option);
    //m_io.run();
    
    //boost::thread t(boost::bind(&boost::asio::io_service::run, &m_io));
    
    
    //writeSome();
    
}

void Dynamixel::readSome(){
    
    //m_port.read_some(boost::asio::buffer(mReadMsg,2));
        m_port.async_read_some(boost::asio::buffer(mReadMsg,512),
                           boost::bind(&Dynamixel::handler,
                                       this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred) );
    /*for(int i=0; i< 512; i++)
        std::cout<<(unsigned short)mReadMsg[i]<<" ";
    std::cout<<std::endl;*/
}

void Dynamixel::handler(const boost::system::error_code& error, size_t bytes_transferred)
{
    
    for(int i=0; i< 512; i++)
        std::cout<<mReadMsg[i]<<" ";
    std::cout<<std::endl;
    
    readSome();
    
}

void Dynamixel::writeSome(){

    //unsigned char buffer[]={255,255,3,4,3,25,1,219};   //good one
    //unsigned char buffer[]={255,255,3,5,3,30,2,0,212};
    //char a;
    //std::vector<unsigned char>* buffer;
    //unsigned char * tab = &buffer->at(0);
    //buffer = constructPacket(3, 30, 1023);
    
    /*for(int i = 0;i< buffer->size();i++)
    {
        std::cout<<tab[i]<<std::endl;
    }
    */
    //m_port.write_some(boost::asio::buffer(&(*buffer)[0],buffer->size()));

}

std::vector<unsigned char>* Dynamixel::constructPacket(unsigned char ID, unsigned char Address, unsigned char Instruction, int Value)
{
    std::vector<unsigned char>* bufVec = new std::vector<unsigned char>();
    unsigned char L_Value;
    unsigned char H_Value;
    unsigned char Lenght = 5;
    unsigned char CheckSum = 0;
    
    bufVec->push_back(255);
    bufVec->push_back(255);
    bufVec->push_back(ID);
    

    L_Value = (Value >> (0 * 8)) & 0xFF;
    H_Value = (Value >> (1 * 8)) & 0xFF;
    
    
    CheckSum = 255-( ID+Lenght+Instruction+Address+L_Value+H_Value);
    
    bufVec->push_back(Lenght);
    bufVec->push_back(Instruction);
    bufVec->push_back((unsigned char)Address);
    bufVec->push_back(L_Value);
    bufVec->push_back(H_Value);
    bufVec->push_back(CheckSum);
    
    return bufVec;

}

void Dynamixel::sendPacket(std::vector<unsigned char>* Packet)
{
    if(m_port.is_open())
    {
        m_port.write_some(boost::asio::buffer(&(*Packet)[0],Packet->size()));
    }
    else
    {
        std::cout<<"connection closed !"<<std::endl;
    }
}

void Dynamixel::moveToPosition(unsigned char ID,int Pos)
{
    std::vector<unsigned char>* PacketToSend;
    
    PacketToSend = constructPacket(ID,30,INSTRUCTIONS::WRITE,Pos);
    
    sendPacket(PacketToSend);
    
}

Dynamixel::~Dynamixel()
{
    m_port.close();
}


