//
//  SerialHandler.h
//  MoOS
//
//  Created by Ludovic Laffineur on 21/03/14.
//  Copyright (c) 2014 Ludovic Laffineur. All rights reserved.
//

#ifndef __MoOS__SerialHandler__
#define __MoOS__SerialHandler__

#include <iostream>
#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>
#include <unistd.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "Grid.h"
#include "CaptureDevice.h"
#include "SerialToucheProcessing.h"

namespace capture{
        class SerialHandler : public CaptureDevice{
        public:
            void init();
            SerialHandler(Grid* g, const char *dev_name, int baudrate);
            //void read_some();


        private:
            boost::asio::io_service m_io;
            boost::asio::serial_port m_port;
            //char read_msg_[512];
            size_char_tab mReadMsg;
            void handler(  const boost::system::error_code& error, size_t bytes_transferred);
            void read_some();
            u_int8_t receivedCommand [8];
            int serialCount =0;
        };
}



#endif /* defined(__MoOS__SerialHandler__) */
