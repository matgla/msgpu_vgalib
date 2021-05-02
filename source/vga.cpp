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

static int io_id;

template <typename T>
void write_msg(T& msg)
{
    
}

int vga_init()
{
    io_id = open("/tmp/msgpu_virtual_serial_1", O_RDWR);
    return 0;
}

int vga_setmode(int mode) 
{
    
    return 0;
}

int vga_setcolor(int color)
{
    return 0;
}

int vga_drawpixel(int x, int y)
{
    return 0;
}

