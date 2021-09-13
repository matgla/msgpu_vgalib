// This file is part of msgpu_libgl project.
// Copyright (C) 2021 Mateusz Stadnik
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.  
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
#include <cstring>

#include <eul/crc/crc.hpp>


template <typename T>
void write_msg(int io_id, T& msg, std::size_t size = 0)
{
    Header header;
    header.id = T::id;

    uint8_t buffer[128];
    Header h;
    h.id = T::id; 
    h.size = sizeof(T);

    std::memset(buffer, 0, sizeof(buffer));
    std::memcpy(buffer, &h, sizeof(h));
    uint16_t header_crc = calculate_crc16(std::span<const uint8_t>(buffer, sizeof(Header)));
 
    uint8_t* next_pos = buffer + sizeof(h);
    std::memcpy(buffer + sizeof(h), &header_crc, sizeof(header_crc));
    next_pos += sizeof(header_crc);
    std::memcpy(next_pos, &msg, sizeof(T));
    uint16_t message_crc = calculate_crc16(std::span<const uint8_t>(next_pos, sizeof(T)));
    next_pos += sizeof(T);
    std::memcpy(next_pos, &message_crc, sizeof(message_crc));
    
    std::span<const uint8_t> data(buffer, sizeof(Header) + sizeof(T) + 2 * sizeof(uint16_t));

    std::cout << "Dump: {";
    for (const auto b : data) 
    {
        std::cout << std::hex << "0x" << static_cast<int>(b) << ",";
    }
    std::cout << std::endl;
 
    constexpr uint8_t start_flag = 0x7e;
    write(io_id, &start_flag, sizeof(start_flag));
    write(io_id, data.data(), data.size()); 
    std::cout << "Sent!" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

}

