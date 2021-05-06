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

#include <unistd.h>
#include <thread>
#include <chrono>

extern int io_id;

template <typename T>
void write_msg(T& msg, std::size_t size = 0)
{
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

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    write(io_id, &header, sizeof(Header));
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    write(io_id, &msg, header.size);
}


