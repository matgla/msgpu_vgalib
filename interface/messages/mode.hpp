 
// ********************************
// * FILE AUTOMATICALLY GENERATED *
// ********************************
// This file is part of msgpu project.
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

#include <cstdint>


enum Mode : uint32_t
{
    Text = 0,
    Graphic = 1
};
 
struct __attribute__((packed, aligned(1))) ModeInfo
{
    uint8_t uses_color_palette : 1;
    uint8_t mode : 1;
    uint8_t used : 1;
    uint8_t id : 5;
    uint16_t resolution_width;
    uint16_t resolution_height;
    uint16_t color_depth;
};
