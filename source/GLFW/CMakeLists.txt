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

add_library(msgpu_glfw)

target_sources(msgpu_glfw
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl/GLFW/glfw3.h
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw_io.cpp
)

target_include_directories(msgpu_glfw SYSTEM BEFORE 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/source/GL
)

target_link_libraries(msgpu_glfw
    PRIVATE 
        msgpu_messages
        eul_crc
)


