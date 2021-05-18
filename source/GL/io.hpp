// This file is part of msgpu_libgl project.
// Copyright (C) 2021 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once 

#include "messages/header.hpp"
#include "messages/ack.hpp"

#include <unistd.h>
#include <thread>
#include <iostream>
#include <chrono>

#include <eul/crc/crc.hpp>

extern int io_id;

template <typename T>
void write_msg(T& msg, std::size_t size = 0)
{
  //  system("clear");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    auto start = std::chrono::high_resolution_clock::now();
    Header header;
    header.id = T::id;

    if (size != 0)
    {
        header.size = size;
    }
    else 
    {
        header.size = sizeof(T);
    }

    header.crc = calculate_crc8(std::span<const uint8_t>(reinterpret_cast<const uint8_t*>(&header), 3));
    bool send_successful = false;
    while (!send_successful)
    {
        write(io_id, &header, sizeof(Header));
        
        write(io_id, &msg, header.size);
        uint8_t msg_crc = 
            calculate_crc8(std::span<const uint8_t>(
                reinterpret_cast<const uint8_t*>(&msg), 
                sizeof(msg)
            )
        );
        write(io_id, &msg_crc, sizeof(msg_crc));
        auto sent_time = std::chrono::high_resolution_clock::now();
        //std::cout << "Sending took " << std::dec << std::chrono::duration_cast<std::chrono::microseconds>(sent_time - start).count() << " us." << std::endl;
        // wait for ACK 

        Header resp;
        
        read(io_id, &resp, sizeof(Header));
        auto f = std::chrono::high_resolution_clock::now() - sent_time;
        //std::cout << "First read" << std::dec << std::chrono::duration_cast<std::chrono::microseconds>(f).count() << " us." << std::endl;
        
       uint8_t crc;
        uint8_t buf[255];
        read(io_id, &crc, sizeof(crc));
        read(io_id, buf, resp.size); 
    
        auto ack_got = std::chrono::high_resolution_clock::now() - sent_time;
        //std::cout << "Resp come time: " << std::chrono::duration_cast<std::chrono::microseconds>(ack_got).count() << std::endl;
        static int resend = 0;
        //std::cout << "count: " << resend << std::endl;
        //std::cout << "Resend: ";
        std::cout << static_cast<int>(resp.id) << std::endl;
        if (resp.id == Ack::id)
        {
            std::cout << "Got ack" << std::endl;
         //   std::cout << "false" << std::endl;
            return;
        }
        std::cout << "Got nack" << std::endl;
    
        resend++;
       // std::cout << "true" << std::endl;
    }
}

