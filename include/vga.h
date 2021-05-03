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

#pragma once

#ifdef __cplusplus 
extern "C" 
{
#endif // __cplusplus

#define TEXT 0
#define G320x240x4K 1
#define __GLASTMODE G320x240x4K

int vga_init();

int vga_clear();

int vga_setmode(int mode);
int vga_setcolor(int color);
int vga_drawpixel(int x, int y);
int vga_drawline(int x1, int y1, int x2, int y2);

#ifdef __cplusplus 
}
#endif // __cplusplus

