//
//  SerialHandler.cpp
//  MoOS
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#include "SerialHandler.h"


using namespace boost;
using namespace capture;
SerialHandler::SerialHandler(Grid* g, const char *dev_name, int baudrate): m_io(), m_port(m_io, dev_name){
    mGrid = g;
    /*
     port.set_option( boost::asio::serial_port_base::parity() );	// default none
     port.set_option( boost::asio::serial_port_base::character_size( 8 ) );
     port.set_option( boost::asio::serial_port_base::stop_bits() );	// default one
     port.set_option( boost::asio::serial_port_base::baud_rate( baud_rate ) );
     */
    boost::asio::serial_port_base::baud_rate baud_option(baudrate);
    m_port.set_option(baud_option);
    mReadMsg.tab = new char[512];
    mProcessings.push_back(new SerialToucheProcessing(g));
    //mReadMsg.tab[512];
    read_some();
    // run the IO service as a separate thread, so the main thread can do others
    boost::thread t(boost::bind(&boost::asio::io_service::run, &m_io));
}


void SerialHandler::handler(const boost::system::error_code& error, size_t bytes_transferred)
{

    mReadMsg.size=bytes_transferred;
    std::vector<Processings*>::iterator i = mProcessings.begin();
    for (i= mProcessings.begin(); i!=mProcessings.end();i++ ) {
        (*i)->process(&mReadMsg);
    }
    read_some();

}

void SerialHandler::read_some()
{
    m_port.async_read_some(boost::asio::buffer(mReadMsg.tab,512),
                           boost::bind(&SerialHandler::handler,
                                       this,
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred) );

}



void SerialHandler::init(){

}


