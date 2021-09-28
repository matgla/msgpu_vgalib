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

add_executable (tutorial_triangle)

target_sources (tutorial_triangle 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp 
)

target_link_libraries(tutorial_triangle
    PRIVATE 
        msgpu_libgl
        msgpu_libglew
        msgpu_glfw
)

add_library (vertex_shader SHARED)

target_sources(vertex_shader 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader.cpp
)

target_compile_options(vertex_shader PRIVATE -include "${CMAKE_CURRENT_SOURCE_DIR}/test.h")

target_compile_options(tutorial_triangle 
    PRIVATE 
        -DCOMPILED_SHADER 
        -DVERTEX_SHADER_PATH=\"$<TARGET_FILE:vertex_shader>\"
)
