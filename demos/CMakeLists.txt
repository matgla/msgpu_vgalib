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

add_library(common_shaders)

target_sources(common_shaders
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/load_shaders.hpp 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/load_shaders.cpp
)

target_include_directories(common_shaders
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if (NOT USE_REAL_GL)

target_link_libraries(common_shaders
    PUBLIC 
        msgpu_libgl
        msgpu_libglew
        msgpu_glfw
)

target_compile_definitions(common_shaders
    PUBLIC 
        -DCOMPILED_SHADER
)

endif()

add_subdirectory (colored_triangle)
add_subdirectory (cube)
add_subdirectory (tutorial)

