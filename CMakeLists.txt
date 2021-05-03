# This file is part of msgpu_vgalib project. This is simple OS for embedded development devices.
# Copyright (C) 2021 Mateusz Stadnik
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.20)

project (msgpu_vgalib C CXX) 

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(source)
add_subdirectory(interface)
add_subdirectory(demos)

add_executable(msgpu_test)

target_sources(msgpu_test 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
)

target_link_libraries(msgpu_test 
    PRIVATE 
        msgpu_vgalib
)

