// This file is part of msgpu_vgalib project.
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

#include "vga.h"

#include <unistd.h>
#include <fcntl.h>

#include <iostream> 

#include "messages/header.hpp"

#include "messages/change_mode.hpp"
#include "messages/draw_line.hpp"
#include "messages/set_pixel.hpp"
#include "messages/clear_screen.hpp"

static int io_id;
static int color;

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

    write(io_id, &header, sizeof(Header));
    write(io_id, &msg, header.size);
}

int vga_init()
{
    io_id = open("/tmp/msgpu_virtual_serial_1", O_RDWR);
    return 0;
}

int vga_clear() 
{
    ClearScreen msg;
    write_msg(msg);
    return 0;
}

int vga_setmode(int mode) 
{
    uint8_t new_mode = 0;
    switch (mode) 
    {
        case TEXT: new_mode = 0; break;
        case G320x240x4K: new_mode = 12; break;
    }

    ChangeMode msg {
        .mode = new_mode
    };

    std::cout << "Changing mode to: " << static_cast<int>(new_mode) << std::endl;
    write_msg(msg);
    return 0;
}

int vga_setcolor(int color)
{
    ::color = color;
    return 0;
}

int vga_drawpixel(int x, int y)
{
    SetPixel set = {
        .x = static_cast<uint16_t>(x),
        .y = static_cast<uint16_t>(y),
        .color = static_cast<uint16_t>(::color)
    };

    write_msg(set);
    return 0;
}

int vga_drawline(int x1, int y1, int x2, int y2)
{
    DrawLine msg = {
        .x1 = x1,
        .y1 = y1, 
        .x2 = x2, 
        .y2 = y2 
    };

    write_msg(msg);
}

