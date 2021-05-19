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

    write(io_id, &header, sizeof(Header));
    uint8_t buffer[64];
   
    std::memset(buffer, 0, sizeof(buffer));
    write(io_id, buffer, 3);
    std::memcpy(buffer, &msg, sizeof(T));
    write(io_id, buffer, sizeof(buffer));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Sent!" << std::endl;
}

