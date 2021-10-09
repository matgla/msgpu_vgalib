# This file is part of msgpu_vgalib project.
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

add_executable (tutorial_cube)

target_sources (tutorial_cube
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/cube.cpp 
)

if (USE_REAL_GL)
    target_link_libraries(tutorial_cube
        PRIVATE 
            common_shaders
            GL 
            GLU 
            GLEW 
            glfw 
    )

    target_compile_definitions(tutorial_cube
        PRIVATE 
            -DVERTEX_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader.glsl"
            -DFRAGMENT_SHADER_PATH="${CMAKE_CURRENT_SOURCE_DIR}/fragment_shader.glsl" 
    )
else ()
    target_link_libraries(tutorial_cube
        PRIVATE 
            common_shaders
            msgpu_libgl
            msgpu_libglew
            msgpu_glfw
    )
    
    add_library (cube_vertex_shader SHARED)
    
    target_sources(cube_vertex_shader 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader.cpp
    )
    
    target_link_libraries(cube_vertex_shader 
        PRIVATE 
            msgpu::interface::shader
    )
    
    
    add_library (cube_fragment_shader SHARED)
    
    target_sources(cube_fragment_shader 
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/fragment_shader.cpp
    )
    
    target_link_libraries(cube_fragment_shader 
        PRIVATE 
            msgpu::interface::shader
    )
    
    
    target_compile_options(tutorial_cube
        PRIVATE 
            -DCOMPILED_SHADER 
            -DVERTEX_SHADER_PATH=\"$<TARGET_FILE:cube_vertex_shader>\"
            -DFRAGMENT_SHADER_PATH=\"$<TARGET_FILE:cube_fragment_shader>\"
    )

endif()