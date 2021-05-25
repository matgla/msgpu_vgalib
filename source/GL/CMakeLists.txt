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

add_library(msgpu_libgl)

target_sources(msgpu_libgl 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl/GL/gl.h
        ${PROJECT_SOURCE_DIR}/include/libgl/GL/glu.h
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/gl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/glu.cpp
)

add_library(msgpu_libglut)

target_sources(msgpu_libglut 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl/GL/glut.h
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/glut.cpp
)

target_include_directories(msgpu_libglut SYSTEM BEFORE 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl
)


add_library(msgpu_libglew)

target_sources(msgpu_libglew
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl/GL/glew.h
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/glew.cpp
)

target_include_directories(msgpu_libglew SYSTEM BEFORE 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl
)


target_include_directories(msgpu_libgl SYSTEM BEFORE 
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include/libgl
)

find_package(eul REQUIRED)

target_link_libraries(msgpu_libgl 
    PRIVATE 
        msgpu_messages
        eul_crc
)

target_link_libraries(msgpu_libglew
    PRIVATE 
        msgpu_messages
        eul_crc
)

target_link_libraries(msgpu_libglut 
    PRIVATE 
        msgpu_messages
        eul_crc
)
