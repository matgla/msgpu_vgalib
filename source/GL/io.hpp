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
#include <cstring>

#include <eul/crc/crc.hpp>


template <typename T>
void write_msg(T& msg, std::size_t size = 0)
{
    Header header;
    header.id = T::id;

    uint8_t buffer[8];
    std::memset(buffer, 0, sizeof(buffer));
//    std::memcpy(buffer, &header, sizeof(Header));
//    std::memcpy(buffer + 4, &msg, sizeof(T));
    buffer[0] = 1;
    buffer[1] = 2;
    buffer[2] = 3; 
    buffer[3] = 4;
    buffer[4] = 5;
    buffer[5] = 6; 
    buffer[6] = 7; 
    buffer[7] = 8;
    std::cout << std::endl;
    for (const auto b : buffer)
    {
        std::cout << std::hex << int(b) << ",";
    }
    std::cout << std::endl;
    write(io_id, &buffer[0], sizeof(buffer));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Sent!" << std::endl;
}

